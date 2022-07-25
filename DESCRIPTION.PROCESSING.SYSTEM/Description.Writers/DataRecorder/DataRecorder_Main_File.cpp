
#include "DataRecorder.h"

int main(int argc, char ** argv){

    if(argc < 3){

       std::cout << "\n The usage: <DataRecorder.exe> <Descriptor File Path> <Data Type> <Data>";

    }

    DataRecorder Recorder;


    // The argv[1] is the descriptor file path

    // The argv[2] is the data ttype

    // The argv[3] is the data to be recorded


    Recorder.SetFilePath(argv[1]);

    Recorder.Add_Data_Record(argv[2],argv[3]);

    return 0;
}
