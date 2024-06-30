/*********************************************************************
 * @file        ArdCom_ConfigSpecific.h
 * @brief       Template_BriefDescription.
 * @details     TemplateDetailsDescription.\n
 *
 * @author      AUDMBA
 * @date        jj/mm/yyyy
 * @version     1.0
 */
  
#ifndef WIFIESP_CFGSPEC_H_INCLUDED
#define WIFIESP_CFGSPEC_H_INCLUDED





    // ********************************************************************
    // *                      Includes
    // ********************************************************************

    #include "ArduinoLib/ArdCom/ESP_8266/WiFi_ESP.h"

    // ********************************************************************
    // *                      Defines
    // ********************************************************************
    #define BAUDRATE_WIFI 115200
    // ********************************************************************
    // *                      Types
    // ********************************************************************
    typedef struct 
    {
        t_eESP_WifiMode             WifiMode_e;
        t_eESP_ExchangeDataMode     exchangeType_e;
        t_eESP_ConnectionType       ProtComType_e;
        t_uint32                    baudRate_u32;
        t_uint8                     rxPin_u8;
        t_uint8                     txPin_u8;
        const char *                serverID_pac;
        t_uint8                     serverPrt_u8;
        const char *                LiveBoxName_pac;
        const char *                password_pac;
    }t_sESP_ClientCfg;
    // ********************************************************************
    // *                      Prototypes
    // ********************************************************************
        
    // ********************************************************************
    // *                      Variables
    // ********************************************************************

    /* CAUTION : Automatic generated code section: Start */

    /**< Wifi COnfiguration*/
    const t_sESP_ClientCfg c_ESPComProjectCfg_s = {
        .WifiMode_e         = ESP_WIFI_MODE_STATION,
        .exchangeType_e     = ESP_EXCHANGE_DATA_SERIAL,
        .ProtComType_e      = ESP_CONNECTION_TCP_CLIENT,
        .baudRate_u32       = (t_uint32)BAUDRATE_WIFI, // Par exemple, BAUDRATE_WIFI peut être 115200
        .rxPin_u8           = 10,
        .txPin_u8           = 11,
        .serverID_pac       = "192.168.1.26",    
        .serverPrt_u8       = 80,
        .LiveBoxName_pac    = "Livebox-E030",
        .password_pac       = "ZRvFTt7t2kfVaWrSYX",
        
    };
    /*const char * SSID_Nantes =  "Livebox-E030";
    const char * Password_Nantes =  "ZRvFTt7t2kfVaWrSYX";
    const char * IP_AUDMBA_Nantes =  "192.168.1.26";*/
    /* CAUTION : Automatic generated code section: End */
    //****************************************************************************
    //                      Public functions - Prototypes
    //********************************************************************************

#endif // WIFIESP_CFGSPEC_H_INCLUDED           
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
/*const char * c_SSID_Petite_Boule_pac =  "Livebox-0BB3";
const char * c_Password_Petite_Boule_pac =  "7CF8844459F167816393050EE2";
const char * c_IP_AUDMBA_Petite_Boule_pac =  "192.168.1.26";*/