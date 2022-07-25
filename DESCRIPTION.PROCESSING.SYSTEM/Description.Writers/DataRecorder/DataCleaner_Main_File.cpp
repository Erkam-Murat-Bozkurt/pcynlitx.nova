

#include "DataRecorder.h"

int main(int argc, char ** argv){

    if(argc < 2){

       std::cout << "\n The usage: <DataCleaner.exe> <Descriptor File Path> <Data Type>";
    }

    DataRecorder Recorder;

    Recorder.SetFilePath(argv[1]);

    // The argument is the data type which its data will be cleaned.

    std::cout << "\n The records related " << argv[2] << " will be removed";

    Recorder.Clear_Data_Record(argv[2]);

    std::cout << "\n\n The end of the file..\n\n";

    return 0;
}
