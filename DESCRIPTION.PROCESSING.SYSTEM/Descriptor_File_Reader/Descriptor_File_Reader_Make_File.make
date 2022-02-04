
DES_RED=D:\pcynlitx.build\DESCRIPTION.PROCESSING.SYSTEM\Descriptor_File_Reader
DES_COL=D:\pcynlitx.build\DESCRIPTION.PROCESSING.SYSTEM\Descriptor_File_Data_Collector
CPP_OPS=D:\pcynlitx.build\BASIC.TOOLS\Cpp_FileOperations
STRING_OPS=D:\pcynlitx.build\BASIC.TOOLS\StringOperator
CHAR_OPS=D:\pcynlitx.build\BASIC.TOOLS\CharOperator


VPATH = $(DES_RED) $(DES_COL) $(CPP_OPS) $(STRING_OPS) $(CHAR_OPS)

Descriptor_File_Reader.exe: Descriptor_File_Reader_Main_File.cpp \
	Descriptor_File_Reader.cpp Descriptor_File_Data_Collector.cpp StringOperator.cpp \
	CharOperator.cpp Cpp_FileOperations.cpp \
  Descriptor_File_Reader.hpp Descriptor_File_Data_Collector.hpp \
	StringOperator.h CharOperator.h Cpp_FileOperations.h

	g++ -std=c++17 -o Descriptor_File_Reader.exe -I$(DES_COL) -I$(CPP_OPS) -I$(STRING_OPS) \
	  -I$(CHAR_OPS) -L$(CPP_OPS) -L$(STRING_OPS) -L$(CHAR_OPS) -L$(DES_COL) \
		Descriptor_File_Reader_Main_File.cpp $(DES_RED)\Descriptor_File_Reader.cpp \
		$(DES_COL)\Descriptor_File_Data_Collector.cpp \
	  $(STRING_OPS)\StringOperator.cpp $(CHAR_OPS)\CharOperator.cpp \
		$(CPP_OPS)\Cpp_FileOperations.cpp \
		-include $(DES_RED)\Descriptor_File_Reader.hpp $(DES_COL)\Descriptor_File_Data_Collector.hpp \
		-include $(STRING_OPS)\StringOperator.h \
		-include $(CHAR_OPS)\CharOperator.h -include $(CPP_OPS)\Cpp_FileOperations.h
