/*********************************************************************
 * @file        Arduino_ConfigSpecific.h
 * @brief       Template_BriefDescription.
 * @details     TemplateDetailsDescription.\n
 *
 * @author      AUDMBA
 * @date        jj/mm/yyyy
 * @version     1.0
 */
  
#ifndef ARDUINO_CONFIGSPECIFIC_C_INCLUDED
#define ARDUINO_CONFIGSPECIFIC_C_INCLUDED





    // ********************************************************************
    // *                      Includes
    // ********************************************************************
    
    // ********************************************************************
    // *                      Defines
    // ********************************************************************
    //#define DEBUG_MODE
    #define DEBUG_PRINTER                                                     
       Serial /**< Define where debug output will be printed.*/                
          

    //uncomment next line to make DEBUG MODE OPERATIONNAL
    //#define DHT_DEBUG


    #ifdef DEBUG_PRINTER
    #define DEBUG_PRINT(...)                                                       \
    { DEBUG_PRINTER.print(__VA_ARGS__); }
    #define DEBUG_PRINTLN(...)                                                     \
    { DEBUG_PRINTER.println(__VA_ARGS__); }
    #else
    #define DEBUG_PRINT(...)                                                       \
    {} // Placeholder si le débogage est désactivé
    #define DEBUG_PRINTLN(...)                                                     \
    {} // Placeholder si le débogage est désactivé
    #endif

    #define MAX_PIN 21
    // ********************************************************************
    // *                      Types
    // ********************************************************************
    typedef enum 
    {
        PINMODE_INPUT = 0x00,   // INPUT
        PINMODE_OUTPUT = 0x01,  // OUTPUT
        PINMODE_PULLUP = 0x02,  // PULL_UP

        PINMODE_NB,
    }t_eArduino_PinMode;
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

    //********************************************************************************
    //                      Local functions - Implementation
    //********************************************************************************
#endif // ARDUINO_CONFIGSPECIFIC_C_INCLUDED           
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
