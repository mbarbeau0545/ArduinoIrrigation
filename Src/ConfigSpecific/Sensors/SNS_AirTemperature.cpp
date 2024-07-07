/*********************************************************************
 * @file        SNS_AirTemp.h
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
#include "SNS_AirTemperature.h"

// ********************************************************************
// *                      Defines
// ********************************************************************
#define DHT_SENSOR_USED DHT_SENSOR_22
// ********************************************************************
// *                      Types
// ********************************************************************
t_uint8 g_AirTemp_Pin_u8;
t_bool g_module_AirTemp_Initialize_b = false;
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
SNS_AirTemp_Cfg
*************************/
t_eReturnCode SNS_AirTemperature_Cfg(t_uint8 f_pin_u8, t_eArduino_PinMode f_pinMode_e)
{
    t_eReturnCode Ret_e = RC_OK;
    if((f_pin_u8 > MAX_PIN) || (f_pin_u8 < (t_uint8)0))
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if((f_pinMode_e > PINMODE_NB) || (f_pinMode_e < 0))
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(Ret_e == RC_OK)
    {        
        g_AirTemp_Pin_u8 = f_pin_u8;
        Ret_e = DHT_Init(f_pin_u8, DHT_SENSOR_USED);
        if(Ret_e == RC_OK)
        {
            Ret_e = DHT_begin();
            if(Ret_e == RC_OK)
            {
                g_module_AirTemp_Initialize_b = (t_bool)true;
            }
            else
            {                
                Ret_e = RC_ERROR_MODULE_NOT_INITIALIZED;
            }
        }
        else
        {
            Ret_e = RC_ERROR_MODULE_NOT_INITIALIZED;
        }
    }
    return Ret_e;
    
}
/*************************
SNS_AirTemp_Get
*************************/
t_eReturnCode SNS_AirTemperature_Get(t_sint16 *f_value_s16)
{
    t_eReturnCode Ret_e = RC_OK;
    t_float32 valueReceive_f32;
    if(g_module_AirTemp_Initialize_b != (t_bool)true)
    {
        Ret_e = RC_ERROR_MODULE_NOT_INITIALIZED;
    }
    if(f_value_s16 == (t_sint16 *)NULL)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(Ret_e == RC_OK)
    {
        *f_value_s16 = (t_sint16)0;
        Ret_e = DHT_ReadTemperature(&valueReceive_f32);
        *f_value_s16 = (t_sint16)valueReceive_f32;
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
