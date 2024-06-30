/*********************************************************************
 * @file        Irrig.cpp
 * @brief       Template_BriefDescription.
 * @details     TemplateDetailsDescription.\n
 *
 * @author      AUDMBA
 * @date        09/03/2024
 * @version     1.0
 *********************************************************************/
  






// ********************************************************************
// *                      Includes
// ********************************************************************

#include "Irrig_Cfg.h"
#include "Irrig.h"
// ********************************************************************
// *                      Defines
// ********************************************************************
#define IRRIG_SERIAL_BAUDRATE 9600
#define ESP_SERIAL_BAUDRATE 115200
#define IRRIG_WIFI_RX 11
#define IRRIG_WIFI_TX 10
#define ARDUINO_WAIT_SERVER 500

#define MAIN_ARDUINO_MAX_ERROR 20

#define IRRIG_CHECK_CONNECT_STATUE 70000

#define SEC_IN_MIN 60
// ********************************************************************
// *                      Types
// ********************************************************************

// ********************************************************************
// *                      Prototypes
// ********************************************************************
    
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
t_bool   g_ActuatorsInitialize_b = (t_bool)false;
t_bool   g_SensorsInitialize_b = (t_bool)false;
t_eIrrig_ArduinoState g_ArduinoState_e = IRRIG_ARDUINO_MODE_WAKEUP;
//********************************************************************************
//                      Local functions - Prototypes
//********************************************************************************
static t_eReturnCode s_Irrig_SetActuatorsValues(t_sint16 f_ActuatorsContainer_as16[]);
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
static t_eReturnCode s_Irrig_GetActuatorsValues(t_sint16 f_ActuatorsContainer_as16[]);
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
static t_eReturnCode s_Irrig_GetSensorsValues(t_sint16 f_SensorsContainer_as16[]);

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

static void s_Irrig_SleepMode(void);
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
static void s_Irrig_WakeUpMode(void);
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
static void s_Irrig_ResetBuffer(char f_buffer_ac[], t_uint16 f_len_u16);
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
static t_eReturnCode s_Irrig_MasterConnection(t_eIrrig_CoState * f_CoState_e);
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
static t_eReturnCode s_Irrig_GetTask_FromMaster(const char *f_RcvData_pc);
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
static t_eReturnCode s_Irrig_ExtractMasterCmd(const char *f_RcvCmdMaster_pac, t_uint16 f_bufferSize_u16, t_sint16 f_container_sa16[]);
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
static t_eReturnCode s_Irrig_ModeAskTask(t_uint8 *f_counterProb_pu8);
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
static t_eReturnCode s_Irrig_ModeRcvActData(t_uint8 *f_counterProb_pu8);
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
static t_eReturnCode s_Irrig_ModeSetActData(t_uint8 *f_counterProb_pu8);
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
static t_eReturnCode s_Irrig_ModeSendSNSVal(t_uint8 *f_counterProb_pu8);
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
static t_eReturnCode s_Irrig_ModeWakeUp(t_uint8 *f_counterProb_pu8, t_eIrrig_CoState *f_ArdCostate_e);
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
static t_eReturnCode s_Irrig_ModeSetWorkMode(t_uint8 *f_counterProb_pu8, t_eIrrig_CoState *f_ArdCostate_e);
//****************************************************************************
//                      Public functions - Implementation
//********************************************************************************
/****************************
* LgcIrrig_Init
****************************/
t_eReturnCode LgcIrrig_Init(void)
{
    t_eReturnCode Ret_e = RC_OK;
    Ret_e = ACT_Init();
    Serial.print("ACT init : ");
    Serial.println(Ret_e);
    if(Ret_e == RC_OK)
    {
        g_ActuatorsInitialize_b = (t_bool)true;
        Serial.print("SNS init : ");
        Serial.println(Ret_e);
        Ret_e = SNS_Init();
    }
    if(Ret_e == RC_OK)
    {
        g_SensorsInitialize_b = (t_bool)true;
        attachInterrupt(digitalPinToInterrupt(IRRIG_WIFI_RX),s_Irrig_WakeUpMode,CHANGE);
    }
    if(Ret_e == RC_OK)
    {

        Ret_e = ArdCom_Init((t_eArdCom_TypeCom)c_ArduinoComUsed_e);
        Serial.print("ArdCom init : ");
        Serial.println(Ret_e);

    }
    if(Ret_e == RC_OK)
    {
        Serial.println("LogicIrrig done");

    }
    return Ret_e;
}
/****************************
* LgcIrrig_Cyclic
****************************/
t_eReturnCode LgcIrrig_Cyclic()
{
    t_eReturnCode Ret_e = RC_OK;

    static t_eIrrig_CoState s_ArdCoState_e = IRRIG_STATUS_UNKNOWN;

    static t_uint8 s_ctr_Problem_u8 = (t_uint8)0;
    static t_uint32 s_actualTime_CoStatue_u32 = millis();
 
    Serial.print("Arduino state :");
    Serial.println(g_ArduinoState_e);

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
            case IRRIG_ARDUINO_MODE_WAKEUP:
            {
                Ret_e = s_Irrig_ModeWakeUp(&s_ctr_Problem_u8, &s_ArdCoState_e);
                if(Ret_e == RC_OK)
                {
                    g_ArduinoState_e = IRRIG_ARDUINO_MODE_ASK_TASK;
                }
                break;                    
            }
            case IRRIG_ARDUINO_MODE_SLEEP:
            {//prepare and set the sleep
                Serial.println("About to go to sleep");
                delay(1000);
                s_Irrig_SleepMode();
                break;
            }
            case IRRIG_ARDUINO_MODE_ASK_TASK:
            {
                Ret_e = s_Irrig_ModeAskTask(&s_ctr_Problem_u8);
                break;
            }
            case IRRIG_ARDUINO_MODE_RCV_ACTUATORS_DATAS:
            {
                Ret_e = s_Irrig_ModeRcvActData(&s_ctr_Problem_u8);
                if(Ret_e == RC_OK)
                {
                    g_ArduinoState_e = IRRIG_ARDUINO_MODE_SET_ACTUATORS;
                }
                break;
            }
            case IRRIG_ARDUINO_MODE_SET_ACTUATORS:
            {
                Ret_e = s_Irrig_ModeSetActData(&s_ctr_Problem_u8);
                if(Ret_e == RC_OK)
                {
                    g_ArduinoState_e = IRRIG_ARDUINO_MODE_ASK_TASK;
                }
                break;
            }
            case IRRIG_ARDUINO_MODE_SEND_SENSORS_VALUES:
            {
                Ret_e = s_Irrig_ModeSendSNSVal(&s_ctr_Problem_u8);
                if(Ret_e == RC_OK)
                {
                    g_ArduinoState_e = IRRIG_ARDUINO_MODE_ASK_TASK;
                }
                break;
            }
            default: 
            {
                g_ArduinoState_e = IRRIG_ARDUINO_MODE_WAKEUP;                
                break;
            }
        }
        /*if(s_ctr_Problem_u8 > MAIN_ARDUINO_MAX_ERROR)
        {
            Serial.println("reset WatchDogs");
            //Reset Arduino using WatchDogs
            wdt_enable(WDTO_15MS);
            delay(150);
        }*/
        
    }
    Serial.print("Cyclic Value");
    Serial.println(Ret_e);
    return Ret_e;
}

 
//********************************************************************************
//                      Local functions - Implementation
//******************************************************************************** 
static t_eReturnCode s_Irrig_ModeWakeUp(t_uint8 *f_counterProb_pu8, t_eIrrig_CoState *f_ArdCostate_e)
{
    t_eReturnCode Ret_e = RC_OK;
    
    
    //re_initialize all Actuators value to default
    //read the task, sheduled it and go to the dedicated mode 
    // if there isn't go to default and make counter 
    //Make Wifi and TCP connection active
    if(f_counterProb_pu8 == NULL ||f_ArdCostate_e == NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        Ret_e = s_Irrig_MasterConnection(f_ArdCostate_e);
        Serial.print("Co State ");
        Serial.println(*f_ArdCostate_e);
        if(Ret_e == RC_OK)
        {   
            Ret_e = s_Irrig_ModeSetWorkMode(f_counterProb_pu8, f_ArdCostate_e);                       
        }
        else 
        {
            *f_counterProb_pu8 += 1;
        }
    }
    return Ret_e;
}
/****************************
* s_Irrig_GetTask_FromMaster
****************************/
static t_eReturnCode s_Irrig_ModeAskTask(t_uint8 *f_counterProb_pu8)
{
    t_eReturnCode Ret_e = RC_OK;
    char RcvServerData_ac[MODEM_MAX_BUFF_SIZE];
    s_Irrig_ResetBuffer(RcvServerData_ac, MODEM_MAX_BUFF_SIZE);
    Serial.print("Set task");
    Ret_e = s_Irrig_GetTask_FromMaster(RcvServerData_ac);
    Serial.println(Ret_e);
    Serial.print("Rcv :");
    Serial.println(RcvServerData_ac);
    if(f_counterProb_pu8 == NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {//see if Master wants sensors values or cmd relay 
        
        if(strstr(RcvServerData_ac, c_Arduino_SendSNSvalues_pac) != (char *)NULL)
        {
            Serial.print("Send sensors values");
            g_ArduinoState_e = IRRIG_ARDUINO_MODE_SEND_SENSORS_VALUES;
        }
        else if (strstr(RcvServerData_ac, c_Arduino_SetActuators_pac) != (char *)NULL)
        {
            
            g_ArduinoState_e = IRRIG_ARDUINO_MODE_RCV_ACTUATORS_DATAS;
        }                        
        else 
        {
            Serial.print("Set cmd check");
            Serial.println(RcvServerData_ac);
            Serial.println("Cmd Server not found");
            *f_counterProb_pu8 += 1;
            g_ArduinoState_e = IRRIG_ARDUINO_MODE_ASK_TASK;
        }
    }
    else
    {                                        
        *f_counterProb_pu8 += 1;
        // stay if ask Cmd 
    }
    return Ret_e;
}
/****************************
* s_Irrig_GetTask_FromMaster
****************************/
static t_eReturnCode s_Irrig_ModeRcvActData(t_uint8 *f_counterProb_pu8)
{
    t_eReturnCode Ret_e = RC_OK;
    t_uint8 LI_u8 = (t_uint8)0;
    char RcvServerData_ac[MODEM_MAX_BUFF_SIZE];
    if(f_counterProb_pu8 == NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        Ret_e = ArdCom_SendData(c_ArduinoComUsed_e, c_Arduino_RcvActuatorsValues_pac);
        if(Ret_e == RC_OK)
        {
            Serial.println("Wait for Actuators value ");
            delay(ARDUINO_WAIT_SERVER);
            Ret_e = ArdCom_RcvData(c_ArduinoComUsed_e, RcvServerData_ac);
            // chekc if ID correspond to what exepected i.e. the actuators values
        
            if( strstr(RcvServerData_ac, c_Arduino_RcvActuatorsValues_pac) != (char *)NULL)
            {// we rcv actuatorsd values
                // check here
                Serial.print("Exctraction actuators value");
                Ret_e = s_Irrig_ExtractMasterCmd((const char *)RcvServerData_ac, (t_uint16)strlen(RcvServerData_ac),g_actuatorsValue_sa16);
                Serial.println(Ret_e);
                if(Ret_e == RC_OK)
                {// we now receive Actuators duration
                    s_Irrig_ResetBuffer(RcvServerData_ac,MODEM_MAX_BUFF_SIZE);
                    Ret_e = ArdCom_SendData(c_ArduinoComUsed_e, c_Arduino_RcvActuatorsDuration_pac);
                    Serial.println(Ret_e);
                    if(Ret_e == RC_OK)
                    {
                        Serial.println("Wait for Actuators duration");
                        delay(ARDUINO_WAIT_SERVER);
                        Ret_e = ArdCom_RcvData(c_ArduinoComUsed_e, RcvServerData_ac);
                        if(strstr(RcvServerData_ac, c_Arduino_RcvActuatorsDuration_pac) != (char * )NULL)
                        {// check rcv actuators duration ok 
                            Serial.println("Exctraction actuators duration");
                            Ret_e = s_Irrig_ExtractMasterCmd((const char *)RcvServerData_ac,(t_uint16)strlen(RcvServerData_ac), g_actuatorsDuration_sa16);
                            for(LI_u8 = 0 ; LI_u8 < ACT_NUMBER ; LI_u8++)
                            {
                                Serial.println(g_actuatorsDuration_sa16[LI_u8]);
                            }
                            Serial.println(Ret_e);
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
            *f_counterProb_pu8 += (t_uint8)1;
        }
    }
    return Ret_e;
}
/****************************
* s_Irrig_ModeSetActData
****************************/
static t_eReturnCode s_Irrig_ModeSetActData(t_uint8 *f_counterProb_pu8)
{
    t_eReturnCode Ret_e = RC_OK;
    static t_uint32 s_actualTime_ActDuration_u32;
    static t_bool s_checkTimeDuration_b = (t_bool)false;
    t_uint8 LI_u8 = (t_uint8)0;
    static t_uint8 s_ctr_IrrigValve_Off_u8 = (t_uint8)0; 
    if(f_counterProb_pu8 == NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        //If here set actuatos values during actuators timings
        // first Set actuators values and then ckeck timeDuration to stop irrig
        if(s_checkTimeDuration_b == false)
        {
            Ret_e = s_Irrig_SetActuatorsValues(g_actuatorsValue_sa16);
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
                    Ret_e = ACT_Set((t_eACT_Actuators)LI_u8, (t_sint16)0);
                    if (Ret_e != RC_OK)
                    {
                        *f_counterProb_pu8 += (t_uint8)1;
                    }
                    g_actuatorsDuration_sa16[LI_u8] = (t_uint32)0;
                    s_ctr_IrrigValve_Off_u8 += (t_uint8)1;
                }
            }   
            if(s_ctr_IrrigValve_Off_u8 == (t_uint8)ACT_NUMBER)
            {// reset timer & passed to another state
                s_ctr_IrrigValve_Off_u8 = (t_uint8)0;
                s_actualTime_ActDuration_u32 = (t_uint32)0;
                s_checkTimeDuration_b = (t_bool)false;
                Ret_e = ArdCom_SendData(c_ArduinoComUsed_e, c_Arduino_ActTaskCompleted_pac);
            } 
        }
    }      
    return Ret_e;
}
/****************************
* s_Irrig_ModeSendSNSVal
****************************/
static t_eReturnCode s_Irrig_ModeSendSNSVal(t_uint8 *f_counterProb_pu8)
{
    t_eReturnCode Ret_e = RC_OK;
    t_uint8 LI_u8 = (t_uint8)0;
    String sendDataToMaster_str = "";
    //IF here send sensors values and go to sleep or make other things
    Serial.println("Get sensor value");
    Ret_e = s_Irrig_GetSensorsValues(g_sensorsValue_sa16);
    if(f_counterProb_pu8 == NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        sendDataToMaster_str = String(c_Arduino_SendSNSvalues_pac) + String(",");
        for(LI_u8 = 0 ; LI_u8 < (t_uint8)SNS_NUMBER ; LI_u8++)
        {
            sendDataToMaster_str += String(LI_u8)+ String("_") + String(c_SensorsTypeCfg_ae[LI_u8]) + String(":") + String(g_sensorsValue_sa16[LI_u8]);
            if(LI_u8 != (SNS_NUMBER) - 1)
            {
                sendDataToMaster_str += String(",");
            }
        }
        Ret_e = ArdCom_SendData(c_ArduinoComUsed_e, sendDataToMaster_str.c_str());
    }
    else
    {
        Ret_e = ArdCom_SendData(c_ArduinoComUsed_e, "ERROR WHEN TRYING GET DATA");
        *f_counterProb_pu8 += (t_uint8)1;
    }
    return Ret_e;
}
/****************************
* s_Irrig_ModeSetWorkMode
****************************/
static t_eReturnCode s_Irrig_ModeSetWorkMode(t_uint8 *f_counterProb_pu8, t_eIrrig_CoState *f_ArdCostate_e)
{
    t_eReturnCode Ret_e = RC_OK;
    String Cmd_WorkMode_str;
    Cmd_WorkMode_str = String("100:") + String(Ard_WorkMode_e);
    Ret_e = ArdCom_SendData(c_ArduinoComUsed_e, Cmd_WorkMode_str.c_str());
    return Ret_e;
}
/****************************
* s_Irrig_GetTask_FromMaster
****************************/
static t_eReturnCode s_Irrig_GetTask_FromMaster(const char *f_RcvData_pc)
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
        Ret_e = ArdCom_SendData(c_ArduinoComUsed_e, c_Arduino_AskCmd_pac);
        delay(ARDUINO_WAIT_SERVER);
        if(Ret_e == RC_OK)
        {
            Ret_e = ArdCom_RcvData(c_ArduinoComUsed_e, espResponse_ac);            
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
* s_Irrig_GetTask_FromMaster
****************************/
static t_eReturnCode s_Irrig_ExtractMasterCmd(const char *f_RcvCmdMaster_pac, t_uint16 f_bufferSize_u16, t_sint16 f_container_sa16[])
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
/****************************
* s_Irrig_ResetBuffer
****************************/
static void s_Irrig_ResetBuffer(char f_buffer_ac[], t_uint16 f_len_u16)
{
    memset(f_buffer_ac,'\0',f_len_u16);
}
/****************************
* s_Irrig_SleepMode
****************************/
static void s_Irrig_SleepMode(void)
{
    Serial.println("Go to sleepMode");
    delay(10000);
    digitalWrite(LED_BUILTIN,LOW);
    //Wake up here 
}
/****************************
* s_Irrig_WakeUpMode
****************************/
static void s_Irrig_WakeUpMode(void)
{
    digitalWrite(LED_BUILTIN,HIGH);
    Serial.println("Just waking up");
    g_ArduinoState_e = IRRIG_ARDUINO_MODE_WAKEUP;
}
/****************************
* s_Irrig_MasterConnection
****************************/
static t_eReturnCode s_Irrig_MasterConnection(t_eIrrig_CoState * f_CoState_e)
{
    t_eReturnCode Ret_e = RC_OK;
    Serial.println("MakeStartCom");
    Ret_e = ArdCom_StartCom(c_ArduinoComUsed_e);
    if(Ret_e == RC_OK)
    {
        *f_CoState_e = IRRIG_STATUS_CONNECTED;
    }
    else 
    {
        *f_CoState_e = IRRIG_STATUS_DISCONNECTED;
    }
    return Ret_e;
}
/****************************
* s_Irrig_SetActuatorsValues
****************************/
static t_eReturnCode s_Irrig_SetActuatorsValues(t_sint16 f_ActuatorsContainer_as16[])
{
    t_eReturnCode Ret_e = RC_OK;
    t_uint8 LI_u8;
    for(LI_u8 = (t_uint8)0 ; (t_uint8)LI_u8 < ACT_NUMBER && Ret_e == RC_OK; LI_u8++ )
    {
        Ret_e = ACT_Set((t_eACT_Actuators)LI_u8,(t_sint16)f_ActuatorsContainer_as16[LI_u8]);
    }
    return Ret_e;
}
/****************************
* s_Irrig_GetActuatorsValues
****************************/
static t_eReturnCode s_Irrig_GetActuatorsValues(t_sint16 f_ActuatorsContainer_as16[])
{
    t_eReturnCode Ret_e = RC_OK;
    t_uint8 LI_u8;
    for(LI_u8 = (t_uint8)0 ; (t_uint8)LI_u8 < ACT_NUMBER && Ret_e == RC_OK; LI_u8++ )
    {
        f_ActuatorsContainer_as16[LI_u8] = (t_sint16)0;
        Ret_e = ACT_Get((t_eACT_Actuators)LI_u8, &f_ActuatorsContainer_as16[LI_u8]);
    }
    return Ret_e;
}
/****************************
* s_Irrig_GetSensorsValues
****************************/
static t_eReturnCode s_Irrig_GetSensorsValues(t_sint16 f_SensorsContainer_as16[])
{
    t_eReturnCode Ret_e = RC_OK;
    t_uint8 LI_u8;
    for(LI_u8 = (t_uint8)0 ; (t_uint8)LI_u8 < SNS_NUMBER && Ret_e == RC_OK; LI_u8++ )
    {
        f_SensorsContainer_as16[LI_u8] = (t_sint16)0;
        Ret_e = SNS_Get((t_eSNSSPEC_Sensors)LI_u8, &f_SensorsContainer_as16[LI_u8]);
        if(Ret_e != RC_OK)
        {
            Serial.print(LI_u8);
            Serial.println(": Something's off, RetVal");
            Serial.println(Ret_e);
        }
    }
    return Ret_e;
}
//************************************************************************************
// End of File
//************************************************************************************

/**
 *
 *	@brief
 *	@details
 *
 *
 *	@params[in] 
 *	@params[out]
 *	 
 *
 *
 */
