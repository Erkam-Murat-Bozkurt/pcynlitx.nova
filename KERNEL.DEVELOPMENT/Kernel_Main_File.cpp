


#include <iostream>
#include <cstring>
#include "Kernel.hpp"
#include "Custom_System_Interface.h"


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

    System_Interface.Connect_NamedPipe_From_Child_Process();


    bool argument_pass_cond = false;

    std::string str = Convert_Std_String(argv[2]);

    if(str == "-ed"){

       Empty_Descriptor_File_Builder Empd_Builder('w');

       argument_pass_cond = true;

       Empd_Builder.Build_Empty_File(argv[1]);

       exit(0);
    }



    if(str == "-ip"){

        argument_pass_cond = true;

        Kernel Build_System(argv[1],'w');

        std::cout << "\n\n C++ BUILD SYSTEM CONSTRUCTION PROCESS INITIATED \n";

        Build_System.Receive_System_Interface(&System_Interface);

        Build_System.Setup_Build_Tools();

        Build_System.Clear_Dynamic_Memory();


        std::cout << "\n THE CONSTRUCTION COMPLATED ";
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

        Kernel Build_System(argv[1],'w');

        std::cout << "\n\e[0;32mTHE MAKEFILE CONSTRUCTION STARTED\e[0m\n";

        Build_System.Receive_System_Interface(&System_Interface);

        Build_System.Build_MakeFile(argv[3],argv[4],*argv[5]);

        Build_System.Clear_Dynamic_Memory();

        std::cout << "\n";

        std::cout << "\n\e[0;32mTHE MAKEFILE CONSTRUCTED\e[0m\n\n";

    }




    if(str == "-ar"){

       argument_pass_cond = true;

       DataRecorder Dt_Recorder(argv[1],'w');

       Dt_Recorder.Add_Data_Record(argv[3],argv[4]);

       Dt_Recorder.Clear_Object_Memory();
    }

    if(str == "-cr"){

       argument_pass_cond = true;

       DataRecorder Dt_Recorder(argv[1],'w');

       Dt_Recorder.Clear_Data_Record(argv[3]);

    }

    if(!argument_pass_cond){

        std::cout << "\n You did not entered an acceptable option";

        exit(0);
    }

    std::cout << "\n";


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