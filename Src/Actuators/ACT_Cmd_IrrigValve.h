/*********************************************************************
 * @file        ACT_Cmd_IrrigValve.h
 * @brief       Template_BriefDescription.
 * @details     TemplateDetailsDescription.\n
 *
 * @author      xxxxxx
 * @date        jj/mm/yyyy
 * @version     1.0
 */
  
#ifndef ACT_IRRIGVALVE_H_INCLUDED
#define ACT_IRRIGVALVE_H_INCLUDED





    // ********************************************************************
    // *                      Includes
    // ********************************************************************
    #include "AppCommon/TypeCommon.h"

    #include "ConfigSpecific/Arduino_ConfigSpecific.h"

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
    t_eReturnCode ACT_Cmd_IrrigValve_Cfg(t_uint8 f_pin, PinMode f_Pinmode);
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
    t_eReturnCode ACT_Cmd_IrrigValve_Get(t_uint16 *f_value);
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
    t_eReturnCode ACT_Cmd_IrrigValve_Set(t_uint16 f_value);

#endif // ACT_IRRIGATIONVALVE_H_INCLUDED           
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
