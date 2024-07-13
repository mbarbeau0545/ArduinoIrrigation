/*********************************************************************
 * @file        Moedem_esp.cpp
 * @brief       Modulation-Demodulation between Arduino and ESP8266.
 * @details     In order to make command on ESP8266 we have to make serial 
 *              protocol communication.\n
 *
 * @author      AUDMBA
 * @date        31/03/2024
 * @version     1.0
 *********************************************************************/

// ********************************************************************
// *                      Includes
// ********************************************************************
#include "Modem.h"
#include "./ConfigSpecific/HAL/Arduino_CfgSpec.h"
#include <SoftwareSerial.h>
#include <stdio.h>

// ********************************************************************
// *                      Defines
// ********************************************************************
#define ESP8266_END_MARKER_OK    "OK"
#define ESP8266_END_MARKER_ERR   "ERROR"
#define ESP8266_END_MARKER_SEND "SEND"
#define ESP8266_END_MARKER_BUSY "busy"

// ********************************************************************
// *                      Types
// ********************************************************************

// ********************************************************************
// *                      Prototypes
// ********************************************************************
    
// ********************************************************************
// *                      Variables
// ********************************************************************
t_bool g_Modem_Initialized_b = false;

SoftwareSerial * g_esp8266Serial_pcl;
//********************************************************************************
//                      Local functions - Prototypes
//********************************************************************************

//******************************************************************************** 
//                      Public functions - Implementation
//********************************************************************************
/**********************
* Modem_InitCom
***********************/
t_eReturnState Modem_InitCom(t_uint32 f_baudrate_u32, t_uint8 f_rxPin_u8, t_uint8 f_txPin_u8)
{
    t_eReturnState Ret_e = RC_OK;
    g_esp8266Serial_pcl = new SoftwareSerial(f_rxPin_u8, f_txPin_u8);
    g_esp8266Serial_pcl->begin(f_baudrate_u32);
    if(g_esp8266Serial_pcl == NULL)
    {
        Ret_e = RC_ERROR_MODULE_NOT_INITIALIZED;
        g_Modem_Initialized_b = (t_bool)false;
    }
    else
    {
        g_Modem_Initialized_b = (t_bool)true;
    }
    return Ret_e;
}
/**********************
* Modem_EndCom
***********************/
void Modem_EndCom(void)
{
    g_esp8266Serial_pcl->end();
    g_Modem_Initialized_b = (t_bool)false;
    delete g_esp8266Serial_pcl;
}
/**********************
* Modem_ReadBuffer
***********************/
t_eReturnState Modem_Write(const char *f_txbuffer_pc)
{
    t_eReturnState Ret_e = RC_OK;
    size_t SendBufferSize_ui;
    size_t BufferSizeToSend_ui;
    t_uint8 LI_u8;
    t_uint8 maxTryWrite_u8 = 10;
    if(f_txbuffer_pc == NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(g_Modem_Initialized_b != (t_bool)true)
    {
        Ret_e = RC_ERROR_MODULE_NOT_INITIALIZED;
    }
    if(Ret_e == RC_OK)
    {        
        g_esp8266Serial_pcl->flush(); // Vider le tampon de réception
        BufferSizeToSend_ui = strlen((char*)f_txbuffer_pc);
        for(LI_u8 = (t_uint8)0 ; LI_u8 < maxTryWrite_u8 ; LI_u8++)
        {
            SendBufferSize_ui = g_esp8266Serial_pcl->write((const t_uint8 *)f_txbuffer_pc, BufferSizeToSend_ui);
            if(BufferSizeToSend_ui != SendBufferSize_ui)
            {
                Ret_e = RC_ERROR_WRONG_RESULT;
            }
            else 
            {
                Ret_e = RC_OK;
                break;
            }
        }
        if(LI_u8 == maxTryWrite_u8)
        {
            Ret_e = RC_ERROR_LIMIT_REACHED;
        }
    }
    g_esp8266Serial_pcl->flush(); // Vider le tampon de réception
    return Ret_e;
}
/**********************
* Modem_ReadBuffer
***********************/
t_eReturnState Modem_ReadBuffer(char *f_rxBuffer_pc) {
    t_eReturnState Ret_e = RC_OK;
    t_uint8 rcvData_u8;
    t_uint8 LI_u8;
    unsigned char rcvData_c;
    t_uint8 idxResponse_u8 = 0;
    t_uint32 startTime_u32;
    if (f_rxBuffer_pc == (char *)NULL) {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if (g_Modem_Initialized_b != (t_bool)true) {
        Ret_e = RC_ERROR_MODULE_NOT_INITIALIZED;
    }
    if (Ret_e == RC_OK) {
        g_esp8266Serial_pcl->flush(); // Vider le tampon de réception
        startTime_u32 = millis();
        while ((g_esp8266Serial_pcl->available() > (int)0) && (millis() - startTime_u32 < MODEM_TIMEOUT)) 
        {
            if (idxResponse_u8 > (MODEM_MAX_BUFF_SIZE - 2)) 
            {
                break;
            } 
            else 
            {
                rcvData_u8 = (t_uint8)g_esp8266Serial_pcl->read();
                rcvData_c = (unsigned char)rcvData_u8;
                f_rxBuffer_pc[idxResponse_u8++] = rcvData_c;
                // Every 4 bytes, check for balise messages
                if (idxResponse_u8 % 4 == 0) {
                    f_rxBuffer_pc[idxResponse_u8] = '\0'; // Terminate the string before checking
                    if (strstr((const char*)f_rxBuffer_pc, ESP8266_END_MARKER_OK) != NULL
                        || strstr((const char*)f_rxBuffer_pc, ESP8266_END_MARKER_ERR) != NULL
                        || strstr((const char*)f_rxBuffer_pc, ESP8266_END_MARKER_SEND) != NULL) 
                        
                    {
                        //DEBUG_PRINTLN("Balise found");
                        //DEBUG_PRINTLN((const char*)f_rxBuffer_pc); // Print the response for diagnostic
                        break;
                    } 
                    if (strstr((const char*)f_rxBuffer_pc, ESP8266_END_MARKER_BUSY) != NULL) 
                    {
                        // Wait a bit, module is busy
                        delay(1000);
                    }
                }
            }
        }
        if (idxResponse_u8 > 0) 
        {
            f_rxBuffer_pc[idxResponse_u8] = '\0'; // Terminate the response string
            memset(f_rxBuffer_pc + idxResponse_u8, '\0', MODEM_MAX_BUFF_SIZE - idxResponse_u8);
            
        } 
        else 
        {
            Ret_e = RC_WARNING_NO_OPERATION;
        }
    }
    g_esp8266Serial_pcl->flush(); // Vider le tampon de réception
    return Ret_e;   
}
//********************************************************************************
//                      Local functions - Implementation
//********************************************************************************
//************************************************************************************
// End of File
//************************************************************************************
/**********************
* 
***********************/
/**
 *
 *	@brief
 *	@details
 *
 *
 *	@param[in] 
 *	@param[out]
 *	 
 *
 *
 */
