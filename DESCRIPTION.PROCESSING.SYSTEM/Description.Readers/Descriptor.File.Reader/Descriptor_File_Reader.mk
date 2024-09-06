
DES_RED=C:\Development.Files\pcynlitx.build\DESCRIPTION.PROCESSING.SYSTEM\Description.Readers\Descriptor.File.Reader
DES_COL=C:\Development.Files\pcynlitx.build\DESCRIPTION.PROCESSING.SYSTEM\Description.Readers\Descriptor.File.Data.Collector
SYN_CON=C:\Development.Files\pcynlitx.build\DESCRIPTION.PROCESSING.SYSTEM\Description.Readers\Descriptor.File.Syntax.Controller
CPP_OPS=C:\Development.Files\pcynlitx.build\BASIC.TOOLS\Cpp_FileOperations
STRING_OPS=C:\Development.Files\pcynlitx.build\BASIC.TOOLS\StringOperator
CHAR_OPS=C:\Development.Files\pcynlitx.build\BASIC.TOOLS\CharOperator


VPATH = $(DES_RED) $(DES_COL) $(CPP_OPS) $(STRING_OPS) $(CHAR_OPS) $(SYN_CON)

Descriptor_File_Reader.exe: Descriptor_File_Reader_Main_File.cpp \
	Descriptor_File_Reader.cpp Descriptor_File_Data_Collector.cpp \
	Descriptor_File_Syntax_Controller.cpp \
	StringOperator.cpp CharOperator.cpp Cpp_FileOperations.cpp \
	CharOperator.cpp Cpp_FileOperations.cpp \
    Descriptor_File_Reader.hpp \
	Descriptor_File_Data_Collector.hpp \
	Descriptor_File_Syntax_Controller.hpp \
	StringOperator.h CharOperator.h Cpp_FileOperations.h

	g++ -std=c++17 -static-libgcc -static-libstdc++ -ggdb \
	  -o Descriptor_File_Reader.exe \
	  -I$(DES_COL) -I$(CPP_OPS) -I$(STRING_OPS) \
		-I$(SYN_CON) -I$(CHAR_OPS) \
		-L$(CPP_OPS) -L$(STRING_OPS) \
		-L$(CHAR_OPS) -L$(DES_COL) -L$(SYN_CON) \
		Descriptor_File_Reader_Main_File.cpp $(DES_RED)\Descriptor_File_Reader.cpp \
		$(DES_COL)\Descriptor_File_Data_Collector.cpp \
		$(SYN_CON)\Descriptor_File_Syntax_Controller.cpp \
	  $(STRING_OPS)\StringOperator.cpp $(CHAR_OPS)\CharOperator.cpp \
		$(CPP_OPS)\Cpp_FileOperations.cpp \
		-include $(DES_RED)\Descriptor_File_Reader.hpp \
		-include $(DES_COL)\Descriptor_File_Data_Collector.hpp \
		-include $(SYN_CON)\Descriptor_File_Syntax_Controller.hpp \
		-include $(STRING_OPS)\StringOperator.h \
		-include $(CHAR_OPS)\CharOperator.h \
		-include $(CPP_OPS)\Cpp_FileOperations.h
