

SYSTEM_INTER_LOCATION=D:\pcynlitx.build\BASIC.TOOLS\Custom_System_Interface
FILE_MANAGER_LOCATION=D:\pcynlitx.build\BASIC.TOOLS\Cpp_FileOperations

VPATH = $(SYSTEM_INTER_LOCATION) \
	    $(FILE_MANAGER_LOCATION)

test_process.exe : KernelTest.cpp \
	Custom_System_Interface.cpp Cpp_FileOperations.cpp \
    Custom_System_Interface.h Cpp_FileOperations.h

	g++ -Wall -std=c++17 -o test_process.exe \
	-I$(SYSTEM_INTER_LOCATION) -I$(FILE_MANAGER_LOCATION) \
    -L$(SYSTEM_INTER_LOCATION) -L$(FILE_MANAGER_LOCATION) \
	KernelTest.cpp \
	$(SYSTEM_INTER_LOCATION)\Custom_System_Interface.cpp \
    $(FILE_MANAGER_LOCATION)\Cpp_FileOperations.cpp \
    -include $(SYSTEM_INTER_LOCATION)\Custom_System_Interface.h \
    -include $(FILE_MANAGER_LOCATION)\Cpp_FileOperations.h