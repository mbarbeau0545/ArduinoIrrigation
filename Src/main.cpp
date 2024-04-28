/*********************************************************************
 * @file        main.cpp
 * @brief       Template_BriefDescription.
 * @details     TemplateDetailsDescription.\n
 *
 * @author      AUDMBA
 * @date        08/03/2024
 * @version     1.0
 *********************************************************************/
  
// ********************************************************************
// *                      Includes
// ********************************************************************

#include <Arduino.h>
#include <avr/sleep.h>
#include <avr/wdt.h>
#include "AppCommon/TypeCommon.h"
#include "ArduinoLib/ESP_8266/WiFi_ESP.h"
#include "ConfigSpecific/Sensors_ConfigSpecific.h"
#include "ConfigSpecific/Actuators_ConfigSpecific.h"
// ********************************************************************
// *                      Defines
// ********************************************************************
#define MAIN_SERIAL_BAUDRATE 115200
#define MAIN_WIFI_RX 11
#define MAIN_WIFI_TX 10
#define ARDUINO_WAIT_SERVER 3000
#define ARDUINO_WAIT_CYCLIC 3000
#define MAIN_ARDUINO_MAX_ERROR 20
// ********************************************************************
// *                      Types
// ********************************************************************
typedef enum 
{
    MAIN_ARDUINO_MODE_SLEEP,
    MAIN_ARDUINO_MODE_WAKEUP,
    MAIN_ARDUINO_MODE_ASK_TASK,
    MAIN_ARDUINO_MODE_SEND_SENSORS_VALUES,
    MAIN_ARDUINO_MODE_SET_CMD,

}t_eMain_ArduinoState;



// ********************************************************************
// *                      Constants
// ********************************************************************
/**< Wifi COnfiguration*/

const char * c_SSID_Petite_Boule_pac =  "Livebox-0BB3";
const char * c_Password_Petite_Boule_pac =  "7CF8844459F167816393050EE2";
const char * c_IP_AUDMBA_Petite_Boule_pac =  "192.168.1.26";
const t_uint8 c_serverPort_u8 = 80;
/*const char * SSID_Nantes =  "Livebox-E030";
const char * Password_Nantes =  "ZRvFTt7t2kfVaWrSYX";
const char * IP_AUDMBA_Nantes =  "192.168.1.26";*/

/**< Msg configuration*/

const char * c_Arduino_AskCmd_pac = "999";
const char * c_Arduino_MustSendData_pac = "111";
const char * c_Arduino_MustCmdRelay_pac = "222";

// ********************************************************************
// *                      Variables
// ********************************************************************

t_sint16 g_actuatorsValue_sa16[ACT_NUMBER] = {
    (t_sint16)0,                    // ACT_CMD_IRRIGVALVE
};
t_sint16 g_sensorsValue_sa16[SNS_NUMBER] = {
    (t_sint16)0,
    (t_sint16)0,
    (t_sint16)0,
    (t_sint16)0,
    (t_sint16)0,
};
t_bool   g_ActuatorsInitialize_b = (t_bool)true;
t_bool   g_SensorsInitialize_b = (t_bool)true;
t_eMain_ArduinoState g_ArduinoState_e = MAIN_ARDUINO_MODE_WAKEUP;


//****************************************************************************
//                      Local functions - Prototypes
//****************************************************************************
/**
 *
 *	@brief      Set Actutators Values
 *	@details
 *
 *
 *	@param[in] 
 *	@param[out]
 *	 
 *
 *
 */
static t_eReturnCode s_Main_SetSNS_ACT_Cfg(void);
/**
 *
 *	@brief      Set Actutators Values
 *	@details
 *
 *
 *	@param[in] 
 *	@param[out]
 *	 
 *
 *
 */
static t_eReturnCode s_Main_SetActuatorsValues(void);
/**
 *
 *	@brief      Get Actuators values from Actuator Drivers
 *	@details    
 *
 *
 *	@param[in] 
 *	@param[out]
 *	 
 *
 *
 */
static t_eReturnCode s_Main_GetActuatorsValues(void);
/**
 *
 *	@brief      Get Sensors values from Captor Drivers
 *	@details
 *
 *
 *	@param[in] 
 *	@param[out]
 *	 
 *
 *
 */
static t_eReturnCode s_Main_GetSensorsValues(void);
/**
 *
 *	@brief      Send Sensors Values to Master 
 *	@details
 *
 *
 *	@param[in] 
 *	@param[out]
 *	 
 *
 *
 */
static t_eReturnCode s_Main_SendSensorsValues(void);
/**
 *
 *	@brief      Receive and Schedule the receive Task
 *	@details
 *
 *
 *	@param[in] 
 *	@param[out]
 *	 
 *
 *
 */
static t_eReturnCode s_Main_GetTask_FromMaster(void);
/**
 *
 *	@brief      Receive and Schedule the receive Task
 *	@details
 *
 *
 *	@param[in] 
 *	@param[out]
 *	 
 *
 *
 */
static t_eReturnCode s_Logic_Main_Cyclic();
/**
 *
 *	@brief      Receive and Schedule the receive Task
 *	@details
 *
 *
 *	@param[in] 
 *	@param[out]
 *	 
 *
 *
 */

static void s_Main_SleepMode(void);
/**
 *
 *	@brief      Receive and Schedule the receive Task
 *	@details
 *
 *
 *	@param[in] 
 *	@param[out]
 *	 
 *
 *
 */
static void s_Main_WakeUpMode(void);
/**
 *
 *	@brief      Receive and Schedule the receive Task
 *	@details
 *
 *
 *	@param[in] 
 *	@param[out]
 *	 
 *
 *
 */
static void s_Main_ResetBuffer(char f_buffer_ac[], t_uint16 f_len_u16);
/**
 *
 *	@brief      Receive and Schedule the receive Task
 *	@details
 *
 *
 *	@param[in] 
 *	@param[out]
 *	 
 *
 *
 */
static t_eReturnCode s_Logic_MasterConnection(t_sESP_Cfg *f_ESP_Wifi_Cfg_ps);
/**
 *
 *	@brief      Receive and Schedule the receive Task
 *	@details
 *
 *
 *	@param[in] 
 *	@param[out]
 *	 
 *
 *
 */
static t_eReturnCode s_Main_GetTask_FromMaster(t_sESP_Cfg f_ESP_Wifi_Cfg_ps, const char *f_RcvData_pc);
/**
 *
 *	@brief      Receive and Schedule the receive Task
 *	@details
 *
 *
 *	@param[in] 
 *	@param[out]
 *	 
 *
 *
 */
static t_eReturnCode s_Main_ExtractMasterCmd(const char *f_RcvCmdMaster_pac, t_uint16 f_bufferSize_u16);
// ***************************************************************************
// *                      Class declaration
// ***************************************************************************

//****************************************************************************
//                      Public functions - Implementation
//****************************************************************************

//****************************************************************************
//                      Local functions - Implementation
//****************************************************************************
static t_eReturnCode s_Logic_Main_Cyclic()
{
    t_eReturnCode Ret_e = RC_OK;
    static t_sESP_Cfg s_ESP_Cfg_s = {
        .WifiCfg_s = {
        .WifiMode_e     = ESP_WIFI_MODE_UNDEFINED,
        .WifiStatus_e   = ESP_WIFI_STATUS_DISCONNECTED,
    },
        .ConnectType_e  = ESP_CONNECTION_UNKNOWN,  
        .ConnectState_e = ESP_PROTOCOL_STATE_DISCONNECT,                                           //All disable
        .SleepMode_e    = ESP_SLEEP_UNKNOWN,
    };
    static t_uint8 s_ctr_FailedConnexion_u8 = (t_uint8)0;
    char RcvServerData_ac[MODEM_MAX_BUFF_SIZE];
    char * answerExpected_pc = NULL;
    String sendDataToMaster_str = "";
    String RcvMasterCmd_str= "";
    t_uint8 LI_u8 = (t_uint8)0;
    if(g_SensorsInitialize_b != (t_bool)true ||g_ActuatorsInitialize_b != (t_bool)true)
    {
        Ret_e = RC_ERROR_MODULE_NOT_INITIALIZED;
    }
    if(Ret_e == RC_OK)
    {

        switch(g_ArduinoState_e)
        {
            case MAIN_ARDUINO_MODE_WAKEUP:
            {//re_initialize all Actuators value to default
                //read the task, sheduled it and go to the dedicated mode 
                // if there isn't go to default and make counter 
                //Make Wifi and TCP connection active
                Ret_e = s_Logic_MasterConnection(&s_ESP_Cfg_s);
                Serial.print("Wifi State");
                Serial.println(s_ESP_Cfg_s.WifiCfg_s.WifiStatus_e);
                Serial.print("Protocol");
                Serial.println(s_ESP_Cfg_s.ConnectState_e);
                if(Ret_e == RC_OK)
                {
                    g_ArduinoState_e = MAIN_ARDUINO_MODE_ASK_TASK;                        
                }
                else 
                {
                    g_ArduinoState_e = MAIN_ARDUINO_MODE_WAKEUP;
                    s_ctr_FailedConnexion_u8 += 1;
                }
                break;                    
            }
            case MAIN_ARDUINO_MODE_SLEEP:
            {//prepare and set the sleep
                Serial.println("About to go to sleep");
                delay(1000);
                s_Main_SleepMode();
                break;
            }
            case MAIN_ARDUINO_MODE_ASK_TASK:
            {
                s_Main_ResetBuffer(RcvServerData_ac, MODEM_MAX_BUFF_SIZE);
                Serial.print("Set task");
                delay(3000);
                Ret_e = s_Main_GetTask_FromMaster(s_ESP_Cfg_s, RcvServerData_ac);
                Serial.println(Ret_e);
                if(Ret_e == RC_OK)
                {//see if Master wants sensors values or cmd relay 
                    answerExpected_pc = strstr(RcvServerData_ac, c_Arduino_MustSendData_pac);
                    if(answerExpected_pc != (char *)NULL)
                    {
                        g_ArduinoState_e = MAIN_ARDUINO_MODE_SEND_SENSORS_VALUES;
                    }
                    else 
                    {
                        answerExpected_pc = strstr(RcvServerData_ac, c_Arduino_MustCmdRelay_pac);
                        if(answerExpected_pc != (char *)NULL)
                        {
                            g_ArduinoState_e = MAIN_ARDUINO_MODE_SET_CMD;
                        }
                        else 
                        {
                            Serial.println(RcvServerData_ac);
                            Serial.println("Cmd Server not found");
                            s_ctr_FailedConnexion_u8 += 1;
                            g_ArduinoState_e = MAIN_ARDUINO_MODE_ASK_TASK;
                        }
                    }
                }
                else
                {                                        
                    s_ctr_FailedConnexion_u8 += 1;
                    g_ArduinoState_e = MAIN_ARDUINO_MODE_WAKEUP;
                }
                break;
            }
            case MAIN_ARDUINO_MODE_SEND_SENSORS_VALUES:
            {//IF here send sensors values and go to sleep or make other things
                //Serial.println("Get sensor value");
                Ret_e = s_Main_GetSensorsValues();
                /*for(LI_u8 = (t_uint8)0 ; LI_u8 < (t_uint8)SNS_NUMBER ; LI_u8++)
                {
                    Serial.print(LI_u8);
                    Serial.print(" : ");
                    Serial.println(g_sensorsValue_sa16[LI_u8]);
                }*/
                if(Ret_e == RC_OK)
                {
                    for(LI_u8 = 0 ; LI_u8 < (t_uint8)SNS_NUMBER ; LI_u8++)
                    {
                        sendDataToMaster_str += String(LI_u8) + String(":") + String(g_sensorsValue_sa16[LI_u8]);
                        if(LI_u8 != (SNS_NUMBER) - 1)
                        {
                            sendDataToMaster_str += String(",");
                        }
                    }
                    Ret_e = ESP_SendData_WithProtocolCom(ESP_EXCHANGE_DATA_SERIAL, sendDataToMaster_str.c_str());
                    if(Ret_e == RC_OK)
                    {
                        g_ArduinoState_e = MAIN_ARDUINO_MODE_WAKEUP;
                    }
                    else
                    {
                        g_ArduinoState_e = MAIN_ARDUINO_MODE_SEND_SENSORS_VALUES;
                    }
                }
                else
                {
                    Ret_e = ESP_SendData_WithProtocolCom(ESP_EXCHANGE_DATA_SERIAL, "ERROR WHEN TRYING GET DATA");
                }
                break;
            }
            case MAIN_ARDUINO_MODE_SET_CMD:
            {//If here set command from receive cmd or what it is scheduled and then do other things
                // wait a little until Raspberry send data
                delay(ARDUINO_WAIT_SERVER);
                Ret_e = ESP_RcvData_WithProtocolCom(ESP_EXCHANGE_DATA_SERIAL,RcvMasterCmd_str.c_str());
                if(Ret_e == RC_OK)
                {
                    Ret_e = s_Main_ExtractMasterCmd(RcvMasterCmd_str.c_str(), RcvMasterCmd_str.length());
                    if(Ret_e == RC_OK)
                    {// make cmd on different relays

                    }
                    else 
                    {
                        s_ctr_FailedConnexion_u8 ++;
                        g_ArduinoState_e = MAIN_ARDUINO_MODE_ASK_TASK;
                    }
                }
                break;
            }
            default: 
            {
                g_ArduinoState_e = MAIN_ARDUINO_MODE_WAKEUP;                
                break;
            }
        }
        /*if(s_ctr_FailedConnexion_u8 > MAIN_ARDUINO_MAX_ERROR)
        {
            Serial.println("reset WatchDogs");
            //Reset Arduino using WatchDogs
            wdt_enable(WDTO_15MS);
            delay(150);
        }*/
        
    }
    return Ret_e;
}
/****************************
* s_Main_ResetBuffer
****************************/
static void s_Main_ResetBuffer(char f_buffer_ac[], t_uint16 f_len_u16)
{
    memset(f_buffer_ac,'\0',f_len_u16);
}
/****************************
* s_Main_SleepMode
****************************/
static void s_Main_SleepMode(void)
{
    Serial.println("Go to sleepMode");
    delay(10000);
    digitalWrite(LED_BUILTIN,LOW);
    //Wake up here 
}
/****************************
* s_Main_WakeUpMode
****************************/
static void s_Main_WakeUpMode(void)
{
    digitalWrite(LED_BUILTIN,HIGH);
    Serial.println("Just waking up");
    g_ArduinoState_e = MAIN_ARDUINO_MODE_WAKEUP;
}
/****************************
* s_Logic_MasterConnection
****************************/
static t_eReturnCode s_Logic_MasterConnection(t_sESP_Cfg *f_ESP_Wifi_Cfg_ps)
{
    static t_bool s_InitModuleESP_b = false;
    t_eReturnCode Ret_e = RC_OK;
    t_sESP_Cfg ESP_Wifi_Cfg_s;
    if(f_ESP_Wifi_Cfg_ps == (t_sESP_Cfg *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(s_InitModuleESP_b == (t_bool)false)
    {
        Ret_e = ESP_Init(MAIN_SERIAL_BAUDRATE, MAIN_WIFI_RX, MAIN_WIFI_TX );
    }    
    if(Ret_e == RC_OK)
    {
        Ret_e = ESP_Get_ProtocolCom_Cfg(&ESP_Wifi_Cfg_s);
    }
    if(Ret_e == RC_OK)
    {       
        if(ESP_Wifi_Cfg_s.WifiCfg_s.WifiStatus_e != ESP_WIFI_STATUS_CONNECTED)
        {
            Ret_e = ESP_ConnectWifi(ESP_WIFI_MODE_STATION ,c_SSID_Petite_Boule_pac, c_Password_Petite_Boule_pac);
            if(Ret_e == RC_OK)
            {
                ESP_Wifi_Cfg_s.WifiCfg_s.WifiStatus_e = ESP_WIFI_STATUS_CONNECTED;
            }
            Serial.print("connect :");
            Serial.println(Ret_e);
        }
        if(ESP_Wifi_Cfg_s.ConnectState_e != ESP_PROTOCOL_STATE_CONNECTED)
        {
            Ret_e = ESP_Start_ProtocolCom(ESP_CONNECTION_TCP_CLIENT, c_IP_AUDMBA_Petite_Boule_pac, (t_uint16)c_serverPort_u8);
            if(Ret_e == RC_OK)
            {
                ESP_Wifi_Cfg_s.ConnectState_e = ESP_PROTOCOL_STATE_CONNECTED;
            }
            Serial.print("protocol :");
            Serial.println(Ret_e);
        }
        f_ESP_Wifi_Cfg_ps->ConnectState_e = ESP_Wifi_Cfg_s.ConnectState_e;
        f_ESP_Wifi_Cfg_ps->ConnectType_e = ESP_Wifi_Cfg_s.ConnectType_e;
        f_ESP_Wifi_Cfg_ps->SleepMode_e = ESP_Wifi_Cfg_s.SleepMode_e;
        f_ESP_Wifi_Cfg_ps->WifiCfg_s.WifiMode_e = ESP_Wifi_Cfg_s.WifiCfg_s.WifiMode_e;
        f_ESP_Wifi_Cfg_ps->WifiCfg_s.WifiStatus_e = ESP_Wifi_Cfg_s.WifiCfg_s.WifiStatus_e;
    }   
    return Ret_e;
}
/****************************
* s_Main_SetSNS_ACT_Cfg
****************************/
static t_eReturnCode s_Main_SetSNS_ACT_Cfg(void)
{
    t_eReturnCode Ret_e = RC_OK;
    t_uint8 LI_u8;
    for(LI_u8 = 0 ; LI_u8 < SNS_NUMBER && Ret_e == RC_OK ; LI_u8++)
    {
        Ret_e = (c_SysSnsCfg_as[LI_u8].SnsCfg_pcb)(c_SensorsPin_ua8[LI_u8], c_Sensors_PinMode_ea[LI_u8]);
        if(Ret_e != RC_OK)
        {
            Serial.println("Problem in CfgSensor");
            Serial.println(Ret_e);
            Serial.println(LI_u8);
        }
    }
    if(Ret_e == RC_OK)
    {
        g_SensorsInitialize_b = (t_bool)true;
        for(LI_u8 = 0 ; LI_u8 < ACT_NUMBER && Ret_e == RC_OK ; LI_u8++)
        {
            Ret_e = (c_SysActCfg_as[LI_u8].ActCfg_pcb)(c_ActuatorsPin_ua8[LI_u8], c_Actuators_PinMode_ea[LI_u8]);
            if(Ret_e != RC_OK)
            {
                Serial.println("Problem in CfgActuator");
                Serial.println(Ret_e);
                Serial.println(LI_u8);
            }
        }
        if(Ret_e == RC_OK)
        {
            g_ActuatorsInitialize_b = (t_bool)true;
        }
    }
    
    return Ret_e;
}
/****************************
* s_Main_SetActuatorsValues
****************************/
static t_eReturnCode s_Main_SetActuatorsValues(void)
{
    t_eReturnCode Ret_e = RC_OK;
    t_uint8 LI_u8;
    for(LI_u8 = (t_uint8)0 ; (t_uint8)LI_u8 < ACT_NUMBER && Ret_e == RC_OK; LI_u8++ )
    {
        Ret_e = c_SysActCfg_as[LI_u8].ActSetVal_pcb(g_actuatorsValue_sa16[LI_u8]);
    }
    return Ret_e;
}
/****************************
* s_Main_GetActuatorsValues
****************************/
static t_eReturnCode s_Main_GetActuatorsValues(void)
{
    t_eReturnCode Ret_e = RC_OK;
    t_uint8 LI_u8;
    for(LI_u8 = (t_uint8)0 ; (t_uint8)LI_u8 < ACT_NUMBER && Ret_e == RC_OK; LI_u8++ )
    {
        g_actuatorsValue_sa16[LI_u8] = (t_sint16)0;
        Ret_e = c_SysActCfg_as[LI_u8].ActGetVal_pcb(&g_actuatorsValue_sa16[LI_u8]);
    }
    return Ret_e;
}
/****************************
* s_Main_GetSensorsValues
****************************/
static t_eReturnCode s_Main_GetSensorsValues(void)
{
    t_eReturnCode Ret_e = RC_OK;
    t_uint8 LI_u8;
    for(LI_u8 = (t_uint8)0 ; (t_uint8)LI_u8 < SNS_NUMBER && Ret_e == RC_OK; LI_u8++ )
    {
        g_sensorsValue_sa16[LI_u8] = (t_sint16)0;
        Ret_e = c_SysSnsCfg_as[LI_u8].SnsGet_pcb(&g_sensorsValue_sa16[LI_u8]);
        if(Ret_e != RC_OK)
        {
            Serial.print(LI_u8);
            Serial.println(": Something's off, RetVal");
            Serial.println(Ret_e);
        }

    }
    return Ret_e;
}
/****************************
* s_Main_GetTask_FromMaster
****************************/
static t_eReturnCode s_Main_GetTask_FromMaster(t_sESP_Cfg f_ESP_Wifi_Cfg_ps, const char *f_RcvData_pc)
{
    t_eReturnCode Ret_e = RC_OK;
    char espResponse_ac[MODEM_MAX_BUFF_SIZE];
    char * checkstrcpy = (char *)NULL;
    if(f_RcvData_pc == (const char *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        if(f_ESP_Wifi_Cfg_ps.WifiCfg_s.WifiStatus_e == ESP_WIFI_STATUS_CONNECTED && f_ESP_Wifi_Cfg_ps.ConnectState_e == ESP_PROTOCOL_STATE_CONNECTED)
        {         
            Ret_e = ESP_SendData_WithProtocolCom(ESP_EXCHANGE_DATA_SERIAL,c_Arduino_AskCmd_pac);
            delay(ARDUINO_WAIT_SERVER);
            if(Ret_e == RC_OK)
            {
                Ret_e = ESP_RcvData_WithProtocolCom(ESP_EXCHANGE_DATA_SERIAL,espResponse_ac);
                if(Ret_e == RC_OK)
                {
                    checkstrcpy = strcpy((char *)f_RcvData_pc,(const char *)espResponse_ac);
                    if(checkstrcpy != (char *)f_RcvData_pc)
                    {
                        Ret_e = RC_ERROR_COPY_FAILED;
                    }
                }
            }
        }
        else
        {
            Ret_e = RC_ERROR_WRONG_STATE;
        }
    }
    return Ret_e;
}
/****************************
* s_Main_GetTask_FromMaster
****************************/
static t_eReturnCode s_Main_ExtractMasterCmd(const char *f_RcvCmdMaster_pac, t_uint16 f_bufferSize_u16)
{
    t_eReturnCode Ret_e = RC_OK;
    t_uint8 counter_u16 = 0;
    t_uint16 LI_u16;
    if(f_RcvCmdMaster_pac == (const char * )NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        for(LI_u16 = (t_uint16)0 ; LI_u16 < f_bufferSize_u16 ; LI_u16++)
        {
            if(f_RcvCmdMaster_pac[LI_u16] == ':')
            {
                g_actuatorsValue_sa16[counter_u16] = atoi(f_RcvCmdMaster_pac + LI_u16 + 2);
                counter_u16 ++;
            }
            if(counter_u16 > ACT_NUMBER)
            {
                Ret_e = RC_ERROR_LIMIT_REACHED;
            }
        }
    }
    return Ret_e;
}
// ********************************************************************
// *                       setup implementation 
// ********************************************************************
void setup() 
{
    Serial.begin(MAIN_SERIAL_BAUDRATE);
    attachInterrupt(digitalPinToInterrupt(MAIN_WIFI_RX),s_Main_WakeUpMode,CHANGE);
    //make all config in once

    t_eReturnCode Ret_e = RC_OK;
    Ret_e = s_Main_SetSNS_ACT_Cfg();
    if(Ret_e == RC_OK)
    {
        Serial.println("Cfg Senssor OK.");
        
    }
    else 
    {
        Serial.println("Cfg Senssor Not OK.");
    }
}

// ********************************************************************
// *                       loop implmentation
// ********************************************************************
void loop() 
{

    t_eReturnCode Ret_e = RC_OK;
    Serial.print("Arduino state :");
    Serial.println(g_ArduinoState_e);
    Ret_e =  s_Logic_Main_Cyclic();
    Serial.print("Cyclic Value");
    Serial.println(Ret_e);
    delay(ARDUINO_WAIT_CYCLIC);
}

//****************************************************************************
// End of File
//****************************************************************************


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