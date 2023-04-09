

#ifndef SOURCE_FILE_SCRPIT_WRITER_H
#define SOURCE_FILE_SCRPIT_WRITER_H

#include <cstring>
#include "Project_Files_Lister.h"
#include "Descriptor_File_Reader.hpp"
#include "Script_Data_Collector.hpp"
#include "DirectoryOperations.h"
#include "Cpp_FileOperations.h"
#include "IntToCharTranslater.h"


class Source_File_Script_Writer
{
public:
 Source_File_Script_Writer();
 virtual ~Source_File_Script_Writer();
 void Receive_Descriptor_File_Reader(Descriptor_File_Reader * Pointer);
 void Receive_Script_Data(Script_Data * Pointer);
 void Write_Source_File_Script(char operating_sis);
 void Determine_Script_Path(char opr_sis);
 void Determine_Warehouse_Paths(char opr_sis);
 void Construct_Path(std::string & pointer,
      std::string string, char opr_sis);
 void Clear_Dynamic_Memory();
 void Clear_String_memory(std::string & pointer);
protected:
 Descriptor_File_Reader * Des_Reader_Ptr;
 Script_Data * Src_Data_Pointer;
 Cpp_FileOperations FileManager;
 DirectoryOperations DirectoryManager;
 IntToCharTranslater Translater;
 std::string Repo_Rood_Dir;
 std::string object_files_location;
 std::string compiler_output_location;
 std::string headers_locations;
 std::string script_path;
 std::string warehouse_path;
 bool Memory_Delete_Condition;
};

#endif /* SOURCE_FILE_SCRPIT_WRITER_H */
