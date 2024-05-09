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
    #include "../Sensors/SNS_AirTemperature.h"
    #include "../Sensors/SNS_SoilMoisture_Carotte.h"
    #include "../Sensors/SNS_SoilMoisture_Courgette.h"
    #include "../Sensors/SNS_SoilMoisture_Tomate.h"

    #include <Arduino.h>
    // ********************************************************************
    // *                      Defines
    // ********************************************************************
    // if using DHT Sensor, both sensor have the same pin 
    #define PIN_SNS_AIRMOISTURE 13
    #define PIN_SNS_AIRTEMPERATURE PIN_SNS_AIRMOISTURE
    #define PIN_SNS_SOILMOISTURE_TOMATE A0
    #define PIN_SNS_SOILMOISTURE_COURGETTE A1
    #define PIN_SNS_SOILMOISTURE_CAROTTE A2
    
    // ********************************************************************
    // *                      Types
    // ********************************************************************
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
    typedef t_eReturnCode (t_cbSNS_cfg)(t_uint8 f_pin_u8, t_eArduino_PinMode);
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
   typedef t_eReturnCode (t_cbSNS_GetVal)(t_sint16 *f_value_s16);
   typedef struct 
   {
        t_cbSNS_cfg    * SnsCfg_pcb;
        t_cbSNS_GetVal * SnsGet_pcb;
   }t_sSNS_SysSnsCfg;

    /* CAUTION : Automatic generated code section: Start */
	typedef enum {
		//SNS_AIRTEMPERATURE,
		//SNS_AIRMOISTURE,
		SNS_SOILMOISTURE_TOMATE,
		SNS_SOILMOISTURE_COURGETTE,
		SNS_SOILMOISTURE_CAROTTE,

		SNS_NUMBER,
	}t_eSNS_Sensors;

	static const t_sSNS_SysSnsCfg c_SysSnsCfg_as[SNS_NUMBER] = 
	{
		//{	SNS_AirTemperature_Cfg                    	,SNS_AirTemperature_Get},
		//{	SNS_AirMoisture_Cfg                       	,SNS_AirMoisture_Get},
		{	SNS_SoilMoisture_Tomate_Cfg               	,SNS_SoilMoisture_Tomate_Get},
		{	SNS_SoilMoisture_Courgette_Cfg            	,SNS_SoilMoisture_Courgette_Get},
		{	SNS_SoilMoisture_Carotte_Cfg              	,SNS_SoilMoisture_Carotte_Get},
	};
	/* CAUTION : Automatic generated code section: End */






    static const t_uint8 c_SensorsPin_ua8[SNS_NUMBER] = {
                                           //(t_uint8)PIN_SNS_AIRTEMPERATURE,                     //SNS_AIRTEMPERATURE, 
                                           //(t_uint8)PIN_SNS_AIRMOISTURE,                        //SNS_AIRMOISTURE,
                                           (t_uint8)PIN_SNS_SOILMOISTURE_TOMATE,                //SNS_SOILMOISTURE_TOMATE,
                                           (t_uint8)PIN_SNS_SOILMOISTURE_COURGETTE,             //SNS_SOILMOISTURE_COURGETTE,
                                           (t_uint8)PIN_SNS_SOILMOISTURE_CAROTTE,               //SNS_SOILMOISTURE_CAROTTE,   
                                        };
                                        //10 & 11 already token by Wifi esp

    static const t_eArduino_PinMode c_Sensors_PinMode_ea[SNS_NUMBER] = {
                                                    //PINMODE_INPUT,                      //SNS_SOILMOISTURE, 
                                                    //PINMODE_INPUT,                      //SNS_SOILTEMP,
                                                    PINMODE_INPUT,                      //SNS_SOIL_PH,
                                                    PINMODE_INPUT,                      //SNS_AIRTEMP,
                                                    PINMODE_INPUT,                     //SNS_AIRMOISTURE,   
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
