/*********************************************************************
 * @file        Irrig.h
 * @brief       Template_BriefDescription.
 * @details     TemplateDetailsDescription.\n
 *
 * @author      AUDMBA
 * @date        09/03/2024
 * @version     1.0
 *********************************************************************/
#ifndef IRRIG_H_INCLUDED
#define IRRIG_H_INCLUDED
// ********************************************************************
// *                      Includes
// ********************************************************************
#include <Arduino.h>
#include <avr/sleep.h>
#include <avr/wdt.h>

#include "Devices/devices.h"
#include "ArduinoLib/ArduinoLib.h"
// ********************************************************************
// *                      Defines
// ********************************************************************

// ********************************************************************
// *                      Types
// ********************************************************************
typedef enum 
{
    IRRIG_STATUS_CONNECTED,
    IRRIG_STATUS_DISCONNECTED,
    IRRIG_STATUS_UNKNOWN,

    IRRIG_STATUS_NB,
}t_eIrrig_CoState;

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
 *	@brief      Receive and Schedule the receive Task
 *	@details
 *
 *
 *	@param[in] 
 *	@param[out]
 *	 
 *
 *
 */
t_eReturnCode LgcIrrig_Init(void);  
/**
 *
 *	@brief      Receive and Schedule the receive Task
 *	@details
 *
 *
 *	@param[in] 
 *	@param[out]
 *	 
 *
 *
 */
t_eReturnCode LgcIrrig_Cyclic(void);        

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
#endif 
