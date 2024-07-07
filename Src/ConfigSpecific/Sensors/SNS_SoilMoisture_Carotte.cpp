/*********************************************************************
 * @file        SNS_SoilMoisture_Carotte.c
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
#include "SNS_SoilMoisture_Carotte.h"

// ********************************************************************
// *                      Defines
// ********************************************************************
#define MAX_VALUE_SOILMOIS_SENSOR (t_uint16)1020
// ********************************************************************
// *                      Types
// ********************************************************************
t_uint8 g_SoilMoisture_Carotte_Pin_u8;
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
/***************************
SNS_SoilMoisture_Tomate_Get
***************************/
/*   0 ~300 in water
     300~700 humid soil
     700~950 dry soil*/
t_eReturnCode SNS_SoilMoisture_Carotte_Cfg(t_uint8 f_pin, t_eArduino_PinMode f_Pinmode_e)
{
    t_eReturnCode Ret_e = RC_OK;
    if(f_pin < (t_uint8) 0|| f_pin > ((t_uint8)MAX_PIN +1))
    {
        Ret_e = RC_ERROR_NOT_ALLOWED;
    }
    if(Ret_e == RC_OK)
    {
        g_SoilMoisture_Carotte_Pin_u8 = f_pin;
        pinMode(f_pin, f_Pinmode_e);
    }   
    return Ret_e;
}
/****************************
SNS_SoilMoisture_Tomate_Get
****************************/
t_eReturnCode SNS_SoilMoisture_Carotte_Get( t_sint16 *f_value_s16)
{
    t_eReturnCode Ret_e = RC_OK;
    t_sint16 valueReceived_s16;
    if(f_value_s16 == (t_sint16 *)NULL)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(Ret_e == RC_OK)
    {
        *f_value_s16 = (t_sint16)0;
        valueReceived_s16 = (t_sint16)analogRead((t_uint8)g_SoilMoisture_Carotte_Pin_u8);   
        //make % value
        //DEBUG_PRINTLN(valueReceived_u16);
        if(valueReceived_s16 > (t_sint16)MAX_VALUE_SOILMOIS_SENSOR)
        {
            valueReceived_s16 =(t_sint16)MAX_VALUE_SOILMOIS_SENSOR;
        }
        else if(valueReceived_s16 <(t_sint16)0 )
        {
            valueReceived_s16 = (t_sint16)0;
        }
        *f_value_s16 = (t_sint16)((t_sint16)100 - (t_sint16)(valueReceived_s16 / (t_sint16)10));
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
