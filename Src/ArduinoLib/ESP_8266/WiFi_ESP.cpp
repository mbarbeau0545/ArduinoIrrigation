/*********************************************************************
 * @file        WiFi_ESP8266.h
 * @brief       Template_BriefDescription.
 * @details     TemplateDetailsDescription.\n
 *
 * @author      AUDMBA
 * @date        jj/mm/yyyy
 * @version     1.0
 *********************************************************************/

// ********************************************************************
// *                      Includes
// ********************************************************************
#include "WiFi_ESP.h"
#include "Wifi_ESP8266_Cmd.h"



// ********************************************************************
// *                      Defines
// ********************************************************************
#define ESP_EXPECT_OK               "OK"
#define ESP_EXPECT_ERROR            "ERROR"
#define ESP_EXPECT_WIFI_CONNECTED "WIFI CONNECTED"
#define ESP_EXPECT_BUSY           "busy"

#define ESP_TIMEOUT_WIFI (t_uint16)5000
#define ESP_TIMEOUT_READ (t_uint8)50
// ********************************************************************
// *                      Types
// ********************************************************************

// ********************************************************************
// *                      Prototypes
// ********************************************************************
    
// ********************************************************************
// *                      Variables
// *******************************************************************

t_bool g_ESP_ModemCom_Initialized_b = false;

t_sESP_Cfg g_ESP8266_Info_s = {
        .WifiCfg_s = {
        .WifiMode_e = ESP_WIFI_MODE_UNDEFINED,
        .WifiStatus_e = ESP_WIFI_STATUS_DISCONNECTED,
    },
        .ConnectType_e = ESP_CONNECTION_UNKNOWN,                                             //All disable
    };
const char *c_WifiCmd_uac[ESP_WIFI_MODE_NB] = {
    CMD_WRITE(_CWMODE)"1",                                                                    //ESP_WIFI_MODE_STATION = 0,
    CMD_WRITE(_CWMODE)"2",                                                                    //ESP_WIFI_MODE_AP,
    CMD_WRITE(_CWMODE)"3",                                                                    //ESP_WIFI_MODE_BOTH,
};
const char * c_ConnectionCmd_uac[ESP_CONNECTION_NB] = {
    CMD_WRITE(_CIPSTART)"\"TCP\"",                                                            //ESP_CONNECTION_TCP_CLIENT = 0,
    CMD_WRITE(_CIPSTART)"\"TCP\"",                                                            //ESP_CONNECTION_TCP_SERVER,
    CMD_WRITE(_CIPSTART)"\"UDP\"",                                                            //ESP_CONNECTION_UDP,
    CMD_WRITE(_CIPSTART)"\"SSL\"",                                                            //ESP_CONNECTION_SSL, 
                                                    
};
//********************************************************************************
//                      Local functions - Prototypes
//********************************************************************************
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
static t_eReturnCode s_ESP_MakeCommand(const char *f_command_pac, const char * f_answerExpected_pac, t_uint16 timeOutMs_u16);
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
static t_eReturnCode s_ESP_MakeCommand_WithResponse(const char *f_command_pac, const char * f_answer_pac);
//******************************************************************************** 
//                      Public functions - Implementation
//********************************************************************************
/**********************
* ESP_Init
***********************/
 t_eReturnCode ESP_Init(t_uint32 f_baudrate_u32, t_uint8 f_rxPin_u8, t_uint8 f_txPin_u8)
 {
    t_eReturnCode Ret_e = RC_OK;
    Ret_e = Modem_InitCom(f_baudrate_u32,f_rxPin_u8,f_txPin_u8);
    if(Ret_e == RC_OK)
    {
        #if !defined(SERIAL_ESP_DEBUG)
        Ret_e = s_ESP_MakeCommand("AT\r\n", ESP_EXPECT_OK, ESP_TIMEOUT_READ);
        #endif // SERIAL_ESP_DEBUG
        if(Ret_e == RC_OK)
        {
            g_ESP_ModemCom_Initialized_b = (t_bool)true;
        }
        
    }
    else if(Ret_e != RC_OK)
    {
        Ret_e = RC_ERROR_MODULE_NOT_INITIALIZED;
        g_ESP_ModemCom_Initialized_b = (t_bool)false;
    }
    DEBUG_PRINT("ESP_Init retval : ");
    DEBUG_PRINTLN(Ret_e);
    return Ret_e;
 }
/**********************
* ESP_ConnectWifi
***********************/
t_eReturnCode ESP_ConnectWifi(const char *f_SSID_pc, const char *f_password_pc)
{
    t_eReturnCode Ret_e = RC_OK;
    String ESPCmd_str;
    if(f_SSID_pc == (const char *)NULL || f_password_pc == (const char *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(g_ESP_ModemCom_Initialized_b != (t_bool)true)
    {
        Ret_e = RC_ERROR_MODULE_NOT_INITIALIZED;
    }
    if(Ret_e == RC_OK)
    {
        //check connection
        //Test connection if not connected, make connection
        Ret_e = s_ESP_MakeCommand(CMD_READ(_CWJAP), f_SSID_pc,(t_uint16)ESP_TIMEOUT_READ);
        if(Ret_e == RC_OK)
        {//if element find means wifi already connected 

            g_ESP8266_Info_s.WifiCfg_s.WifiStatus_e =  ESP_WIFI_STATUS_CONNECTED;
        }
        else 
        {//make connection to wifi
            ESPCmd_str = String(CMD_WRITE(_CWJAP_DEF))+ String("\"") + String(f_SSID_pc) + "\",\"" + String(f_password_pc) + "\"\r\n";
            Ret_e = s_ESP_MakeCommand(ESPCmd_str.c_str(),ESP_EXPECT_WIFI_CONNECTED,ESP_TIMEOUT_WIFI);
            if(Ret_e == RC_WARNING_WRONG_RESULT || Ret_e == RC_ERROR_LIMIT_REACHED)
            {
                Ret_e = RC_ERROR_WRONG_RESULT;
                g_ESP8266_Info_s.WifiCfg_s.WifiStatus_e =  ESP_WIFI_STATUS_DISCONNECTED;
            }
            else if(Ret_e == RC_OK)
            {//Ret_e == RC_OK
                g_ESP8266_Info_s.WifiCfg_s.WifiStatus_e =  ESP_WIFI_STATUS_CONNECTED;
            }
        }                
    }
    DEBUG_PRINT("ESP_ConnectWifi Retval :");
    DEBUG_PRINT(Ret_e);
    return Ret_e;
}
/**********************
* ESP_DisConnectWifi
***********************/
t_eReturnCode ESP_DisConnectWifi(void)
{
    t_eReturnCode Ret_e = RC_OK;
    //make disconnection
    if(g_ESP_ModemCom_Initialized_b != (t_bool)true)
    {
        Ret_e = RC_ERROR_MODULE_NOT_INITIALIZED;
    }
    if(Ret_e == RC_OK)
    {    
        Ret_e = s_ESP_MakeCommand(CMD(_CWQAP), ESP_EXPECT_OK, (t_uint16)150);
        if(Ret_e == RC_OK)
        {
            g_ESP8266_Info_s.WifiCfg_s.WifiStatus_e = ESP_WIFI_STATUS_DISCONNECTED;
        }
        else 
        {
            Ret_e = RC_ERROR_WRONG_RESULT;
        }
    }
    return Ret_e;
}
/**********************
* ESP_Cfg
***********************/
t_eReturnCode ESP_Cfg(t_eESP_WifiMode f_WifiMode_e, t_eESP_TCPState f_TCPState_e, const char* f_IP_address_pc, t_uint16 f_port_u16)
{
    t_eReturnCode Ret_e = RC_OK;
    if(g_ESP_ModemCom_Initialized_b != (t_bool)false)
    {
        Ret_e = RC_ERROR_MODULE_NOT_INITIALIZED;
    }
    if(f_WifiMode_e > ESP_WIFI_MODE_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(Ret_e == RC_OK)
    {
        switch (f_WifiMode_e)
        {
            case ESP_WIFI_MODE_STATION:
            {
                break;
            }
            case ESP_WIFI_MODE_AP:
            {
                break;
            }
            case ESP_WIFI_MODE_BOTH:
            {
                break;
            }           
            default:
            {
                Ret_e = RC_WARNING_NO_OPERATION;
                break;
            }
        }
        
    }
    DEBUG_PRINT("ESP_Cfg retval : ");
    DEBUG_PRINTLN(Ret_e);
    return Ret_e;
}
/**********************
* ESP_GetCfg
***********************/
t_eReturnCode ESP_GetCfg(t_sESP_Cfg *f_ESP_Config_e)
{
    t_eReturnCode Ret_e = RC_OK;
    if(f_ESP_Config_e == (t_sESP_Cfg *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        *f_ESP_Config_e = g_ESP8266_Info_s;
    }
    DEBUG_PRINT("ESP_GetCfg retval : ");
    DEBUG_PRINTLN(Ret_e);
    return Ret_e;
}
/***********************
* ESP_GetFirmwareVersion
************************/
t_eReturnCode ESP_GetFirmwareVersion(const char *f_firmwareVersion_pc)
{
    t_eReturnCode Ret_e = RC_OK;
    if(f_firmwareVersion_pc == (const char *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        Ret_e = s_ESP_MakeCommand_WithResponse(CMD(_GMR),f_firmwareVersion_pc);
    }
    DEBUG_PRINT("ESP_GetFirmwareVersion retval : ");
    DEBUG_PRINTLN(Ret_e);
    return Ret_e;
}
//********************************************************************************
//                      Local functions - Implementation
//********************************************************************************
/***********************
* s_ESP_MakeCommand
***********************/
static t_eReturnCode s_ESP_MakeCommand(const char *f_command_pac, const char * f_answerExpected_pac, t_uint16 timeOutMs_u16)
{
    t_eReturnCode Ret_e = RC_OK;
    t_uint8 LI_u8;
    t_uint8 maxTryWrite_u8 = ESP_WL_MAX_ATTEMPT_CONNECTION;
    char response_ac[MODEM_MAX_BUFF_SIZE];
    char * answerExepctedFind_pc = (char*)NULL;
    if(f_command_pac == (const char*)NULL || f_answerExpected_pac == (const char*)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        for(LI_u8 = 0 ; LI_u8 < maxTryWrite_u8 ; LI_u8++)
        {
            Ret_e = Modem_Write(f_command_pac);
            delay(timeOutMs_u16);
            if(Ret_e == RC_OK)
            {   
                Ret_e = Modem_ReadBuffer(response_ac);
                //see if ESP answer is corresponding with what expected
                if(Ret_e == RC_OK)
                {
                    //if "busy" in response_ac go read the rest of the buffer 'cause ESP did not finished is previous task                  
                    answerExepctedFind_pc = strstr(response_ac, ESP_EXPECT_BUSY);
                    if(answerExepctedFind_pc != (char *)NULL)
                    {
                        //Serial.println("Waiting");
                        
                        Ret_e = Modem_ReadBuffer(response_ac);
                    }
                    Serial.println(response_ac);
                    if(Ret_e == RC_OK)
                    {
                        answerExepctedFind_pc = (char * )NULL;
                        answerExepctedFind_pc = strstr(response_ac, f_answerExpected_pac);
                        if(answerExepctedFind_pc != (char *)NULL)
                        {
                            Ret_e = RC_OK;
                            break;
                        }
                        else 
                        {
                            Ret_e = RC_WARNING_WRONG_RESULT;
                        }     
                    }                        
                }        
            }            
        }
        
        if(LI_u8 >= maxTryWrite_u8)
        {
          Ret_e = RC_ERROR_LIMIT_REACHED;
        }
    }
    DEBUG_PRINT("s_ESP_MakeCommand RetVal:");
    DEBUG_PRINTLN(Ret_e);
    return Ret_e;
}
/********************************
* s_ESP_MakeCommand_WithResponse
********************************/    
static t_eReturnCode s_ESP_MakeCommand_WithResponse(const char *f_command_pac, const char * f_answer_pac)
{
    t_eReturnCode Ret_e = RC_OK;
    char response_ac[MODEM_MAX_BUFF_SIZE];
    char * answerExepctedFind_pc = (char*)NULL;
    char *checkstrcpy = (char *)NULL;
    if(f_command_pac == (const char*)NULL ||f_answer_pac == (const char *)NULL )
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        Ret_e = Modem_Write(f_command_pac);
        if(Ret_e == RC_OK)
        {
            Ret_e = Modem_ReadBuffer(response_ac);
            //see if ESP answer is corresponding with what expected
            if(Ret_e == RC_OK)
            {
                //if "busy" in response_ac go read the rest of the buffer 'cause ESP did not finished is previous task                  
                answerExepctedFind_pc = strstr(response_ac, ESP_EXPECT_BUSY);
                if(answerExepctedFind_pc != (char *)NULL)
                {
                    //Serial.println("Waiting");
                    
                    Ret_e = Modem_ReadBuffer(response_ac);
                }
                //Serial.println(response_ac);
                else
                {
                    checkstrcpy = strcpy((char *)f_answer_pac, (const char *)response_ac);
                    if ((char *)checkstrcpy != (char *)f_answer_pac) 
                    {
                        Ret_e = RC_ERROR_COPY_FAILED;
                    }
                    else
                    {
                        Ret_e = RC_OK;
                    }                       
                }                        
            }        
        }         
    }
    DEBUG_PRINT("s_ESP_MakeCommand_WithResponse RetVal:");
    DEBUG_PRINTLN(Ret_e);
    return Ret_e;
}   
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
