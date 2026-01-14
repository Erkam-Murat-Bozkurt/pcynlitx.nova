
HEADERS_LOCATION=D:\WAREHOUSE\PROJECT.HEADER.FILES
OBJECTS_LOCATION=D:\WAREHOUSE\PROJECT.OBJECT.FILES
CURRENT_LOCATION=D:\pcynlitx.build\PROJECT.BUILD.TOOLS\Directory_Enumerator

vpath %.h $(HEADERS_LOCATION)
vpath %.o $(OBJECTS_LOCATION)

Directory_Enumerator.o : Directory_Enumerator.cpp Directory_Enumerator.h Cpp_FileOperations.h

	g++ -Wall -c -std=c++17 -I$(HEADERS_LOCATION) -I$(CURRENT_LOCATION) Directory_Enumerator.cpp \
	 Directory_Enumerator.h  -include Cpp_FileOperations.h 
