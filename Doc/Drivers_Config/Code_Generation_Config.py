
"""
#  @file        main.py
#  @brief       Template_BriefDescription.
#  @details     TemplateDetailsDescription.\n
#
#  @author      AUDMBA
#  @date        jj/mm/yyyy
#  @version     1.0
"""
# Le path pour écrire, le path du fichier Excel, la feuille du fichier Excel 
# Des fonctions pour écrire du code générique : Dict, list de list, list ...
# Une fonction où l'on donne en entrée une str et on l'écrit dans le fichiers 
# Une fonction pour foutre dans une list de list le tableau 
#------------------------------------------------------------------------------
#                                       IMPORT
#------------------------------------------------------------------------------
from typing import List
from TypeCommon import *
import openpyxl
import os

#------------------------------------------------------------------------------
#                                       DEFINE
#------------------------------------------------------------------------------



TARGET_START_LINE = "/* CAUTION : Automatic generated code section: Start */\n"
TARGET_END_LINE =   "/* CAUTION : Automatic generated code section: End */\n"

TARGET_T_START_LINE = "    /* CAUTION : Automatic generated code section: Start */\n"
TARGET_T_END_LINE =   "    /* CAUTION : Automatic generated code section: End */\n"

TARGET_T_ENUM_START_LINE = "    /* CAUTION : Automatic generated code section for Enum: Start */\n"
TARGET_T_ENUM_END_LINE =   "    /* CAUTION : Automatic generated code section for Enum: End */\n"

TARGET_T_STRUCT_START_LINE = "    /* CAUTION : Automatic generated code section for Structure: Start */\n"
TARGET_T_STRUCT_END_LINE =   "    /* CAUTION : Automatic generated code section for Structure: End */\n"


ACTUATORS_CONFIGSPECIFIC_PATH = "Src\\ConfigSpecific\\Actuators\\Actuators_CfgSpec.h"
SENSORS_CONFIGSPECIFIC_PATH =   "Src\\ConfigSpecific\\Sensors\\Sensors_CfgSpc.h"
DRIVERS_SENSORS_FOLDER_PATH = "Src\\ConfigSpecific\\Sensors"
DRIVERS_ACTUATORS_FOLDER_PATH = "Src\\ConfigSpecific\\Actuators"
EXCEL_PATH = "Doc\Drivers_Config\DriversConfig.xlsm"


SENSORS_ARRAY_NAME = "Sensors_Drivers"
ACTUATORS_NAME_ARRAY = "Actuators_Drivers"

# Sensor Column 
SENSOR_NAME = 0x00
SENSOR_CODE = 0x01

ACTUATOR_CODE = 0x01
SPACE_CST = 44
#------------------------------------------------------------------------------
#                                       CLASS
#------------------------------------------------------------------------------
class LoadConfig_FromExcel():
    """
    @brief          Allow user to generate automatic code from an Excel Array
    @details

    @params[in]    f_excelPath_str : The relative path of Excel file    
    @params[in]    f_scriptPath_str : The relative path of the file you want to write   
    @params[in]    f_excelSheet_str : The name of the sheet Excel to find the array   
    @params[out]
    @retval
"""
    #--------------------------
    # __init__
    #--------------------------
    def __init__(self, ):
            self.excelPath_str = ""
            self.SheetName_str = ""
            self.workbook = None
            self.sheets_astr = ""
            self.lines = None
            self.targetStartLine_str = TARGET_START_LINE
            self.targetEndLine_str = TARGET_END_LINE
            self.line_start_index = None
            self.line_end_index = None
            self.ErasePreviousCode_b = False
            self.ScriptList = {}
    #--------------------------
    # _GetLineToGenerateCode
    #--------------------------
    def _GetLineToGenerateCode(self, f_scriptPath_str:str):
        """
                @brief In order to write into script we have to know where the balise target are.\n
        """
        self.line_start_index = int(0)
        self.line_end_index   = int(0)
        try:
                with open(f_scriptPath_str, 'r') as file:
                    self.line = file.readlines()
        except:
            raise FileNotFoundError("[MakeList_FromExcelArray] : cannot open Script file")
        self.line_end_index = self.line.index(self.targetEndLine_str)
        self.line_start_index = self.line.index(self.targetStartLine_str)
        if(self.line_end_index and self.line_start_index) != int(0):
            f_Path_Balise = f_scriptPath_str + self.targetStartLine_str
            if(f_Path_Balise not in self.ScriptList):
                self.ScriptList[f_Path_Balise] = False
            if(self.ScriptList[f_Path_Balise] == False):
                del self.line[self.line_start_index + 1:self.line_end_index]
                self.ScriptList[f_Path_Balise] = True
        else:
            raise ValueError(f"At least one of the target not found -> start {self.line_start_index} end -> {self.line_end_index}")
        return None
    #--------------------------
    # _Extract_DataArray
    #--------------------------
    def _Extract_DataArray(self, f_array):
        """
                @brief Store the array into data.\n
        """
        data_Array_a = []
        for index,line in enumerate(f_array):
            dataLine_a = []
            for cell in line:
                dataLine_a.append(cell.value)
            data_Array_a.append(dataLine_a)
        return data_Array_a
    #--------------------------
    # _WriteIntoFile
    #--------------------------    
    def _WriteIntoFile(self,f_generatedCode_str:str, f_scriptPath_str:str ):
        
        if(isinstance(f_scriptPath_str,str) == True  
           and os.path.isfile(f_scriptPath_str) == True):
            self._GetLineToGenerateCode(f_scriptPath_str)
            self.line.insert(self.line_start_index + 1, f_generatedCode_str)
            with open(f_scriptPath_str, "w") as file:
                file.writelines(self.line)
        else:
            raise FileNotFoundError(f"[_WriteIntoFile] : Param Invalid {f_scriptPath_str}")
    #--------------------------
    # GetArray_FromExcel
    #--------------------------
    def ChangeTargetBalise(self, f_targetStartLine:str,f_targetEndLine:str):
        if (isinstance(f_targetEndLine,str) and isinstance(f_targetStartLine,str)):
            self.targetStartLine_str = f_targetStartLine
            self.targetEndLine_str = f_targetEndLine
        else:
            raise TypeError
    #--------------------------
    # _GetArray_FromExcel
    #--------------------------
    def _GetArray_FromExcel(self, f_ArrayName_str):
        """
            @brief      Search the right array from Excel file
        """
        if(isinstance(f_ArrayName_str,str) == True):
            getArray_a = None
            self.workbook = openpyxl.load_workbook(self.excelPath_str, data_only=True)
            self.sheets_astr = self.workbook.sheetnames
            for sheetName_str in self.sheets_astr:
                sheet = self.workbook[sheetName_str]
                for array in sheet.tables.values():
                    if array.displayName == f_ArrayName_str:
                        try:
                            getArray_a =  (self._Extract_DataArray(sheet[array.ref]))
                        except:
                            raise ValueError("[GetArray_FromExcel] : Cannot extract array from Excel")
        else:
            raise ValueError("[GetArray_FromExcel] : param invalid")

        return getArray_a
    #--------------------------
    # Load_ExcelFile
    #--------------------------
    def Load_ExcelFile(self, f_excelPath_str:str):
        """
            @brief Store the Excel path where Excel Array are.\n
        """
        if(isinstance(f_excelPath_str, str) == True and os.path.isfile(f_excelPath_str) == True):
            self.excelPath_str = f_excelPath_str
        else:
            raise ValueError("[Load_ExcelFile] param invalid or path nopt found")
        return
    #--------------------------
    # MakeEnum_fromExcel
    #--------------------------
    def MakeEnum_fromExcel(self,  f_ArrayName_str:str ,f_scriptPath_str:str, f_spaceVariable_ui:int = 30, f_variableName_str:str = " ", f_IsStringValue_b = True ):
        arrayEnum_a:List[List]= []
        generatedCode_str = ""
        arrayEnum_a = self._GetArray_FromExcel(f_ArrayName_str)[1:]
        if(arrayEnum_a != None and isinstance(f_variableName_str,str) and os.path.isfile(f_scriptPath_str)):
            generatedCode_str += "\ttypedef enum\n\t{\n"
            for idx, InstanceEnum_a in enumerate(arrayEnum_a):
                if(len(InstanceEnum_a) != 2):
                    raise ValueError(f"Array Enum should be a len of 2 but it's {len(InstanceEnum_a)}")
                # If value of enum is none and it's the first, initiliaze to 0 
                # If value of enum isn't None take the variable, else just put ","
                generatedCode_str += "\t" + str(InstanceEnum_a[0]).upper() 
                if(InstanceEnum_a[1] == None and idx == 0):
                    generatedCode_str += " " * (f_spaceVariable_ui - len(str(InstanceEnum_a[0]))) +  "= 0,\n"
                elif (InstanceEnum_a[1] == None):
                    generatedCode_str += ",\n"
                else:
                    generatedCode_str += "= " + str(int(InstanceEnum_a[1])) + ",\n"
            generatedCode_str +=  "\t}" + f'{f_ArrayName_str if f_variableName_str == " " else f_variableName_str};\n'
            self.ChangeTargetBalise(TARGET_T_ENUM_START_LINE,TARGET_T_ENUM_END_LINE)
            self._WriteIntoFile(generatedCode_str, f_scriptPath_str)
            self.ChangeTargetBalise(TARGET_START_LINE,TARGET_END_LINE)
        else:
            raise TypeError("Arg Invalid")
        return
    #--------------------------
    # MakeStruct_fromExcel
    #--------------------------
    def MakeStruct_fromExcel(self,  f_ArrayName_str:str ,f_scriptPath_str:str, f_spaceVariable_ui:int = 30, f_variableName_str:str = " ", f_IsStringValue_b = True ):
        arrayStruct_a:List[List]= []
        generatedCode_str = ""
        arrayStruct_a = self._GetArray_FromExcel(f_ArrayName_str)[1:]
        if(arrayStruct_a != None and isinstance(f_variableName_str,str) and os.path.isfile(f_scriptPath_str)):        
            generatedCode_str += "\ttypedef struct\n\t{\n"
            for arrayStruct_a in arrayStruct_a:
                if len(arrayStruct_a) != 2:
                    raise ValueError(f"Array Struct should have len 2 but have {len(arrayStruct_a)}")
                generatedCode_str += f"\t{arrayStruct_a[0]}" + " " * (f_spaceVariable_ui - len(str(arrayStruct_a[0]))) + f"{arrayStruct_a[1]};\n"
            generatedCode_str += "\t}" + f'{f_ArrayName_str if f_variableName_str == " " else f_variableName_str};\n'
            self.ChangeTargetBalise(TARGET_T_STRUCT_START_LINE,TARGET_T_STRUCT_END_LINE)
            self._WriteIntoFile(generatedCode_str, f_scriptPath_str)
            self.ChangeTargetBalise(TARGET_START_LINE,TARGET_END_LINE)
        else:
            raise TypeError("Arg Invalid")
        return
    #--------------------------
    # MakeSensorsfiles_fromExcel
    #--------------------------
    def MakeSensorsfiles_fromExcel(self):
        ArrayList = None
        generated_code_str = ""
        if(os.path.isfile(EXCEL_PATH) != bool(True) and
           os.path.isfile(SENSORS_CONFIGSPECIFIC_PATH) != bool(True)):
            raise Exception("[MakeSensorsfiles_fromExcel] -> Invalid Path")
        ArrayList = self._GetArray_FromExcel(SENSORS_ARRAY_NAME)
        if(ArrayList == None):
            raise Exception("[MakeSensorsfiles_fromExcel] -> Array is empty")
        generated_code_str = "\ttypedef enum {\n"
        #make enum
        for Sensor in ArrayList:
            generated_code_str += f"\t\tSNS_{str(Sensor[SENSOR_CODE]).upper()},\n"
        generated_code_str += "\n\t\tSNS_NUMBER,\n"
        generated_code_str += "\t}t_eSNSSPEC_Sensors;\n\n"
        #make c_SysActCfg_as 
        generated_code_str += "\tstatic const t_sSNSSPEC_SysSnsCfg c_SysSnsCfg_as[SNS_NUMBER] = \n\t{\n"
        #make c_SysActCfg_as 
        for Sensor in ArrayList:
            generated_code_str += "\t\t{"
            generated_code_str += f"\tSNS_{str(Sensor[SENSOR_CODE])}_Cfg"
            generated_code_str += " " * (SPACE_CST - len(f"\tSNS_{str(Sensor[SENSOR_CODE])}_Cfg,"))
            generated_code_str += f"\t,SNS_{str(Sensor[SENSOR_CODE])}_Get"
            generated_code_str += "},\n"
        generated_code_str += "\t};\n" 
        self._WriteIntoFile(SENSORS_CONFIGSPECIFIC_PATH, generated_code_str)
        #create Files for make function 
        for Sensor in ArrayList:
            if(os.path.isfile(f"{DRIVERS_SENSORS_FOLDER_PATH}/SNS_{str(Sensor[SENSOR_CODE])}.cpp") == bool(False) and
                os.path.isfile(f"{DRIVERS_SENSORS_FOLDER_PATH}/SNS_{str(Sensor[SENSOR_CODE])}.h") == bool(False)):
                try:
                    open(f"{DRIVERS_SENSORS_FOLDER_PATH}/SNS_{str(Sensor[SENSOR_CODE])}.cpp", "w")
                    open(f"{DRIVERS_SENSORS_FOLDER_PATH}/SNS_{str(Sensor[SENSOR_CODE])}.h", "w")
                except:
                    raise Exception (f"[MakeSensorsfiles_fromExcel] : cannot open file {DRIVERS_SENSORS_FOLDER_PATH}")
        return
    #--------------------------
    # MakeActuatorsFiles_fromExcel
    #--------------------------
    def MakeActuatorsFiles_fromExcel(self):
        ArrayList = None
        generated_code_str = ""
        if(os.path.isfile(EXCEL_PATH) != bool(True) and
           os.path.isfile(ACTUATORS_CONFIGSPECIFIC_PATH) != bool(True)):
            raise Exception("[MakeActuatorsFiles_fromExcel] -> Invalid Path")
        ArrayList = self._GetArray_FromExcel(ACTUATORS_NAME_ARRAY)
        if(ArrayList == None):
            raise Exception("[MakeActuatorsFiles_fromExcel] -> Array empty")

        generated_code_str = "\ttypedef enum {\n"
        for Actuator in ArrayList:
            generated_code_str += f"\t\tACT_{str(Actuator[ACTUATOR_CODE]).upper()},\n"
        generated_code_str += "\n\t\tACT_NUMBER,\n"
        generated_code_str += "\t}t_eACT_Actuators;\n"
        generated_code_str += "\tstatic const t_sACT_SysActCfg c_SysActCfg_as[ACT_NUMBER] = \n\t{\n"
        #make c_SysActCfg_as 
        for Actuator in ArrayList:
            generated_code_str += "\t\t{"
            generated_code_str += f"ACT_{str(Actuator[ACTUATOR_CODE])}_Cfg"
            generated_code_str += " " * (SPACE_CST - len(f"\tACT_{str(Actuator[ACTUATOR_CODE])}_Cfg"))
            generated_code_str += f",ACT_{str(Actuator[ACTUATOR_CODE])}_Set"
            generated_code_str += " " * (SPACE_CST - len(f"\tACT_{str(Actuator[ACTUATOR_CODE])}_Set"))
            generated_code_str += f",ACT_{str(Actuator[ACTUATOR_CODE])}_Get"
            generated_code_str += "},\n"
        generated_code_str += "\t};\n"
        self._WriteIntoFile(ACTUATORS_CONFIGSPECIFIC_PATH, generated_code_str)
        for Actuator in ArrayList:
            if(os.path.isfile(f"{DRIVERS_ACTUATORS_FOLDER_PATH}/ACT_{str(Actuator[ACTUATOR_CODE])}.cpp") == bool(False) and
                os.path.isfile(f"{DRIVERS_ACTUATORS_FOLDER_PATH}/ACT_{str(Actuator[ACTUATOR_CODE])}.h") == bool(False)):
                try:
                    open(f"{DRIVERS_ACTUATORS_FOLDER_PATH}/ACT_{str(Actuator[ACTUATOR_CODE])}.cpp", "w")
                    open(f"{DRIVERS_ACTUATORS_FOLDER_PATH}/ACT_{str(Actuator[ACTUATOR_CODE])}.h", "w")
                except:
                    raise Exception (f"[MakeActuatorsfiles_fromExcel] : cannot open file {DRIVERS_ACTUATORS_FOLDER_PATH}")
        return
    #--------------------------
    # MakeActuatorsFiles_fromExcel
    #--------------------------
    def MakeComCfg_File_FromExcel(self):
        ProjectCom_astr = self._GetArray_FromExcel("PROJECT_COM_CFG")
        print(ProjectCom_astr[0])
        ProjectCom_str = str(ProjectCom_astr[1][0])
        fileComCfg_str = ""
        space_ui = 25
        ProjectComCfg_a = None
        print(ProjectCom_str[0])
        ArdComGeneratedCode_str = f"\tconst t_eArdCom_TypeCom c_ArduinoComUsed_e = ARDCOM_{ProjectCom_str.upper()};\n"
        generatedCode_str ="\t/**< Wifi COnfiguration*/\n\t"
        self.ChangeTargetBalise(TARGET_T_START_LINE, TARGET_T_END_LINE)
        match ProjectCom_str:
            case WIFI if "WiFi".upper() in ProjectCom_str.upper():
                ProjectComCfg_a = self._GetArray_FromExcel("WIFI_CFG")[1] # dont't need descritpion
                generatedCode_str +="\tconst t_sESP_ClientCfg c_ESPComProjectCfg_s = {\n"
                generatedCode_str += ("\t\t.WifiMode_e"       + " " * (space_ui - len("WifiMode_e")     )    + f"= {ProjectComCfg_a[0]},\n")
                generatedCode_str += ("\t\t.exchangeType_e"   + " " * (space_ui - len("exchangeType_e") )    + f"= {ProjectComCfg_a[1]},\n")
                generatedCode_str += ("\t\t.ProtComType_e"    + " " * (space_ui - len("ProtComType_e")  )    + f"= {ProjectComCfg_a[2]},\n")
                generatedCode_str += ("\t\t.baudRate_u32"     + " " * (space_ui - len("baudRate_u32")   )    + f"= {ProjectComCfg_a[3]},\n")
                generatedCode_str += ("\t\t.rxPin_u8"         + " " * (space_ui - len("rxPin_u8")       )    + f"= {ProjectComCfg_a[4]},\n")
                generatedCode_str += ("\t\t.txPin_u8"         + " " * (space_ui - len("txPin_u8")       )    + f"= {ProjectComCfg_a[5]},\n")
                generatedCode_str += ("\t\t.serverID_pac"     + " " * (space_ui - len("serverID_pac")   )    + f'= "{ProjectComCfg_a[6]}",\n')
                generatedCode_str += ("\t\t.serverPrt_pac"    + " " * (space_ui - len("serverPrt_pac")  )    + f'= "{ProjectComCfg_a[7]}",\n')
                generatedCode_str += ("\t\t.LiveBoxName_pac"  + " " * (space_ui - len("LiveBoxName_pac"))    + f'= "{ProjectComCfg_a[8]}",\n')
                generatedCode_str += ("\t\t.password_pac"     + " " * (space_ui - len("password_pac")   )    + f'= "{ProjectComCfg_a[9]}",\n')
                generatedCode_str += "\t};\n"
                fileComCfg_str = "Src\\ConfigSpecific\\ArduinoCom\\WiFiESP_CfgSpec.h"
            case BLUETOOTH if "BlueTooth".upper() in ProjectCom_str.upper():
                pass
            case SPI if "SPI" in ProjectCom_str.upper():
                pass
        self._WriteIntoFile(generatedCode_str, fileComCfg_str)
        self._WriteIntoFile(ArdComGeneratedCode_str,"Src\\ConfigSpecific\\ArduinoCom\\ArdCom_CfgSpec.h" )
        self.ChangeTargetBalise(TARGET_START_LINE, TARGET_END_LINE)
        return
#------------------------------------------------------------------------------
#                              FUNCTION DECLARATION
#------------------------------------------------------------------------------

#------------------------------------------------------------------------------
#                             FUNCTION IMPLMENTATION
#------------------------------------------------------------------------------
def main()-> None:
    Load = LoadConfig_FromExcel()
    Load.Load_ExcelFile(EXCEL_PATH)
    #Load.MakeSensorsfiles_fromExcel()
    #Load.MakeActuatorsFiles_fromExcel()
    Load.MakeEnum_fromExcel("t_eEssaisEnum","Src\\ConfigSpecific\\ArduinoCom\\WiFiESP_CfgSpec.h")
    Load.MakeStruct_fromExcel("t_sESSAisSTRuct","Src\\ConfigSpecific\\ArduinoCom\\WiFiESP_CfgSpec.h")
    #Load.MakeComCfg_File_FromExcel()
#------------------------------------------------------------------------------
#			                MAIN
#------------------------------------------------------------------------------
if (__name__ == '__main__'):
    main()

#------------------------------------------------------------------------------
#		                    END OF FILE
#------------------------------------------------------------------------------
#--------------------------
# Function_name
#--------------------------

"""
    @brief
    @details




    @params[in]
    @params[out]
    @retval
"""

