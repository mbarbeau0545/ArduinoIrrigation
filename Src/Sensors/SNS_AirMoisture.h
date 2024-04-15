/*********************************************************************
 * @file        SNS_AirMoisture.h
 * @brief       Template_BriefDescription.
 * @details     TemplateDetailsDescription.\n
 *
 * @author      xxxxxx
 * @date        jj/mm/yyyy
 * @version     1.0
 */
  
#ifndef SNS_AIRMOISTURE_H_INCLUDED
#define SNS_AIRMOISTURE_H_INCLUDED





    // ********************************************************************
    // *                      Includes
    // ********************************************************************
    #include "../AppCommon/TypeCommon.h"

    #include "../ConfigSpecific/Arduino_ConfigSpecific.h"
    #include "../ArduinoLib/DHT/DHT.h"

    #include <Arduino.h>
    // ********************************************************************
    // *                      Defines
    // ********************************************************************

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
    t_eReturnCode SNS_AirMoisture_Cfg(t_uint8 f_pin_u8, t_eArduino_PinMode f_pinMode_e);
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
    t_eReturnCode SNS_AirMoisture_Get(t_sint16 *f_value_s16);
#endif // SNS_AIRMOISTURE_H_INCLUDED           
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
