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
#define MAIN_SERIAL_BAUDRATE 9600
#define ESP_SERIAL_BAUDRATE 115200
#define MAIN_WIFI_RX 11
#define MAIN_WIFI_TX 10
#define ARDUINO_WAIT_SERVER 5000
#define ARDUINO_WAIT_CYCLIC 1000
#define MAIN_ARDUINO_MAX_ERROR 20

#define MAIN_CHECK_CONNECT_STATUE 70000

#define SEC_IN_MIN 60
// ********************************************************************
// *                      Types
// ********************************************************************
typedef enum 
{
    MAIN_ARDUINO_MODE_SLEEP,
    MAIN_ARDUINO_MODE_WAKEUP,
    MAIN_ARDUINO_MODE_ASK_TASK,
    MAIN_ARDUINO_MODE_SEND_SENSORS_VALUES,
    MAIN_ARDUINO_MODE_RCV_ACTUATORS_DATAS,
    MAIN_ARDUINO_MODE_SET_ACTUATORS,
    MAIN_ARDUINO_MODE_CHECK_ACT_DURATION,

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

const char * c_Arduino_AskCmd_pac               = "999";
const char * c_Arduino_MustSendData_pac         = "111";
const char * c_Arduino_SendData_pac             = "144";
const char * c_Arduino_SetActuators_pac         = "200";
const char * c_Arduino_RcvActuatorsValues_pac   = "222";
const char * c_Arduino_RcvActuatorsDuration_pac = "244";

// ********************************************************************
// *                      Variables
// ********************************************************************
t_sint16 g_actuatorsValue_sa16[ACT_NUMBER] = {
    (t_sint16)0,                    // ACT_CMD_IRRIGVALVE_TOMATE
    (t_sint16)0,                    // ACT_CMD_IRRIGVALVE_COURGETTE
    (t_sint16)0,                    // ACT_CMD_IRRIGVALVE_CAROTTE
};
t_sint16 g_actuatorsDuration_sa16[ACT_NUMBER] = {

    (t_sint16)0,                    // ACT_CMD_IRRIGVALVE_TOMATE
    (t_sint16)0,                    // ACT_CMD_IRRIGVALVE_COURGETTE
    (t_sint16)0,                    // ACT_CMD_IRRIGVALVE_CAROTTE
};
t_sint16 g_sensorsValue_sa16[SNS_NUMBER] = {
    //(t_sint16)0,
    //I(t_sint16)0,
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
static t_eReturnCode s_Main_SetActuatorsValues(t_sint16 f_ActuatorsContainer_as16[]);
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
static t_eReturnCode s_Main_GetActuatorsValues(t_sint16 f_ActuatorsContainer_as16[]);
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
static t_eReturnCode s_Main_GetSensorsValues(t_sint16 f_SensorsContainer_as16[]);
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
static t_eReturnCode s_Logic_Main_Cyclic(void);
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
static t_eReturnCode s_Main_ExtractMasterCmd(const char *f_RcvCmdMaster_pac, t_uint16 f_bufferSize_u16, t_sint16 f_container_sa16[]);
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
    static t_uint32 s_actualTime_CoStatue_u32 = millis();
    static t_uint32 s_actualTime_ActDuration_u32;
    static t_uint8 s_ctr_IrrigValve_Off_u8 = (t_uint8)0; 
    char RcvServerData_ac[MODEM_MAX_BUFF_SIZE];
    char * answerExpected_pc = NULL;
    String sendDataToMaster_str = "";
    String RcvMasterCmd_str= "";
    t_uint8 LI_u8 = (t_uint8)0;
    static t_bool s_checkTimeDuration_b = (t_bool)false;
    if(g_SensorsInitialize_b != (t_bool)true || g_ActuatorsInitialize_b != (t_bool)true)
    {
        Ret_e = RC_ERROR_MODULE_NOT_INITIALIZED;
    }
    if(Ret_e == RC_OK)
    {
        // check if we have to actualize WifiStatue & Protocol statue
        /*Serial.println("here");
        if((millis()  - s_actualTime_CoStatue_u32) > (t_uint32)MAIN_CHECK_CONNECT_STATUE)
        {
            Ret_e = ESP_Get_ProtocolCom_Cfg(&s_ESP_Cfg_s);
        }*/
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
                Ret_e = s_Main_GetTask_FromMaster(s_ESP_Cfg_s, RcvServerData_ac);
                Serial.println(Ret_e);
                Serial.print("Rcv :");
                Serial.println(RcvServerData_ac);
                if(Ret_e == RC_OK)
                {//see if Master wants sensors values or cmd relay 
                    answerExpected_pc = strstr(RcvServerData_ac, c_Arduino_MustSendData_pac);
                    if(answerExpected_pc != (char *)NULL)
                    {
                        Serial.print("Send sensors values");
                        g_ArduinoState_e = MAIN_ARDUINO_MODE_SEND_SENSORS_VALUES;
                    }
                    else
                    {
                        answerExpected_pc = strstr(RcvServerData_ac, c_Arduino_SetActuators_pac);
                        if(answerExpected_pc != (char *)NULL)
                        {
                            g_ArduinoState_e = MAIN_ARDUINO_MODE_RCV_ACTUATORS_DATAS;
                        }
                        else 
                        {
                            Serial.print("Set cmd check");
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
            case MAIN_ARDUINO_MODE_RCV_ACTUATORS_DATAS:
            {
                Ret_e = ESP_SendData_WithProtocolCom(ESP_EXCHANGE_DATA_SERIAL, c_Arduino_RcvActuatorsValues_pac);
                if(Ret_e == RC_OK)
                {
                    Serial.println("Wait for Actuators value ");
                    delay(ARDUINO_WAIT_SERVER);
                    Ret_e = ESP_RcvData_WithProtocolCom(ESP_EXCHANGE_DATA_SERIAL,RcvServerData_ac);
                    // chekc if ID correspond to what exepected i.e. the actuators values
                    answerExpected_pc = strstr(RcvServerData_ac, c_Arduino_RcvActuatorsValues_pac);
                    if(answerExpected_pc != (char *)NULL)
                    {// we rcv actuatorsd values
                        // check here
                        Serial.print("Exctraction actuators value");
                        Ret_e = s_Main_ExtractMasterCmd((const char *)RcvServerData_ac, (t_uint16)strlen(RcvServerData_ac),g_actuatorsValue_sa16);
                        Serial.println(Ret_e);
                        if(Ret_e == RC_OK)
                        {// we now receive Actuators duration
                            s_Main_ResetBuffer(RcvServerData_ac,MODEM_MAX_BUFF_SIZE);
                            answerExpected_pc = (char *)NULL;
                            Ret_e = ESP_SendData_WithProtocolCom(ESP_EXCHANGE_DATA_SERIAL,c_Arduino_RcvActuatorsDuration_pac);
                            Serial.println(Ret_e);
                            if(Ret_e == RC_OK)
                            {
                                Serial.println("Wait for Actuators duration");
                                delay(ARDUINO_WAIT_SERVER);
                                Ret_e = ESP_RcvData_WithProtocolCom(ESP_EXCHANGE_DATA_SERIAL, RcvServerData_ac);
                                answerExpected_pc = strstr(RcvServerData_ac, c_Arduino_RcvActuatorsDuration_pac);
                                if(answerExpected_pc != (char * )NULL)
                                {// check rcv actuators duration ok 
                                    Serial.println("Exctraction actuators duration");
                                    Ret_e = s_Main_ExtractMasterCmd((const char *)RcvServerData_ac,(t_uint16)strlen(RcvServerData_ac), g_actuatorsDuration_sa16);
                                    for(LI_u8 = 0 ; LI_u8 < ACT_NUMBER ; LI_u8++)
                                    {
                                        Serial.println(g_actuatorsDuration_sa16[LI_u8]);
                                    }
                                    Serial.println(Ret_e);
                                    if(Ret_e == RC_OK)
                                    {
                                        g_ArduinoState_e = MAIN_ARDUINO_MODE_SET_ACTUATORS;
                                    }
                                }
                                else
                                {
                                    Ret_e = RC_WARNING_WRONG_RESULT;
                                }                                   
                            }
                        }
                        
                    }
                    else 
                    {
                        Ret_e = RC_WARNING_WRONG_RESULT;
                    }
                }
                if(Ret_e != RC_OK)
                {
                    s_ctr_FailedConnexion_u8 += (t_uint8)1;
                    g_ArduinoState_e = MAIN_ARDUINO_MODE_ASK_TASK;
                }
                break;
            }
            case MAIN_ARDUINO_MODE_SET_ACTUATORS:
            {//If here set actuatos values during actuators timings
                // first Set actuators values and then ckeck timeDuration to stop irrig
                if(s_checkTimeDuration_b == false)
                {
                    Ret_e = s_Main_SetActuatorsValues(g_actuatorsValue_sa16);
                    s_checkTimeDuration_b = (t_bool)true;
                    s_actualTime_ActDuration_u32 = millis();
                }
                else
                {
                    // check timing duration 
                    for (LI_u8 = (t_uint8)0; LI_u8 < ACT_NUMBER ; LI_u8++)
                    {
                        if(millis() - s_actualTime_ActDuration_u32 > ((t_uint32)g_actuatorsDuration_sa16[LI_u8] * (t_uint32)SEC_IN_MIN))
                        {// cut the irrigation valve 
                            Serial.println((millis() - s_actualTime_ActDuration_u32));
                            Serial.println(g_actuatorsDuration_sa16[LI_u8]* (t_uint32)SEC_IN_MIN);
                            c_SysActCfg_as[LI_u8].ActSetVal_pcb((t_uint16)0);
                            g_actuatorsDuration_sa16[LI_u8] = (t_uint32)0;
                            s_ctr_IrrigValve_Off_u8 += (t_uint8)1;
                        }
                    }   
                    if(s_ctr_IrrigValve_Off_u8 == (t_uint8)ACT_NUMBER)
                    {// reset timer & passed to another state
                        s_ctr_IrrigValve_Off_u8 = (t_uint8)0;
                        s_actualTime_ActDuration_u32 = (t_uint32)0;
                        s_checkTimeDuration_b = (t_bool)false;
                        Ret_e = ESP_SendData_WithProtocolCom(ESP_EXCHANGE_DATA_SERIAL, "200 : done");
                        g_ArduinoState_e = MAIN_ARDUINO_MODE_WAKEUP;
                    } 
                }                
                break;
            }
            case MAIN_ARDUINO_MODE_SEND_SENSORS_VALUES:
            {//IF here send sensors values and go to sleep or make other things
                Serial.println("Get sensor value");
                Ret_e = s_Main_GetSensorsValues(g_sensorsValue_sa16);
                if(Ret_e == RC_OK)
                {
                    sendDataToMaster_str = String(c_Arduino_SendData_pac) + String(",");
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
                    s_ctr_FailedConnexion_u8 += (t_uint8)1;
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
        Ret_e = ESP_Init(ESP_SERIAL_BAUDRATE, MAIN_WIFI_RX, MAIN_WIFI_TX );
        if(Ret_e == RC_OK)
        {
            s_InitModuleESP_b = (t_bool)true;
        }
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
        }
        if(ESP_Wifi_Cfg_s.ConnectState_e != ESP_PROTOCOL_STATE_CONNECTED)
        {
            Ret_e = ESP_Start_ProtocolCom(ESP_CONNECTION_TCP_CLIENT, c_IP_AUDMBA_Petite_Boule_pac, (t_uint16)c_serverPort_u8);
            if(Ret_e == RC_OK)
            {
                ESP_Wifi_Cfg_s.ConnectState_e = ESP_PROTOCOL_STATE_CONNECTED;
            }
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
static t_eReturnCode s_Main_SetActuatorsValues(t_sint16 f_ActuatorsContainer_as16[])
{
    t_eReturnCode Ret_e = RC_OK;
    t_uint8 LI_u8;
    for(LI_u8 = (t_uint8)0 ; (t_uint8)LI_u8 < ACT_NUMBER && Ret_e == RC_OK; LI_u8++ )
    {
        Ret_e = c_SysActCfg_as[LI_u8].ActSetVal_pcb(f_ActuatorsContainer_as16[LI_u8]);
    }
    return Ret_e;
}
/****************************
* s_Main_GetActuatorsValues
****************************/
static t_eReturnCode s_Main_GetActuatorsValues(t_sint16 f_ActuatorsContainer_as16[])
{
    t_eReturnCode Ret_e = RC_OK;
    t_uint8 LI_u8;
    for(LI_u8 = (t_uint8)0 ; (t_uint8)LI_u8 < ACT_NUMBER && Ret_e == RC_OK; LI_u8++ )
    {
        f_ActuatorsContainer_as16[LI_u8] = (t_sint16)0;
        Ret_e = c_SysActCfg_as[LI_u8].ActGetVal_pcb(&f_ActuatorsContainer_as16[LI_u8]);
    }
    return Ret_e;
}
/****************************
* s_Main_GetSensorsValues
****************************/
static t_eReturnCode s_Main_GetSensorsValues(t_sint16 f_SensorsContainer_as16[])
{
    t_eReturnCode Ret_e = RC_OK;
    t_uint8 LI_u8;
    for(LI_u8 = (t_uint8)0 ; (t_uint8)LI_u8 < SNS_NUMBER && Ret_e == RC_OK; LI_u8++ )
    {
        f_SensorsContainer_as16[LI_u8] = (t_sint16)0;
        Ret_e = c_SysSnsCfg_as[LI_u8].SnsGet_pcb(&f_SensorsContainer_as16[LI_u8]);
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
    return Ret_e;
}
/****************************
* s_Main_GetTask_FromMaster
****************************/
static t_eReturnCode s_Main_ExtractMasterCmd(const char *f_RcvCmdMaster_pac, t_uint16 f_bufferSize_u16, t_sint16 f_container_sa16[])
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
                if(counter_u16 != (t_uint16)0)
                {
                    f_container_sa16[counter_u16 - (t_sint16)1] = atoi(f_RcvCmdMaster_pac + LI_u16 + 1);
                    
                }
                counter_u16 ++;
                
            }
            if(counter_u16 - (t_sint16)1 > ACT_NUMBER)
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
    Serial.begin(115200);
    attachInterrupt(digitalPinToInterrupt(MAIN_WIFI_RX),s_Main_WakeUpMode,CHANGE);
    //make all config in once

    t_eReturnCode Ret_e = RC_OK;
    Ret_e = s_Main_SetSNS_ACT_Cfg();
    if(Ret_e == RC_OK)
    {
        g_SensorsInitialize_b = (t_bool)true;
        g_ActuatorsInitialize_b = (t_bool)true;
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