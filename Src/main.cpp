/*********************************************************************
 * @file        main.cpp
 * @brief       Template_BriefDescription.
 * @details     TemplateDetailsDescription.\n
 *
 * @author      AUDMBA
 * @date        08/03/2024
 * @version     1.0
 *********************************************************************/
  
// ********************************************************************
// *                      Includes
// ********************************************************************
#include "Logic/Irrigation/Irrig.h"
#include "avr8-stub.h"
// ********************************************************************
// *                      Defines
// ********************************************************************
#define SERIAL_BAUDRATE 115200
#define ARDUINO_WAIT_CYCLIC 2000
// ********************************************************************
// *                      Types
// ********************************************************************

// ********************************************************************
// *                      Constants
// ********************************************************************

// ********************************************************************
// *                      Variables
// ********************************************************************
t_uint8 g_ComUsed_u8 = ARDCOM_WIFI;
//****************************************************************************
//                      Local functions - Prototypes
//****************************************************************************

// ***************************************************************************
// *                      Class declaration
// ***************************************************************************

//****************************************************************************
//                      Public functions - Implementation
//****************************************************************************

//****************************************************************************
//                      Local functions - Implementation
//****************************************************************************

// ***************************************************************************
// *                       setup implementation 
// ***************************************************************************
void setup() 
{
    t_eReturnCode Ret_e = RC_OK;
    #ifdef DEBUG_PRINTER // see in ArduinoCfg
    Serial.begin(SERIAL_BAUDRATE);
    #endif
    #ifdef DEBUG_MODE
    debug_init();
    #endif
    Ret_e = LgcIrrig_Init();
    if(Ret_e != RC_OK)
    {
        while(1)
        {
            DEBUG_PRINT("Error in Init");
            delay(1000);
        }
    }
}

// ********************************************************************
// *                       loop implmentation
// ********************************************************************
void loop() 
{
    t_eReturnCode Ret_e = RC_OK;
    
    Ret_e =  LgcIrrig_Cyclic();

    delay(ARDUINO_WAIT_CYCLIC);
}

//****************************************************************************
// End of File
//****************************************************************************


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