/*********************************************************************
 * @file        Irrig.h
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

// ********************************************************************
// *                      Defines
// ********************************************************************

// ********************************************************************
// *                      Types
// ********************************************************************
typedef enum 
{
    IRRIG_ARDUINO_MODE_SLEEP,
    IRRIG_ARDUINO_MODE_WAKEUP,
    IRRIG_ARDUINO_MODE_ASK_TASK,
    IRRIG_ARDUINO_MODE_SEND_SENSORS_VALUES,
    IRRIG_ARDUINO_MODE_RCV_ACTUATORS_DATAS,
    IRRIG_ARDUINO_MODE_SET_ACTUATORS,
    IRRIG_ARDUINO_MODE_CHECK_ACT_DURATION,

}t_eIrrig_ArduinoState;

typedef enum 
{
    IRRIG_MODE_SNS,
    IRRIG_MODE_SNS_ACT,
    IRRIG_MODE_ACT,

    IRRIG_MODE_NB,
}t_eIrrig_ArduinoMode;
// ********************************************************************
// *                      Prototypes
// ********************************************************************
    
// ********************************************************************
// *                      Variables
// ********************************************************************


/**< Msg configuration*/

const char * c_Arduino_AskCmd_pac               = "999";
const char * c_Arduino_SendSNSvalues_pac        = "111";
const char * c_Arduino_SetActuators_pac         = "200";
const char * c_Arduino_RcvActuatorsValues_pac   = "222";
const char * c_Arduino_RcvActuatorsDuration_pac = "244";
const char * c_Arduino_ActTaskCompleted_pac     = "200 : ok";

/**<Arduino Mode Configuration */
t_eIrrig_ArduinoMode ArdMode_e = IRRIG_MODE_SNS_ACT;
//********************************************************************************
//                      Local functions - Prototypes
//********************************************************************************

//****************************************************************************
//                      Public functions - Implementation
//********************************************************************************


 
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
