


#include <iostream>
#include <cstring>
#include "Kernel.hpp"
#include "Source_File_Dependency_Determiner.hpp"
#include "Custom_System_Interface.h"


void Print_Src_Dependency_Data(std::vector<Compiler_Data> * ptr);

std::string Convert_Std_String(char * str);

int main(int argc, char ** argv){

    if(argc< 3){

       std::cout << "\n\n usage: BuildSystem <Descriptor File Path> <operation>";

       std::cout << "\n\n";

       exit(0);
    }

    SetPriorityClass(GetCurrentProcess(),HIGH_PRIORITY_CLASS);

    Custom_System_Interface System_Interface;

    System_Interface.SetCpuRate();

    bool argument_pass_cond = false;

    std::string str = Convert_Std_String(argv[2]);



    if(str == "-ip_for_gui"){

        System_Interface.Connect_NamedPipe_From_Child_Process();
    }


    if(str == "-if_for_gui"){

        System_Interface.Connect_NamedPipe_From_Child_Process();
    }


    if(str == "-ex_dep_for_gui"){

       argument_pass_cond = true;

       System_Interface.Connect_NamedPipe_From_Child_Process();

       Kernel Build_System(argv[1],'w','g');
       
       Build_System.Receive_System_Interface(&System_Interface);

       Build_System.Determine_Source_File_Dependency_List(argv[3]);


       char read_seperator [] = "\n\n\n\n";

       System_Interface.WriteTo_NamedPipe_FromChild(read_seperator);


       std::vector<Compiler_Data> * ptr = Build_System.Get_Src_Dependency_List();

       for(size_t i=0;i<ptr->size();i++){

         size_t src_name_size = ptr->at(i).source_file_name_witout_ext.size();

         char * str = new char[2*src_name_size];

         for(size_t k=0;k<2*src_name_size;k++){

             str[k] = '\0';
         }

         size_t index=0;

         str[index] = ' ';

         index++;

         for(size_t k=0;k<src_name_size;k++){

             str[index] = ptr->at(i).source_file_name_witout_ext.at(k);

             index++;
         }

         str[index] = '\n';

         index++;

         str[index] = '\0';

         System_Interface.WriteTo_NamedPipe_FromChild(str);

         delete [] str;
       }
    }

    if(str == "-ed"){

       Empty_Descriptor_File_Builder Empd_Builder('w');

       argument_pass_cond = true;

       Empd_Builder.Build_Empty_File(argv[1]);

       System_Interface.WriteChildProcess_StdOutput();

       System_Interface.WriteChildProcess_StdError();
       
       exit(0);
    }



    if(str == "-ip_for_gui"){

        argument_pass_cond = true;

        Kernel Build_System(argv[1],'w','g');

        std::cout << "\n\n C++ BUILD SYSTEM CONSTRUCTION PROCESS INITIATED \n";

        Build_System.Receive_Build_Type('g');

        Build_System.Receive_System_Interface(&System_Interface);

        Build_System.Setup_Build_Tools();

        Build_System.Clear_Dynamic_Memory();

        std::cout << "\n THE CONSTRUCTION COMPLATED ";
    }



    if(str == "-ip"){

        argument_pass_cond = true;

        Kernel Build_System(argv[1],'w','n');

        std::cout << "\n\nC++ BUILD SYSTEM CONSTRUCTION PROCESS INITIATED \n";

        Build_System.Receive_Build_Type('n');

        Build_System.Setup_Build_Tools();

        Build_System.Clear_Dynamic_Memory();

        std::cout << "\nTHE CONSTRUCTION COMPLATED ";

        std::cout << "\n";
    }

    if(str == "-if"){

        if(argc < 6){
            
           std::cout << "\n You must also specify the name of the executable";
           std::cout << "\n and construction strategy";
           std::cout << "\n";
           std::cout << "\n usage: BuildSystem [Descriptor File Path] [operation] \\";
           std::cout << "\n        [Source File Path] [Executable File Name] [Strategy]";

           std::cout << "\n";
           std::cout << "\n";
        }

        argument_pass_cond = true;

        Kernel Build_System(argv[1],'w','n');

        std::cout << "\n\e[0;32mTHE MAKEFILE CONSTRUCTION STARTED\e[0m\n";

        Build_System.Build_MakeFile(argv[3],argv[4],*argv[5]);

        Build_System.Clear_Dynamic_Memory();

        std::cout << "\n";

        std::cout << "\n\e[0;32mTHE MAKEFILE CONSTRUCTED\e[0m\n\n";

    }


    if(str == "-if_for_gui"){

        if(argc < 6){
            
           std::cout << "\n You must also specify the name of the executable";
           std::cout << "\n and construction strategy";
           std::cout << "\n";
           std::cout << "\n usage: BuildSystem [Descriptor File Path] [operation] \\";
           std::cout << "\n        [Source File Path] [Executable File Name] [Strategy]";

           std::cout << "\n";
           std::cout << "\n";
        }

        argument_pass_cond = true;

        Kernel Build_System(argv[1],'w','g');

        std::cout << "\n\e[0;32mTHE MAKEFILE CONSTRUCTION STARTED\e[0m\n";

        Build_System.Receive_System_Interface(&System_Interface);

        Build_System.Build_MakeFile(argv[3],argv[4],*argv[5]);

        Build_System.Clear_Dynamic_Memory();

        std::cout << "\n";

        std::cout << "\n\e[0;32mTHE MAKEFILE CONSTRUCTED\e[0m\n\n";

    }



    if(str == "-ar"){

       argument_pass_cond = true;

       DataRecorder Dt_Recorder(argv[1],'w','n');

       Dt_Recorder.Add_Data_Record(argv[3],argv[4]);

       Dt_Recorder.Clear_Object_Memory();

       System_Interface.WriteChildProcess_StdOutput();

       System_Interface.WriteChildProcess_StdError();
       
    }

    if(str == "-cr"){

       argument_pass_cond = true;

       DataRecorder Dt_Recorder(argv[1],'w','n');

       Dt_Recorder.Clear_Data_Record(argv[3]);

       System_Interface.WriteChildProcess_StdOutput();

       System_Interface.WriteChildProcess_StdError();
    }

    if(str == "-up_lib"){

        argument_pass_cond = true;

        Kernel Build_System(argv[1],'w','n');

        Build_System.Update_Library();
    }



    if(!argument_pass_cond){

        std::cout << "\n You did not entered an acceptable option";

        System_Interface.WriteChildProcess_StdOutput();

        System_Interface.WriteChildProcess_StdError();

        exit(0);
    }

    std::cout << "\n";

    if(str == "-ip_for_gui"){

       System_Interface.Close_Child_Handles_For_Named_Pipe_Connection();

    }

    if(str == "-if_for_gui"){

       System_Interface.Close_Child_Handles_For_Named_Pipe_Connection();

    }



    return 0;
}


std::string Convert_Std_String(char * str){

     std::string st_string;

     size_t  string_size = strlen(str);

     for(size_t i=0;i<string_size;i++){

         st_string.push_back(str[i]);
     }

     st_string.shrink_to_fit();

     return st_string;
}


void Print_Src_Dependency_Data(std::vector<Compiler_Data> * ptr){

     for(size_t i=0;i<ptr->size();i++){

        std::cout << "\n";
        std::cout << "\n source file name:" << ptr->at(i).source_file_name;

        /*
        std::cout << "\n object file name:" << ptr->at(i).object_file_name;
        std::cout << "\n source file path:" << ptr->at(i).source_file_path;

        size_t header_number = ptr->at(i).dependent_headers.size();

        std::cout << "\n priority:" << ptr->at(i).priority;

        std::cout << "\n header_number:" << header_number;        

        std::cout << "\n dependent headers:";

        for(size_t j=0;j<header_number;j++){

            std::cout << "\n Header: " << j << "-:" << ptr->at(i).dependent_headers.at(j);
        }

        */
    }

    std::cout << "\n\n";
}

