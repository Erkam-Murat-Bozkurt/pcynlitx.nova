
HEADERS_LOCATION=D:\WAREHOUSE\PROJECT.HEADER.FILES
OBJECTS_LOCATION=D:\WAREHOUSE\PROJECT.OBJECT.FILES
CURRENT_LOCATION=D:\pcynlitx.build\BASIC.TOOLS\StringOperator

vpath %.h $(HEADERS_LOCATION)
vpath %.o $(OBJECTS_LOCATION)

StringOperator.o : StringOperator.cpp StringOperator.h Cpp_FileOperations.h CharOperator.h

	g++ -Wall -c -std=c++17 -I$(HEADERS_LOCATION) -I$(CURRENT_LOCATION) StringOperator.cpp \
	 StringOperator.h  -include Cpp_FileOperations.h  -include CharOperator.h 
