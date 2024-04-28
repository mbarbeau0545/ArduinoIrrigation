/*********************************************************************
 * @file        ACT_Cmd_IrrigValve_Courgette.c
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
#include "ACT_Cmd_IrrigValve_Courgette.h"
// ********************************************************************
// *                      Defines
// ********************************************************************

// ********************************************************************
// *                      Types
// ********************************************************************
t_uint8 g_IrrigValve_Courgette_Pin_u8 = (t_uint8)0;
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
/********************************
ACT_Cmd_IrrigValve_Courgette_Cfg
********************************/
t_eReturnCode ACT_Cmd_IrrigValve_Courgette_Cfg(t_uint8 f_pin_u8, t_eArduino_PinMode f_Pinmode_e)
{
    t_eReturnCode Ret_e = RC_OK;
    if(f_pin_u8 > MAX_PIN)
    {
        Ret_e = RC_ERROR_NOT_ALLOWED;
    }
    if (Ret_e == RC_OK)
    {
        g_IrrigValve_Courgette_Pin_u8 = f_pin_u8;
        pinMode(f_pin_u8, f_Pinmode_e);
    }    
    return Ret_e;
}
/********************************
ACT_Cmd_IrrigValve_Courgette_Set
********************************/
t_eReturnCode ACT_Cmd_IrrigValve_Courgette_Set(t_sint16 f_value)
{
    t_eReturnCode Ret_e = RC_OK;
    // Get the value of the ACT
    digitalWrite(g_IrrigValve_Courgette_Pin_u8, (t_uint8)f_value);
    return Ret_e;

}
/********************************
ACT_Cmd_IrrigValve_Courgette_Get
*********************************/
t_eReturnCode ACT_Cmd_IrrigValve_Courgette_Get(t_sint16 *f_value)
{
    t_eReturnCode Ret_e = RC_OK;
    if(f_value == NULL)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(Ret_e == RC_OK)
    {
        *f_value = (t_sint16)digitalRead((t_uint8)g_IrrigValve_Courgette_Pin_u8);        
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
