
LIB_NAME_EXT=D:\pcynlitx.build\PROJECT.BUILD.TOOLS\Library_Name_Extractor
DIR_ENUM=D:\pcynlitx.build\PROJECT.BUILD.TOOLS\Directory_Enumerator
DES_RED=D:\pcynlitx.build\DESCRIPTION.PROCESSING.SYSTEM\Descriptor_File_Reader
DES_COL=D:\pcynlitx.build\DESCRIPTION.PROCESSING.SYSTEM\Descriptor_File_Data_Collector
CPP_OPS=D:\pcynlitx.build\BASIC.TOOLS\Cpp_FileOperations
STRING_OPS=D:\pcynlitx.build\BASIC.TOOLS\StringOperator
CHAR_OPS=D:\pcynlitx.build\BASIC.TOOLS\CharOperator
DIR_OPS=D:\pcynlitx.build\BASIC.TOOLS\DirectoryOperations


VPATH = $(LIB_NAME_EXT) $(DIR_ENUM) $(DES_RED) $(DES_COL) $(CPP_OPS) $(STRING_OPS) $(CHAR_OPS)

Descriptor_File_Reader.exe: Library_Name_Extractor_Main_File.cpp \
	Library_Name_Extractor.cpp Directory_Enumerator.cpp \
	Descriptor_File_Reader.cpp Descriptor_File_Data_Collector.cpp StringOperator.cpp \
	CharOperator.cpp Cpp_FileOperations.cpp \
  Library_Name_Extractor.hpp Directory_Enumerator.h Descriptor_File_Reader.hpp Descriptor_File_Data_Collector.hpp \
	StringOperator.h CharOperator.h Cpp_FileOperations.h

	g++ -std=c++17 -o Library_Name_Extractor.exe -I$(LIB_NAME_EXT) -I$(DIR_ENUM) \
	  -I$(DES_RED) -I$(DES_COL) -I$(CPP_OPS) -I$(STRING_OPS) -I$(DIR_OPS) \
	  -I$(CHAR_OPS) -L$(LIB_NAME_EXT) -L$(DIR_ENUM) -L$(DES_RED) \
		-L$(CPP_OPS) -L$(STRING_OPS) -L$(CHAR_OPS) -L$(DES_COL) -L$(DIR_OPS) \
		$(LIB_NAME_EXT)\Library_Name_Extractor_Main_File.cpp \
		$(LIB_NAME_EXT)\Library_Name_Extractor.cpp $(DIR_ENUM)\Directory_Enumerator.cpp \
		$(DES_RED)\Descriptor_File_Reader.cpp \
		$(DES_COL)\Descriptor_File_Data_Collector.cpp \
	  $(STRING_OPS)\StringOperator.cpp $(DIR_OPS)\DirectoryOperations.cpp $(CHAR_OPS)\CharOperator.cpp \
		$(CPP_OPS)\Cpp_FileOperations.cpp \
		-include $(LIB_NAME_EXT)\Library_Name_Extractor.hpp -include $(DIR_ENUM)\Directory_Enumerator.h \
		-include $(DES_RED)\Descriptor_File_Reader.hpp $(DES_COL)\Descriptor_File_Data_Collector.hpp \
		-include $(STRING_OPS)\StringOperator.h -include $(DIR_OPS)\DirectoryOperations.h  \
		-include $(CHAR_OPS)\CharOperator.h -include $(CPP_OPS)\Cpp_FileOperations.h
