/*********************************************************************
 * @file        ArduinoLib.h
 * @brief       Template_BriefDescription.
 * @details     TemplateDetailsDescription.\n
 *
 * @author      AUDMBA
 * @date        09/03/2024
 * @version     1.0
 *********************************************************************/
  

#ifndef ARDCOM_H_INCLUDED
#define ARDCOM_H_INCLUDED




    // ********************************************************************
    // *                      Includes
    // ********************************************************************
    # include "ConfigSpecific/Func_CfgSpecific/ArdCom_ConfigSpecific.h"
    // ********************************************************************
    // *                      Defines
    // ********************************************************************

    //****************************************************************************
    //                      Public functions - Prototype
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
    t_eReturnCode ArdCom_Init(t_eArdCom_TypeCom f_TypeCom_e);
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
    t_eReturnCode ArdCom_Close(t_eArdCom_TypeCom f_TypeCom_e);
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
    t_eReturnCode ArdCom_GetComCfg(t_eArdCom_TypeCom f_TypeCom_e, t_uArdCom_GetCfg *f_ComCfg_u);
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
    t_eReturnCode ArdCom_StartCom(t_eArdCom_TypeCom f_TypeCom_e);
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
    t_eReturnCode ArdCom_EndCom(t_eArdCom_TypeCom f_TypeCom_e);
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
    t_eReturnCode ArdCom_RcvData(t_eArdCom_TypeCom f_TypeCom_e, const char * f_DataRcv_ps);
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
    t_eReturnCode ArdCom_SendData(t_eArdCom_TypeCom f_TypeCom_e, const char* f_dataToSend_pc);

#endif
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