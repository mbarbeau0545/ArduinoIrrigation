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
#include <SoftwareSerial.h>
#include <stdio.h>
// ********************************************************************
// *                      Defines
// ********************************************************************
#define ESP8266_END_MARKER "\r\nOK\r\n"
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
t_eReturnCode Modem_InitCom(t_uint32 f_baudrate_u32, t_uint8 f_rxPin_u8, t_uint8 f_txPin_u8)
{
    t_eReturnCode Ret_e = RC_OK;
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
    DEBUG_PRINT("Modem_InitCom Retval :");
    DEBUG_PRINTLN(Ret_e);
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
    DEBUG_PRINTLN("Modem-EndCom done.");
}
/**********************
* Modem_ReadBuffer
***********************/
t_eReturnCode Modem_Write(const char *f_txbuffer_pc)
{
    t_eReturnCode Ret_e = RC_OK;
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
            //DEBUG_PRINT("Modem-Send to ESP : ");
            //DEBUG_PRINTLN(f_txbuffer_pc);
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
    DEBUG_PRINT("Modem_Write Retval :");
    DEBUG_PRINTLN(Ret_e);
    return Ret_e;
}
/**********************
* Modem_ReadBuffer
***********************/
/**********************
* Modem_ReadBuffer
***********************/
t_eReturnCode Modem_ReadBuffer(char *f_rxBuffer_pc) {
    t_eReturnCode Ret_e = RC_OK;
    char rcvData_c;
    char RcvResponse_ac[MODEM_MAX_BUFF_SIZE]; 
    t_uint8 idxResponse_u8 = 0;
    t_uint32 startTime_u32;
    char *checkmemcpy;
    
    if (f_rxBuffer_pc == (const char *)NULL) 
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if (g_Modem_Initialized_b != (t_bool)true) 
    {
        Ret_e = RC_ERROR_MODULE_NOT_INITIALIZED;
    }
    if (Ret_e == RC_OK) 
    {
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
                rcvData_c = (char)g_esp8266Serial_pcl->read();
                RcvResponse_ac[idxResponse_u8] = (char)rcvData_c;
                idxResponse_u8 += (t_uint8)1;
                //essaisResponse[index_u8++] = (char)rcvData_c;
                //rcvData_c = (char)' ';
                delay(5);
            }
        }
        //if Ret_e = RC_WARNING_NOT_ALLOWED, return something 
        if (idxResponse_u8 > (t_uint8)0) 
        {
            RcvResponse_ac[idxResponse_u8] = '\0';
            // Copie de la réponse dans le tampon de sortie
            checkmemcpy = strncpy((char *)f_rxBuffer_pc, (const char *)RcvResponse_ac, MODEM_MAX_BUFF_SIZE);
            if ((char *)checkmemcpy != (char *)f_rxBuffer_pc) 
            {
                Ret_e = RC_ERROR_COPY_FAILED;
            }
            else
            {// make sure t o terminate as normal
                f_rxBuffer_pc[MODEM_MAX_BUFF_SIZE - 1] = '\0';
            }
        }
        else
        {
            Ret_e = RC_WARNING_NO_OPERATION;
        }
    }
    g_esp8266Serial_pcl->flush(); // Vider le tampon de réception
    DEBUG_PRINT("Modem_ReadBuffer Retval :");
    DEBUG_PRINTLN(Ret_e);
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
