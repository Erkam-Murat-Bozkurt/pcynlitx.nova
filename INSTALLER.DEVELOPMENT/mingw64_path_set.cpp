
#include <cstdlib>
#include <cstring>
#include <iostream>

void Place_String(char ** command, char * string, int * index_counter);

int main(){

    char reg_exe [] = "reg.exe add HKCU\\Environment /v Path /t REG_SZ /d \"%Path%";

    char path_1 [] = ";C:\\Program Files\\Mingw64;";

    char path_2 [] = "C:\\Program Files\\Mingw64\\bin;";

    char path_3 [] = "C:\\Program Files\\Mingw64\\include;";

    char path_4 [] = "C:\\Program Files\\Mingw64\\x86_64-w64-mingw32;";

    char path_5 [] = "C:\\Program Files\\Mingw64\\x86_64-w64-mingw32\\include;";

    char path_6 [] = "C:\\Program Files\\Mingw64\\x86_64-w64-mingw32\\lib;\" /f";

    size_t reg_exe_size = strlen(reg_exe);

    size_t path_1_size = strlen(path_1);

    size_t path_2_size = strlen(path_2);

    size_t path_3_size = strlen(path_3);

    size_t path_4_size = strlen(path_4);

    size_t path_5_size = strlen(path_5);

    size_t path_6_size = strlen(path_6);


    size_t command_size = reg_exe_size + path_1_size + path_2_size + path_3_size

                          + path_4_size + path_5_size + path_6_size ;

    char * set_command = new char [10*command_size];

    int index_counter = 0;

    Place_String(&set_command,reg_exe,&index_counter);

    Place_String(&set_command,path_1,&index_counter);

    Place_String(&set_command,path_2,&index_counter);

    Place_String(&set_command,path_3,&index_counter);

    Place_String(&set_command,path_4,&index_counter);

    Place_String(&set_command,path_5,&index_counter);

    Place_String(&set_command,path_6,&index_counter);

    set_command[index_counter] ='\0';

    int value = system(set_command);

    if(value == -1){

        std::cout << "\n The mingw path can not be assigned.";

        exit(EXIT_FAILURE);
    }

    delete [] set_command;

    return 0;
}

void Place_String(char ** command, char * string, int * index_counter)
{
     size_t string_size = strlen(string);

     for(size_t i=0;i<string_size;i++){

         (*command) [*index_counter] = string[i];

         (*index_counter)++;
     }
}
