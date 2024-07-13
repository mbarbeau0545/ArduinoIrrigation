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
#include "ConfigSpecific/HAL/Arduino_CfgSpec.h"
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
#define ESP_EXPECT_WIFI_CONNECT    "CWJAP:"
#define ESP_EXPECT_RCV_DATA         "IPD"
#define ESP_EXPECT_TCP_CONNECT      "3"
#define EXP_EXPECT_TCP_DISCONNECT   "2"

#define ESP_TIMEOUT_BETWEEN_ECHANGE (t_uint16)1000
#define ESP_TIMEOUT_WRITE           (t_uint16)500                            //Time waiting from ESP doing the cmd 
#define ESP_TIMEOUT_READ            (t_uint16)350                               //Time waiting from ESP to send info
#define ESP_TIMEOUT_SEND            (t_uint16)100
#define ESP_TIMEOUT_RCV             (t_uint16)6000

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
    CMD_WRITE(_CWMODE)"1\r\n",                                                                    //ESP_WIFI_MODE_STATION = 0,
    CMD_WRITE(_CWMODE)"2\r\n",                                                                    //ESP_WIFI_MODE_AP,
    CMD_WRITE(_CWMODE)"3\r\n",                                                                    //ESP_WIFI_MODE_BOTH,
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
static t_eReturnState s_ESP_MakeCommand(const char *f_command_pac, const char * f_answerExpected_pac, t_uint16 timeOutMs_u16);
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
static t_eReturnState s_ESP_MakeCommand_WithResponse(const char *f_command_pac, t_uint16 timeOutMs_u16,char * f_answer_pac);
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
static t_eReturnState s_ESP_GetInfo_StateESP(void);
void printWithVisibleNewlines(const char* str);
void printWithVisibleNewlines(const char* str) {
    while (*str) {
        if (*str == '\n') 
        {
            DEBUG_PRINT("\\n");
        } else if (*str == '\r') 
        {
            DEBUG_PRINT("\\r");
        }
        else if (*str == '\0') 
        {
            DEBUG_PRINT("\\0");
        } 
        else 
        {
            DEBUG_PRINT(*str);
        }
        str++;
    }
    DEBUG_PRINTLN(); // Move to the next line after printing the entire string
}
//******************************************************************************** 
//                      Public functions - Implementation
//********************************************************************************
/**********************
* ESP_Init
***********************/
 t_eReturnState ESP_Init(void)
 {
    t_eReturnState Ret_e = RC_OK;
    t_uint32 baudRate_u32 = (t_uint32)c_ESPComProjectCfg_s.baudRate_u32;
    t_uint8  rxPin_u8     = (t_uint8)c_ESPComProjectCfg_s.rxPin_u8;
    t_uint8  txPin_u8     = (t_uint8)c_ESPComProjectCfg_s.txPin_u8;
    Ret_e = Modem_InitCom(baudRate_u32, rxPin_u8, txPin_u8);
    if(Ret_e == RC_OK)
    {
        Ret_e = s_ESP_MakeCommand((const char *)"AT\r\n", (char *)ESP_EXPECT_OK, (t_uint16)ESP_TIMEOUT_READ);
        if(Ret_e == RC_OK)
        {
            g_ESP_ModemCom_Initialized_b = (t_bool)true;
        }        
    }
    if(Ret_e != RC_OK)
    {
        g_ESP_ModemCom_Initialized_b = (t_bool)false;
    }
    return Ret_e;
 }
 /**********************
* ESP_Close
***********************/
 t_eReturnState ESP_Close(void)
 {
    t_eReturnState Ret_e = RC_OK;
    if(g_ESP_ModemCom_Initialized_b == (t_bool)true)
    {
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
        Modem_EndCom();
        g_ESP_ModemCom_Initialized_b = (t_bool)false;
    }
    return Ret_e;
 }
/**********************
* ESP_ConnectWifi
***********************/
t_eReturnState ESP_ConnectWifi(const char *f_SSID_pc, const char *f_password_pc)
{
    t_eReturnState Ret_e = RC_OK;
    t_eESP_WifiMode WifiMode_e = c_ESPComProjectCfg_s.WifiMode_e;
    char ESP_WifiModeCmd_ac[strlen(c_WifiCmd_uac[WifiMode_e]) + 1];
    char ESP_WifiCom_ac[MODEM_MAX_BUFF_SIZE];
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
    {// ask Module if it's connected
        Ret_e = s_ESP_MakeCommand(CMD_READ(_CWJAP), (const char *)f_SSID_pc, ESP_TIMEOUT_READ);
        if(Ret_e == RC_OK)
        {
            g_ESP8266_Info_s.WifiCfg_s.WifiStatus_e = ESP_WIFI_STATUS_CONNECTED;
        }
        else
        {// set mode, make connection, ask Modumle to check ocnnection again
            if(g_ESP8266_Info_s.WifiCfg_s.WifiMode_e != WifiMode_e)
            {
                strcpy(ESP_WifiModeCmd_ac, c_WifiCmd_uac[WifiMode_e]);
                Ret_e = s_ESP_MakeCommand((const char *)ESP_WifiModeCmd_ac,(const char *)ESP_EXPECT_OK, ESP_TIMEOUT_READ);
            }
            if(Ret_e == RC_OK)
            {
                g_ESP8266_Info_s.WifiCfg_s.WifiMode_e = (t_eESP_WifiMode)WifiMode_e;
                strcpy(ESP_WifiCom_ac, CMD_WRITE(_CWJAP_DEF));
                strcat(ESP_WifiCom_ac, "\"");  
                strcat(ESP_WifiCom_ac, f_SSID_pc); 
                strcat(ESP_WifiCom_ac, "\",\"");   
                strcat(ESP_WifiCom_ac, f_password_pc); 
                strcat(ESP_WifiCom_ac, "\"\r\n");  
                Ret_e = s_ESP_MakeCommand((const char *)ESP_WifiCom_ac,(const char *)ESP_EXPECT_OK, ESP_TIMEOUT_RCV);
                if(Ret_e == RC_OK)
                {// check status
                    Ret_e = s_ESP_MakeCommand(CMD_READ(_CWJAP), (const char *)f_SSID_pc, ESP_TIMEOUT_READ);
                    if(Ret_e == RC_OK)
                    {
                        g_ESP8266_Info_s.WifiCfg_s.WifiStatus_e =  ESP_WIFI_STATUS_CONNECTED;
                    }
                    else
                    {
                        Ret_e = RC_ERROR_WRONG_RESULT;
                        g_ESP8266_Info_s.WifiCfg_s.WifiStatus_e =  ESP_WIFI_STATUS_DISCONNECTED;
                    }
                }
            }
        }
    }
    return Ret_e;
}

/**********************
* ESP_DisConnectWifi
***********************/
t_eReturnState ESP_DisConnectWifi(void)
{
    t_eReturnState Ret_e = RC_OK;
    //make disconnection
    if(g_ESP_ModemCom_Initialized_b != (t_bool)true)
    {
        Ret_e = RC_ERROR_MODULE_NOT_INITIALIZED;
    }
    if(Ret_e == RC_OK)
    {    
        Ret_e = s_ESP_MakeCommand(CMD(_CWQAP), ESP_EXPECT_OK, (t_uint16)ESP_TIMEOUT_READ);
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
t_eReturnState ESP_Start_ProtocolCom(void)
{
    t_eESP_ConnectionType ProtComType_e = c_ESPComProjectCfg_s.ProtComType_e;
    t_eReturnState Ret_e = RC_OK;
    char ProtocolCmd_ac[MODEM_MAX_BUFF_SIZE];
    const char * IP_Address_pc = c_ESPComProjectCfg_s.serverID_pac;
    const char * serverPort_ac = c_ESPComProjectCfg_s.serverPrt_pac;
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
    {// know the status by asking moudule

        g_ESP8266_Info_s.ConnectType_e = ProtComType_e;
        strcpy(ProtocolCmd_ac, c_ConnectionCmd_uac[ProtComType_e]);
        strcat(ProtocolCmd_ac, ",\"");
        strcat(ProtocolCmd_ac, IP_Address_pc);
        strcat(ProtocolCmd_ac, "\",");
        strcat(ProtocolCmd_ac, serverPort_ac);
        strcat(ProtocolCmd_ac, "\r\n");
        Ret_e = s_ESP_MakeCommand((const char *)ProtocolCmd_ac, (const char *)ESP_EXPECT_OK, ESP_TIMEOUT_RCV);
        if(Ret_e == RC_OK)
        {            
            Ret_e = s_ESP_MakeCommand(CMD_READ(_CIPSTATUS), (const char *)ESP_EXPECT_TCP_CONNECT, ESP_TIMEOUT_READ);
            if(Ret_e == RC_OK)
            {
                g_ESP8266_Info_s.ConnectState_e = ESP_PROTOCOL_STATE_CONNECTED;
            }
            else
            {
                g_ESP8266_Info_s.ConnectState_e = ESP_PROTOCOL_STATE_FAILED;
            }
        }        
    }
    if(Ret_e == RC_WARNING_ALREADY_CONFIGURED)
    {
        Ret_e = RC_OK;
    }
    return Ret_e;
}
/*************************
* ESP_Close_ProtocolCom
**************************/
t_eReturnState ESP_Close_ProtocolCom(void)
{
    t_eReturnState Ret_e = RC_OK;
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
t_eReturnState ESP_SendData_WithProtocolCom(char * f_dataToSend_pc)
{
    t_eReturnState Ret_e = RC_OK;
    t_eESP_ExchangeDataMode DataMode_e = c_ESPComProjectCfg_s.exchangeType_e;
    char dataESpCmd_ac[MODEM_MAX_BUFF_SIZE/4];
    t_uint16 lenghtData_u16;
    char dataLenght_ac[10]; // 2 number will always be send but ten is a goud buffer although
    if(g_ESP_ModemCom_Initialized_b == (t_bool)false)
    {
        Ret_e = RC_ERROR_MODULE_NOT_INITIALIZED;
    }
    if(f_dataToSend_pc == (char *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(g_ESP8266_Info_s.ConnectState_e != ESP_PROTOCOL_STATE_CONNECTED)
    {
        Ret_e = RC_ERROR_WRONG_STATE;
    }
    if(DataMode_e > ESP_EXCHANGE_DATA_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    //Datasheet say that you cannot  use ESP_SEND_DATA_BUFF in SSL connection 
    if(Ret_e == RC_OK)
    {
        lenghtData_u16 = strlen(f_dataToSend_pc);
        switch(DataMode_e)
        {
            case ESP_EXCHANGE_DATA_SERIAL:
            {
                snprintf(dataLenght_ac,sizeof(dataLenght_ac),"%d", lenghtData_u16);
                strcpy(dataESpCmd_ac, CMD_WRITE(_CIPSEND));
                strcat(dataESpCmd_ac, dataLenght_ac);
                strcat(dataESpCmd_ac, "\r\n");
                //Data sheet say first send Lenght and if esp Repond OK then send it DATA
                //dataESpCmd_str = String(CMD_WRITE(_CIPSEND)) + String(lenghtData_u16) + String("\r\n");
                //ExpectRcvEsp_str = String(lenghtData_u16);
                Ret_e = s_ESP_MakeCommand((const char *)dataESpCmd_ac, (const char *)ESP_EXPECT_OK, ESP_TIMEOUT_READ);
                if(Ret_e == RC_OK)
                {
                    Ret_e = s_ESP_MakeCommand((const char *)f_dataToSend_pc,ESP_EXPECT_OK, ESP_TIMEOUT_READ);
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
            default:
            {
                Ret_e = RC_ERROR_WRONG_STATE;
                break;
            }
        }
    }
    return Ret_e;
}
/******************************
* ESP_RcvData_WithProtocolCom
*******************************/
t_eReturnState ESP_RcvData_WithProtocolCom(char *f_RcvData_pc)
{
    t_eReturnState Ret_e = RC_OK;
    //t_uint8 LI_u8;
    if(f_RcvData_pc == (char *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(g_ESP8266_Info_s.ConnectState_e != ESP_PROTOCOL_STATE_CONNECTED)
    {
        Ret_e = RC_WARNING_WRONG_CONFIG;
    }
    if(Ret_e == RC_OK)
    {
        // Used ReadBuffer function until there is something to read
        Ret_e = Modem_ReadBuffer(f_RcvData_pc);
        DEBUG_PRINT("Rcv :");
        printWithVisibleNewlines(f_RcvData_pc);
        if(Ret_e == RC_OK)
        {
            //DEBUG_PRINTLN(espResponse_ac);
            if(strstr((const char *)f_RcvData_pc,(const char*)ESP_EXPECT_RCV_DATA) == (char *)NULL)
            {
                Ret_e = RC_ERROR_WRONG_RESULT;
            }
        }
    }
    return Ret_e;
}
/*************************
* ESP_Get_ProtocolCom_Cfg
**************************/
t_eReturnState ESP_Get_ProtocolCom_Cfg(t_sESP_ComStatus *f_ESP_Config_e)
{
    t_eReturnState Ret_e = RC_OK;
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
    return Ret_e;
}
/***********************
* ESP_GetFirmwareVersion
************************/
t_eReturnState ESP_GetFirmwareVersion(char *f_firmwareVersion_pc)
{
    t_eReturnState Ret_e = RC_OK;
    if(f_firmwareVersion_pc == (char *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        Ret_e = s_ESP_MakeCommand_WithResponse(CMD(_GMR),(t_uint16)ESP_TIMEOUT_READ,f_firmwareVersion_pc);
    }
    return Ret_e;
}
/***********************
* ESP_SetSleepMode
************************/
t_eReturnState ESP_SetSleepMode(t_eESP_SleepMode f_sleepMode_e, t_uint32 f_timeSleeping_u32)
{
    t_eReturnState Ret_e = RC_OK;
    char ESP_Cmd_ac[MODEM_MAX_BUFF_SIZE/2];
    char number_ac[10];

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
            strcpy(ESP_Cmd_ac, c_sleepModeCmd_ac[f_sleepMode_e]);
            if(f_sleepMode_e == ESP_SLEEPMODE_TIME)
            {
                snprintf(number_ac, sizeof(number_ac), "%d", (int)f_timeSleeping_u32);
                strcat(ESP_Cmd_ac,number_ac);
                //ESP_Cmd_str = String(c_sleepModeCmd_ac[f_sleepMode_e]) + String(f_timeSleeping_u32) + String("\r\n");
            }
            strcat(ESP_Cmd_ac,"\r\n");
            DEBUG_PRINT("SleepCmd :");
            DEBUG_PRINTLN(ESP_Cmd_ac);
            Ret_e = s_ESP_MakeCommand((const char *)ESP_Cmd_ac, (const char *)ESP_EXPECT_OK, ESP_TIMEOUT_READ);
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
    //DEBUG_PRINTLN(g_ESP8266_Info_s.SleepMode_e);
    return Ret_e;
}
//********************************************************************************
//                      Local functions - Implementation
//********************************************************************************
/********************************
* s_ESP_GetInfo_StateESP
********************************/   
static t_eReturnState s_ESP_GetInfo_StateESP(void)
{
    t_eReturnState Ret_e = RC_OK;
    char response_ac[MODEM_MAX_BUFF_SIZE];
    char *answerExpectedFound_pc;
    //check Wi-fi connection 
    Ret_e = s_ESP_MakeCommand_WithResponse(CMD_READ(_CWJAP), ESP_TIMEOUT_READ, response_ac);
    if(Ret_e == RC_OK)
    {
        //ESP send +CWJAP : "livebox name", "IP address", if Wifi Connected, and NO AP if not 
        answerExpectedFound_pc = (char *)strstr((const char *)response_ac, (const char *)ESP_EXPECT_WIFI_CONNECT);
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
        Ret_e = s_ESP_MakeCommand_WithResponse(CMD(_CIPSTATUS), ESP_TIMEOUT_READ, response_ac);
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
static t_eReturnState s_ESP_MakeCommand(const char *f_command_pac, const char * f_answerExpected_pac, t_uint16 timeOutMs_u16)
{
    t_eReturnState Ret_e = RC_OK;
    t_uint8 LI_u8;
    char response_ac[MODEM_MAX_BUFF_SIZE];
    if(f_command_pac == (const char*)NULL || f_answerExpected_pac == (const char*)NULL)
    {
        DEBUG_PRINTLN("MakeCmd ptr null");
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        DEBUG_PRINT("Send : ");
        printWithVisibleNewlines(f_command_pac);
        for(LI_u8 = 0 ; LI_u8 < ESP_WL_MAX_ATTEMPT_CONNECTION ; LI_u8++)
        {
            delay(ESP_TIMEOUT_BETWEEN_ECHANGE);
            Ret_e = Modem_Write(f_command_pac);
            delay(timeOutMs_u16);
            if(Ret_e == RC_OK)
            {   
                Ret_e = Modem_ReadBuffer(response_ac);
                DEBUG_PRINT("Rcv :");
                printWithVisibleNewlines(response_ac);
                //see if ESP answer is corresponding with what expected
            }
            if(Ret_e == RC_OK)
            {
                if(strstr(response_ac, f_answerExpected_pac) != (char *)NULL)
                {
                    Ret_e = RC_OK;
                    break;
                }
                else 
                {
                    DEBUG_PRINT(f_answerExpected_pac);
                    DEBUG_PRINTLN("Noot Found");
                    Ret_e = RC_WARNING_WRONG_RESULT;
                }                
            }                        
        } 
    }
    return Ret_e;
}
/********************************
* s_ESP_MakeCommand_WithResponse
********************************/    
static t_eReturnState s_ESP_MakeCommand_WithResponse(const char *f_command_pac, t_uint16 timeOutMs_u16, char * f_answer_pac)
{
    t_eReturnState Ret_e = RC_OK;
    if(f_command_pac == (const char *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        DEBUG_PRINT("Send : ");
        printWithVisibleNewlines(f_command_pac);
        delay(ESP_TIMEOUT_READ);
        Ret_e = Modem_Write(f_command_pac);
        delay(timeOutMs_u16);
        if(Ret_e == RC_OK)
        {   
            Ret_e = Modem_ReadBuffer(f_answer_pac);
            DEBUG_PRINT("Rcv : ");
            printWithVisibleNewlines(f_answer_pac);
        }
    }
    return Ret_e;
}   