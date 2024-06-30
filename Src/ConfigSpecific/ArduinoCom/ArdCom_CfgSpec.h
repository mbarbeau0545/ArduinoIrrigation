/*********************************************************************
 * @file        ArdCom_ConfigSpecific.h
 * @brief       Template_BriefDescription.
 * @details     TemplateDetailsDescription.\n
 *
 * @author      AUDMBA
 * @date        jj/mm/yyyy
 * @version     1.0
 */
  
#ifndef ARDCOM_CONFIGSPECIFIC_H_INCLUDED
#define ARDCOM_CONFIGSPECIFIC_H_INCLUDED





// ********************************************************************
    // *                      Includes
    // ********************************************************************
    #include "./WiFiESP_CfgSpec.h"
    // ********************************************************************
    // *                      Defines
    // ********************************************************************
    #define BAUDRATE_BT   9600
    #define BAUDRATE_LORA 9600
    #define BAUDRATE_SPI  9600
    // ********************************************************************
    // *                      Types
    // ********************************************************************
    typedef enum
    {
        ARDCOM_WIFI,
        ARDCOM_BT,
        ARDCOM_LORA,
        ARDCOM_SPI,

        ARDCOM_NB,
    }t_eArdCom_TypeCom;

    typedef union 
    {
        t_sESP_ComStatus ESP_CfgStatus;
    }t_uArdCom_GetCfg;
    
    /*typedef union for arg structure and callback func*/

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
    typedef t_eReturnCode (t_cbArdCom_Init)(void);
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
    typedef t_eReturnCode (t_cbArdCom_Close)(void);
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
    typedef t_eReturnCode (t_cbArdCom_StartProtocolCom)(void);
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
    typedef t_eReturnCode (t_cbArdCom_CloseProtocolCom)(void);
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
    typedef t_eReturnCode (t_cbArdCom_SendData)(const char* f_dataToSend_pc);
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
    typedef t_eReturnCode (t_cbArdCom_RcvData)(const char *f_RcvData_pc);

    typedef struct 
    {
        t_cbArdCom_Init                     *ArdCom_Init_pcb;
        t_cbArdCom_Close                    *ArdCom_Close_pcb;
        t_cbArdCom_StartProtocolCom         *ArdCom_StartCom_pcb;
        t_cbArdCom_CloseProtocolCom         *ArdCom_EndCom_pcb;
        t_cbArdCom_RcvData                  *ArdCom_RcvData_pcb; 
        t_cbArdCom_SendData                 *ArdCom_SendData_pcb;

    }t_sArdCom_SysComCfg;
    // ********************************************************************
    // *                      Prototypes
    // ********************************************************************
        
    // ********************************************************************
    // *                      Variables
    // ********************************************************************



    static const t_sArdCom_SysComCfg c_SysArdComCfg_as[ARDCOM_NB] = 
    {
        {ESP_Init       ,ESP_Close              ,ESP_Start_ProtocolCom       ,ESP_Close_ProtocolCom       ,ESP_RcvData_WithProtocolCom       ,ESP_SendData_WithProtocolCom},  //ARDCOM_WIFI,
        {NULL           ,NULL                   ,NULL                        ,NULL                        ,NULL                              ,NULL                        },  //ARDCOM_BT
        {NULL           ,NULL                   ,NULL                        ,NULL                        ,NULL                              ,NULL                        },  //ARDCOM_LORA
        {NULL           ,NULL                   ,NULL                        ,NULL                        ,NULL                              ,NULL                        },  //ARDCOM_SPI
    };
    /* CAUTION : Automatic generated code section: Start */

    const t_eArdCom_TypeCom c_ArduinoComUsed_e = ARDCOM_WIFI;

    /* CAUTION : Automatic generated code section: End */
    //****************************************************************************
    //                      Public functions - Prototypes
    //********************************************************************************

#endif // ARDCOM_CONFIGSPECIFIC_C_INCLUDED           
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