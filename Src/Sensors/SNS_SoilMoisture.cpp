/*********************************************************************
 * @file        SNS_SoilMoisture.c
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
#include "SNS_SoilMoisture.h"

// ********************************************************************
// *                      Defines
// ********************************************************************
#define MAX_VALUE_SOILMOIS_SENSOR (t_uint16)1020
// ********************************************************************
// *                      Types
// ********************************************************************
t_uint8 g_SoilMoisture_Pin_u8;
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
/*************************
SNS_SoilMoisture_Cfg
*************************/
/*   0 ~300 in water
     300~700 humid soil
     700~950 dry soil*/
t_eReturnCode SNS_SoilMoisture_Cfg(t_uint8 f_pin, t_eArduino_PinMode f_Pinmode)
{
    t_eReturnCode Ret_e = RC_OK;
    if(f_pin < (t_uint8) 0|| f_pin > (t_uint8)MAX_PIN)
    {
        Ret_e = RC_ERROR_NOT_ALLOWED;
    }
    if(Ret_e == RC_OK)
    {
        g_SoilMoisture_Pin_u8 = f_pin;
        pinMode(f_pin, f_Pinmode);
    }   
    return Ret_e;
}
/*************************
SNS_SoilMoisture_Get
*************************/
t_eReturnCode SNS_SoilMoisture_Get( t_uint16 *f_value_16)
{
    t_eReturnCode Ret_e = RC_OK;
    t_uint16 valueReceived_u16;
    if(f_value_16 == (t_uint16 *)NULL)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(Ret_e == RC_OK)
    {
        *f_value_16 = (t_uint16)0;
        valueReceived_u16 = (t_uint16)analogRead((t_uint8)g_SoilMoisture_Pin_u8);   
        //make % value
        Serial.println(valueReceived_u16);
        *f_value_16 = (t_uint16)(valueReceived_u16 / 10);
    }
    return Ret_e;

}
//********************************************************************************
//                      Local functions - Implementation
//******************************************************************************** 
         
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
