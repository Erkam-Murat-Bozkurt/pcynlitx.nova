
HEADERS_LOCATION=D:\WAREHOUSE\PROJECT.HEADER.FILES
OBJECTS_LOCATION=D:\WAREHOUSE\PROJECT.OBJECT.FILES
CURRENT_LOCATION=D:\pcynlitx.build\BASIC.TOOLS\DirectoryOperations

vpath %.h $(HEADERS_LOCATION)
vpath %.o $(OBJECTS_LOCATION)

DirectoryOperations.o : DirectoryOperations.cpp DirectoryOperations.h CharOperator.h

	g++ -Wall -c -std=c++17 -I$(HEADERS_LOCATION) -I$(CURRENT_LOCATION) DirectoryOperations.cpp \
	 DirectoryOperations.h  -include CharOperator.h 
