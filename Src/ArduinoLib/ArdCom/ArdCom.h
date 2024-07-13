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
    # include "ConfigSpecific/ArduinoCom/ArdCom_CfgSpec.h"
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
    t_eReturnState ArdCom_Init(t_eArdCom_TypeCom f_TypeCom_e);
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
    t_eReturnState ArdCom_Close(t_eArdCom_TypeCom f_TypeCom_e);
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
    t_eReturnState ArdCom_GetComCfg(t_eArdCom_TypeCom f_TypeCom_e, t_uArdCom_GetCfg *f_ComCfg_u);
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
    t_eReturnState ArdCom_StartCom(t_eArdCom_TypeCom f_TypeCom_e);
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
    t_eReturnState ArdCom_EndCom(t_eArdCom_TypeCom f_TypeCom_e);
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
    t_eReturnState ArdCom_RcvData(t_eArdCom_TypeCom f_TypeCom_e,char * f_DataRcv_ps);
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
    t_eReturnState ArdCom_SendData(t_eArdCom_TypeCom f_TypeCom_e,char* f_dataToSend_pc);
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