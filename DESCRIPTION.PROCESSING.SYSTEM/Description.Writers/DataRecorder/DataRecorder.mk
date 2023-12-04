
STRING_OPS=D:\pcynlitx.build\BASIC.TOOLS\StringOperator
CHAR_OPS=D:\pcynlitx.build\BASIC.TOOLS\CharOperator
FILE_OPRS=D:\pcynlitx.build\BASIC.TOOLS\Cpp_FileOperations
DTR_REC=D:\pcynlitx.build\DESCRIPTION.PROCESSING.SYSTEM\Description.Writers\DataRecorder

DES_RED=D:\pcynlitx.build\DESCRIPTION.PROCESSING.SYSTEM\Description.Readers\Descriptor.File.Reader
DES_COL=D:\pcynlitx.build\DESCRIPTION.PROCESSING.SYSTEM\Description.Readers\Descriptor.File.Data.Collector
SYN_CON=D:\pcynlitx.build\DESCRIPTION.PROCESSING.SYSTEM\Description.Readers\Descriptor.File.Syntax.Controller

VPATH = $(STRING_OPS) $(CHAR_OPS) $(FILE_OPRS) $(DTR_REC) \
		$(DES_RED) $(DES_COL) $(SYN_CON)

DataRecorder.exe : DataRecorder_Main_File.cpp \
	DataRecorder.cpp \
	Descriptor_File_Reader.cpp \
	Descriptor_File_Data_Collector.cpp \
	Descriptor_File_Syntax_Controller.cpp\
	StringOperator.cpp \
	CharOperator.cpp \
	Cpp_FileOperations.cpp \
	DataRecorder.h \
	Descriptor_File_Reader.hpp \
	Descriptor_File_Data_Collector.hpp \
	Descriptor_File_Syntax_Controller.hpp \
	StringOperator.h \
	CharOperator.h \
	Cpp_FileOperations.h

	g++ -std=c++17 -o DataRecorder.exe \
	-I$(STRING_OPS) -I$(CHAR_OPS) \
	-I$(FILE_OPRS)  -I$(DTR_REC) \
	-I$(DES_RED)    -I$(DES_COL) \
	-I$(SYN_CON) \
	-L$(STRING_OPS) -L$(CHAR_OPS) \
	-L$(FILE_OPRS) -L$(DTR_REC) \
	-L$(DES_RED)   -L$(DES_COL) \
	-L$(SYN_CON) \
	$(DTR_REC)\DataRecorder_Main_File.cpp \
	$(DTR_REC)\DataRecorder.cpp \
	$(DES_RED)\Descriptor_File_Reader.cpp \
	$(DES_COL)\Descriptor_File_Data_Collector.cpp \
	$(SYN_CON)\Descriptor_File_Syntax_Controller.cpp \
	$(STRING_OPS)\StringOperator.cpp \
	$(CHAR_OPS)\CharOperator.cpp \
	$(FILE_OPRS)\Cpp_FileOperations.cpp \
	-include $(DTR_REC)\DataRecorder.h \
	-include $(DES_RED)\Descriptor_File_Reader.hpp \
	-include $(DES_COL)\Descriptor_File_Data_Collector.hpp \
	-include $(SYN_CON)\Descriptor_File_Syntax_Controller.hpp \
	-include $(STRING_OPS)\StringOperator.h \
	-include $(CHAR_OPS)\CharOperator.h \
	-include $(FILE_OPRS)\Cpp_FileOperations.h
