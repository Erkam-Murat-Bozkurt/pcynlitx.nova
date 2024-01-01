
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "Custom_System_Interface.h"

std::condition_variable cv;
std::mutex mtx;



void Read_From_Pipe(Custom_System_Interface * SysInt);

int main(int argc, char ** argv){

    Custom_System_Interface SysInt;

    size_t arg_name_size = 0;

    for(int i=0;i<argc;i++){

        arg_name_size = arg_name_size + strlen(argv[i]);
    }

    char cmd[2*arg_name_size];

    size_t index = 0;

    for(int i=1;i<argc;i++){

        for(size_t j=0;j<strlen(argv[i]);j++){

            cmd[index] = argv[i][j];

            index++;
        }

        cmd[index] = ' ';

        index++;
    }

    cmd[index] = '\0';

    SysInt.CreateProcessWith_NamedPipe_From_Parent(cmd);
    
    std::thread pipe_reader(Read_From_Pipe,&SysInt);

    pipe_reader.detach();

    std::unique_lock<std::mutex> lck(mtx);

    cv.wait(lck);

    lck.unlock();


    SysInt.Close_Parent_Handles_For_Named_Pipe_Connection();

    return 0;
}

void Read_From_Pipe(Custom_System_Interface * SysInt){

     for(;;)
     {

        if(!SysInt->IsChildProcessStillAlive()){

            break;
        }
        
        std::string pipeStr = SysInt->ReadNamedPipe_From_Parent();

        std::cout << pipeStr;
     } 
     
     cv.notify_all();
}