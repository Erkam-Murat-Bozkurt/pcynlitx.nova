

#include <cstdlib>
#include <cstring>
#include <iostream>

int main(){

    int value = system(".\\7z.exe x -y .\\FiraCode_Fonts.tar");

    if(value == -1){

      std::cout << "\n The fonts can not be extracted.";

      exit(EXIT_FAILURE);
    }

    value = system("xcopy /s /y .\\FiraCode_Fonts C:\\Windows\\Fonts");

    if(value == -1){

        std::cout << "\n The Liberation fonts can not be copied to the C:\\Windows\\Fonts";

        exit(EXIT_FAILURE);
    }

    value = system("del .\\FiraCode_Fonts.tar");

    value = system("rmdir .\\7z.exe /s /q");

    //value = system("rmdir .\\FiraCode_Fonts /s /q");



    char FiraCode_Regular   [] = "reg add \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Fonts\" /v \"FiraCode-Regular (TrueType)\" /t REG_SZ /d FiraCode-Regular.ttf /f";

    char FiraCode_Bold      [] = "reg add \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Fonts\" /v \"FiraCode-Bold (TrueType)\" /t REG_SZ /d FiraCode-Bold.ttf /f";

    char FiraCode_Light     [] = "reg add \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Fonts\" /v \"FiraCode-Light (TrueType)\" /t REG_SZ /d FiraCode-Light.ttf /f";

    char FiraCode_SemiBold  [] = "reg add \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Fonts\" /v \"FiraCode-SemiBold (TrueType)\" /t REG_SZ /d FiraCode-SemiBold.ttf /f";

    char FiraCode_Medium    [] = "reg add \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Fonts\" /v \"FiraCode-Medium (TrueType)\" /t REG_SZ /d FiraCode-Medium.ttf /f";

    char FiraCode_Variable  [] = "reg add \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Fonts\" /v \"FiraCode-VariableFont_wght (TrueType)\" /t REG_SZ /d FiraCode-VariableFont_wght.ttf /f";



    value = system(FiraCode_Regular);

    if(value == -1){

        std::cout << "\n The FiraCode_Regular font can not be installed.";

        exit(EXIT_FAILURE);
    }

    value = system(FiraCode_Bold);

    if(value == -1){

       std::cout << "\n The FiraCode_Bold font can not be installed.";

       exit(EXIT_FAILURE);
    }

    value = system(FiraCode_Light);

    if(value == -1){

        std::cout << "\n The FiraCode_Light font can not be installed.";

        exit(EXIT_FAILURE);
    }

    value = system(FiraCode_SemiBold);

    if(value == -1){

       std::cout << "\n The FiraCode_SemiBold font can not be installed";

       exit(EXIT_FAILURE);
    }


    value = system(FiraCode_Medium);

    if(value == -1){

       std::cout << "\n The FiraCode_Medium font can not be installed";

       exit(EXIT_FAILURE);
    }

    value = system(FiraCode_Variable);

    if(value == -1){

       std::cout << "\n The FiraCode_Variable font can not be installed";

       exit(EXIT_FAILURE);
    }

    return 0;
}
