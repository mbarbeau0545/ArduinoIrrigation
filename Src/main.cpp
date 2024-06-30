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
#define _AT                     "AT"   
#define CMD_WRITE(x)       _AT x "="
#define _CWJAP_DEF              "+CWJAP_DEF"
// ********************************************************************
// *                       setup implementation 
// ********************************************************************
void Printconschar(const char * f_print);
void Printconschar(const char * f_print)
{
    Serial.println(f_print);
    return;
}
void setup() 
{
    t_eReturnCode Ret_e = RC_OK;
    
    Serial.begin(SERIAL_BAUDRATE);
    // Variables SSID et mot de passe
    const char* f_SSID_pc = "Livebox-0BB3";
    const char* f_password_pc = "7CF8844459F167816393050EE2";
    char ESP_SetWifiCmd_str[MODEM_MAX_BUFF_SIZE]; 
    // Étape 1 : Vérifiez les valeurs individuelles
    /*Serial.print("CMD_WRITE: ");
    Serial.println(CMD_WRITE(_CWJAP_DEF));

    Serial.print("SSID: ");
    Serial.println(f_SSID_pc);

    Serial.print("Password: ");
    Serial.println(f_password_pc);





    // Étape 3 : Concaténer progressivement
    String ESP_SetWifiCmd_str = String(CMD_WRITE(_CWJAP_DEF))+ String("\"") + String(f_SSID_pc) + "\",\"" + String(f_password_pc) + "\"\r\n";*/


    Ret_e = LgcIrrig_Init();
    if(Ret_e != RC_OK)
    {
        while(1)
        {
            Serial.print("Error in Init");
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