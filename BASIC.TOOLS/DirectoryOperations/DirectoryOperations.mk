
HEADERS_LOCATION=D:\WAREHOUSE\PROJECT.HEADER.FILES
OBJECTS_LOCATION=D:\WAREHOUSE\PROJECT.OBJECT.FILES
CURRENT_LOCATION=D:\pcynlitx.build\BASIC.TOOLS\DirectoryOperations
CHAR_OPR=D:\pcynlitx.build\BASIC.TOOLS\CharOperator
CPP_OPR=D:\pcynlitx.build\BASIC.TOOLS\Cpp_FileOperations
INT_CHAR=D:\pcynlitx.build\BASIC.TOOLS\IntToCharTranslater


VPATH = $(HEADERS_LOCATION) $(OBJECTS_LOCATION) $(CHAR_OPR) $(CPP_OPR) $(INT_CHAR)

DirectoryOperations.exe : DirectoryOperations_Main_File.cpp DirectoryOperations.cpp CharOperator.cpp \
					      Cpp_FileOperations.cpp DirectoryOperations.h CharOperator.h \
						  IntToCharTranslater.h  Cpp_FileOperations.h 

	g++ -Wall -std=c++17 -o DirectoryOperations.exe \
	-I$(HEADERS_LOCATION) -I$(CHAR_OPR) -I$(INT_CHAR) -I$(CPP_OPR) \
	-I$(CURRENT_LOCATION) -L$(CHAR_OPR) -L$(CPP_OPR)-L$(INT_CHAR) DirectoryOperations_Main_File.cpp \
	 DirectoryOperations.cpp $(CHAR_OPR)\CharOperator.cpp $(INT_CHAR)\IntToCharTranslater.cpp \
	 $(CPP_OPR)\Cpp_FileOperations.cpp \
	 -include DirectoryOperations.h -include $(CHAR_OPR)\CharOperator.h \
	 -include $(INT_CHAR)\IntToCharTranslater.h -include $(CPP_OPR)\Cpp_FileOperations.h
