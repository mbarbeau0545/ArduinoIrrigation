/*********************************************************************
 * @file        ACT_Cmd_IrrigValve_Courgette.h
 * @brief       Template_BriefDescription.
 * @details     TemplateDetailsDescription.\n
 *
 * @author      audmba
 * @date        jj/mm/yyyy
 * @version     1.0
 */
  
#ifndef ACT_CMD_IRRIGVALVE_COURGETTE_H_INCLUDED
#define ACT_CMD_IRRIGVALVE_COURGETTE_H_INCLUDED





    // ********************************************************************
    // *                      Includes
    // ********************************************************************
    #include "./AppCommon/TypeCommon.h"

    #include "./ConfigSpecific/Func_CfgSpecific/Arduino_ConfigSpecific.h"

    #include <Arduino.h>
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
    
    //****************************************************************************
    //                      Public functions - Prototypes
    //********************************************************************************
    /**
    *
    *	@brief
    *	@details
    *
    *
    *	@param[in] 
    *	@param[out]
    *	 
    *
    *
    */
    t_eReturnCode ACT_Cmd_IrrigValve_Courgette_Cfg(t_uint8 f_pin, t_eArduino_PinMode f_Pinmode);
    /**
    *
    *	@brief
    *	@details
    *
    *
    *	@param[in] 
    *	@param[out]
    *	 
    *
    *
    */
    t_eReturnCode ACT_Cmd_IrrigValve_Courgette_Set(t_sint16 f_value);
    /**
    *
    *	@brief
    *	@details
    *
    *
    *	@param[in] 
    *	@param[out]
    *	 
    *
    *
    */
    t_eReturnCode ACT_Cmd_IrrigValve_Courgette_Get(t_sint16 *f_value);

#endif // ACT_CMD_IRRIGVALVE_CAROTTE_H_INCLUDED           
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
