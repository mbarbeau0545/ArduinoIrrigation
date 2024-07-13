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

#define ARDUINO_WAIT_ACT_EXCHANGE 500
#define ARDUINO_WAIT_TASK_FROM_SERVER 1500

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

t_uint8  g_counterProb_u8      = (t_uint8)0;

t_eIrrig_ArduinoState  g_ArduinoState_e = IRRIG_ARDUINO_MODE_WAKEUP;
t_eIrrig_CoState       g_ArdRaspCo_e    = IRRIG_STATUS_UNKNOWN;
//********************************************************************************
//                      Local functions - Prototypes
//********************************************************************************
static t_eReturnState s_Irrig_SetActuatorsValues(t_sint16 f_ActuatorsContainer_as16[]);
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
static t_eReturnState s_Irrig_GetActuatorsValues(t_sint16 f_ActuatorsContainer_as16[]);
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
static t_eReturnState s_Irrig_GetSensorsValues(t_sint16 f_SensorsContainer_as16[]);

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
static void s_Irrig_ResetBuffer( char f_buffer_ac[], t_uint16 f_len_u16);
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
static t_eReturnState s_Irrig_MasterConnection(void);
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
static t_eReturnState s_Irrig_GetTask_FromMaster(char *f_RcvData_pc);
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
static t_eReturnState s_Irrig_ExtractMasterCmd(char *f_RcvCmdMaster_pac, t_uint16 f_bufferSize_u16, t_sint16 f_container_sa16[]);
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
static t_eReturnState s_Irrig_ModeAskTask(void);
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
static t_eReturnState s_Irrig_ModeRcvActData(void);
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
static t_eReturnState s_Irrig_ModeSetActData(void);
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
static t_eReturnState s_Irrig_ModeSendSNSVal(void);
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
static t_eReturnState s_Irrig_ModeWakeUp(void);
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
static t_eReturnState s_Irrig_ModeSetWorkMode(void);
//****************************************************************************
//                      Public functions - Implementation
//********************************************************************************
/****************************
* LgcIrrig_Init
****************************/
t_eReturnState LgcIrrig_Init(void)
{
    t_eReturnState Ret_e = RC_OK;
    Ret_e = ACT_Init();
    DEBUG_PRINT("ACT init : ");
    DEBUG_PRINTLN(Ret_e);
    if(Ret_e == RC_OK)
    {
        g_ActuatorsInitialize_b = (t_bool)true;
        DEBUG_PRINT("SNS init : ");
        DEBUG_PRINTLN(Ret_e);
        Ret_e = SNS_Init();
    }
    if(Ret_e == RC_OK)
    {
        g_SensorsInitialize_b = (t_bool)true;
        //attachInterrupt(digitalPinToInterrupt(IRRIG_WIFI_RX),s_Irrig_WakeUpMode,CHANGE);
    }
    if(Ret_e == RC_OK)
    {

        Ret_e = ArdCom_Init((t_eArdCom_TypeCom)c_ArduinoComUsed_e);
        DEBUG_PRINT("ArdCom init : ");
        DEBUG_PRINTLN(Ret_e);

    }
    if(Ret_e == RC_OK)
    {
        DEBUG_PRINTLN("LogicIrrig done");

    }
    return Ret_e;
}
/****************************
* LgcIrrig_Cyclic
****************************/
t_eReturnState LgcIrrig_Cyclic()
{
    t_eReturnState Ret_e = RC_OK;
    static t_uint32 s_actualTime_CoStatue_u32 = millis();
 
    DEBUG_PRINT("Arduino state : ");
    DEBUG_PRINTLN(g_ArduinoState_e);

    if(g_SensorsInitialize_b != (t_bool)true || g_ActuatorsInitialize_b != (t_bool)true)
    {
        Ret_e = RC_ERROR_MODULE_NOT_INITIALIZED;
    }
    if(Ret_e == RC_OK)
    {
        // check if we have to actualize WifiStatue & Protocol statue
        /*DEBUG_PRINTLN("here");
        if((millis()  - s_actualTime_CoStatue_u32) > (t_uint32)MAIN_CHECK_CONNECT_STATUE)
        {
            Ret_e = ESP_Get_ProtocolCom_Cfg(&s_ESP_Cfg_s);AT+CIPSTART="TCP","192.168.1.27",80\r\r\n\r\nERROR\r\nCLOSED\r\n
            AT+CWJAP?\r\r\n+CWJ@P:"Livebox-0BB3","a4:3e951:09:0b:b3#,1,-71\r\n\r\nOK\r\n
        }*/
        switch(g_ArduinoState_e)
        {
            case IRRIG_ARDUINO_MODE_WAKEUP:
            {
                Ret_e = s_Irrig_ModeWakeUp();
                if(Ret_e == RC_OK)
                {
                    g_ArduinoState_e = IRRIG_ARDUINO_MODE_ASK_TASK;
                }
                break;                    
            }
            case IRRIG_ARDUINO_MODE_SLEEP:
            {//prepare and set the sleep
                DEBUG_PRINTLN("About to go to sleep");
                delay(1000);
                s_Irrig_SleepMode();
                break;
            }
            case IRRIG_ARDUINO_MODE_ASK_TASK:
            {
                Ret_e = s_Irrig_ModeAskTask();
                break;
            }
            case IRRIG_ARDUINO_MODE_RCV_ACTUATORS_DATAS:
            {
                Ret_e = s_Irrig_ModeRcvActData();
                if(Ret_e == RC_OK)
                {
                    g_ArduinoState_e = IRRIG_ARDUINO_MODE_SET_ACTUATORS;
                }
                break;
            }
            case IRRIG_ARDUINO_MODE_SET_ACTUATORS:
            {
                Ret_e = s_Irrig_ModeSetActData();
                if(Ret_e == RC_OK)
                {
                    g_ArduinoState_e = IRRIG_ARDUINO_MODE_ASK_TASK;
                }
                break;
            }
            case IRRIG_ARDUINO_MODE_SEND_SENSORS_VALUES:
            {
                Ret_e = s_Irrig_ModeSendSNSVal();
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
        if(g_counterProb_u8 > MAIN_ARDUINO_MAX_ERROR)
        {
            DEBUG_PRINTLN("reset WatchDogs");
            //Reset Arduino using WatchDogs
            //wdt_enable(WDTO_15MS);
            delay(150);
        }
        
    }
    DEBUG_PRINT("Cyclic Value : ");
    DEBUG_PRINTLN(Ret_e);
    return Ret_e;
}

 
//********************************************************************************
//                      Local functions - Implementation
//******************************************************************************** 
static t_eReturnState s_Irrig_ModeWakeUp(void)
{
    t_eReturnState Ret_e = RC_OK;
    
    
    //re_initialize all Actuators value to default
    //read the task, sheduled it and go to the dedicated mode 
    // if there isn't go to default and make counter 
    //Make Wifi and TCP connection active

    Ret_e = s_Irrig_MasterConnection();
    DEBUG_PRINT("Co State ");
    DEBUG_PRINTLN(g_ArdRaspCo_e);
    if(Ret_e == RC_OK)
    {   
        Ret_e = s_Irrig_ModeSetWorkMode();                       
    }
    else 
    {
        g_counterProb_u8 += 1;
    }
    
    return Ret_e;
}
/****************************
* s_Irrig_GetTask_FromMaster
****************************/
static t_eReturnState s_Irrig_ModeAskTask(void)
{
    t_eReturnState Ret_e = RC_OK;
    char RcvServerData_ac[MODEM_MAX_BUFF_SIZE];
    s_Irrig_ResetBuffer(RcvServerData_ac, MODEM_MAX_BUFF_SIZE);
    DEBUG_PRINT("Set task");
    Ret_e = s_Irrig_GetTask_FromMaster(RcvServerData_ac);
    DEBUG_PRINTLN(Ret_e);
    DEBUG_PRINT("Rcv :");
    DEBUG_PRINTLN(RcvServerData_ac);
    //see if Master wants sensors values or cmd relay  
    if(strstr(RcvServerData_ac, c_Arduino_SendSNSvalues_pac) != (char *)NULL)
    {
        DEBUG_PRINT("Send sensors values");
        g_ArduinoState_e = IRRIG_ARDUINO_MODE_SEND_SENSORS_VALUES;
    }
    else if(strstr(RcvServerData_ac, c_Arduino_SetActuators_pac) != (char *)NULL)
    {
        
        g_ArduinoState_e = IRRIG_ARDUINO_MODE_RCV_ACTUATORS_DATAS;
    }                        
    else 
    {
        DEBUG_PRINTLN("Cmd Server not found");
        g_counterProb_u8 += 1;
        g_ArduinoState_e = IRRIG_ARDUINO_MODE_ASK_TASK;
    }
    return Ret_e;
}
/****************************
* s_Irrig_GetTask_FromMaster
****************************/
static t_eReturnState s_Irrig_ModeRcvActData(void)
{
    t_eReturnState Ret_e = RC_OK;
    t_uint8 LI_u8 = (t_uint8)0;
    char RcvServerData_ac[MODEM_MAX_BUFF_SIZE];
    Ret_e = ArdCom_SendData(c_ArduinoComUsed_e, c_Arduino_RcvActuatorsValues_pac);
    if(Ret_e == RC_OK)
    {
        DEBUG_PRINTLN("Wait for Actuators value ");
        delay(ARDUINO_WAIT_ACT_EXCHANGE);
        Ret_e = ArdCom_RcvData(c_ArduinoComUsed_e, RcvServerData_ac);
        // chekc if ID correspond to what exepected i.e. the actuators values
    
        if( strstr(RcvServerData_ac, c_Arduino_RcvActuatorsValues_pac) != (char *)NULL)
        {// we rcv actuatorsd values
            // check here
            DEBUG_PRINT("Exctraction actuators value");
            Ret_e = s_Irrig_ExtractMasterCmd((char *)RcvServerData_ac, (t_uint16)strlen(RcvServerData_ac),g_actuatorsValue_sa16);
            DEBUG_PRINTLN(Ret_e);
            if(Ret_e == RC_OK)
            {// we now receive Actuators duration
                s_Irrig_ResetBuffer(RcvServerData_ac,MODEM_MAX_BUFF_SIZE);
                Ret_e = ArdCom_SendData(c_ArduinoComUsed_e, c_Arduino_RcvActuatorsDuration_pac);
                DEBUG_PRINTLN(Ret_e);
                if(Ret_e == RC_OK)
                {
                    DEBUG_PRINTLN("Wait for Actuators duration");
                    delay(ARDUINO_WAIT_ACT_EXCHANGE);
                    Ret_e = ArdCom_RcvData(c_ArduinoComUsed_e, RcvServerData_ac);
                    if(strstr(RcvServerData_ac, c_Arduino_RcvActuatorsDuration_pac) != (char * )NULL)
                    {// check rcv actuators duration ok 
                        DEBUG_PRINTLN("Exctraction actuators duration");
                        Ret_e = s_Irrig_ExtractMasterCmd((char *)RcvServerData_ac,(t_uint16)strlen(RcvServerData_ac), g_actuatorsDuration_sa16);
                        for(LI_u8 = 0 ; LI_u8 < ACT_NUMBER ; LI_u8++)
                        {
                            DEBUG_PRINTLN(g_actuatorsDuration_sa16[LI_u8]);
                        }
                        DEBUG_PRINTLN(Ret_e);
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
        g_counterProb_u8 += (t_uint8)1;
    }
    
    return Ret_e;
}
/****************************
* s_Irrig_ModeSetActData
****************************/
static t_eReturnState s_Irrig_ModeSetActData(void)
{
    t_eReturnState Ret_e = RC_OK;
    static t_uint32 s_actualTime_ActDuration_u32;
    static t_bool s_checkTimeDuration_b = (t_bool)false;
    t_uint8 LI_u8 = (t_uint8)0;
    static t_uint8 s_ctr_IrrigValve_Off_u8 = (t_uint8)0; 

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
                DEBUG_PRINTLN((millis() - s_actualTime_ActDuration_u32));
                DEBUG_PRINTLN(g_actuatorsDuration_sa16[LI_u8]* (t_uint32)SEC_IN_MIN);
                Ret_e = ACT_Set((t_eACT_Actuators)LI_u8, (t_sint16)0);
                if (Ret_e != RC_OK)
                {
                    g_counterProb_u8 += (t_uint8)1;
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
          
    return Ret_e;
}
/****************************
* s_Irrig_ModeSendSNSVal
****************************/
/****************************
* s_Irrig_ModeSendSNSVal
****************************/
static t_eReturnState s_Irrig_ModeSendSNSVal(void)
{
    t_eReturnState Ret_e = RC_OK;
    t_uint8 LI_u8 = (t_uint8)0;
    t_sint16 SNSVal_as16[SNS_NUMBER];
    char sendDataToMaster_ac[MODEM_MAX_BUFF_SIZE];
    char SNSNidx_ac[3]; // store the char number of SNS
    char SNSType_ac[3]; // store the char Sensors type
    char SNSVal_ac[MODEM_MAX_BUFF_SIZE/8]; //Store the char Sensors values
    
    //IF here send sensors values and go to sleep or make other things
    DEBUG_PRINTLN("Get sensor value");

    Ret_e = s_Irrig_GetSensorsValues(SNSVal_as16);
    if(Ret_e == RC_OK)
    {
        strcpy(sendDataToMaster_ac, c_Arduino_SendSNSvalues_pac);
        strcat(sendDataToMaster_ac, ",");
        for(LI_u8 = 0 ; LI_u8 < (t_uint8)SNS_NUMBER ; LI_u8++)
        {
            snprintf(SNSNidx_ac, sizeof(SNSNidx_ac), "%d", LI_u8);
            snprintf(SNSVal_ac,  sizeof(SNSVal_ac),  "%d", SNSVal_as16[LI_u8]);
            snprintf(SNSType_ac, sizeof(SNSType_ac), "%d", c_SensorsTypeCfg_ae[LI_u8]);

            strcat(sendDataToMaster_ac, SNSNidx_ac);
            strcat(sendDataToMaster_ac, "_");
            strcat(sendDataToMaster_ac, SNSType_ac);
            strcat(sendDataToMaster_ac, ":");
            strcat(sendDataToMaster_ac, SNSVal_ac);

            if(LI_u8 != (SNS_NUMBER) - 1)
            {
                strcat(sendDataToMaster_ac,",");
            }
        }
        Ret_e = ArdCom_SendData(c_ArduinoComUsed_e, sendDataToMaster_ac);
    }
    else
    {
        Ret_e = ArdCom_SendData(c_ArduinoComUsed_e, "ERROR WHEN TRYING GET DATA");
        g_counterProb_u8 += (t_uint8)1;
    }
    return Ret_e;
}
/****************************
* s_Irrig_ModeSetWorkMode
****************************/
static t_eReturnState s_Irrig_ModeSetWorkMode(void)
{
    t_eReturnState Ret_e = RC_OK;
    String Cmd_WorkMode_str;
    Cmd_WorkMode_str = String("100:") + String(Ard_WorkMode_e);
    Ret_e = ArdCom_SendData(c_ArduinoComUsed_e, Cmd_WorkMode_str.c_str());
    return Ret_e;
}
/****************************
* s_Irrig_GetTask_FromMaster
****************************/
static t_eReturnState s_Irrig_GetTask_FromMaster(char *f_RcvData_pc)
{
    t_eReturnState Ret_e = RC_OK;
    if(f_RcvData_pc == (char *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {        
        Ret_e = ArdCom_SendData(c_ArduinoComUsed_e, c_Arduino_AskCmd_pac);
        delay(ARDUINO_WAIT_TASK_FROM_SERVER);
        if(Ret_e == RC_OK)
        {
            Ret_e = ArdCom_RcvData(c_ArduinoComUsed_e, f_RcvData_pc);
        }        
    }
    return Ret_e;
}
/****************************
* s_Irrig_GetTask_FromMaster
****************************/
static t_eReturnState s_Irrig_ExtractMasterCmd(char *f_RcvCmdMaster_pac, t_uint16 f_bufferSize_u16, t_sint16 f_container_sa16[])
{
    t_eReturnState Ret_e = RC_OK;
    t_uint8 counter_u16 = 0;
    t_uint16 LI_u16;
    if(f_RcvCmdMaster_pac == (char * )NULL)
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
    DEBUG_PRINTLN("Go to sleepMode");
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
    DEBUG_PRINTLN("Just waking up");
    g_ArduinoState_e = IRRIG_ARDUINO_MODE_WAKEUP;
}
/****************************
* s_Irrig_MasterConnection
****************************/
static t_eReturnState s_Irrig_MasterConnection(void)
{
    t_eReturnState Ret_e = RC_OK;
    DEBUG_PRINTLN("MakeStartCom");
    Ret_e = ArdCom_StartCom(c_ArduinoComUsed_e);
    if(Ret_e == RC_OK)
    {
        g_ArdRaspCo_e = IRRIG_STATUS_CONNECTED;
    }
    else 
    {
        g_ArdRaspCo_e = IRRIG_STATUS_DISCONNECTED;
    }
    return Ret_e;
}
/****************************
* s_Irrig_SetActuatorsValues
****************************/
static t_eReturnState s_Irrig_SetActuatorsValues(t_sint16 f_ActuatorsContainer_as16[])
{
    t_eReturnState Ret_e = RC_OK;
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
static t_eReturnState s_Irrig_GetActuatorsValues(t_sint16 f_ActuatorsContainer_as16[])
{
    t_eReturnState Ret_e = RC_OK;
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
static t_eReturnState s_Irrig_GetSensorsValues(t_sint16 f_SensorsContainer_as16[])
{
    t_eReturnState Ret_e = RC_OK;
    t_uint8 LI_u8;
    for(LI_u8 = (t_uint8)0 ; (t_uint8)LI_u8 < SNS_NUMBER && Ret_e == RC_OK; LI_u8++ )
    {
        f_SensorsContainer_as16[LI_u8] = (t_sint16)0;
        Ret_e = SNS_Get((t_eSNSSPEC_Sensors)LI_u8, &f_SensorsContainer_as16[LI_u8]);
        if(Ret_e != RC_OK)
        {
            DEBUG_PRINT(LI_u8);
            DEBUG_PRINTLN(": Something's off, RetVal");
            DEBUG_PRINTLN(Ret_e);
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
