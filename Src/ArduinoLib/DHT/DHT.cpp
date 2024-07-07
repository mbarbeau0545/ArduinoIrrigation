/*********************************************************************
 * @file        DHT.h
 * @brief       Template_BriefDescription.
 * @details     TemplateDetailsDescription.\n
 *
 * @author      xxxxxx
 * @date        jj/mm/yyyy
 * @version     1.0
 *********************************************************************/

// ********************************************************************
// *                      Includes
// ********************************************************************
#include "DHT.h"
// ********************************************************************
// *                      Defines
// ********************************************************************
//#define DHT_DEBUG

#define MIN_INTERVAL 2000 // minimun intervall between to measure
#define TIMEOUT UINT32_MAX //max time waiting for AM2302 to response
#define MAX_TASK_REFUSE (t_uint8)100
// ********************************************************************
// *                      Types
// ********************************************************************


typedef struct 
{
    t_uint8 pin_u8;
    t_eDHT_SensorType sensorType_e;
    t_uint8 sendBit_u8;
    t_uint8 sendPort_u8; 
}t_sDHT_SensorCfg;

typedef struct
{ 
    t_uint32 maxCycles_u32;
    t_uint8 pullTime_u8;
    t_uint32 lastReadTime_u32;
}t_sDHT_SensorTiming;

// ********************************************************************
// *                      Prototypes
// ********************************************************************
    
// ********************************************************************
// *                      Variables
// ********************************************************************
t_bool g_ModuleInitialized_b = false;

t_sDHT_SensorCfg  g_sensorCfg_s;
t_sDHT_SensorTiming g_sensorTime_s;

t_uint8 g_dataSensor_ua8[5];
//********************************************************************************
//                      Local functions - Prototypes
//********************************************************************************
/**
 *
 *	@brief      Say if the pulse is HIGH or LOW
 *	@details
 *
 *
 *	@param[in] 
 *	@param[out]
 *	 
 *
 *
 */
//t_uint32 DHT_ExpectPulse(bool level);
t_eReturnCode DHT_ExpectPulse(t_bool level, t_uint32 *f_counter_u32);
//******************************************************************************** 
//                      Public functions - Implementation
//********************************************************************************
/**********************
* DHT_Init
***********************/
t_eReturnCode DHT_Init(t_uint8 f_pin_u8, t_eDHT_SensorType f_Sensortype_e, t_uint8 f_count_u8)
{
    t_eReturnCode Ret_e = RC_OK;
    if(f_Sensortype_e < (t_uint8)0 || f_Sensortype_e > (t_uint8)DHT_SENSOR_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(Ret_e == RC_OK)
    {
        g_sensorCfg_s.pin_u8 = (t_uint8)f_pin_u8;
        g_sensorCfg_s.sensorType_e = (t_eDHT_SensorType)f_Sensortype_e;
        g_sensorCfg_s.sendBit_u8 = (t_uint8)digitalPinToBitMask(f_pin_u8);
        g_sensorCfg_s.sendPort_u8  = (t_uint8)digitalPinToPort(f_pin_u8);
        g_sensorTime_s.maxCycles_u32 = microsecondsToClockCycles(1000);
        g_ModuleInitialized_b = (t_bool)true;
    }
    return Ret_e;
}
/**********************
* DHT_begin
***********************/
t_eReturnCode DHT_begin(t_uint8 f_pullTimeSec_u8)
{
    t_eReturnCode Ret_e = RC_OK;
    if(g_ModuleInitialized_b == true)
    {
        //set ut the pins : Host pull low 1ms min, 10ms max
        //When communication between MCU and AM2302 begins, MCU will
        //pull lowdata-bus and this process must beyond at least 1~10ms to ensure AM2302 could detect MCU's signal, then
        //MCU will pulls up and wait 20-40us for AM2302's response
        pinMode(g_sensorCfg_s.pin_u8, INPUT_PULLUP);
        g_sensorTime_s.lastReadTime_u32 = (t_uint32)(millis() - MIN_INTERVAL);
        g_sensorTime_s.pullTime_u8 = (t_uint8)f_pullTimeSec_u8;
    }
    else
    {
        Ret_e = RC_ERROR_MODULE_NOT_INITIALIZED;
    }
    return Ret_e;
}
/**********************
* DHT_ReadTemperature
***********************/
t_eReturnCode DHT_ReadTemperature(t_float32 *f_tempValue_pf32, t_bool f_forcedMode_b)
{
    t_eReturnCode Ret_e = RC_OK;
    t_bool lastResult_b;
    static t_uint8 counterTaskResfuse_u8 = (t_uint8)0;
    if(f_tempValue_pf32 == NULL)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(g_ModuleInitialized_b == (t_bool)false)
    {
        Ret_e = RC_ERROR_MODULE_NOT_INITIALIZED;
    }
    if(Ret_e == RC_OK)
    {
        counterTaskResfuse_u8 = (t_uint8)0;
        Ret_e = DHT_ReadSensor( &lastResult_b, f_forcedMode_b);
        if(lastResult_b == (t_bool)true && Ret_e == RC_OK)
        {
            switch(g_sensorCfg_s.sensorType_e)
            {
                case DHT_SENSOR_11:
                {
                    (*f_tempValue_pf32) = g_dataSensor_ua8[2];
                    if(g_dataSensor_ua8[3] & 0x08)
                    {
                        (*f_tempValue_pf32) = (-1 - (*f_tempValue_pf32));
                    }
                    (*f_tempValue_pf32) += (g_dataSensor_ua8[3] & 0x0F) * 0.1;
                    break;
                }
                case DHT_SENSOR_12:
                {
                    (*f_tempValue_pf32) = g_dataSensor_ua8[2];
                    (*f_tempValue_pf32) += (g_dataSensor_ua8[3] & 0x0F) * 0.1;
                    if(g_dataSensor_ua8[2] & 0x08)
                    {
                        (*f_tempValue_pf32) *= -1;
                    }
                    break;
                }
                case DHT_SENSOR_21:
                {
                    (*f_tempValue_pf32) = ((word)(g_dataSensor_ua8[2] & 0x7F)) << 8 | g_dataSensor_ua8[3];
                    (*f_tempValue_pf32) *= 0.1;
                    if(g_dataSensor_ua8[2] & 0x08)
                    {
                        (*f_tempValue_pf32) *= -1;
                    }
                    break;
                }
                case DHT_SENSOR_22:
                {    
                    (*f_tempValue_pf32) = ((word)(g_dataSensor_ua8[2] & 0x7F)) << 8 | g_dataSensor_ua8[3];
                    (*f_tempValue_pf32) *= 0.1;
                    if(g_dataSensor_ua8[2] & 0x80)
                    {
                        (*f_tempValue_pf32) *= -(t_float32)1;
                    }
                    break;
                }
                case DHT_SENSOR_NB:
                {    
                    break;
                }
                default:
                {
                    break;
                }
            }
        }        
    }
    else
    {
        counterTaskResfuse_u8 += (t_uint8)1;
        Ret_e = RC_ERROR_BUSY;
    }
    if(counterTaskResfuse_u8 >= (t_uint8)MAX_TASK_REFUSE && Ret_e != RC_OK)
    {
        g_ModuleInitialized_b = (t_bool)false;
    }
    return Ret_e;
}
/**********************
* DHT_ReadMoisture
***********************/
t_eReturnCode DHT_ReadMoisture(t_float32 *f_moistValue_pf32, t_bool f_forcedMode_b)
{
    t_eReturnCode Ret_e = RC_OK;
    t_bool lastResult_b;
    static t_uint8 counterTaskResfuse_u8;
    if(g_ModuleInitialized_b == (t_bool)false)
    {
        Ret_e = RC_ERROR_MODULE_NOT_INITIALIZED;
    }
    if(f_moistValue_pf32 == (t_float32 *)NULL)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(Ret_e == RC_OK)
    {
        counterTaskResfuse_u8 = (t_uint8)0;
        Ret_e = DHT_ReadSensor( &lastResult_b, f_forcedMode_b);
        if(lastResult_b == (t_bool)true && Ret_e == RC_OK)
        {
            switch(g_sensorCfg_s.sensorType_e)
            {
                case DHT_SENSOR_11:
                {
                    (*f_moistValue_pf32) = (t_float32)(g_dataSensor_ua8[0]  + g_dataSensor_ua8[1] * (t_uint8)0.1);
                    break;
                }
                case DHT_SENSOR_12:
                {
                    (*f_moistValue_pf32) = (t_float32)(g_dataSensor_ua8[0]  + g_dataSensor_ua8[1] * (t_uint8)0.1);
                    break;
                }
                case DHT_SENSOR_21:
                {
                    (*f_moistValue_pf32) = ((word)g_dataSensor_ua8[0]) << 8 | g_dataSensor_ua8[1];
                    (*f_moistValue_pf32) *= (t_float32)0.1;
                    break;
                }
                case DHT_SENSOR_22:
                {    
                    (*f_moistValue_pf32) = ((word)g_dataSensor_ua8[0]) << 8 | g_dataSensor_ua8[1];
                    (*f_moistValue_pf32) *= (t_float32)0.1;
                    break;
                }
                case DHT_SENSOR_NB:
                {    
                    break;
                }
                default:
                {
                    delay(20);
                    break;
                }
            }
        }
        else 
        {
            counterTaskResfuse_u8 += (t_uint8)1;
            Ret_e = RC_ERROR_BUSY;
        }
    }
    if(counterTaskResfuse_u8 >= (t_uint8)MAX_TASK_REFUSE && Ret_e != RC_OK)
    {
        g_ModuleInitialized_b = (t_bool)false;
    }
    return Ret_e;
}
/**********************
* DHT_ReadSensor
***********************/
t_eReturnCode DHT_ReadSensor(t_bool *f_lastResult_b ,t_bool f_forcedMode_b)
{
    t_eReturnCode Ret_e = RC_OK;
    t_uint32 current_time_u32 = millis();
    t_uint8 LI_U8;
    t_uint32 cycles_ua32[80];
    t_uint32 ExpectPulseValue_u32;
    t_uint32 lowCycles_u32;
    t_uint32 highCycles_u32;
    if (f_lastResult_b == NULL)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    else if (g_ModuleInitialized_b == false)
    {
        Ret_e = RC_ERROR_MODULE_NOT_INITIALIZED;
    }
    if(Ret_e == RC_OK)
    {
        if(f_forcedMode_b == false && (current_time_u32 - g_sensorTime_s.lastReadTime_u32) < MIN_INTERVAL)
        {
            *f_lastResult_b = (t_bool)true;
        }
        else
        {
            g_sensorTime_s.lastReadTime_u32 = current_time_u32;
            // Reset 40 bits of received data to zero.
            for(LI_U8 = (t_uint8)0 ; LI_U8 < (t_uint8)5; LI_U8++)
            {
                g_dataSensor_ua8[LI_U8] = (t_uint8)0;
            }
            // Go into high impedence state to let pull-up raise data line level and
            // start the reading process.
            pinMode(g_sensorCfg_s.pin_u8, INPUT_PULLUP);
            delay(1);
            // First set data line low for a period according to sensor type
            pinMode(g_sensorCfg_s.pin_u8, OUTPUT);
            digitalWrite(g_sensorCfg_s.pin_u8, LOW);
            switch(g_sensorCfg_s.sensorType_e)
            {
                case DHT_SENSOR_11:
                {
                    delay(20);
                    break;
                }
                case DHT_SENSOR_12:
                {
                    delay(20);
                    break;
                }
                case DHT_SENSOR_21:
                {
                    // data sheet says "at least 1ms"
                    delayMicroseconds(1100);
                    break;
                }
                case DHT_SENSOR_22:
                {   
                    // data sheet says "at least 1ms"
                    delayMicroseconds(1100); 
                    break;
                }
                case DHT_SENSOR_NB:
                {    
                    break;
                }
                default:
                {
                    delay(20);
                    break;
                }
            }
            // End the start signal by setting data line high for 40 microseconds.
            pinMode(g_sensorCfg_s.pin_u8, INPUT_PULLUP);
            // Delay a moment to let sensor pull data line low.
            delayMicroseconds(g_sensorTime_s.pullTime_u8);
            // Now start reading the data line to get the value from the DHT sensor.

            // Turn off interrupts temporarily because the next sections
            // are timing critical and we don't want any interruptions.
            InterruptLock lock;
            Ret_e = DHT_ExpectPulse(LOW, &ExpectPulseValue_u32);
            //ExpectPulseValue_u32 = DHT_ExpectPulse(LOW);
            if(Ret_e == RC_OK && ExpectPulseValue_u32 == TIMEOUT)
            {
                *f_lastResult_b = false;
            }
            Ret_e = DHT_ExpectPulse(HIGH, &ExpectPulseValue_u32);
            //ExpectPulseValue_u32 = DHT_ExpectPulse(HIGH);
            if(Ret_e == RC_OK && ExpectPulseValue_u32 == TIMEOUT)
            {
                *f_lastResult_b = false;
            }
            else
            {
                //everythin' ok 
                // Now read the 40 bits sent by the sensor.  Each bit is sent as a 50
                // microsecond low pulse followed by a variable length high pulse.  If the
                // high pulse is ~28 microseconds then it's a 0 and if it's ~70 microseconds
                // then it's a 1.  We measure the cycle count of the initial 50us low pulse
                // and use that to compare to the cycle count of the high pulse to determine
                // if the bit is a 0 (high state cycle count < low state cycle count), or a
                // 1 (high state cycle count > low state cycle count). Note that for speed
                // all the pulses are read into a array and then examined in a later step.
                for(LI_U8 = 0 ; LI_U8 < (t_uint8)80 && Ret_e == RC_OK ; LI_U8 += (t_uint8)2)
                {
                    //cycles_ua32[LI_U8] = DHT_ExpectPulse(LOW);
                    //cycles_ua32[LI_U8+1] = DHT_ExpectPulse(HIGH);
                    Ret_e = DHT_ExpectPulse(LOW, &cycles_ua32[LI_U8]);
                    Ret_e = DHT_ExpectPulse(HIGH, &cycles_ua32[LI_U8 + (t_uint8)1]);
                }
                // Timing critical code is now complete
                // Inspect pulses and determine which ones are 0 (high state cycle count < low
                // state cycle count), or 1 (high state cycle count > low state cycle count).
                if(Ret_e == RC_OK)
                {
                    for(LI_U8 = 0 ; LI_U8 < (t_uint8)40 ; ++LI_U8)
                    {
                        lowCycles_u32 = cycles_ua32[2 * LI_U8];
                        highCycles_u32 = cycles_ua32[2 * LI_U8 + (t_uint8)1];
                        if(lowCycles_u32 == TIMEOUT || highCycles_u32 == TIMEOUT)
                        {
                            *f_lastResult_b = (t_bool)false;
                            break;
                        }
                        else 
                        {
                            g_dataSensor_ua8[LI_U8 / (t_uint8)8] <<=1;
                            // Now compare the low and high cycle times to see if the bit is a 0 or 1.
                            if( highCycles_u32 > lowCycles_u32)
                            {
                                g_dataSensor_ua8[LI_U8 / (t_uint8)8] |= 1;
                            }
                            // Else high cycles are less than (or equal to, a weird case) the 50us low
                            // cycle count so this must be a zero.  Nothing needs to be changed in the
                            // stored data.
                        }                        
                    }
                    if(g_dataSensor_ua8[4]  == ((g_dataSensor_ua8[3] + g_dataSensor_ua8[2] + 
                                                    g_dataSensor_ua8[1] + g_dataSensor_ua8[0]) & 0xFF))
        
                    {
                        *f_lastResult_b = (t_bool)true;
                    }
                    else
                    {
                        Ret_e = RC_ERROR_WRONG_RESULT;
                        *f_lastResult_b = (t_bool)false;
                    }
                }
            }
        }
    }
    #ifdef DHT_DEBUG
    DEBUG_PRINT("Cycles :");
    for(LI_U8 = 0 ; LI_U8 < (t_uint8)80 ; LI_U8 += (t_uint8)2)
    {
        
        DEBUG_PRINTLN(cycles_ua32[LI_U8])
        DEBUG_PRINTLN(cycles_ua32[LI_U8 + 1])
    }
    
    DEBUG_PRINTLN(F("Received from DHT:"));
    DEBUG_PRINT(g_dataSensor_ua8[0], HEX);
    DEBUG_PRINT(F(", "));
    DEBUG_PRINT(g_dataSensor_ua8[1], HEX);
    DEBUG_PRINT(F(", "));
    DEBUG_PRINT(g_dataSensor_ua8[2], HEX);
    DEBUG_PRINT(F(", "));
    DEBUG_PRINT(g_dataSensor_ua8[3], HEX);
    DEBUG_PRINT(F(", "));
    DEBUG_PRINT(g_dataSensor_ua8[4], HEX);
    DEBUG_PRINT(F(" =? "));
    DEBUG_PRINTLN(F("Retval DHT_ReadSensor:"));
    DEBUG_PRINTLN(Ret_e);
    #endif
    return Ret_e;
}
//********************************************************************************
//                      Local functions - Implementation
//********************************************************************************
/**********************
* DHT_ExpectPulse
***********************/
t_eReturnCode DHT_ExpectPulse(t_bool f_voltageLevel_b, t_uint32 *f_counter_u32) 
{
    t_eReturnCode Ret_e = RC_OK;
    t_uint32 counter_u32 = (t_uint16)0;
    t_uint8 portState_u8;
    if(g_ModuleInitialized_b == (t_bool)false)
    {
        Ret_e = RC_ERROR_MODULE_NOT_INITIALIZED;
    }
    if(f_voltageLevel_b != HIGH && f_voltageLevel_b != LOW)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(f_counter_u32 ==(t_uint32 *)NULL)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(Ret_e == RC_OK)
    {
        // F_CPU is not be known at compile time on platforms such as STM32F103.
        // The preprocessor seems to evaluate it to zero in that case.
        //t_uint16 count = 0; // To work fast enough on slower AVR boards
        // On AVR platforms use direct GPIO port access as it's much faster and better
        // for catching pulses that are 10's of microseconds in length:
        portState_u8 = f_voltageLevel_b ? g_sensorCfg_s.sendBit_u8 : 0;
        while ((*portInputRegister(g_sensorCfg_s.sendPort_u8) &  g_sensorCfg_s.sendBit_u8) == portState_u8) 
        {
            if (counter_u32++ >= g_sensorTime_s.maxCycles_u32) {
                *f_counter_u32 = TIMEOUT;
                Ret_e =  RC_ERROR_LIMIT_REACHED; // Exceeded timeout, fail.
                break;
            }
        }
        if(Ret_e == RC_OK)
        {
            *f_counter_u32 = counter_u32;
        }
    }
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
