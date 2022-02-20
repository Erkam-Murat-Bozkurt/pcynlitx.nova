



#ifndef PROJECT_FILES_DATA_COLLECTOR_H
#define PROJECT_FILES_DATA_COLLECTOR_H

#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <iostream>


class Project_Files_Data_Collector
{
public:
 Project_Files_Data_Collector();
 Project_Files_Data_Collector(const Project_Files_Data_Collector & orig);
 virtual ~Project_Files_Data_Collector();
 void Determine_File_Exact_Path(char ** pointer,

      char * repo_dir, char * string_line, char operating_sis);

 void Extract_Upper_Directory_Path(char ** pointer,

           char * string_line, char operating_sis);

 void Determine_File_Name(char ** pointer, char * string_line);

 void Determine_Source_File_Name_With_Ext(char ** pointer,

      char * file_name);
 void Determine_File_Name_With_Ext(char ** pointer,

      char * string_line);
protected:

};

#endif /* PROJECT_FILES_DATA_COLLECTOR_H */
