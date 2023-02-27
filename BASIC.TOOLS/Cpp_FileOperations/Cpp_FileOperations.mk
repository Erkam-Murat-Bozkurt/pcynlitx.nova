
HEADERS_LOCATION=D:\WAREHOUSE\PROJECT.HEADER.FILES
OBJECTS_LOCATION=D:\WAREHOUSE\PROJECT.OBJECT.FILES
CURRENT_LOCATION=D:\pcynlitx.build\BASIC.TOOLS\Cpp_FileOperations

vpath %.h $(HEADERS_LOCATION)
vpath %.o $(OBJECTS_LOCATION)

Cpp_FileOperations.exe : Cpp_FileOperations_Main_File.cpp \
Cpp_FileOperations.cpp Cpp_FileOperations.h

	g++ -Wall -std=c++17 -o Cpp_FileOperations.exe \
	-I$(HEADERS_LOCATION) -I$(CURRENT_LOCATION) \
	Cpp_FileOperations_Main_File.cpp Cpp_FileOperations.cpp \
	 Cpp_FileOperations.h
