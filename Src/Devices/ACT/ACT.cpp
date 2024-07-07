/*********************************************************************
 * @file        ACT.h
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
#include "ACT.h"
// ********************************************************************
// *                      Defines
// ********************************************************************

// ********************************************************************
// *                      Types
// ********************************************************************

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
/****************************
* ACT_Init
****************************/
t_eReturnCode ACT_Init(void)
{
    t_eReturnCode Ret_e = RC_OK;
    t_uint8 LI_u8;
    if(Ret_e == RC_OK)
    {
        for(LI_u8 = 0 ; LI_u8 < ACT_NUMBER && Ret_e == RC_OK ; LI_u8++)
        {
            Ret_e = (c_SysActCfg_as[LI_u8].ActCfg_pcb)(c_ActuatorsPin_ua8[LI_u8], c_Actuators_PinMode_ea[LI_u8]);
            if(Ret_e != RC_OK)
            {
                DEBUG_PRINTLN("Problem in CfgActuator");
                DEBUG_PRINTLN(Ret_e);
                DEBUG_PRINTLN(LI_u8);
            }
        }    
    }
    return Ret_e;
}
/****************************
* ACT_Set_Cfg
****************************/
t_eReturnCode ACT_Set_Cfg(t_eACT_Actuators f_actuatorName_e)
{
    t_eReturnCode Ret_e = RC_OK;
    if(f_actuatorName_e > ACT_NUMBER)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(Ret_e == RC_OK)
    {

        Ret_e = (c_SysActCfg_as[f_actuatorName_e].ActCfg_pcb)(c_ActuatorsPin_ua8[f_actuatorName_e], c_Actuators_PinMode_ea[f_actuatorName_e]);
        if(Ret_e != RC_OK)
        {
            DEBUG_PRINTLN("Problem in ACT_Set_Cfg");
            DEBUG_PRINT(f_actuatorName_e);
            DEBUG_PRINTLN(Ret_e);
        } 
    }
    return Ret_e;
}
/****************************
* ACT_Set_Cfg
****************************/
 t_eReturnCode ACT_Set(t_eACT_Actuators f_actuatorName_e, t_sint16 f_ActVal_s16)
 {
    t_eReturnCode Ret_e = RC_OK;
    if(f_actuatorName_e > ACT_NUMBER)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(Ret_e == RC_OK)
    {
        Ret_e = (c_SysActCfg_as[f_actuatorName_e].ActSetVal_pcb)(f_ActVal_s16);
        if(Ret_e != RC_OK)
        {
            DEBUG_PRINTLN("Problem in ACT_Set");
            DEBUG_PRINT(f_actuatorName_e);
            DEBUG_PRINTLN(Ret_e);
        } 
    }
    return Ret_e;
 }
 /****************************
* ACT_Get
****************************/
 t_eReturnCode ACT_Get(t_eACT_Actuators f_actuatorName_e, t_sint16 *f_ActVal_s16)
 {
    t_eReturnCode Ret_e = RC_OK;
    if(f_actuatorName_e > ACT_NUMBER)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(Ret_e == RC_OK)
    {
        Ret_e = (c_SysActCfg_as[f_actuatorName_e].ActGetVal_pcb)(f_ActVal_s16);
        if(Ret_e != RC_OK)
        {
            DEBUG_PRINTLN("Problem in ACT_Get");
            DEBUG_PRINT(f_actuatorName_e);
            DEBUG_PRINTLN(Ret_e);
        } 
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
