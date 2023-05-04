
#include "DataRecorder.h"

int main(int argc, char ** argv)
{

    if(argc < 3){

       std::cout << "\n The usage: <DataRecorder.exe> <Descriptor File Path> <Data Type> <Data>";

    }

    DataRecorder Recorder(argv[1]);

    Recorder.Add_Data_Record(argv[2],argv[3]);

    return 0;
}
