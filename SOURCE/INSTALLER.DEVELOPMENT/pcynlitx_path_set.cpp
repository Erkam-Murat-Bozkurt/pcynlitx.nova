

#include <cstdlib>
#include <cstring>
#include <iostream>

void Place_String(char ** command, char * string, int * index_counter);

int main(){

    char reg_exe [] = "reg.exe add HKCU\\Environment /v Path /t REG_SZ /d \"%Path%";

    char path [] = ";C:\\Program Files\\Pcynlitx;\" /f";

    size_t reg_exe_size = strlen(reg_exe);

    size_t path_size = strlen(path);

    size_t command_size = reg_exe_size + path_size;

    char * set_command = new char [10*command_size];

    int index_counter = 0;

    Place_String(&set_command,reg_exe,&index_counter);

    Place_String(&set_command,path,&index_counter);

    set_command[index_counter] ='\0';

    int value = system(set_command);

    if(value == -1){

        std::cout << "\n The pcynlitx path can not be assigned.";

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
