/*********************************************************************
 * @file        Sensors_ConfigSpecific.h
 * @brief       Template_BriefDescription.
 * @details     TemplateDetailsDescription.\n
 *
 * @author      AUDMBA
 * @date        jj/mm/yyyy
 * @version     1.0
 ********************************************************************/
  
#ifndef SNS_CONFIGSPECIFIC_C_INCLUDED
#define SNS_CONFIGSPECIFIC_C_INCLUDED





    // ********************************************************************
    // *                      Includes
    // ********************************************************************
    #include "../AppCommon/TypeCommon.h"

    #include "../Sensors/SNS_AirMoisture.h"
    #include "../Sensors/SNS_AirTemp.h"
    #include "../Sensors/SNS_SoilMoisture.h"
    #include "../Sensors/SNS_SoilTemp.h"
    #include "../Sensors/SNS_Soil_pH.h"

    #include <Arduino.h>
    // ********************************************************************
    // *                      Defines
    // ********************************************************************
    // if using DHT Sensor, both sensor have the same pin 
    #define PIN_AIRTEMP 2
    #define PIN_AIRMOISTURE PIN_AIRTEMP
    #define PIN_SOILMOISTURE 3
    #define PIN_SOILTEMP 4 
    #define PIN_SOIL_PH 5
    
    // ********************************************************************
    // *                      Types
    // ********************************************************************
    /* CAUTION : Automatic generated code section: Start */
	typedef enum {
		SNS_SOILMOISTURE,
		SNS_SOILTEMP,
		SNS_SOIL_PH,
		SNS_AIRTEMP,
		SNS_AIRMOISTURE,

		SNS_NUMBER,
	}t_eSNS_Sensors;

	t_eReturnCode (*g_Sensors_Cfg_apf[SNS_NUMBER])(t_uint8, t_eArduino_PinMode) = {
		SNS_SoilMoisture_Cfg,
		SNS_SoilTemp_Cfg,
		SNS_Soil_pH_Cfg,
		SNS_AirTemp_Cfg,
		SNS_AirMoisture_Cfg,
	};

	t_eReturnCode (*g_Sensors_Get_apf[SNS_NUMBER])(t_uint16*) = {
		SNS_SoilMoisture_Get,
		SNS_SoilTemp_Get,
		SNS_Soil_pH_Get,
		SNS_AirTemp_Get,
		SNS_AirMoisture_Get,
	};
    /* CAUTION : Automatic generated code section: End */

    t_uint8 g_SensorsPin_ua[SNS_NUMBER] = {
                                           (t_uint8)PIN_SOILMOISTURE,                  //SNS_SOILMOISTURE, 
                                           (t_uint8)PIN_SOILTEMP,                      //SNS_SOILTEMP,
                                           (t_uint8)PIN_SOIL_PH,                       //SNS_SOIL_PH,
                                           (t_uint8)PIN_AIRTEMP,                       //SNS_AIRTEMP,
                                           (t_uint8)PIN_AIRMOISTURE,                   //SNS_AIRMOISTURE,   
                                        };

    t_eArduino_PinMode g_Sensors_PinMode_ea[SNS_NUMBER] = {
                                                    PINMODE_INPUT,                      //SNS_SOILMOISTURE, 
                                                    PINMODE_INPUT,                      //SNS_SOILTEMP,
                                                    PINMODE_INPUT,                      //SNS_SOIL_PH,
                                                    PINMODE_OUTPUT,                     //SNS_AIRTEMP,
                                                    PINMODE_OUTPUT,                     //SNS_AIRMOISTURE,   
                                                    };


    
    // ********************************************************************
    // *                      Prototypes
    // ********************************************************************
        
    // ********************************************************************
    // *                      Variables
    // ********************************************************************
    
    //********************************************************************************
    //                      Local functions - Prototypes
    //********************************************************************************

    //****************************************************************************
    //                      Public functions - Implementation
    //********************************************************************************

    //********************************************************************************
    //                      Local functions - Implementation
    //********************************************************************************
#endif // SNS_CONFIGSPECIFIC_C_INCLUDED           
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
