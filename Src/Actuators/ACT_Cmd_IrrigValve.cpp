/*********************************************************************
 * @file        ACT_IrrigationValve.c
 * @brief       Template_BriefDescription.
 * @details     TemplateDetailsDescription.\n
 *
 * @author      AUDMBA
 * @date        09/03/2024
 * @version     1.0
 *********************************************************************/
  






// ********************************************************************
// *                      Includes
// ********************************************************************
#include "ACT_Cmd_IrrigValve.h"
// ********************************************************************
// *                      Defines
// ********************************************************************

// ********************************************************************
// *                      Types
// ********************************************************************
t_uint8 g_IrrigValve_Pin_u8 = (t_uint8)0;
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
ACT_IrrigValve_Cfg
*************************/
t_eReturnCode ACT_Cmd_IrrigValve_Cfg(t_uint8 f_pin, t_eArduino_PinMode f_Pinmode)
{
    t_eReturnCode Ret_e = RC_OK;
    if(f_pin < (t_uint8)0 || f_pin > MAX_PIN)
    {
        Ret_e = RC_ERROR_NOT_ALLOWED;
    }
    if (Ret_e == RC_OK)
    {
        g_IrrigValve_Pin_u8 = f_pin;
        pinMode(f_pin, f_Pinmode);
    }    
    return Ret_e;
}
/*************************
ACT_Cmd_IrrigValve_Set
*************************/
t_eReturnCode ACT_Cmd_IrrigValve_Set(t_sint16 f_value)
{
    t_eReturnCode Ret_e = RC_OK;
    // Get the value of the ACT
    digitalWrite(g_IrrigValve_Pin_u8, (t_uint8)f_value);
    return Ret_e;

}
/*************************
ACT_Cmd_IrrigValve_Get
*************************/
t_eReturnCode ACT_Cmd_IrrigValve_Get(t_sint16 *f_value)
{
    t_eReturnCode Ret_e = RC_OK;
    if(f_value == NULL)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(Ret_e == RC_OK)
    {
        *f_value = (t_sint16)digitalRead((t_uint8)g_IrrigValve_Pin_u8);        
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
