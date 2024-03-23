/*********************************************************************
 * @file        Actuators_ConfigSpecific.h
 * @brief       Template_BriefDescription.
 * @details     TemplateDetailsDescription.\n
 *
 * @author      AUDMBA
 * @date        jj/mm/yyyy
 * @version     1.0
 */
  
#ifndef ACT_CONFIGSPECIFIC_C_INCLUDED
#define ACT_CONFIGSPECIFIC_C_INCLUDED





    // ********************************************************************
    // *                      Includes
    // ********************************************************************
    
    // ********************************************************************
    // *                      Defines
    // ********************************************************************
    #include "Arduino.h"

    #include "../AppCommon/TypeCommon.h"
    #include "../Actuators/ACT_Cmd_IrrigValve.h"
    // ********************************************************************
    // *                      Types
    // ********************************************************************
    /* CAUTION : Automatic generated code section: Start */
	typedef enum {
		ACT_CMD_IRRIGVALVE,

		ACT_NUMBER,
	}t_eACT_Actuators;


	t_eReturnCode (*g_Actuators_Cfg_apf[ACT_NUMBER])(t_uint8, t_eArduino_PinMode) = {
		ACT_Cmd_IrrigValve_Cfg,
	};

	t_eReturnCode (*g_Actuators_Get_apf[SNS_NUMBER])(t_uint16*) = {
		ACT_Cmd_IrrigValve_Get,
	};

	t_eReturnCode (*g_Actuators_Set_apf[SNS_NUMBER])(t_uint16) = {
		ACT_Cmd_IrrigValve_Set,
	};
    /* CAUTION : Automatic generated code section: End */
    // ********************************************************************
    // *                      Prototypes
    // ********************************************************************
        
    // ********************************************************************
    // *                      Variables
    // ********************************************************************
    t_uint8 g_ActuatorsPin_ua[ACT_NUMBER] = {
        12                            //ACT_CMD_IRRIGVALVE
    };

    t_eArduino_PinMode g_Actuators_PinMode_ea[ACT_NUMBER] = {PINMODE_OUTPUT};
    
    
    //********************************************************************************
    //                      Local functions - Prototypes
    //********************************************************************************

    //****************************************************************************
    //                      Public functions - Implementation
    //********************************************************************************

    //********************************************************************************
    //                      Local functions - Implementation
    //********************************************************************************
#endif // ACT_CONFIGSPECIFIC_C_INCLUDED           
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
