


#ifndef GUI_LIST_DATA_RECORDER_H
#define GUI_LIST_DATA_RECORDER_H

#include <wx\wx.h>
#include <wx\sizer.h>
#include <wx\event.h>
#include <wx\aui\aui.h>
#include <wx\aui\framemanager.h>
#include <wx\sizer.h>
#include <wx\dataview.h>
#include <wx\textdlg.h>
#include <wx\msgdlg.h>
#include <wx\dir.h>
#include "Descriptor_File_Reader.hpp"
#include "StringOperator.h"
#include "Cpp_FileOperations.h"
#include <cstring>
#include <string>


struct Record_Data_For_Gui {

       std::string standard;
       std::string build_system_type;
       std::string project_name;
       std::string version_number;
       std::string root_dir;
       std::string warehouse_location;
       std::vector<std::string> Include_Directories;
       std::vector<std::string> Source_File_Directories;
       std::vector<std::string> Library_Directories;
       std::vector<std::string> Library_Files;
       std::vector<std::string> Exe_File_Names;
       std::vector<std::string> compiler_options;
       std::vector<std::string> linker_options;
       std::vector<std::string> Main_File_Names;  
};



class GUI_List_Data_Recorder
{
public:
  GUI_List_Data_Recorder(char opr_sis);
  virtual ~GUI_List_Data_Recorder();
  void Receive_Descriptions_Record_Data(Record_Data_For_Gui * Data);
  void Receive_Descriptor_File_Path(std::string DesPATH);
  void Record_Data(std::string Data_Type, std::string Data_Record);
  void Record_Data(std::string Data_Type, std::vector<std::string> & vec);
  void Extract_Data_List(std::vector<std::string> & vec, std::string data);
  void Update_Descriptor_File();
  wxWindow * parent;
  void Clear_Object_Memory();
  void Clear_Dynamic_Memory();
private:
  Descriptor_File_Reader Des_Reader;
  StringOperator StringOperations;
  Cpp_FileOperations File_Manager;
  void Receive_Decriptor_File();
  void Clear_String_Memory(std::string & str);
  void Clear_String_Vector(std::vector<std::string> & vec);
  void Place_Vector_Data(const std::vector<std::string> & base_vec, 
       std::vector<std::string> & target_vec);
  void Place_String_Data(const std::string & base_str, std::string & target_str);
  void Place_String_Data(char * base_str, std::string & target_str);
  void WriteNewLines(int line_number);
  void Write_Vector_Data(std::vector<std::string> & vec);
  void Write_String_Data(std::string dt);
  bool Is_Data_List(std::string data);
  void Clear_Data_Memory();
  char opr_sis;
  std::string standard;
  std::string build_system_type;
  std::string project_name;
  std::string version_number;
  std::string root_dir;
  std::string warehouse_location;
  std::string Descriptor_File_Path;
  std::vector<std::string> compiler_options;
  std::vector<std::string> linker_options;
  std::vector<std::string> Include_Directories;
  std::vector<std::string> Source_File_Directories;
  std::vector<std::string> Library_Directories;
  std::vector<std::string> Library_Files;
  std::vector<std::string> Exe_File_Names;
  std::vector<std::string> Main_File_Names;
  bool Memory_Delete_Condition;
};

#endif /* GUI_LIST_DATA_RECORDER_H */
