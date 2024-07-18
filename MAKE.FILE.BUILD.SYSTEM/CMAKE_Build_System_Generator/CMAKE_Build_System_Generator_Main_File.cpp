




#include <iostream>
#include <cstring>
#include "CMAKE_Build_System_Generator.hpp"
#include "CMAKE_System_Constructor.hpp"
#include "CMAKE_Main_File_Writer.hpp"
#include "Descriptor_File_Reader.hpp"


std::string Convert_Std_String(char * str);


int main(int argc, char ** argv){

    if(argc< 4){

       std::string error_message = "\n\n USAGE FOR BUILD SYSTEM CONSTRUCTION:";

       error_message += "\n\n <CMAKE_Build.exe> -bs ";

       error_message += "<Descriptor File Path> <project-name> <version-num>";

       error_message += "\n -bs: build type";

       error_message += "\n\n";

       error_message += "\n\n USAGE FOR EXECUTABLE FILE (TARGET) CONSTRUCTION:";

       error_message += "\n\n <CMAKE_Build.exe> -ef ";

       error_message += "<Descriptor File Path> <target-main-file path> <exe file name>";

       error_message += "\n -ef: build type";

       error_message += "\n\n";

       error_message += "\n\n";


       std::cout << error_message;

       exit(0);
    }




    // BUILD TYPE DETERMINATION

    size_t type_size = strlen(argv[1]);

    std::string build_type;

    for(size_t i=0;i<type_size;i++){

        build_type.push_back(argv[1][i]);
    }


    // COMMAND LINE ARGUMENTS TYPE CONVERSION

    size_t _argm3_size = strlen(argv[3]);

    std::string _argm3;

    for(size_t i=0;i<_argm3_size;i++){

          _argm3.push_back(argv[3][i]);
       }

    _argm3.shrink_to_fit();

    
    std::string _argm4;

    size_t _argm4_size = strlen(argv[4]);

    for(size_t i=0;i<_argm4_size;i++){

        _argm4.push_back(argv[4][i]);
    }

    _argm4.shrink_to_fit();



    SetPriorityClass(GetCurrentProcess(),HIGH_PRIORITY_CLASS);

    Custom_System_Interface System_Interface;

    System_Interface.SetCpuRate();
    



    Descriptor_File_Reader Des_File_Reader('w','n');    

    Des_File_Reader.Receive_Descriptor_File_Path(argv[2]);

    Des_File_Reader.Read_Descriptor_File();


    Git_Data_Processor Data_Processor('w','n');

    Data_Processor.Receive_Descriptor_File_Path(argv[2]);

    Data_Processor.Write_Git_Repo_List_File();

    Data_Processor.Determine_Git_Repo_Info();


    Source_File_Dependency_Determiner Dep_Determiner(argv[2],'w');

    Dep_Determiner.Receive_Descriptor_File_Reader(&Des_File_Reader);

    Dep_Determiner.Receive_Git_Data_Processor(&Data_Processor);



    if(build_type == "-ef"){

       Dep_Determiner.Collect_Dependency_Information(_argm3);
    }


    if(build_type == "-bs"){
         
       Dep_Determiner.Collect_Dependency_Information();
    }



    // BUILD SYSTEM GENERATOR OBJECT CONSTRUCTION

    CMAKE_Build_System_Generator BLD_System_Generator(argv[2],'w','n');

    BLD_System_Generator.Receive_System_Interface(&System_Interface);

    BLD_System_Generator.Receive_Descriptor_File_Reader(&Des_File_Reader);

    BLD_System_Generator.Receive_Git_Data_Processor(&Data_Processor);

    BLD_System_Generator.Receive_Source_File_Dependency_Determiner(&Dep_Determiner);

    if(build_type == "-bs"){

       BLD_System_Generator.Construct_Build_System(_argm3,_argm4);
    }




    if(build_type == "-bs_gui"){

        System_Interface.Connect_NamedPipe_From_Child_Process();

        BLD_System_Generator.Construct_Build_System(_argm3,_argm4);
    }


    if(build_type == "-ef"){

        BLD_System_Generator.Construct_Exe_Build_System(_argm3,_argm4);

    }

    if(build_type == "-ef_gui"){

        System_Interface.Connect_NamedPipe_From_Child_Process();

        BLD_System_Generator.Construct_Exe_Build_System(_argm3,_argm4);

    }


    std::cout << "\n";

    if(build_type == "-bs_gui"){

       System_Interface.Close_Child_Handles_For_Named_Pipe_Connection();
    }

    if(build_type == "-ef_gui"){

       System_Interface.Close_Child_Handles_For_Named_Pipe_Connection();

    }


    std::cout << "\n\nThe end of the program ..";

    std::cout << "\n\n";

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