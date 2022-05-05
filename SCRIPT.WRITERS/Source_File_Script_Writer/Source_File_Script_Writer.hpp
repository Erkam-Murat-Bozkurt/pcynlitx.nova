

#ifndef SOURCE_FILE_SCRPIT_WRITER_H
#define SOURCE_FILE_SCRPIT_WRITER_H

#include <cstring>
#include "Project_Files_Lister.h"
#include "Descriptor_File_Reader.hpp"
#include "Script_Data_Collector.hpp"
#include "Include_Dependency_Counter.hpp"
#include "DirectoryOperations.h"
#include "Cpp_FileOperations.h"
#include "IntToCharTranslater.h"


class Source_File_Script_Writer
{
public:
 Source_File_Script_Writer();
 Source_File_Script_Writer(const Source_File_Script_Writer & orig);
 virtual ~Source_File_Script_Writer();
 void Receive_Descriptor_File_Reader(Descriptor_File_Reader * Pointer);
 void Receive_Script_Data(Script_Data * Pointer);
 void Receive_Project_Files_Lister(Project_Files_Lister * Pointer);
 void Write_Source_File_Script(char operating_sis);
 void Determine_Script_Path(char opr_sis);
 void Determine_Warehouse_Paths(char opr_sis);
 void Construct_Path(char ** pointer,
      char * string, char opr_sis);
 void Clear_Dynamic_Memory();
 void Clear_Pointer_Memory(char ** pointer);
protected:
 Descriptor_File_Reader * Des_Reader_Ptr;
 Script_Data * Src_Data_Pointer;
 Project_Files_Lister * Dir_Lister;
 Cpp_FileOperations FileManager;
 DirectoryOperations DirectoryManager;
 IntToCharTranslater Translater;
 char * Repo_Rood_Dir;
 char * object_files_location;
 char * compiler_output_location;
 char * headers_locations;
 char * script_path;
 char * warehouse_path;
 bool Memory_Delete_Condition;
};

#endif /* SOURCE_FILE_SCRPIT_WRITER_H */
