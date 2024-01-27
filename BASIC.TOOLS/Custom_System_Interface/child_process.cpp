

#include <iostream>
#include "Source_File_Dependency_Determiner.hpp"
#include "Custom_System_Interface.h"

int main(int argc, char *argv[]){
    
    Custom_System_Interface SysInt;

    SysInt.Connect_NamedPipe_From_Child_Process();



    Descriptor_File_Reader Des_Reader('w');

    Des_Reader.Receive_Descriptor_File_Path(argv[1]);

    Des_Reader.Read_Descriptor_File();


    Git_Data_Processor Data_Processor('w');

    Data_Processor.Receive_Descriptor_File_Path(argv[1]);

    Data_Processor.Write_Git_Repo_List_File();

    Data_Processor.Determine_Git_Repo_Info();

    size_t index_size = Data_Processor.Get_Git_File_Index_Size();


    Source_File_Dependency_Determiner Dep_Determiner(argv[1],'w');

    Dep_Determiner.Receive_Descriptor_File_Reader(&Des_Reader);

    Dep_Determiner.Receive_Git_Data_Processor(&Data_Processor);

    Dep_Determiner.Collect_Dependency_Information(argv[2]);




     std::vector<Compiler_Data> * ptr = Dep_Determiner.Get_Compiler_Data_Address();

     for(size_t i=0;i<ptr->size();i++){

         size_t src_name_size = ptr->at(i).source_file_name_witout_ext.size();

         char str[2*src_name_size];

         for(size_t k=0;k<2*src_name_size;k++){

             str[k] = '\0';
         }

         size_t index=0;

         for(size_t k=0;k<src_name_size;k++){

             str[index] = ptr->at(i).source_file_name_witout_ext.at(k);

             index++;
         }

         str[index] = '\0';

         SysInt.WriteTo_NamedPipe_FromChild(str);
     }


    return 0;
}