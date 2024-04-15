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
#include "AppCommon/TypeCommon.h"
#include "ConfigSpecific/Sensors_ConfigSpecific.h"
#include "ConfigSpecific/Actuators_ConfigSpecific.h"
// ********************************************************************
// *                      Defines
// ********************************************************************
#define MAIN_SERIAL_BAUDRATE 115200
// ********************************************************************
// *                      Types
// ********************************************************************
typedef enum 
{
    MAIN_ARDUINO_SLEEP,
    MAIN_ARDUINO_WAKEUP,
    MAIN_ARDUINO_SEND_SENSORS_VALUES,
    MAIN_ARDUINO_SET_CMD,

}t_eMain_ArduinoState;

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
t_bool   g_ActuatorsInitialize_b = (t_bool)false;
t_bool   g_SensorsInitialize_b = (t_bool)false;
t_eMain_ArduinoState g_ArduinoState_e = MAIN_ARDUINO_WAKEUP;

const t_uint8 pinSleepMode_u8 = 2;
// ********************************************************************
// *                      Constants
// ********************************************************************

// ********************************************************************
// *                      Variables
// ********************************************************************

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
static t_eReturnCode s_Main_SetActuatorsValues(t_sint16 f_ActuatorsValue_sa16[]);
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
static void s_Main_SleepMode(void);
static void s_Main_WakeUpMode(void);
// ***************************************************************************
// *                      Class declaration
// ***************************************************************************

//****************************************************************************
//                      Public functions - Implementation
//****************************************************************************

//****************************************************************************
//                      Local functions - Implementation
//****************************************************************************
static void s_Main_SleepMode(void)
{
    Serial.println("Go to sleepMode");
    delay(1000);
    digitalWrite(LED_BUILTIN,LOW);
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_mode();
    
    //Wake up here 
}
static void s_Main_WakeUpMode(void)
{
    digitalWrite(LED_BUILTIN,HIGH);
    Serial.println("Just waking up");
    g_ArduinoState_e = MAIN_ARDUINO_WAKEUP;
}
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
    for(LI_u8 = 0 ; LI_u8 < ACT_NUMBER && Ret_e == RC_OK ; LI_u8++)
    {
        Ret_e = (c_SysActCfg_as[LI_u8].ActCfg_pcb)(c_ActuatorsPin_ua8[LI_u8], c_Actuators_PinMode_ea[LI_u8]);
        if(Ret_e != RC_OK)
        {
            Serial.println("Problem in CfgActuator");
        }
    }
    return Ret_e;
}
/****************************
* s_Main_SetActuatorsValues
****************************/
static t_eReturnCode s_Main_SetActuatorsValues(t_sint16 f_ActuatorsValue_sa16[])
{
    t_eReturnCode Ret_e = RC_OK;
    t_uint8 LI_u8;
    if(f_ActuatorsValue_sa16 == (t_sint16)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
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
* s_Main_SendSensorsValues
****************************/
static t_eReturnCode s_Main_SendSensorsValues(void)
{
    t_eReturnCode Ret_e = RC_OK;
    return Ret_e;
}
/****************************
* s_Main_GetTask_FromMaster
****************************/
static t_eReturnCode s_Main_GetTask_FromMaster(void)
{
    t_eReturnCode Ret_e = RC_OK;
    return Ret_e;
}
// ********************************************************************
// *                       setup implementation 
// ********************************************************************
void setup() 
{
    Serial.begin(MAIN_SERIAL_BAUDRATE);
    attachInterrupt(digitalPinToInterrupt(pinSleepMode_u8),s_Main_WakeUpMode,CHANGE);
    //make all config in once
    t_eReturnCode Ret_e = RC_OK;
    Ret_e = s_Main_SetSNS_ACT_Cfg();
    if(Ret_e == RC_OK)
    {
        Serial.println("Cfg Senssor OK.");
        g_SensorsInitialize_b = (t_bool)true;
    }
}

// ********************************************************************
// *                       loop implmentation
// ********************************************************************
void loop() 
{
    t_eReturnCode Ret_e = RC_OK;
    t_uint8 LI_u8;
    if(g_SensorsInitialize_b != (t_bool)true)
    {
        Serial.println("Cfg sensor Error.");
    }
    else
    {
        if(Ret_e != RC_OK)
        {
            Serial.println("In main also off");
        }
        if(Ret_e == RC_OK)
        {
            switch(g_ArduinoState_e)
            {
                case MAIN_ARDUINO_WAKEUP:
                {//re_initialize all Actuators value to default
                    //read the task, sheduled it and go to the dedicated mode 
                    // if there isn't go to default and make counter 
                    g_ArduinoState_e = MAIN_ARDUINO_SEND_SENSORS_VALUES;
                    Serial.println("Change my state");
                    break;
                    
                }
                case MAIN_ARDUINO_SLEEP:
                {//prepare and set the sleep
                    Serial.println("About to go to sleep");
                    delay(1000);
                    s_Main_SleepMode();
                    break;
                }
                case MAIN_ARDUINO_SEND_SENSORS_VALUES:
                {//IF here send sensors values and go to sleep or make other things
                    Serial.println("Get sensor value");
                    Ret_e = s_Main_GetSensorsValues();
                    for(LI_u8 = (t_uint8)0 ; LI_u8 < (t_uint8)SNS_NUMBER ; LI_u8++)
                    {
                        Serial.print(LI_u8);
                        Serial.print(" : ");
                        Serial.println(g_sensorsValue_sa16[LI_u8]);
                    }
                    delay(1000);
                    g_ArduinoState_e = MAIN_ARDUINO_WAKEUP;
                    break;
                }
                case MAIN_ARDUINO_SET_CMD:
                {//If here set command from receive cmd or what it is scheduled and then do other things
                    break;
                }
                default: 
                {
                    g_ArduinoState_e = MAIN_ARDUINO_WAKEUP;                
                    break;
                }
            }
        }
    }
    
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