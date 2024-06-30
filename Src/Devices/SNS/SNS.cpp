/*********************************************************************
 * @file        SNS.h
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
#include "SNS.h"
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
* SNS_Init
****************************/
t_eReturnCode SNS_Init(void)
{
    t_eReturnCode Ret_e = RC_OK;
    t_uint8 LI_u8;
    if(Ret_e == RC_OK)
    {
         for(LI_u8 = 0 ; LI_u8 < SNS_NUMBER && Ret_e == RC_OK ; LI_u8++)
        {
            Ret_e = (c_SysSnsCfg_as[LI_u8].SnsCfg_pcb)(c_SensorsPin_ua8[LI_u8], c_Sensors_PinMode_ea[LI_u8]);
            if(Ret_e != RC_OK)
            {
                Serial.println("Problem in SNS_Init");
                Serial.println(Ret_e);
                Serial.println(LI_u8);
            }
        }
    }
    return Ret_e;
}
/****************************
* SNS_Set_Cfg
****************************/
t_eReturnCode SNS_Set_Cfg(t_eSNSSPEC_Sensors f_SNSName_e)
{
    t_eReturnCode Ret_e = RC_OK;
    if(f_SNSName_e > SNS_NUMBER)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(Ret_e == RC_OK)
    {
        Ret_e = (c_SysSnsCfg_as[f_SNSName_e].SnsCfg_pcb)(c_SensorsPin_ua8[f_SNSName_e], c_Sensors_PinMode_ea[f_SNSName_e]);
        if(Ret_e != RC_OK)
        {
            Serial.println("Problem in SNS_Set_Cfg");
            Serial.print(f_SNSName_e);
            Serial.println(Ret_e);
        } 
    }
    return Ret_e;
}
 /****************************
* SNS_Get
****************************/
 t_eReturnCode SNS_Get(t_eSNSSPEC_Sensors f_SNSName_e, t_sint16 *f_SNSVal_s16)
 {
    t_eReturnCode Ret_e = RC_OK;
    if(f_SNSName_e > SNS_NUMBER)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(Ret_e == RC_OK)
    {
        Ret_e = (c_SysSnsCfg_as[f_SNSName_e].SnsGet_pcb)(f_SNSVal_s16);
        if(Ret_e != RC_OK)
        {
            Serial.println("Problem in SNS_Get");
            Serial.print(f_SNSName_e);
            Serial.println(Ret_e);
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
