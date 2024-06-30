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
#include "ConfigSpecific/ArduinoCom/WiFiESP_CfgSpec.h"
#include "Wifi_ESP8266_Cmd.h"

#include <stdio.h>




// ********************************************************************
// *                      Defines
// ********************************************************************
#define ESP_EXPECT_AT               "AT"
#define ESP_EXPECT_OK               "OK"                            // Expected from ESP : "OK"
#define ESP_EXPECT_ERROR            "ERROR"                         // Expected from ESP : "ERROR"
#define ESP_EXPECT_CONNECT          "CONNECT"                       // Expected from ESP : "CONNECT"
#define ESP_EXPECT_DICONNECT        "DISCONNECT"                    // Expected from ESP : "DISCONNECT"
#define ESP_EXPECT_BUSY             "busy"                          // Expected from ESP : "busy"
#define ESP_EXPECT_DATA_SEND        "SEND OK"
#define ESP_EXCPECT_WIFI_CONNECT    "CWJAP:"
#define ESP_EXPECT_RCV_DATA         "IPD"
#define ESP_EXPECT_TCP_CONNECT      "3"
#define EXP_EXPECT_TCP_DISCONNECT   "2"

#define ESP_TIMEOUT_WRITE     (t_uint16)500                            //Time waiting from ESP doing the cmd 
#define ESP_TIMEOUT_READ      (t_uint16)350                               //Time waiting from ESP to send info
#define ESP_TIMEOUT_SEND      (t_uint16)100
#define ESP_TIMEOUT_RCV       (t_uint16)4000

#define ESP_CHECK_CONNECTION  10000U
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

t_sESP_ComStatus g_ESP8266_Info_s = {
        .WifiCfg_s = {
            .WifiMode_e     = ESP_WIFI_MODE_UNDEFINED,
            .WifiStatus_e   = ESP_WIFI_STATUS_DISCONNECTED,
        },
        .ConnectType_e  = ESP_CONNECTION_UNKNOWN,  
        .ConnectState_e = ESP_PROTOCOL_STATE_DISCONNECT,                                           //All disable
        .SleepMode_e    = ESP_SLEEP_UNKNOWN,
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
const char * c_sleepModeCmd_ac[ESP_SLEEPMODE_NB] = {
    CMD_WRITE(_SLEEP)"0",                                                                     //ESP_SLEEPMODE_DISABLE
    CMD_WRITE(_SLEEP)"1",                                                                     //ESP_SLEEPMODE_LIGHT
    CMD_WRITE(_SLEEP)"2",  
    CMD_WRITE(_GSLP),                                                              //ESP_SLEEPMODE_MODEM
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
static t_eReturnCode s_ESP_MakeCommand_WithResponse(const char *f_command_pac, const char * f_answerExpected_pac, t_uint16 timeOutMs_u16,const char * f_answer_pac);
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
static t_eReturnCode s_ESP_GetInfo_StateESP(void);
void printWithVisibleNewlines(const char* str);
void printWithVisibleNewlines(const char* str) {
    while (*str) {
        if (*str == '\n') {
            Serial.print("\\n");
        } else if (*str == '\r') {
            Serial.print("\\r");
        } else {
            Serial.print(*str);
        }
        str++;
    }
    Serial.println(); // Move to the next line after printing the entire string
}
//******************************************************************************** 
//                      Public functions - Implementation
//********************************************************************************
/**********************
* ESP_Init
***********************/
 t_eReturnCode ESP_Init(void)
 {
    t_eReturnCode Ret_e = RC_OK;
    t_uint32 baudRate_u32 = (t_uint32)c_ESPComProjectCfg_s.baudRate_u32;
    t_uint8  rxPin_u8     = (t_uint8)c_ESPComProjectCfg_s.rxPin_u8;
    t_uint8  txPin_u8     = (t_uint8)c_ESPComProjectCfg_s.txPin_u8;
    char ESP_InitCmd_ac[MODEM_MAX_BUFF_SIZE/8];
    Ret_e = Modem_InitCom(baudRate_u32, rxPin_u8, txPin_u8);
    if(Ret_e == RC_OK)
    {
        snprintf(ESP_InitCmd_ac, sizeof(ESP_InitCmd_ac), "%s\r\n", _AT);
        Ret_e = s_ESP_MakeCommand(ESP_InitCmd_ac, ESP_EXPECT_OK, ESP_TIMEOUT_READ);
        if(Ret_e == RC_OK)
        {
            g_ESP_ModemCom_Initialized_b = (t_bool)true;
        }        
    }
    if(Ret_e != RC_OK)
    {
        g_ESP_ModemCom_Initialized_b = (t_bool)false;
    }
    DEBUG_PRINT("ESP_Init retval : ");
    DEBUG_PRINTLN(Ret_e);
    return Ret_e;
 }
 /**********************
* ESP_Close
***********************/
 t_eReturnCode ESP_Close(void)
 {
    t_eReturnCode Ret_e = RC_OK;
    if(g_ESP_ModemCom_Initialized_b == (t_bool)true)
    {
        Modem_EndCom();
        g_ESP_ModemCom_Initialized_b = (t_bool)false;
        if(g_ESP8266_Info_s.WifiCfg_s.WifiStatus_e != ESP_WIFI_STATUS_DISCONNECTED)
        {
            Ret_e = ESP_DisConnectWifi();
            if(Ret_e == RC_OK)
            {
                g_ESP8266_Info_s.WifiCfg_s.WifiStatus_e = ESP_WIFI_STATUS_DISCONNECTED;
            }
        }
        if(g_ESP8266_Info_s.ConnectState_e != ESP_PROTOCOL_STATE_DISCONNECT)
        {
            Ret_e = ESP_Close_ProtocolCom();
            if(Ret_e == RC_OK)
            {
                g_ESP8266_Info_s.ConnectState_e = ESP_PROTOCOL_STATE_DISCONNECT;
            }
        }
    }
    return Ret_e;
 }
/**********************
* ESP_ConnectWifi
***********************/
t_eReturnCode ESP_ConnectWifi(const char *f_SSID_pc, const char *f_password_pc)
{
    t_eReturnCode Ret_e = RC_OK;
    String ESP_WifiModeCmd_str;
    String ESP_WifiCom_str;
    t_eESP_WifiMode WifiMode_e = c_ESPComProjectCfg_s.WifiMode_e;
    if(f_SSID_pc == (const char *)NULL || f_password_pc == (const char *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(g_ESP_ModemCom_Initialized_b != (t_bool)true)
    {
        Ret_e = RC_ERROR_MODULE_NOT_INITIALIZED;
    }
    if(WifiMode_e > ESP_WIFI_MODE_NB)
    {
        Ret_e = RC_ERROR_NOT_SUPPORTED;
    }
    if(Ret_e == RC_OK)
    {
        if(g_ESP8266_Info_s.WifiCfg_s.WifiMode_e != WifiMode_e)
        {
            
            ESP_WifiModeCmd_str = String(c_WifiCmd_uac[WifiMode_e]) + String("\r\n");
            Ret_e = s_ESP_MakeCommand(ESP_WifiModeCmd_str.c_str(),(const char *)"1", ESP_TIMEOUT_READ);
        } 
        if(Ret_e == RC_OK)
        {        
            g_ESP8266_Info_s.WifiCfg_s.WifiMode_e = (t_eESP_WifiMode)WifiMode_e;
            //make connection to wifi
            ESP_WifiCom_str = String((CMD_WRITE(_CWJAP_DEF)));
            ESP_WifiCom_str += "\"";
            ESP_WifiCom_str += f_SSID_pc;
            ESP_WifiCom_str += "\",\""  ;
            ESP_WifiCom_str += f_password_pc;
            ESP_WifiCom_str += "\"\r\n";
            //ESP_WifiCom_str = String()+ String("\"") + String(f_SSID_pc) + String("\",\"") + String(f_password_pc) + String("\"\r\n");
            Ret_e = s_ESP_MakeCommand(ESP_WifiCom_str.c_str(),ESP_EXPECT_CONNECT, ESP_TIMEOUT_RCV);
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
/*************************
* ESP_Start_ProtocolCom  
*************************/
t_eReturnCode ESP_Start_ProtocolCom(void)
{
    static t_uint32 actualTime_u32 = 0;
    t_eESP_ConnectionType ProtComType_e = c_ESPComProjectCfg_s.ProtComType_e;
    t_eReturnCode Ret_e = RC_OK;
    String Protocol_Cmd_str;
    const char * IP_Address_pc = c_ESPComProjectCfg_s.serverID_pac;
    t_uint8      serverPort_u8 = c_ESPComProjectCfg_s.serverPrt_u8;
    const char * wifiRouterName_pac; 
    const char * wifiPassWord_pac;
    if(g_ESP_ModemCom_Initialized_b != (t_bool)true)
    {
        Ret_e = RC_ERROR_MODULE_NOT_INITIALIZED;
    }
    if(ProtComType_e > ESP_CONNECTION_NB)
    {
        g_ESP8266_Info_s.ConnectType_e = ESP_CONNECTION_UNKNOWN;
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    // get info status
    if (((t_uint32)millis - actualTime_u32) > (t_uint32)ESP_CHECK_CONNECTION)
    {
        Serial.println("CheckCo every x sec");
        actualTime_u32 = (t_uint32)millis();
        Ret_e = s_ESP_GetInfo_StateESP();
    }  
    if(g_ESP8266_Info_s.WifiCfg_s.WifiStatus_e != ESP_WIFI_STATUS_CONNECTED)
    {//Wifi not Connected, make connection 
        wifiRouterName_pac = c_ESPComProjectCfg_s.LiveBoxName_pac;
        wifiPassWord_pac   = c_ESPComProjectCfg_s.password_pac;
        Ret_e = ESP_ConnectWifi((const char *)wifiRouterName_pac, (const char *)wifiPassWord_pac);
    }
    if(g_ESP8266_Info_s.ConnectState_e == ESP_PROTOCOL_STATE_CONNECTED)
    {// not execute the rest 'cause TCP com already on
        Ret_e = RC_WARNING_ALREADY_CONFIGURED;
    }
    if(Ret_e == RC_OK)
    {
        g_ESP8266_Info_s.ConnectType_e = ProtComType_e;
        Protocol_Cmd_str = c_ConnectionCmd_uac[ProtComType_e] + String(",\"") + String(IP_Address_pc) + String("\",") + String(serverPort_u8) + String("\r\n");
        //Serial.print("SendCmd : ");
        //Serial.println(Protocol_Cmd_str);
        Ret_e = s_ESP_MakeCommand(Protocol_Cmd_str.c_str(), ESP_EXPECT_CONNECT, ESP_TIMEOUT_RCV);
        //Serial.println(esp_reponse_pc);
        if(Ret_e == RC_OK)
        {            
            g_ESP8266_Info_s.ConnectState_e = ESP_PROTOCOL_STATE_CONNECTED;
        }
        else
        {
            g_ESP8266_Info_s.ConnectState_e = ESP_PROTOCOL_STATE_FAILED;
        }
    }
    if(Ret_e == RC_WARNING_ALREADY_CONFIGURED)
    {
        Ret_e = RC_OK;
    }
    DEBUG_PRINT("ESP_Cfg retval : ");
    DEBUG_PRINTLN(Ret_e);
    return Ret_e;
}
/*************************
* ESP_Close_ProtocolCom
**************************/
t_eReturnCode ESP_Close_ProtocolCom(void)
{
    t_eReturnCode Ret_e = RC_OK;
    if(g_ESP8266_Info_s.ConnectState_e != ESP_PROTOCOL_STATE_DISCONNECT)
    {
        Ret_e = s_ESP_MakeCommand(CMD(_CIPCLOSE),ESP_EXPECT_OK,ESP_TIMEOUT_READ);
    }
    if(Ret_e == RC_OK)
    {
        g_ESP8266_Info_s.ConnectState_e = ESP_PROTOCOL_STATE_DISCONNECT;
    }
    return Ret_e;
}
/******************************
* ESP_Send_DataWithProtocolCom
*******************************/
t_eReturnCode ESP_SendData_WithProtocolCom(const char * f_dataToSend_pc)
{
    t_eReturnCode Ret_e = RC_OK;
    t_eESP_ExchangeDataMode DataMode_e = c_ESPComProjectCfg_s.exchangeType_e;
    String dataESpCmd_str;
    String dataToSend_str = String(f_dataToSend_pc);
    t_uint16 lenghtData_u16;
    String ExpectRcvEsp_str;
    if(g_ESP_ModemCom_Initialized_b == (t_bool)false)
    {
        Ret_e = RC_ERROR_MODULE_NOT_INITIALIZED;
    }
    if(f_dataToSend_pc == (const char *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(g_ESP8266_Info_s.ConnectState_e != ESP_PROTOCOL_STATE_CONNECTED)
    {
        Ret_e = RC_WARNING_WRONG_CONFIG;
    }
    if(DataMode_e > ESP_EXCHANGE_DATA_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    //Datasheet say that you cannot  use ESP_SEND_DATA_BUFF in SSL connection 
    if(Ret_e == RC_OK)
    {
        lenghtData_u16 = dataToSend_str.length();
        switch(DataMode_e)
        {
            case ESP_EXCHANGE_DATA_SERIAL:
            {
                //Data sheet say first send Lenght and if esp Repond OK then send it DATA
                dataESpCmd_str = String(CMD_WRITE(_CIPSEND)) + String(lenghtData_u16) + String("\r\n");
                ExpectRcvEsp_str = String(lenghtData_u16);
                Ret_e = s_ESP_MakeCommand(dataESpCmd_str.c_str(), ExpectRcvEsp_str.c_str(), ESP_TIMEOUT_READ);
                if(Ret_e == RC_OK)
                {
                    Ret_e = s_ESP_MakeCommand(dataToSend_str.c_str(),ESP_EXPECT_DATA_SEND, ESP_TIMEOUT_READ);
                    //Verify data send correctly 
                }
                break;
            }
            case ESP_EXCHANGE_DATA_HEX:
            {
                break;
            }
            case ESP_EXCHANGE_DATA_BUFF:
            {
                //Datasheet says we cannot use ESP_SEND_DATA_BUFF when SSL is set
                if(g_ESP8266_Info_s.ConnectType_e == ESP_CONNECTION_SSL)
                {
                    Ret_e = RC_ERROR_NOT_ALLOWED;
                }
                else 
                {//do logic

                }
                
                break;
            }
            case ESP_EXCHANGE_DATA_NB:
            {
                break;
            }
            default:
            {
                Ret_e = RC_ERROR_WRONG_STATE;
                break;
            }
        }
    }
    DEBUG_PRINT("ESP_SendData_WithProtocolCom retval : ");
    DEBUG_PRINTLN(Ret_e);
    return Ret_e;
}
/******************************
* ESP_RcvData_WithProtocolCom
*******************************/
t_eReturnCode ESP_RcvData_WithProtocolCom(const char *f_RcvData_pc)
{
    t_eReturnCode Ret_e = RC_OK;
    //t_uint8 LI_u8;
    char * answerExepctedFind_pc = (char*)NULL;
    char * checkstrcpy = (char*)NULL;
    char espResponse_ac[MODEM_MAX_BUFF_SIZE];
    if(f_RcvData_pc == (const char *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(g_ESP8266_Info_s.ConnectState_e != ESP_PROTOCOL_STATE_CONNECTED)
    {
        Ret_e = RC_WARNING_WRONG_CONFIG;
    }
    if(Ret_e == RC_OK)
    {
        Ret_e = RC_WARNING_NO_OPERATION;
        // Used ReadBuffer function until there is something to read
        Ret_e = Modem_ReadBuffer(espResponse_ac);
        Serial.println(espResponse_ac);
        if(Ret_e == RC_OK)
        {
            answerExepctedFind_pc = strstr((const char *)espResponse_ac,(const char*)ESP_EXPECT_RCV_DATA);
            //Serial.println(espResponse_ac);
            if(answerExepctedFind_pc != (char *)NULL)
            {
                //Serial.println("Find IPD");
                checkstrcpy = strcpy((char *)f_RcvData_pc,(const char *)espResponse_ac);
                if(checkstrcpy != (char *)f_RcvData_pc)
                {
                    Ret_e = RC_ERROR_COPY_FAILED;
                }
                else 
                {
                    Ret_e = RC_OK;
                }
            }
            else
            {
                Ret_e = RC_ERROR_WRONG_RESULT;
            }
        }
    }
    DEBUG_PRINT("ESP_RcvData_WithProtocolCom retval : ");
    DEBUG_PRINTLN(Ret_e);
    return Ret_e;
}
/*************************
* ESP_Get_ProtocolCom_Cfg
**************************/
t_eReturnCode ESP_Get_ProtocolCom_Cfg(t_sESP_ComStatus *f_ESP_Config_e)
{
    t_eReturnCode Ret_e = RC_OK;
    if(f_ESP_Config_e == (t_sESP_ComStatus *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
    
        Ret_e = s_ESP_GetInfo_StateESP();
        if(Ret_e == RC_OK)
        {
            *f_ESP_Config_e = g_ESP8266_Info_s;
        }
        else 
        {
            f_ESP_Config_e->WifiCfg_s.WifiMode_e   = ESP_WIFI_MODE_UNDEFINED;
            f_ESP_Config_e->WifiCfg_s.WifiStatus_e = ESP_WIFI_STATUS_DISCONNECTED;
            f_ESP_Config_e->ConnectType_e           = ESP_CONNECTION_UNKNOWN;
            f_ESP_Config_e->ConnectState_e          = ESP_PROTOCOL_STATE_DISCONNECT;
            f_ESP_Config_e->SleepMode_e             = ESP_SLEEP_UNKNOWN;
        }
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
        Ret_e = s_ESP_MakeCommand_WithResponse(CMD(_GMR)," ",(t_uint16)ESP_TIMEOUT_READ,f_firmwareVersion_pc);
    }
    DEBUG_PRINT("ESP_GetFirmwareVersion retval : ");
    DEBUG_PRINTLN(Ret_e);
    return Ret_e;
}
/***********************
* ESP_SetSleepMode
************************/
t_eReturnCode ESP_SetSleepMode(t_eESP_SleepMode f_sleepMode_e, t_uint32 f_timeSleeping_u32)
{
    t_eReturnCode Ret_e = RC_OK;
    String ESP_Cmd_str;
    if(g_ESP_ModemCom_Initialized_b == (t_bool)false)
    {
        Ret_e = RC_ERROR_MODULE_NOT_INITIALIZED;
    }
    if(f_sleepMode_e > ESP_SLEEPMODE_NB)
    {
        Ret_e = RC_ERROR_NOT_SUPPORTED;
    }
    if(Ret_e == RC_OK)
    {
        if(g_ESP8266_Info_s.SleepMode_e != f_sleepMode_e)
        {
            if(f_sleepMode_e == ESP_SLEEPMODE_TIME)
            {
                ESP_Cmd_str = String(c_sleepModeCmd_ac[f_sleepMode_e]) + String(f_timeSleeping_u32) + String("\r\n");
            }
            else 
            {
                ESP_Cmd_str = String(c_sleepModeCmd_ac[f_sleepMode_e]) + String("\r\n");
            }
            Ret_e = s_ESP_MakeCommand(ESP_Cmd_str.c_str(), ESP_EXPECT_OK, ESP_TIMEOUT_READ);
        }
        //ESP_SLEEPMODE_TIME is not considered as continuous, once time is out, ESP is no longer with this sleepMode, others are.
        if(Ret_e == RC_OK && g_ESP8266_Info_s.SleepMode_e != ESP_SLEEPMODE_TIME)
        {
            g_ESP8266_Info_s.SleepMode_e = f_sleepMode_e;
        }
        else if(Ret_e != RC_OK && g_ESP8266_Info_s.SleepMode_e != ESP_SLEEPMODE_TIME)
        {
            g_ESP8266_Info_s.SleepMode_e = ESP_SLEEP_UNKNOWN;
        }
    }
    //Serial.println(g_ESP8266_Info_s.SleepMode_e);
    return Ret_e;
}
//********************************************************************************
//                      Local functions - Implementation
//********************************************************************************
/********************************
* s_ESP_GetInfo_StateESP
********************************/   
static t_eReturnCode s_ESP_GetInfo_StateESP(void)
{
    t_eReturnCode Ret_e = RC_OK;
    char response_ac[MODEM_MAX_BUFF_SIZE];
    char *answerExpectedFound_pc;
    //check Wi-fi connection 
    Ret_e = s_ESP_MakeCommand_WithResponse(CMD_READ(_CWJAP), ESP_EXPECT_AT, ESP_TIMEOUT_READ, response_ac);
    if(Ret_e == RC_OK)
    {
        //ESP send +CWJAP : "livebox name", "IP address", if Wifi Connected, and NO AP if not 
        answerExpectedFound_pc = (char *)strstr(response_ac, ESP_EXCPECT_WIFI_CONNECT);
        if(answerExpectedFound_pc == (char *)NULL)
        {
            g_ESP8266_Info_s.WifiCfg_s.WifiStatus_e = ESP_WIFI_STATUS_DISCONNECTED;
        }
        else
        {
            g_ESP8266_Info_s.WifiCfg_s.WifiStatus_e = ESP_WIFI_STATUS_CONNECTED;
        }
        //re-initialiaze data
        answerExpectedFound_pc = (char *)NULL;
        memset(response_ac, '\0', sizeof(response_ac));
        //datasheet say 2 : got IP, 3 : connected, 4 : disconnected, 5 : Wifi connection failed
        Ret_e = s_ESP_MakeCommand_WithResponse(CMD(_CIPSTATUS), ESP_EXPECT_AT, ESP_TIMEOUT_READ, response_ac);
        if(Ret_e == RC_OK)
        {
            answerExpectedFound_pc = (char *)strstr(response_ac, ESP_EXPECT_TCP_CONNECT);
            if(answerExpectedFound_pc == (char*)NULL)
            {
                g_ESP8266_Info_s.ConnectState_e = ESP_PROTOCOL_STATE_DISCONNECT;
            }
            else 
            {
                g_ESP8266_Info_s.ConnectState_e = ESP_PROTOCOL_STATE_CONNECTED;
            }
        }
    }
    return Ret_e;    
}
/***********************
* s_ESP_MakeCommand
***********************/
static t_eReturnCode s_ESP_MakeCommand(const char *f_command_pac, const char * f_answerExpected_pac, t_uint16 timeOutMs_u16)
{
    t_eReturnCode Ret_e = RC_OK;
    t_uint8 LI_u8;
    char response_ac[MODEM_MAX_BUFF_SIZE];
    char * answerExepctedFind_pc = (char*)NULL;
    if(f_command_pac == (const char*)NULL || f_answerExpected_pac == (const char*)NULL)
    {
        Serial.println("MakeCmd ptr null");
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        Serial.print("Send : ");
        printWithVisibleNewlines(f_command_pac);
        Serial.print("len : ");
        Serial.println(strlen(f_command_pac));
        for(LI_u8 = 0 ; LI_u8 < ESP_WL_MAX_ATTEMPT_CONNECTION ; LI_u8++)
        {
            delay(ESP_TIMEOUT_READ);
            Ret_e = Modem_Write(f_command_pac);
            delay(timeOutMs_u16);
            if(Ret_e == RC_OK)
            {   
                Ret_e = Modem_ReadBuffer(response_ac);
                Serial.print("Rcv :");
                Serial.println(response_ac);
                //see if ESP answer is corresponding with what expected
            }
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
                    Serial.print(f_answerExpected_pac);
                    Serial.println("Noot Found");
                    Ret_e = RC_WARNING_WRONG_RESULT;
                }
            }                        
        } 
    }
    DEBUG_PRINT("s_ESP_MakeCommand RetVal:");
    DEBUG_PRINTLN(Ret_e);
    return Ret_e;
}
/********************************
* s_ESP_MakeCommand_WithResponse
********************************/    
static t_eReturnCode s_ESP_MakeCommand_WithResponse(const char *f_command_pac, const char * f_answerExpected_pac, t_uint16 timeOutMs_u16, const char * f_answer_pac)
{
    t_eReturnCode Ret_e = RC_OK;
    t_uint8 LI_u8;
    t_uint8 maxTryWrite_u8 = ESP_WL_MAX_ATTEMPT_CONNECTION;
    char response_ac[MODEM_MAX_BUFF_SIZE];
    char * answerExepctedFind_pc = (char*)NULL;
    char * checkstrcpy = (char*)NULL;
    if(f_command_pac == (const char*)NULL || f_answerExpected_pac == (const char*)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        for(LI_u8 = 0 ; LI_u8 < ESP_WL_MAX_ATTEMPT_CONNECTION ; LI_u8++)
        {
            delay(ESP_TIMEOUT_READ);
            Ret_e = Modem_Write(f_command_pac);
            delay(timeOutMs_u16);
            if(Ret_e == RC_OK)
            {   
                Ret_e = Modem_ReadBuffer(response_ac);
            }
            //see if ESP answer is corresponding with what expected
            if(Ret_e == RC_OK)
            {
                //if "busy" in response_ac go read the rest of the buffer 'cause ESP did not finished is previous task                  
                answerExepctedFind_pc = strstr(response_ac, ESP_EXPECT_BUSY);
                if(answerExepctedFind_pc != (char *)NULL)
                {
                    //Serial.println("Waiting");
                    Ret_e = RC_WARNING_BUSY;
                }
                else
                {
                    //Serial.println("ReceivedCmd :");
                    //Serial.println(response_ac);
                    answerExepctedFind_pc = (char * )NULL;
                    answerExepctedFind_pc = strstr(response_ac, f_answerExpected_pac);
                    if(answerExepctedFind_pc != (char *)NULL)
                    {
                        //Serial.println("find it");
                        checkstrcpy = strcpy((char *)f_answer_pac, (const char *)response_ac);
                        if ((char *)checkstrcpy != (char *)f_answer_pac) 
                        {
                            Ret_e = RC_ERROR_COPY_FAILED;
                        }
                        else
                        {
                            Ret_e = RC_OK;
                            break;
                        }                            
                    }
                    else 
                    {
                        Ret_e = RC_WARNING_WRONG_RESULT;
                    }     
                }                          
            }            
        }
        //Serial.println(LI_u8);
        if(LI_u8 >= maxTryWrite_u8)
        {
          Ret_e = RC_ERROR_LIMIT_REACHED;
        }
    }
    DEBUG_PRINT("s_ESP_MakeCommand_Withreponse RetVal:");
    DEBUG_PRINTLN(Ret_e);
    return Ret_e;
}   