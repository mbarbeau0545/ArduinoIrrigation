/*********************************************************************
 * @file        SNS_AirTemperature.h
 * @brief       Template_BriefDescription.
 * @details     TemplateDetailsDescription.\n
 *
 * @author      xxxxxx
 * @date        jj/mm/yyyy
 * @version     1.0
 */
  
#ifndef SNS_AIRTEMPERATURE_H_INCLUDED
#define SNS_AIRTEMPERATURE_H_INCLUDED





    // ********************************************************************
    // *                      Includes
    // ********************************************************************
    
    // ********************************************************************
    // *                      Defines
    // ********************************************************************
    #include "../AppCommon/TypeCommon.h"

    #include "../ConfigSpecific/Arduino_ConfigSpecific.h"
    #include "../ArduinoLib/DHT/DHT.h"
    #include <Arduino.h>
    // ********************************************************************
    // *                      Types
    // ********************************************************************

    // ********************************************************************
    // *                      Prototypes
    // ********************************************************************
        
    // ********************************************************************
    // *                      Variables
    // ********************************************************************
    
    //****************************************************************************
    //                      Public functions - Prototypes
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
    t_eReturnCode SNS_AirTemperature_Cfg(t_uint8 f_pin, t_eArduino_PinMode f_Pinmode);
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
    t_eReturnCode SNS_AirTemperature_Get(t_sint16 *f_value_s16);
#endif // SNS_AIRTEMP_H_INCLUDED           
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
