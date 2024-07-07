/*********************************************************************
 * @file        ArduinoLib.h
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
#include "ArdCom.h"
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
// *******************************************************************

t_bool g_ArdComModule_Initialized_ab[ARDCOM_NB] = {
    (t_bool)false,
    (t_bool)false,
    (t_bool)false,
    (t_bool)false,
};
//********************************************************************************
//                      Local functions - Prototypes
//********************************************************************************
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
t_eReturnCode s_ArdCom_MngWifiDisparity(t_sESP_ComStatus *f_ESP_Wifi_Cfg_ps);
//****************************************************************************
//                      Public functions - Implementation
//********************************************************************************
/*****************
 * ArdCom_Init
 ****************/
t_eReturnCode ArdCom_Init(t_eArdCom_TypeCom f_TypeCom_e)
{
    t_eReturnCode Ret_e = RC_OK;
    if(f_TypeCom_e > ARDCOM_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(Ret_e == RC_OK)
    {
        Ret_e = c_SysArdComCfg_as[f_TypeCom_e].ArdCom_Init_pcb();    
        if(Ret_e == RC_OK)
        {
            g_ArdComModule_Initialized_ab[f_TypeCom_e] = (t_bool)true;
        }
    }    
    return Ret_e;
}
/*****************
 * ArdCom_Close
 ****************/
t_eReturnCode ArdCom_Close(t_eArdCom_TypeCom f_TypeCom_e)
{
    t_eReturnCode Ret_e = RC_OK;
    if(f_TypeCom_e > ARDCOM_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(Ret_e == RC_OK)
    {
        Ret_e = c_SysArdComCfg_as[f_TypeCom_e].ArdCom_Close_pcb();
    }
    return Ret_e;
}
/********************
 * ArdCom_GetComCfg
 *******************/
t_eReturnCode ArdCom_GetComCfg(t_eArdCom_TypeCom f_TypeCom_e, t_uArdCom_GetCfg *f_ComCfg_u)
{
    t_eReturnCode Ret_e = RC_OK;
    if(f_TypeCom_e > ARDCOM_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if (g_ArdComModule_Initialized_ab[f_TypeCom_e] == false)
    {
        Ret_e = RC_ERROR_MODULE_NOT_INITIALIZED;
    }
    if(Ret_e == RC_OK)
    {
        switch (f_TypeCom_e)
        {
            case ARDCOM_WIFI:
            {
                Ret_e = ESP_Get_ProtocolCom_Cfg(&(f_ComCfg_u->ESP_CfgStatus));
                break;
            }
            case ARDCOM_BLUETOOTH:
            case ARDCOM_LORA:
            case ARDCOM_SPI:
            case ARDCOM_NB:
            break;
        }        
    }
    return Ret_e;
}
/********************
 * ArdCom_StartCom
 *******************/
t_eReturnCode ArdCom_StartCom(t_eArdCom_TypeCom f_TypeCom_e)
{
    t_eReturnCode Ret_e = RC_OK;
    if(f_TypeCom_e > ARDCOM_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if (g_ArdComModule_Initialized_ab[f_TypeCom_e] == false)
    {
        Ret_e = RC_ERROR_MODULE_NOT_INITIALIZED;
    }
    if(Ret_e == RC_OK)
    {
        Ret_e = c_SysArdComCfg_as[f_TypeCom_e].ArdCom_StartCom_pcb();
        if(Ret_e == RC_WARNING_ALREADY_CONFIGURED)
        {
            Ret_e = RC_OK;
        }
        
    }
    return Ret_e;
}
/********************
 * ArdCom_StartCom
 *******************/
t_eReturnCode ArdCom_EndCom(t_eArdCom_TypeCom f_TypeCom_e)
{
    t_eReturnCode Ret_e = RC_OK;
    if(f_TypeCom_e > ARDCOM_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if (g_ArdComModule_Initialized_ab[f_TypeCom_e] == false)
    {
        Ret_e = RC_ERROR_MODULE_NOT_INITIALIZED;
    }
    if(Ret_e == RC_OK)
    {
        Ret_e = c_SysArdComCfg_as[f_TypeCom_e].ArdCom_EndCom_pcb();
    }
    return Ret_e;
}
/********************
 * ArdCom_RcvData
 *******************/
t_eReturnCode ArdCom_RcvData(t_eArdCom_TypeCom f_TypeCom_e, const char * f_DataRcv_ps)
{
    t_eReturnCode Ret_e = RC_OK;
    if(f_TypeCom_e > ARDCOM_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if (g_ArdComModule_Initialized_ab[f_TypeCom_e] == false)
    {
        Ret_e = RC_ERROR_MODULE_NOT_INITIALIZED;
    }
    if(Ret_e == RC_OK)
    {
        Ret_e = c_SysArdComCfg_as[f_TypeCom_e].ArdCom_RcvData_pcb(f_DataRcv_ps);
    }
    return Ret_e;
}
/********************
 * ArdCom_SendData
 *******************/
t_eReturnCode ArdCom_SendData(t_eArdCom_TypeCom f_TypeCom_e, const char* f_dataToSend_pc)
{
    t_eReturnCode Ret_e = RC_OK;

    if(f_TypeCom_e > ARDCOM_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if (g_ArdComModule_Initialized_ab[f_TypeCom_e] == false)
    {
        Ret_e = RC_ERROR_MODULE_NOT_INITIALIZED;
    }
    if(Ret_e == RC_OK)
    {
        Ret_e = c_SysArdComCfg_as[f_TypeCom_e].ArdCom_SendData_pcb(f_dataToSend_pc);
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


