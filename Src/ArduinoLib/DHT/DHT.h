/*********************************************************************
 * @file        DHT.h
 * @brief       Template_BriefDescription.
 * @details     TemplateDetailsDescription.\n
 *
 * @author      xxxxxx
 * @date        jj/mm/yyyy
 * @version     1.0
 */
  
#ifndef DHT_H_INCLUDED
#define DHT_H_INCLUDED





    // ********************************************************************
    // *                      Includes
    // ********************************************************************
    #include "AppCommon/TypeCommon.h"
     
    #include "./ConfigSpecific/Func_CfgSpecific/Arduino_ConfigSpecific.h"
    
    #include <Arduino.h>
    // ********************************************************************
    // *                      Defines
    // ********************************************************************
    
    // ********************************************************************
    // *                      Types
    // ********************************************************************
    typedef enum 
    {
        DHT_SENSOR_11 = 0,
        DHT_SENSOR_12,
        DHT_SENSOR_21,
        DHT_SENSOR_22,

        DHT_SENSOR_NB,
    }t_eDHT_SensorType;
    // ********************************************************************
    // *                      Prototypes
    // ********************************************************************
        
    // ********************************************************************
    // *                      Variables
    // ********************************************************************

    // ********************************************************************
    // *                      Classe
    // ********************************************************************
    class InterruptLock {
    public:
      InterruptLock() {
    #if !defined(ARDUINO_ARCH_NRF52)
        noInterrupts();
    #endif
      }
      ~InterruptLock() {
    #if !defined(ARDUINO_ARCH_NRF52)
        interrupts();
    #endif
      }
    };
    //********************************************************************************
    //                      Public functions - Prototypes
    //********************************************************************************
    t_eReturnCode DHT_Init(t_uint8 f_pin_u8, t_eDHT_SensorType f_Sensortype_e, t_uint8 f_count_u8 = 6);
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
        t_eReturnCode DHT_begin(t_uint8 f_pullTimeSec_u8 = 55);
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
        t_eReturnCode DHT_ReadTemperature(t_float32 *f_tempValue_pf32, t_bool f_forcedMode_b = false);
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
        t_eReturnCode DHT_ReadMoisture(t_float32 *f_moistValue_pf32, t_bool f_forcedMode_b = false);
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
        t_eReturnCode DHT_ReadSensor(t_bool *f_lastResult_b ,t_bool f_forcedMode_b = false);

#endif // DHT_H_INCLUDED           
//************************************************************************************
// End of File
//************************************************************************************

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
