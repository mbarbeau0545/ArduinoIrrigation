/*********************************************************************
 * @file        WiFi_ESP8266.h
 * @brief       Template_BriefDescription.
 * @details     TemplateDetailsDescription.\n
 *
 * @author      xxxxxx
 * @date        jj/mm/yyyy
 * @version     1.0
 */
  
#ifndef WIFI_ESP8266_H_INCLUDED
#define WIFI_ESP8266_H_INCLUDED





    // ********************************************************************
    // *                      Includes
    // ********************************************************************
    #include "Arduino.h"

    #include "Modem.h"
    // ********************************************************************
    // *                      Defines
    // ********************************************************************


    // Maximum size of a SSID
    #define ESP_WL_SSID_MAX_LENGTH 32
    // Length of passphrase. Valid lengths are 8-63.
    #define ESP_WL_WPA_KEY_MAX_LENGTH 63
    // Length of key in bytes. Valid values are 5 and 13.
    #define ESP_WL_WEP_KEY_MAX_LENGTH 13
    // Size of a MAC-address or BSSID
    #define ESP_WL_MAC_ADDR_LENGTH 6
    // Size of a MAC-address or BSSID
    #define ESP_WL_IPV4_LENGTH 4
    // Maximum size of a SSID list
    #define ESP_WL_NETWORKS_LIST_MAXNUM	10
    // Maxmium number of socket
    #define	ESP_AX_SOCK_NUM		4
    // Socket not available constant
    #define ESP_OCK_NOT_AVAIL  255
    // Default state value for Wifi state field
    #define ESP_NA_STATE -1
    //Maximum number of attempts to establish esp connection
    #define ESP_WL_MAX_ATTEMPT_CONNECTION	3
    //TCP, UDP max buufer size to send data 
    #define ESP_TCP_UDP_MAX_BUFFER_SIZE 2048
    //SSL max buffer size 
    #define ESP_SSL_MAX_BUFFER_SIZE 2048
    //SSL min buffer size 
    #define ESP_SSL_MIN_BUFFER_SIZE 4096
    // ********************************************************************
    // *                      Types
    // ********************************************************************
        /**<START FOR ESP8266 */
    typedef enum 
    {
        ESP_WIFI_STATUS_CONNECTED = 0,              //The WiFi is now connected.
        ESP_WIFI_STATUS_CONNECTION_FAILED,          // Try to connect to WiFi but failed.
        ESP_WIFI_STATUS_CONNECTION_LOST,            // For unknown reason, connection lost.
        ESP_WIFI_STATUS_DISCONNECTED,               //The WiFi is know deconnected
        ESP_WIFI_STATUS_AP_LISTENNING,
        ESP_WIFI_STATUS_AP_CONNECTED,
        ESP_WIFI_STATUS_AP_FAILED,
        ESP_WIFI_STATUS_NO_SSID_AVAILABLE,

        ESP__WIFI_NB,
    }t_eESP_WiFiStatus;

    typedef enum 
    {
        ESP_WIFI_MODE_STATION = 0,
        ESP_WIFI_MODE_AP,
        ESP_WIFI_MODE_BOTH,

        ESP_WIFI_MODE_NB,
        ESP_WIFI_MODE_UNDEFINED,        
    }t_eESP_WifiMode;

    typedef struct
    {
        t_eESP_WifiMode   WifiMode_e;
        t_eESP_WiFiStatus WifiStatus_e;
    }t_sESP_WifiCfg;
    typedef enum 
    {
        ESP_PROTOCOL_STATE_CONNECTED = 0,                   // Protocol communication is connected 
        ESP_PROTOCOL_STATE_DISCONNECT,                      // Protocol communication is disconnected
        ESP_PROTOCOL_STATE_FAILED,                          // Try to make protocol communication but failed
        ESP_PROTOCOL_STATE_SYN_SENT,
        ESP_PROTOCOL_STATE_SYN_RCV,
    }t_eESP_ProtocolState;
    typedef enum 
   {
        ESP_CONNECTION_TCP_CLIENT = 0,
        ESP_CONNECTION_TCP_SERVER,
        ESP_CONNECTION_UDP,
        ESP_CONNECTION_SSL,

        ESP_CONNECTION_NB,
        ESP_CONNECTION_UNKNOWN,
   }t_eESP_ConnectionType;

   typedef enum 
   {
        ESP_SLEEPMODE_DISABLE = 0,                          // Disable sleep mode, full operational. still responding.
        ESP_SLEEPMODE_LIGHT,                                // ext/int timers are off but proccessuer still responding. 
        ESP_SLEEPMODE_MODEM,                                // Modem Wifi is on, but proccess and timer are off,still responding
        ESP_SLEEPMODE_TIME,                                 // everything is disconnected during an amount of time, not responding until time is out, DEFAULT MODE

        ESP_SLEEPMODE_NB,
        ESP_SLEEP_UNKNOWN,
   }t_eESP_SleepMode;

    typedef enum 
   {
    ESP_MAKE_CFG_INTO_FLASH = 0, // Advised, automatically configured Wi-Fi and Connection Type
    ESP_MAKE_CFG_INTO_RAM,

    ESP_MAKE_CFG_INTO_NB,
   }t_eESP_WriteCfgMode;

    typedef enum
    {
        ESP_ENC_TYPE_WEP = 0,
        ESP_ENC_TYPE_WPA,
        ESP_ENC_TYPE_WPA2,
        ESP_ENC_TYPE_WPA2_ENTERPRISE,
        ESP_ENC_TYPE_WPA3,
        ESP_ENC_TYPE_NONE,
        ESP_ENC_TYPE_AUTO,

        ESP_ENC_TYPE_NB,
    }t_eESP_EncryptionType;

    typedef enum 
    {
        ESP_EXCHANGE_DATA_SERIAL = 0,                   //  transparent transmission mode which require to be single connection mode
        ESP_EXCHANGE_DATA_HEX,                          //  Send data hexadecimal way
        ESP_EXCHANGE_DATA_BUFF,                         // Write data into TCP-send-buffer, This command can NOT be used on SSL connection.

        ESP_EXCHANGE_DATA_NB,
    }t_eESP_ExchangeDataMode;


    typedef struct 
    {
        t_sESP_WifiCfg        WifiCfg_s;
        t_eESP_ConnectionType ConnectType_e;
        t_eESP_ProtocolState  ConnectState_e;
        t_eESP_SleepMode      SleepMode_e;
    }t_sESP_ComStatus;


    // ********************************************************************
    // *                      Prototypes
    // ********************************************************************
        
    // ********************************************************************
    // *                      Variables
    // *******************************************************************
    
    // ********************************************************************
    // *                      Public Functions
    // ********************************************************************  
    /**
    *
    *	@brief Initialize the communication with the ESP
    *	@details Using Serial Communication 
    *
    *
    *	@param[in] f_baudrate_u32 : The Baudrate use to communicate, usually for ESP8266, it should be 115200
    *	@param[in] f_rxPin_u8     : Rx pin serial communication 
    *	@param[in] f_TxPin_u8     : Tx pin serial communication 
    *	@param[out]
    *   RC_ERROR_MODULE_NOT_INITIALIZED : An error occured, The module is not initialized
    *   RC_OK                           : Module succesfully initialized 
    *	 
    *
    *
    */ 
    t_eReturnState ESP_Init(void);
    /**
    *
    *	@brief      End every Communication outside and inside the ESP
    *	@details    If Wifi or a Protocol communication is connected, 
    *               there will be disconnected. The Serial Com is also disconnected.
    *
    *
    *	@param[in] 
    *	@param[out]
    *   RC_OK                           : Function succesfully close all communication 
    *   See ESP_DisConnectWifi and ESP_Close_ProtocolCom
    */
    t_eReturnState ESP_Close(void);
    /**
    *
    *	@brief     Connection to the Wifi using the ESP 
    *	@details   Thanks to AT command make connection to the Wifi
    *
    *
    *	@param[in] f_WifiMode_e    : WiFi Configuration 
    *	@param[in] f_SSID          : ssid of WiFi
    *	@param[in] f_password      : password of Wi_Fi
    *	@param[out]
    *   RC_ERROR_MODULE_NOT_INITIALIZED : The module is not initialized.
    *   RC_ERROR_PTR_NULL               : At least one of pointor is null.
    *   RC_ERROR_WRONG_RESULT           : Problem With Module Modem
    *   RC_OK                           : Wifi Connected
    *	 
    *
    *
    */ 
    t_eReturnState ESP_ConnectWifi(const char *f_SSID, const char *f_password);
        /**
    *
    *	@brief Disconnect the Wifi 
    *	@details
    *
    *
    *	@param[out]
    *	RC_ERROR_MODULE_NOT_INITIALIZED : The module was not initialized.
    *   RC_ERROR_WRONG_RESULT           : Problem With Module Modem
    *   RC_OK                           : Wifi Disconnected
    *
    */ 
    t_eReturnState ESP_DisConnectWifi(void);
    /**
    *
    *	@brief      Enable user to make communication
    *	@details    The user can choose between 3 protocol communication in
    *               t_eESP_ConnectionType, TCP, UDP, SSL
    *               If Wifi is not connected, it try make it.\n
    *
    *
    *	@param[in] f_ProtocolCom_Type_e   : kinf of Protocol accepted TCP, UDP, SSL
    *	@param[in] f_IP_Address_pc        : address IP of Server / may be client ?
    *	@param[in] f_port_u16             : Port to connect
    *   @param[out]
    *   
    */  
    t_eReturnState ESP_Start_ProtocolCom(void);
    /**
    *
    *	@brief      Close Protocol Communication
    *	@details
    *
    *
    *	@param[in] 
    *	@param[out]
    *   RC_OK                           : Communication Port closed Succesfully
    *   See s_ESP_MakeCommand in .c file for other RetVal
    *
    *
    */
    t_eReturnState ESP_Close_ProtocolCom(void);
    /**
    *
    *	@brief      Allow user to send data using Protocol Communication
    *	@details    Once ESP_Start_ProtocolCom is call and connection is established 
    *               as server or client. In the second case user can send msg in different 
    *               way posssible by the esp according to t_eESP_SendDataMode
    *
    *
    *	@param[in] f_DataMode_e         : Message format 
    *	@param[in] f_dataToSend_pc      : Message user want to send 
    *	@param[out]
    *	RC_ERROR_MODULE_NOT_INITIALIZED : The module was not initialized.\n
    *   RC_ERROR_PTR_NULL               : At least one of pointor is null.\n
    *   RC_ERROR_PARAM_INVALID          : f_DataMode_e not allowed.\n
    *   RC_WARNING_WRONG_CONFIG         : Conexion is not currently estalibished.\n
    *   RC_ERROR_NOT_ALLOWED            : User can not use SendBuf in SSL connection.\n
    *   RC_OK                           : Data send succesfully.\n
    */ 
    t_eReturnState ESP_SendData_WithProtocolCom(char * f_dataToSend_pc);
    /**
    *
    *	@brief
    *	@details
    *
    *
    *	@param[in] f_RcvDataMode_e : The Rcv mode
    *	@param[in] f_RcvData_pc    : contain the Rcv msg from Connection 
    *	@param[out]
    *	RC_ERROR_MODULE_NOT_INITIALIZED : The module was not initialized.\n
    *   RC_ERROR_PTR_NULL               : At least one of pointor is null.\n
    *   RC_ERROR_PARAM_INVALID          : f_RcvDataMode_e not allowed.\n
    *   RC_WARNING_WRONG_CONFIG         : Conexion is not currently estalibished.\n
    *   RC_ERROR_COPY_FAILED            : Copy into f_RcvData_pc failed
    *   RC_OK                           : Data receive succesfully.\n
    *	 
    *
    *
    */
    t_eReturnState ESP_RcvData_WithProtocolCom(char * f_RcvData_pc);
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
    t_eReturnState ESP_Get_ProtocolCom_Cfg(t_sESP_ComStatus *f_ESP_Config_u);
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
    t_eReturnState ESP_GetFirmwareVersion(char *f_firmwareVersion_pc);
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
    t_eReturnState ESP_SetSleepMode(t_eESP_SleepMode f_sleepMode_e, t_uint32 f_timeSleeping_u32);
#endif // WIFI_ESP8266_H_INCLUDED           
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
