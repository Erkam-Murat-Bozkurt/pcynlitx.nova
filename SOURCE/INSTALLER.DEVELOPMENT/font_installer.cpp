

#include <cstdlib>
#include <cstring>
#include <iostream>

int main(){


    int value = system("xcopy /s /y .\\FiraCode_Standard C:\\Windows\\Fonts");

    if(value == -1){

        std::cout << "\n The Fira Code fonts can not be copied to the C:\\Windows\\Fonts";

        exit(EXIT_FAILURE);
    }


    value = system("xcopy /s /y .\\Oswald C:\\Windows\\Fonts");

    if(value == -1){

        std::cout << "\n The Oswald fonts can not be copied to the C:\\Windows\\Fonts";

        exit(EXIT_FAILURE);
    }



    char FiraCode_Regular   [] = "reg add \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Fonts\" /v \"FiraCode-Regular (TrueType)\" /t REG_SZ /d FiraCode-Regular.ttf /f";

    char FiraCode_Bold      [] = "reg add \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Fonts\" /v \"FiraCode-Bold (TrueType)\" /t REG_SZ /d FiraCode-Bold.ttf /f";

    char FiraCode_Light     [] = "reg add \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Fonts\" /v \"FiraCode-Light (TrueType)\" /t REG_SZ /d FiraCode-Light.ttf /f";

    char FiraCode_SemiBold  [] = "reg add \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Fonts\" /v \"FiraCode-SemiBold (TrueType)\" /t REG_SZ /d FiraCode-SemiBold.ttf /f";

    char FiraCode_Medium    [] = "reg add \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Fonts\" /v \"FiraCode-Medium (TrueType)\" /t REG_SZ /d FiraCode-Medium.ttf /f";



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


    char Oswald_Regular     [] = "reg add \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Fonts\" /v \"Oswald-Regular (TrueType)\" /t REG_SZ /d Oswald-Regular.ttf /f";

    char Oswald_Bold        [] = "reg add \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Fonts\" /v \"Oswald-Bold (TrueType)\" /t REG_SZ /d Oswald-Bold.ttf /f";

    char Oswald_Light       [] = "reg add \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Fonts\" /v \"Oswald-Light (TrueType)\" /t REG_SZ /d Oswald-Light.ttf /f";

    char Oswald_SemiBold    [] = "reg add \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Fonts\" /v \"Oswald-SemiBold (TrueType)\" /t REG_SZ /d Oswald-SemiBold.ttf /f";

    char Oswald_Medium      [] = "reg add \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Fonts\" /v \"Oswald-Medium (TrueType)\" /t REG_SZ /d Oswald-Medium.ttf /f";

    char Oswald_ExtraLight  [] = "reg add \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Fonts\" /v \"Oswald-ExtraLight (TrueType)\" /t REG_SZ /d Oswald-ExtraLight.ttf /f";



    value = system(Oswald_Regular);

    if(value == -1){

        std::cout << "\n The Oswald_Regular font can not be installed.";

        exit(EXIT_FAILURE);
    }

    value = system(Oswald_Bold);

    if(value == -1){

       std::cout << "\n The Oswald_Bold font can not be installed.";

       exit(EXIT_FAILURE);
    }

    value = system(Oswald_Light);

    if(value == -1){

        std::cout << "\n The Oswald_Light font can not be installed.";

        exit(EXIT_FAILURE);
    }

    value = system(Oswald_SemiBold);

    if(value == -1){

       std::cout << "\n The Oswald_SemiBold font can not be installed";

       exit(EXIT_FAILURE);
    }


    value = system(Oswald_Medium);

    if(value == -1){

       std::cout << "\n The FiraCode_Medium font can not be installed";

       exit(EXIT_FAILURE);
    }

    value = system(Oswald_ExtraLight);

    if(value == -1){

       std::cout << "\n The Oswald_Variable font can not be installed";

       exit(EXIT_FAILURE);
    }


    return 0;
}
