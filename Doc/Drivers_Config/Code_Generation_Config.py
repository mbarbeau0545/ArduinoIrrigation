
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
from TypeCommon import *
import pandas as pd 
import openpyxl
import os

#------------------------------------------------------------------------------
#                                       DEFINE
#------------------------------------------------------------------------------



TARGET_START_LINE = "/* CAUTION : Automatic generated code section: Start */\n"
TARGET_END_LINE =   "/* CAUTION : Automatic generated code section: End */\n"

ACTUATORS_CONFIGSPECIFIC_PATH = "Src\ConfigSpecific\Actuators_ConfigSpecific.h"
SENSORS_CONFIGSPECIFIC_PATH =   "Src\ConfigSpecific\Sensors_ConfigSpecific.h"
DRIVERS_SENSORS_FOLDER_PATH = "Src\Sensors"
DRIVERS_ACTUATORS_FOLDER_PATH = "Src\Actuators"
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
    def __init__(self):
        RC = t_eReturnCode()
        Ret_e = RC.OK
        if(os.path.isfile(EXCEL_PATH) != bool(True)):
            Ret_e = RC.ERROR_PARAM_INVALID
        if(Ret_e == RC.OK):
            self.excelPath_str = EXCEL_PATH
            self.workbook = None
            self.sheets_astr = ""
            self.lines = None
            self.line_start_index = None
            self.line_end_index = None
            self.ErasePreviousCode_b = False
            self.ScriptList = {}
            
        return
    def _GetLineToGenerateCode(self, f_scriptPath_str):
        self.line_start_index = None
        self.line_end_index = None
        try:
                with open(f_scriptPath_str, 'r') as file:
                    self.line = file.readlines()
        except:
            raise Exception("[_GetLineToGenerateCode] : cannot open Script file")
        for index, line in enumerate(self.line):
            if TARGET_START_LINE in line:
                self.line_start_index = index
            if TARGET_END_LINE in line:
                self.line_end_index = index
            if self.line_start_index is not None and self.line_end_index is not None:
                break
        if(self.line_start_index is None or self.line_end_index is None):
            raise Exception("[Error] in _GetLineToGenerateCode -> cannot find Target line for automated code")
        if(f_scriptPath_str not in self.ScriptList):
            self.ScriptList[f_scriptPath_str] = False
        if(self.ScriptList[f_scriptPath_str] == bool(False)):
            del self.line[self.line_start_index + 1:self.line_end_index]
            self.ScriptList[f_scriptPath_str] = bool(True)
    #--------------------------
    # _Extract_DataArray
    #--------------------------
    def _Extract_DataArray(self, f_array):
        data_Array_a = []
        for index,line in enumerate(f_array):
            if(index == 0):
                continue
            else:
                dataLine_a = []
                for cell in line:
                    dataLine_a.append(cell.value)
                data_Array_a.append(dataLine_a)
        return data_Array_a        
    #--------------------------
    # _GetArray_FromExcel
    #--------------------------
    def _GetArray_FromExcel(self, f_ArrayName_str):
        RC = t_eReturnCode()
        Ret_e = RC.OK
        if(isinstance(f_ArrayName_str,str) != bool(True)):
            Ret_e = RC.ERROR_PARAM_INVALID
            raise Exception("[GetArray_FromExcel] : param invalid")
        if(Ret_e ==RC.OK):
            getArray_a = None
            self.workbook = openpyxl.load_workbook(EXCEL_PATH, data_only=True)
            self.sheets_astr = self.workbook.sheetnames

            for sheetName_str in self.sheets_astr:
                sheet = self.workbook[sheetName_str]
                for array in sheet.tables.values():
                    if array.displayName == f_ArrayName_str:
                        try:
                            getArray_a =  (self._Extract_DataArray(sheet[array.ref]))
                        except:
                            raise Exception("[GetArray_FromExcel] : Cannot extract array from Excel")

        return getArray_a  
    def MakeSensorsfiles_fromExcel(self) -> t_eReturnCode:
        RC = t_eReturnCode()
        Ret_e = RC.OK
        ArrayList = None
        generated_code_str = ""
        if(os.path.isfile(EXCEL_PATH) != bool(True) and
           os.path.isfile(SENSORS_CONFIGSPECIFIC_PATH) != bool(True)):
            Ret_e = RC.ERROR_NOT_SUPPORTED
        ArrayList = self._GetArray_FromExcel(SENSORS_ARRAY_NAME)
        if(ArrayList == None):
            Ret_e = RC.ERROR_MISSING_CONFIG
        if(Ret_e == RC.OK):
            self._GetLineToGenerateCode(SENSORS_CONFIGSPECIFIC_PATH)
            generated_code_str = "\ttypedef enum {\n"
            #make enum
            for Sensor in ArrayList:
                generated_code_str += f"\t\tSNS_{str(Sensor[SENSOR_CODE]).upper()},\n"
            generated_code_str += "\n\t\tSNS_NUMBER,\n"
            generated_code_str += "\t}t_eSNS_Sensors;\n\n"
            #make c_SysActCfg_as 
            generated_code_str += "\tstatic const t_sSNS_SysSnsCfg c_SysSnsCfg_as[SNS_NUMBER] = \n\t{\n"
            #make c_SysActCfg_as 
            for Sensor in ArrayList:
                generated_code_str += "\t\t{"
                generated_code_str += f"\tSNS_{str(Sensor[SENSOR_CODE])}_Cfg"
                generated_code_str += " " * (SPACE_CST - len(f"\tSNS_{str(Sensor[SENSOR_CODE])}_Cfg,"))
                generated_code_str += f"\t,SNS_{str(Sensor[SENSOR_CODE])}_Get,"
                generated_code_str += " " *(SPACE_CST - len(f"\tSNS_{str(Sensor[SENSOR_CODE])},")) 
                generated_code_str += "},\n"
            generated_code_str += "\t};\n" 
            self.line.insert(self.line_start_index + 1, generated_code_str)      
            try:
                with open(SENSORS_CONFIGSPECIFIC_PATH, "w") as file:
                    file.writelines(self.line)
            except:
                raise Exception (f"[MakeSensorsfiles_fromExcel] : cannot open file {SENSORS_CONFIGSPECIFIC_PATH}")
            #create Files for make function 
            for Sensor in ArrayList:
                if(os.path.isfile(f"{DRIVERS_SENSORS_FOLDER_PATH}/SNS_{str(Sensor[SENSOR_CODE])}.cpp") == bool(False) and
                   os.path.isfile(f"{DRIVERS_SENSORS_FOLDER_PATH}/SNS_{str(Sensor[SENSOR_CODE])}.h") == bool(False)):
                    try:
                        open(f"{DRIVERS_SENSORS_FOLDER_PATH}/SNS_{str(Sensor[SENSOR_CODE])}.cpp", "w")
                        open(f"{DRIVERS_SENSORS_FOLDER_PATH}/SNS_{str(Sensor[SENSOR_CODE])}.h", "w")
                    except:
                        raise Exception (f"[MakeSensorsfiles_fromExcel] : cannot open file {DRIVERS_SENSORS_FOLDER_PATH}")
        return Ret_e
    def MakeActuatorsFiles_fromExcel(self):
        RC = t_eReturnCode()
        Ret_e = RC.OK
        ArrayList = None
        generated_code_str = ""
        if(os.path.isfile(EXCEL_PATH) != bool(True) and
           os.path.isfile(ACTUATORS_CONFIGSPECIFIC_PATH) != bool(True)):
            Ret_e = RC.ERROR_NOT_SUPPORTED
        ArrayList = self._GetArray_FromExcel(ACTUATORS_NAME_ARRAY)
        if(ArrayList == None):
            Ret_e = RC.ERROR_MISSING_CONFIG
        if(Ret_e == RC.OK):
            self._GetLineToGenerateCode(ACTUATORS_CONFIGSPECIFIC_PATH)
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
            self.line.insert(self.line_start_index + 1, generated_code_str)
            try:
                with open(ACTUATORS_CONFIGSPECIFIC_PATH, "w") as file:
                    file.writelines(self.line)
            except:
                raise Exception (f"[MakeSensorsfiles_fromExcel] : cannot open file {ACTUATORS_CONFIGSPECIFIC_PATH}")
            for Actuator in ArrayList:
                if(os.path.isfile(f"{DRIVERS_ACTUATORS_FOLDER_PATH}/ACT_{str(Actuator[ACTUATOR_CODE])}.cpp") == bool(False) and
                   os.path.isfile(f"{DRIVERS_ACTUATORS_FOLDER_PATH}/ACT_{str(Actuator[ACTUATOR_CODE])}.h") == bool(False)):
                    try:
                        open(f"{DRIVERS_ACTUATORS_FOLDER_PATH}/ACT_{str(Actuator[ACTUATOR_CODE])}.cpp", "w")
                        open(f"{DRIVERS_ACTUATORS_FOLDER_PATH}/ACT_{str(Actuator[ACTUATOR_CODE])}.h", "w")
                    except:
                        raise Exception (f"[MakeActuatorsfiles_fromExcel] : cannot open file {DRIVERS_ACTUATORS_FOLDER_PATH}")
            return Ret_e
            







        


    
            
            
        
#------------------------------------------------------------------------------
#                              FUNCTION DECLARATION
#------------------------------------------------------------------------------

#------------------------------------------------------------------------------
#                             FUNCTION IMPLMENTATION
#------------------------------------------------------------------------------
def main()-> None:
    RC = t_eReturnCode()
    Ret_e = RC.OK
    Load = LoadConfig_FromExcel()
    Ret_e =  Load.MakeSensorsfiles_fromExcel()
    print(Ret_e)
    Load.MakeActuatorsFiles_fromExcel()
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

