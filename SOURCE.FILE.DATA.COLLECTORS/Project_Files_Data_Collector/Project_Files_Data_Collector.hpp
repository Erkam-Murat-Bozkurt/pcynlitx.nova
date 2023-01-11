



#ifndef PROJECT_FILES_DATA_COLLECTOR_H
#define PROJECT_FILES_DATA_COLLECTOR_H

#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <iostream>


class Project_Files_Data_Collector
{
public:
 Project_Files_Data_Collector(char operating_sis);
 virtual ~Project_Files_Data_Collector();

 void Determine_File_Exact_Path(std::string * pointer,

      std::string repo_dir, std::string string_line);

 void Extract_Upper_Directory_Path(std::string * pointer,

      std::string string_line);

 void Determine_File_Name(std::string * pointer, std::string string_line);

 void Determine_Source_File_Name_With_Ext(std::string * pointer,

      std::string file_name);

 void Determine_File_Name_With_Ext(std::string * pointer,

      std::string string_line);
private:
  char operating_sis;
};

#endif /* PROJECT_FILES_DATA_COLLECTOR_H */
