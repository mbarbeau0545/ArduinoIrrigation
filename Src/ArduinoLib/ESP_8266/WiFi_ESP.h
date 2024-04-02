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
   


    #define MODEM_TIMEOUT          10000            /* Maximum time waiting for device to respond*/
    #define MODEM_EXTENDED_TIMEOUT 60000
    #define MODEM_MAX_BUFF_SIZE    128              /*Max buffer size*/
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
    #define ESP_WL_MAX_ATTEMPT_CONNECTION	5
    //SSL max buffer size 
    #define ESP_SSL_MAX_BUFFER_SIZE 2048
    //SSL min buffer size 
    #define ESP_SSL_MIN_BUFFER_SIZE 4096
    // ********************************************************************
    // *                      Types
    // ********************************************************************
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
    /*START : Connection State of the different kind of connection */
    typedef enum
    {
        ESP_TCP_DISANBALE = 0,
        ESP_TCP_ENBALE,
        ESP_TCP_LISTEN,
        ESP_TCP_SYN_SENT,
        ESP_TCP_SYN_RCVD,
        ESP_TCP_FIN_WAIT_1,
        ESP_TCP_FIN_WAIT_2,
        ESP_TCP_CLOSE_WAIT,
        ESP_TCP_CLOSING,
        ESP_TCP_LAST_ACK,
        ESP_TCP_TIME_WAIT,

        ESP_TCP_NB,
    }t_eESP_TCPState;

    typedef enum
    {
        ESP_UDP_DISABLE = 0,
        ESP_UDP_ENABLE,
        ESP_UDP_SYN_SENT,
        ESP_UDP_SYN_RCV,
        ESP_UDP_TIME_WAIT,

        ESP_UDP_NB,
    }t_eESP_UDPState;

    typedef enum 
    {
        ESP_SSL_DISABLE = 0,
        ESP_SSL_ENABLE,
        ESP_SSL_SYN_SENT,
        ESP_SSL_SYN_RCV,
        ESP_SSL_TIME_WAIT,

        ESP_SSL_NB,
    }t_eESP_SSLState;
    /*END : Connection State of the different kind of connection */
    typedef union 
    {
        t_eESP_TCPState TCP_State_e;
        t_eESP_UDPState UDPState_e;
        t_eESP_SSLState SSLState_e;
    }t_uESP_ConnectionState;
    typedef enum 
   {
        ESP_CONNECTION_TCP_CLIENT = 0,
        ESP_CONNECTION_TCP_SERVER,
        ESP_CONNECTION_UDP,
        ESP_CONNECTION_SSL,

        ESP_CONNECTION_NB,
        ESP_CONNECTION_UNKNOWN,
   }t_eESP_ConnectionType;

    typedef struct 
    {
        t_sESP_WifiCfg        WifiCfg_s;
        t_eESP_ConnectionType ConnectType_e;
        t_uESP_ConnectionState ConnectState_u;
    }t_sESP_Cfg;


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
        ESP_SEND_DATA_SERIAL = 0,                   //  transparent transmission mode which require to be single connection mode
        ESP_SEND_DATA_HEX,                          //  Send data hexadecimal way
        ESP_SEND_DATA_BUFF,                         // Write data into TCP-send-buffer, This command can NOT be used on SSL connection.
    }t_eESP_SendDataMode;
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
    t_eReturnCode ESP_Init(t_uint32 f_baudrate_u32, t_uint8 f_rxPin_u8, t_uint8 f_txPin_u8);
    /**
    *
    *	@brief     Connection to the Wifi using the ESP 
    *	@details   Thanks to AT command make connection to the Wifi
    *
    *
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
    t_eReturnCode ESP_ConnectWifi(const char *f_SSID, const char *f_password);
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
    t_eReturnCode ESP_DisConnectWifi(void);
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
    t_eReturnCode ESP_Cfg(t_eESP_WifiMode f_WifiMode_e, t_eESP_TCPState f_TCPState_e, const char* f_IP_address_pc, t_uint16 f_port_u16);
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
    t_eReturnCode ESP_GetCfg(t_sESP_Cfg *f_ESP_Config_e);
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
    t_eReturnCode ESP_GetFirmwareVersion(const char *f_firmwareVersion_pc);

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
