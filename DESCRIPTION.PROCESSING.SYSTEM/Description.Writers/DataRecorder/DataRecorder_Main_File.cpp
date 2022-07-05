
#include "DataRecorder.h"

int main(int argc, char ** argv){

    DataRecorder Recorder;

    Recorder.SetFilePath(argv[1]);

    char Data_Type [] = "INCLUDE DIRECTORIES";

    char Clear_Data_Type [] = "MAIN FILE NAMES";

    char dir [] = "D:\\PCYNLITX.BUILD.TEST";

    Recorder.Add_Data_Record(Data_Type,dir);

    Recorder.Clear_Data_Record(Clear_Data_Type);

    std::cout << "\n\n The end of the file..\n\n";

    return 0;
}
