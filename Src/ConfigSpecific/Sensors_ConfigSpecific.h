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

    #include "../Sensors/SNS_SoilMoisture.h"

    #include <Arduino.h>
    // ********************************************************************
    // *                      Defines
    // ********************************************************************

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

	t_eReturnCode (*g_Sensors_Cfg_apf[SNS_NUMBER])(t_uint8, PinMode) = {
		SNS_SoilMoisture_Cfg,
		/*SNS_SoilTemp_Cfg,
		SNS_Soil_pH_Cfg,
		SNS_AirTemp_Cfg,
		SNS_AirMoisture_Cfg,*/
	};

	t_eReturnCode (*g_Sensors_Get_apf[SNS_NUMBER])(t_uint16*) = {
		SNS_SoilMoisture_Get,
		/*SNS_SoilTemp_Get,
		SNS_Soil_pH_Get,
		SNS_AirTemp_Get,
		SNS_AirMoisture_Get,*/
	};
    /* CAUTION : Automatic generated code section: End */

    t_uint8 g_SensorsPin_ua[SNS_NUMBER] = {(t_uint8)1,
                                           (t_uint8)2,
                                           (t_uint8)3};

    PinMode g_Sensors_PinMode_ea[SNS_NUMBER] = {INPUT, OUTPUT,OUTPUT};


    
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
