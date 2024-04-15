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
    #define PIN_AIRTEMP 12
    #define PIN_AIRMOISTURE PIN_AIRTEMP
    #define PIN_SOILMOISTURE A0
    #define PIN_SOILTEMP 11
    #define PIN_SOIL_PH 5
    
    // ********************************************************************
    // *                      Types
    // ********************************************************************
    typedef union 
    {
        t_float32 retVal_f32;
        t_uint16  retVal_u16;
        t_bool    retVal_b;

    }t_uSNS_ReturnGetValue;
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
    typedef t_eReturnCode (t_cbSNS_cfg)(t_uint8 f_pin, t_eArduino_PinMode);
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

    typedef enum 
    {
        SENS_FUNCTION_CFG = 0,
        SENS_FUNCTION_GET,
        
        SENS_FUNCTION_NB,
    }t_eSNS_Function;
    /* CAUTION : Automatic generated code section: Start */
	typedef enum {
		SNS_SOILMOISTURE,
		SNS_SOILTEMP,
		SNS_SOIL_PH,
		SNS_AIRTEMP,
		SNS_AIRMOISTURE,

		SNS_NUMBER,
	}t_eSNS_Sensors;

	static const t_sSNS_SysSnsCfg c_SysSnsCfg_as[SNS_NUMBER] = 
	{
		{	SNS_SoilMoisture_Cfg                      	,SNS_SoilMoisture_Get,                          },
		{	SNS_SoilTemp_Cfg                          	,SNS_SoilTemp_Get,                              },
		{	SNS_Soil_pH_Cfg                           	,SNS_Soil_pH_Get,                               },
		{	SNS_AirTemp_Cfg                           	,SNS_AirTemp_Get,                               },
		{	SNS_AirMoisture_Cfg                       	,SNS_AirMoisture_Get,                           },
	};
	/* CAUTION : Automatic generated code section: End */






    static const t_uint8 c_SensorsPin_ua8[SNS_NUMBER] = {
                                           (t_uint8)PIN_SOILMOISTURE,                  //SNS_SOILMOISTURE, 
                                           (t_uint8)PIN_SOILTEMP,                      //SNS_SOILTEMP,
                                           (t_uint8)PIN_SOIL_PH,                       //SNS_SOIL_PH,
                                           (t_uint8)PIN_AIRTEMP,                       //SNS_AIRTEMP,
                                           (t_uint8)PIN_AIRMOISTURE,                   //SNS_AIRMOISTURE,   
                                        };

    static const t_eArduino_PinMode c_Sensors_PinMode_ea[SNS_NUMBER] = {
                                                    PINMODE_INPUT,                      //SNS_SOILMOISTURE, 
                                                    PINMODE_INPUT,                      //SNS_SOILTEMP,
                                                    PINMODE_INPUT,                      //SNS_SOIL_PH,
                                                    PINMODE_INPUT,                     //SNS_AIRTEMP,
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
