/*********************************************************************
 * @file        ACT.h
 * @brief       Template_BriefDescription.
 * @details     TemplateDetailsDescription.\n
 *
 * @author      AUDMBA
 * @date        09/03/2024
 * @version     1.0
 *********************************************************************/


#ifndef ACT_H_INCLUDED
#define ACT_H_INCLUDED
    // ********************************************************************
    // *                      Includes
    // ********************************************************************
    #include "./AppCommon/TypeCommon.h"

    #include "./ConfigSpecific/Actuators/Actuators_CfgSpec.h"

    #include  <Arduino.h>
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
    t_eReturnCode ACT_Init(void);
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
    t_eReturnCode ACT_Set_Cfg(t_eACT_Actuators f_actuatorName_e);

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
    t_eReturnCode ACT_Set(t_eACT_Actuators f_actuatorName_e, t_sint16 f_ActVal_s16);

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
    t_eReturnCode ACT_Get(t_eACT_Actuators f_actuatorName_e, t_sint16 *f_ActVal_s16);
    
    //********************************************************************************
    //                      Local functions - Implementation
    //******************************************************************************** 
#endif // ACT_H_INCLUDED      
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
