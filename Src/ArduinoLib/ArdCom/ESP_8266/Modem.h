/*********************************************************************
 * @file        Modem.h
 * @brief       Template_BriefDescription.
 * @details     TemplateDetailsDescription.\n
 *
 * @author      AUDMBA
 * @date        31/03/2024
 * @version     1.0
 */
  
#ifndef MODEM_H_INCLUDED
#define MODEM_H_INCLUDED





    // ********************************************************************
    // *                      Includes
    // ********************************************************************
    #include "AppCommon/TypeCommon.h"
    #include "Arduino.h"
    // ********************************************************************
    // *                      Defines
    // ********************************************************************
    #define MODEM_TIMEOUT          7000            /* Maximum time waiting for device to respond*/
    #define MODEM_EXTENDED_TIMEOUT 60000
    #define MODEM_MAX_BUFF_SIZE    96              /*Max buffer size*/
    // ********************************************************************
    // *                      Types
    // ********************************************************************

    // ********************************************************************
    // *                      Prototypes
    // ********************************************************************
        
    // ********************************************************************
    // *                      Variables
    // ********************************************************************
	
	// ********************************************************************
    // *                      Public Functions
    // ********************************************************************
    /**
    *
    *	@brief Initiate SerialPort for communication with ESP
    *	@details
    *
    *
    *	@param[in] f_baudrate_u32 : The Baudrate use to communicate, usually for ESP8266, it should be 115200
    *	@param[in] f_rxPin_u8     : Rx pin serial communication 
    *	@param[in] f_TxPin_u8     : Tx pin serial communication 
    *	@param[out] 
    *   RC_ERROR_MODULE_NOT_INITIALIZED : An error occured, The module is not initialized
    *   RC_OK                           : Module initialized 
    */
    t_eReturnState Modem_InitCom(t_uint32 f_baudrate_u32, t_uint8 f_rxPin_u8, t_uint8 f_txPin_u8);
    /**
    *
    *	@brief End communication with Serial 
    *	@details End Serial Communication and desalloc memory 
    *            for g_esp8266Serial_pcl
    *
    *
    *	@param[in] 
    *	@param[out]
    *	 
    *
    *
    */
   void Modem_EndCom(void);
   /**
    *
    *	@brief Write data using UTF8 encoded message
    *	@details 
    *
    *
    *	@param[in] f_txbuffer_pc : Message to send
    *	@param[out]
    *   RC_ERROR_MODULE_NOT_INITIALIZED : The module is not initialized.
    *   RC_ERROR_PTR_NULL               : At least one of pointor is null.
    *   RC_ERROR_LIMIT_REACHED          : Data has been send but not entirely.
    *   RC_OK                           : Data has been send succesfully. 
   */
  t_eReturnState Modem_Write(const char *f_txbuffer_pc);
  /**
    *
    *	@brief Read buffer and copy it on f_rxBuffer_pc 
    *	@details
    *
    *
    *	@param[in] f_rxBuffer_pc : data received
    *	@param[out]
    *   RC_ERROR_MODULE_NOT_INITIALIZED : The module is not initialized.
    *   RC_ERROR_PTR_NULL               : At least one of pointor is null.
    *   RC_WARNING_LIMIT_REACHED        : The data received has fullfilled buffer size or take to much to time to arrive.
    *   RC_ERROR_COPY_FAILED            : Data received but copy into f_rxBuffer_pc failed.
    *   RC_OK                           : Data received and copy succesfully.
    *	 
    *
    *
    */
   t_eReturnState Modem_ReadBuffer(char *f_rxBuffer_pc);


#endif // MODEM_H_INCLUDED           
//************************************************************************************
// End of File
//************************************************************************************

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
