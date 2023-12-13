



FILE_MANAGER_LOCATION=D:\pcynlitx.build\BASIC.TOOLS\Cpp_FileOperations

VPATH = $(FILE_MANAGER_LOCATION) \
	    $(FILE_MANAGER_LOCATION)

child_process.exe : child_process.cpp \
	Custom_System_Interface.cpp Cpp_FileOperations.cpp \
    Custom_System_Interface.h Cpp_FileOperations.h

	g++ -Wall -std=c++17 -o child_process.exe \
	-I$(FILE_MANAGER_LOCATION) -I$(FILE_MANAGER_LOCATION) \
	child_process.cpp \
	Custom_System_Interface.cpp $(FILE_MANAGER_LOCATION)\Cpp_FileOperations.cpp \
    Custom_System_Interface.h $(FILE_MANAGER_LOCATION)\Cpp_FileOperations.h
