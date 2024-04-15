/*********************************************************************
 * @file        SNS_AirMoisture.h
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
#include "SNS_AirMoisture.h"
// ********************************************************************
// *                      Defines
// ********************************************************************
#define DHT_SENSOR_USED DHT_SENSOR_22
// ********************************************************************
// *                      Types
// ********************************************************************
t_uint8 g_AirMoisture_Pin_u8;
t_bool g_module_AirMoisture_Initialize_b = false;
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
SNS_AirMoisture_Cfg
*************************/
t_eReturnCode SNS_AirMoisture_Cfg(t_uint8 f_pin_u8, t_eArduino_PinMode f_pinMode_e)
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
        
        g_AirMoisture_Pin_u8 = f_pin_u8;
        Ret_e = DHT_Init(f_pin_u8, DHT_SENSOR_USED);
        if(Ret_e == RC_OK)
        {
            Ret_e = DHT_begin();
            if(Ret_e == RC_OK)
            {
                g_module_AirMoisture_Initialize_b = (t_bool)true;
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
    DEBUG_PRINT("RetCode [SNS_AirMoisture_Cfg] :")
    DEBUG_PRINTLN(Ret_e)
    return Ret_e;
}
/*************************
SNS_AirMoisture_Get
*************************/
t_eReturnCode SNS_AirMoisture_Get(t_sint16 *f_value_s16)
{
    t_eReturnCode Ret_e = RC_OK;
    t_float32 valueReceive_f32;
    if(g_module_AirMoisture_Initialize_b != (t_bool)true)
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
        Ret_e = DHT_ReadMoisture(&valueReceive_f32);
        
        *f_value_s16 = (t_sint16)valueReceive_f32;
    }  
    DEBUG_PRINT("RetCode [SNS_AirMoisture_Get] :")
    DEBUG_PRINTLN(Ret_e) 
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
