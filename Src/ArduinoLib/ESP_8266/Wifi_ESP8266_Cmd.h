/*********************************************************************
 * @file        Wifi_ESP8266_Cmd.h
 * @brief       This file repertory all cmd used.
 * @details     In order to interact with the ESP_8266,\n
 *              We have to send him command thanks to esp8266 instruction.\n
 *
 * @author      xxxxxx
 * @date        jj/mm/yyyy
 * @version     1.0
 */
  
#ifndef WIFI_ESP8266_CMD_H_INCLUDED
#define WIFI_ESP8266_CMD_H_INCLUDED





    // ********************************************************************
    // *                      Includes
    // ********************************************************************
    
    // ********************************************************************
    // *                      Defines
    // *********************************************************************
    /*START enumerate AT command*/

    #define _AT                     "AT"                   //Test AT startup 
    #define _ENDL                   "\r\n"             
    #define _RESET                  "+RST"                 //Restart module
    #define _GMR                    "+GMR"                 //View version info
    #define _SLPMODE_T              "+GSLP"                //Enter deep-sleep mode With time 
    #define _RESTORE                "+RESTORE"             //Reset all parameters saved in flash
    #define _UART                   "+UART"                // sets the UART configuration and writes the new configuration to the flash
    #define _UART_CUR               "+UART_CUR"            //sets the UART configuration and writes the new configuration to the flash
    #define _UART_DEF               "+UART_DEF"            //sets the UART configuration and writes the new configuration to the flash
    #define _SLPMODE_M              "+SLEEP"               //Enter deep-sleep modeWith mode
    #define _RFPOWER                "+RFPOWER"             //maximum value of RF TX power, range 0 ~ 82, unit:0.25dBm
    #define _RFVDD                  "+RFVDD"               // RF TX power according to VDD33
    #define _CWMODE                 "+CWMODE"              //1-stationmode, 2 SoftAP mode, 3- SOFTAP+Station Mode
    #define _CWMODE_CUR             "+CWMODE_CUR"          //Not store in flash
    #define _CWMODE_DEF             "+CWMODE_DEF"          //This configuration will store in Flash system parameter area.
    #define _CWJAP                  "+CWJAP"               //DEPRECATED !! 
    #define _CWJAP_CUR              "+CWJAP_CUR"           //Connect to AP, for current, This configuration will NOT store in Flash .
    #define _CWJAP_DEF              "+CWJAP_DEF"           //– Connect to AP, for current, This configuration will store in Flash system parameter area.
    #define _CWLAPOPT               "+CWLAPOPT"            //This command is to set the configuration for command AT+CWLAP
    #define _CWLAP                  "+CWLAP"               //List of all available AP's detected by ESP8266
    #define _CWQAP                  "+CWQAP"               //– Disconnect from WiFi
    #define _CWSAP                  "+CWSAP"               //DEPECRATED use CUR or DEF,  Configuration of softAP mode
    #define _CWSAP_CUR              "+CWSAP_CUR"           //  Configuration of softAP mode
    #define _CWSAP_DEF              "+CWSAP_DEF"           //  Configuration of softAP mode
    #define _CWLIF                  "+CWLIF"               //get the IP of stations that are connected to ESP8266 softAP
    #define _CWDHCP                 "+CWDHCP"              //DEPRECATED !! Enable/Disable DHCP,  AT+CWDHCP=<mode>, <en>
    #define _CWDHCP_CUR             "+CWDHCP_CUR"          // Enable/Disable DHCP, won’t save to flash
    #define _CWDHCP_DEF             "+CWDHCP_DEF"          //Enable/Disable DHCP and save to flash
    #define _CWDHCPS_CUR            "+CWDHCPS_CUR"         //Set the IP address allocated by ESP8266 soft-AP DHCP, cannot save to flash
    #define _CWDHCPS_DEF            "CWDHCPS_DEF"          //Set the IP address allocated by ESP8266 soft-AP DHCP, save to flash
    #define _CWAUTOCONN             "+CWAUTOCONN"          //Auto connect to AP or not,store in Flash
    #define _CIPSTAMAC              "+CIPSTAMAC"           //Set MAC address of station,MAC addresses of ESP8266 soft-AP and station are different, do not make the same
    #define _CIPSTAMAC_CUR          "+CIPSTAMAC_CUR"       // Set MAC address of station 
    #define _CIPSTAMAC_DEF          "+CIPSTAMAC_DEF"       //Set MAC address of station, save as default, Store in flash
    #define _CIPAPMAC               "+CIPAPMAC"            //DEPRECATED !! 
    #define _CIPAPMAC_CUR           "+CIPAPMAC_CUR"        // Set MAC address of softAP, MAC addresses of ESP8266 soft-AP and station are different, please do NOT set them identically, not store in flash
    #define _CIPAPMAC_DEF           "+CIPAPMAC_DEF"        // Set MAC address of softAP, MAC addresses of ESP8266 soft-AP and station are different, please do NOT set them identically, store in flash
    #define _CIPSTA                 "+CIPSTA"              //DEPRECATED !! Set IP address of station
    #define _CIPSTA_CUR             "+CIPSTA_CUR"          //Set IP address of station, not store in flash
    #define _CIPSTA_DEF             "+CIPSTA_DEF"          //Set IP address of station, store in flash
    #define _CIPAP                  "+CIPAP"               //DEPPRECATED !! 
    #define _CIPAP_CUR              "+CIPAP_CUR"           // Set IP address of softAP,This configuration will NOT store in Flash. 
    #define _CIPAP_DEF              "+CIPAP_DEF"           // Set IP address of softAP, save as default, store in Flash
    #define _CWSTARTSMART           "+CWSTARTSMART"        //SmartConfig is only available in station mode. SmartConfig can get protocol type
    #define _CWSTARTDISCOVER        "+CWSTARTDISCOVER"     //stop SmartConfig
    #define _CWSTARTDISCOVER        "+CWSTARTDISCOVER"     //Start the mode that ESP8266 can be found by WeChat
    #define _CWSTOPDISCOVER         "+CWSTOPDISCOVER"      //Stop the mode that ESP8266 can be found by WeChat
    #define _WPS                    "+WPS"                 //Notice that WPS function can only be used when ESP8266 station is enabled. And WPS function does not support WEP encryption        
    #define _MDNS                   "+MDNS"                //ESP8266 softAP mode can not support MDNS. Do not contain special characters
    #define _CIPSTATUS              "+CIPSTATUS"           //Check network connection status
    #define _CIPDOMAIN              "+CIPDOMAIN"           //ESP8266 needs to connect to a router to access to the internet first, then it is able to call the DNS function
    #define _CIPSTART               "+CIPSTART"            //– Establish TCP connection, UDP transmission or SSL connection
    #define _CIPSSLSIZE             "+CIPSSLSIZE"          //Set the size of SSL buffer
    #define _CIPSEND                "+CIPSEND"             //Send data 
    #define _CIPSENDEX              "+CIPSENDEX"           //Send data  hex
    #define _CIPSENDBUF             "+CIPSENDBUF"          //Write data into TCP-send-buffer
    #define _CIPBUFSTATUS           "CIPBUFSTATUS"         //Check status of TCP-send-buffer
    #define _CIPCHECKSEQ            "+CIPCHECKSEQ"         //Check if specific segment sent successfully or not
    #define _CIPBUFRESET            "+CIPBUFRESET"         //Reset segment ID count
    #define _CIPCLOSE               "+CIPCLOSE"            // Close TCP, UDP or SSL connection 
    #define _CIFSR                  "+CIFSR"               //Get local IP address 
    #define _CIPMUX                 "+CIPMUX"              //Enable multiple connections
    #define _CIPSERVER              "+CIPSERVER"           //Configure as TCP server
    #define _CIPMODE                "+CIPMODE"             //– Set transfer mode, ,ot store in flash
    #define _SAVETRANSLINK          "SAVETRANSLINK"        //Save transparent transmission link to Flash
    #define _CIPSTO                 "+CIPSTO"              //Set TCP server timeout 
    #define _PING                   "+PING"                // Function Ping
    #define _CIUPDATE               "+CIUPDATE"            // Update through network
    #define _CIPDINFO               "+CIPDINFO"            //Show remote IP and port with "+IPD"
    #define _IPD                    "+IPD"                 //Receive network data

    /*END enumerate AT command*/



    
    #define CMD(x)             _AT x _ENDL
    #define CMD_WRITE(x)       _AT x "="
    //#define CMD_WRITE(x,y)       _AT x"=" #y _ENDL
    #define CMD_READ(x)        _AT x "?" _ENDL
    // ********************************************************************
    // *                      Types
    // ********************************************************************

    // ********************************************************************
    // *                      Prototypes
    // ********************************************************************
        
    // ********************************************************************
    // *                      Variables
    // ********************************************************************
    

#endif // WIFI_ESP8266_CMD_H_INCLUDED           
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
