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
    typedef t_eReturnCode (t_cbACT_cfg)(t_uint8 f_pin, t_eArduino_PinMode);
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

    typedef enum 
    {
        ACT_FUNCTION_CFG = 0,
        ACT_FUNCTION_SET,
        ACT_FUNCTION_GET,

        ACT_FUNCTION_NB,
    }t_eACT_Function;
    /* CAUTION : Automatic generated code section: Start */
	typedef enum {
		ACT_CMD_IRRIGVALVE,

		ACT_NUMBER,
	}t_eACT_Actuators;
	static const t_sACT_SysActCfg c_SysActCfg_as[ACT_NUMBER] = 
	{
		{ACT_Cmd_IrrigValve_Cfg                     ,ACT_Cmd_IrrigValve_Set                     ,ACT_Cmd_IrrigValve_Get},
	};
	/* CAUTION : Automatic generated code section: End */
    // ********************************************************************
    // *                      Prototypes
    // ********************************************************************
        
    // ********************************************************************
    // *                      Variables
    // ********************************************************************
    static const t_uint8 c_ActuatorsPin_ua8[ACT_NUMBER] = {
        12                            //ACT_CMD_IRRIGVALVE
    };

    static const t_eArduino_PinMode c_Actuators_PinMode_ea[ACT_NUMBER] = {PINMODE_OUTPUT};
    
    
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
