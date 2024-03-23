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

t_uint16 g_actuators_value_ua[ACT_NUMBER] = {
    (t_uint16)0,                    // ACT_CMD_IRRIGVALVE
};
t_uint16 g_sensors_value_ua[SNS_NUMBER];
t_bool   g_ActuatorsInitialize_b = (t_bool)false;
t_bool   g_SensorsInitialize_b = (t_bool)false;
t_eMain_ArduinoState g_ArduinoState_e = MAIN_ARDUINO_WAKEUP;
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
// ***************************************************************************
// *                      Class declaration
// ***************************************************************************

//****************************************************************************
//                      Public functions - Implementation
//****************************************************************************

//****************************************************************************
//                      Local functions - Implementation
//****************************************************************************
/****************************
* s_Main_SetActuatorsValues
****************************/
static t_eReturnCode s_Main_SetActuatorsValues(void)
{
    t_eReturnCode Ret_e = RC_OK;
    t_uint8 LI_u8;
    for(LI_u8 = (t_uint8)0 ; (t_uint8)LI_u8 < ACT_NUMBER && Ret_e == RC_OK; LI_u8++ )
    {
        Ret_e = g_Actuators_Set_apf[LI_u8](g_actuators_value_ua[LI_u8]);
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
        Ret_e = g_Actuators_Get_apf[LI_u8](&g_sensors_value_ua[LI_u8]);
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
        Ret_e = g_Sensors_Get_apf[LI_u8](&g_sensors_value_ua[LI_u8]);
        if(Ret_e != RC_OK)
        {
            Serial.println("Something's off");
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
    Serial.begin(9600);
    //make all config in once
    t_eReturnCode Ret_e = RC_OK;
    t_uint8 LI_u8;
    /*for( LI_u8 = 0 ; LI_u8 < ACT_NUMBER && Ret_e == RC_OK; LI_u8++)
    {        
        Ret_e = (*g_Actuators_Cfg_apf[LI_u8])(g_ActuatorsPin_ua[LI_u8],g_Actuators_PinMode_ea[LI_u8]);
    }
    if(LI_u8 == ACT_NUMBER && Ret_e ==  RC_OK)
    {
        g_ActuatorsInitialize_b = (t_bool)true;
        Ret_e = RC_ERROR_MODULE_NOT_INITIALIZED;
    }
    for(LI_u8 = 0 ; LI_u8 < SNS_NUMBER  && Ret_e == RC_OK ; LI_u8++)
    {
        Ret_e = (*g_Sensors_Cfg_apf[LI_u8])(g_SensorsPin_ua[LI_u8], g_Actuators_PinMode_ea[LI_u8]);
    }
    if(LI_u8 == SNS_NUMBER && Ret_e ==  RC_OK)
    {
        g_ActuatorsInitialize_b = (t_bool)true;
        Ret_e = RC_ERROR_MODULE_NOT_INITIALIZED;
    }*/
    //initiate Communication SPI
    /*Ret_e = SNS_AirMoisture_Cfg(13, PINMODE_INPUT);
    Serial.println(Ret_e);
    SNS_AirTemp_Cfg(13,PINMODE_INPUT);
    Serial.println(Ret_e);
    SNS_SoilMoisture_Cfg(A0,PINMODE_INPUT);
    Serial.println(Ret_e);
    ACT_Cmd_IrrigValve_Cfg(12,PINMODE_OUTPUT);*/
    for(LI_u8 = 0 ; LI_u8 < SNS_NUMBER && Ret_e == RC_OK ; LI_u8++)
    {
        Ret_e = (g_Sensors_Cfg_apf[LI_u8])(g_SensorsPin_ua[LI_u8], g_Sensors_PinMode_ea[LI_u8]);
        if(Ret_e != RC_OK)
        {
            Serial.println("Problem in CfgSensor");
            Serial.println(Ret_e);
            Serial.println(LI_u8);
        }
    }
    for(LI_u8 = 0 ; LI_u8 < ACT_NUMBER && Ret_e == RC_OK ; LI_u8++)
    {
        Ret_e = (g_Actuators_Cfg_apf[LI_u8])(g_ActuatorsPin_ua[LI_u8], g_Actuators_PinMode_ea[LI_u8]);
        if(Ret_e != RC_OK)
        {
            Serial.println("Problem in CfgActuator");
        }
    }
}

// ********************************************************************
// *                       loop implmentation
// ********************************************************************
void loop() 
{
    t_eReturnCode Ret_e = RC_OK;
    t_uint8 LI_u8;
    Ret_e = s_Main_GetSensorsValues();
    if(Ret_e != RC_OK)
    {
        Serial.println("IN main also off");
    }
    for(LI_u8 = 0 ; LI_u8 < SNS_NUMBER ; LI_u8++)
    {
        Serial.print(LI_u8);
        Serial.print(" : ");
        Serial.println(g_sensors_value_ua[LI_u8]);
    }
    if(g_sensors_value_ua[SNS_AIRMOISTURE] < (t_uint16)50)
    {
        ACT_Cmd_IrrigValve_Set((t_uint16)HIGH);
    }
    else 
    {
        ACT_Cmd_IrrigValve_Set((t_uint16)LOW);
    }
    delay(2000);
    /*t_uint16 soilMoisture_u16;
    t_uint16 airMoisture_u16;
    t_uint16 airTemperature_u16;
    Ret_e = SNS_SoilMoisture_Get(&soilMoisture_u16);
    Serial.print("RetCode soilMoist:");
    Serial.println(Ret_e);
    Serial.print("Value soilmoist :");
    Serial.print(soilMoisture_u16);
    Serial.println("%");
    delay(1000);
    Ret_e = SNS_AirMoisture_Get(&airMoisture_u16);
    Serial.print("RetCode airMoist:");
    Serial.println(Ret_e);
    Serial.print("Value in airmoist :");
    Serial.print(airMoisture_u16);
    Serial.println("%");
    delay(1000);
    Ret_e = SNS_AirTemp_Get(&airTemperature_u16);
    Serial.print("RetCode airTemp:");
    Serial.println(Ret_e);
    Serial.print("Value in airtemp :");
    Serial.print(airTemperature_u16);
    Serial.println("%");
    delay(1000);
    ACT_Cmd_IrrigValve_Set((t_uint16)HIGH);
    delay(1000);
    ACT_Cmd_IrrigValve_Set((t_uint16)LOW);
    /*t_eReturnCode Ret_e = RC_OK;
    t_uint16 humidity_f32;
    t_uint16 temperature_f32;
    Ret_e = SNS_AirMoisture_Get(&humidity_f32);
    Serial.print("RetCode Moist:");
    Serial.println(Ret_e);
    Ret_e = SNS_AirTemp_Get(&temperature_f32);
    Serial.print("RetCode Temp:");
    Serial.println(Ret_e);
    Serial.print("Value in main_moist :");
    Serial.println(humidity_f32);
    Serial.print("Value in main temp:");
    Serial.println(temperature_f32);*/
    /*if(g_SensorsInitialize_b != (t_bool)true || g_ActuatorsInitialize_b != (t_bool)true)
    {
        Ret_e = RC_ERROR_MODULE_NOT_INITIALIZED;
    }
    if(Ret_e == RC_OK)
    {
        switch(g_ArduinoState_e)
        {
            case MAIN_ARDUINO_WAKEUP:
            {//re_initialize all Actuators value to default
                //read the task, sheduled it and go to the dedicated mode 
                // if there isn't go to default and make counter 
                break;
                
            }
            case MAIN_ARDUINO_SLEEP:
            {//prepare and set the sleep
                break;

            }
            case MAIN_ARDUINO_SEND_SENSORS_VALUES:
            {//IF here send sensors values and go to sleep or make other things
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
    }*/
    
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