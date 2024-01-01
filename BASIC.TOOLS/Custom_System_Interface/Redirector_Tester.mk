

FILE_MANAGER_LOCATION=D:\pcynlitx.build\BASIC.TOOLS\Cpp_FileOperations

VPATH = $(FILE_MANAGER_LOCATION) \
	    $(FILE_MANAGER_LOCATION)

Redirector_Tester.exe : Redirector_Tester.cpp \
	Custom_System_Interface.cpp Cpp_FileOperations.cpp \
    Custom_System_Interface.h Cpp_FileOperations.h

	g++ -Wall -std=c++17 -o Redirector_Tester.exe \
	-I$(FILE_MANAGER_LOCATION) -I$(FILE_MANAGER_LOCATION) \
	Redirector_Tester.cpp \
	Custom_System_Interface.cpp $(FILE_MANAGER_LOCATION)\Cpp_FileOperations.cpp \
    Custom_System_Interface.h $(FILE_MANAGER_LOCATION)\Cpp_FileOperations.h