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
    #include "Arduino.h"

    #include "./AppCommon/TypeCommon.h"

    #include "../Actuators/ACT_Cmd_IrrigValve_Carotte.h"
    #include "../Actuators/ACT_Cmd_IrrigValve_Courgette.h"
    #include "../Actuators/ACT_Cmd_IrrigValve_Tomate.h"
    // ********************************************************************
    // *                      Defines
    // ********************************************************************
    #define PIN_ACT_IRRIGVALVE_TOMATE       7
    #define PIN_ACT_IRRIGVALVE_COURGETTE    8
    #define PIN_ACT_IRRIGVALVE_CAROTTE      9
    // ********************************************************************
    // *                      Types
    // ********************************************************************
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
    typedef t_eReturnCode (t_cbACT_cfg)(t_uint8 f_pin_u8, t_eArduino_PinMode f_Pinmode_e);
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
    typedef t_eReturnCode (t_cbACT_SetVal)(t_sint16 f_value_s16);
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
    typedef t_eReturnCode (t_cbACT_GetVal)(t_sint16 *f_value_s16);

    typedef struct
    {
        t_cbACT_cfg    *ActCfg_pcb;
        t_cbACT_SetVal *ActSetVal_pcb;
        t_cbACT_GetVal *ActGetVal_pcb;

    }t_sACT_SysActCfg;

    /* CAUTION : Automatic generated code section: Start */
	typedef enum {
		ACT_CMD_IRRIGVALVE_TOMATE,
		ACT_CMD_IRRIGVALVE_COURGETTE,
		ACT_CMD_IRRIGVALVE_CAROTTE,

		ACT_NUMBER,
	}t_eACT_Actuators;
    
	static const t_sACT_SysActCfg c_SysActCfg_as[ACT_NUMBER] = 
	{
		{ACT_Cmd_IrrigValve_Tomate_Cfg              ,ACT_Cmd_IrrigValve_Tomate_Set              ,ACT_Cmd_IrrigValve_Tomate_Get},
		{ACT_Cmd_IrrigValve_Courgette_Cfg           ,ACT_Cmd_IrrigValve_Courgette_Set           ,ACT_Cmd_IrrigValve_Courgette_Get},
		{ACT_Cmd_IrrigValve_Carotte_Cfg             ,ACT_Cmd_IrrigValve_Carotte_Set             ,ACT_Cmd_IrrigValve_Carotte_Get},
	};
	/* CAUTION : Automatic generated code section: End */
    // ********************************************************************
    // *                      Prototypes
    // ********************************************************************
        
    // ********************************************************************
    // *                      Variables
    // ********************************************************************
    static const t_uint8 c_ActuatorsPin_ua8[ACT_NUMBER] = {
        PIN_ACT_IRRIGVALVE_TOMATE,                              // ACT_CMD_IRRIGVALVE_TOMATE
        PIN_ACT_IRRIGVALVE_COURGETTE,                           // ACT_CMD_IRRIGVALVE_COURGETTE
        PIN_ACT_IRRIGVALVE_CAROTTE,                             // ACT_CMD_IRRIGVALVE_CAROTTE            
    };
    static const t_eArduino_PinMode c_Actuators_PinMode_ea[ACT_NUMBER] = {PINMODE_OUTPUT, PINMODE_OUTPUT, PINMODE_OUTPUT};
    
    
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
