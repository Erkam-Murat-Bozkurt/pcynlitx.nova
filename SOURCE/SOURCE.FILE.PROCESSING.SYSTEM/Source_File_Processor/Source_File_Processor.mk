



STRING_OPS=D:\pcynlitx.build\BASIC.TOOLS\StringOperator
DIR_OPS=D:\pcynlitx.build\BASIC.TOOLS\DirectoryOperations
CHAR_OPS=D:\pcynlitx.build\BASIC.TOOLS\CharOperator
FILE_OPRS=D:\pcynlitx.build\BASIC.TOOLS\Cpp_FileOperations
GIT_LIST=D:\pcynlitx.build\PROJECT.BUILD.TOOLS\Git_File_List_Receiver
DES_READ=D:\pcynlitx.build\DESCRIPTION.PROCESSING.SYSTEM\Description.Readers\Descriptor.File.Reader
DES_DATA_COL=D:\pcynlitx.build\DESCRIPTION.PROCESSING.SYSTEM\Description.Readers\Descriptor.File.Data.Collector
DES_FILE_SYNT_COL=D:\pcynlitx.build\DESCRIPTION.PROCESSING.SYSTEM\Description.Readers\Descriptor.File.Syntax.Controller
SOURCE_DETR=D:\pcynlitx.build\SOURCE.FILE.DATA.COLLECTORS\Source_File_Determiner
HEAD_DETR=D:\pcynlitx.build\SOURCE.FILE.DATA.COLLECTORS\Header_File_Determiner
SRC_READER=D:\pcynlitx.build\PROJECT.BUILD.TOOLS\Project_Src_Code_Rdr

VPATH = $(DIR_OPS) $(STRING_OPS) $(CHAR_OPS) $(FILE_OPRS) \
	    $(GIT_LIST) $(DES_READ) $(DES_DATA_COL) \
		$(DES_FILE_SYNT_COL) $(HEAD_DETR) \
        $(SOURCE_DETR) $(SRC_READER) 

Source_File_Processor.exe: Source_File_Processor_Main_File.cpp \
	Source_File_Processor.cpp \
	Project_Src_Code_Rdr.cpp \
	Descriptor_File_Reader.cpp \
	Descriptor_File_Data_Collector.cpp \
	Descriptor_File_Syntax_Controller.cpp \
	Git_File_List_Receiver.cpp \
	Source_File_Determiner.cpp \
	Header_File_Determiner.cpp \
	Project_Src_Code_Rdr.cpp \
	DirectoryOperations.cpp \
	StringOperator.cpp \
	CharOperator.cpp \
	Cpp_FileOperations.cpp \
	Source_File_Processor.hpp \
	Project_Src_Code_Rdr.hpp \
	Descriptor_File_Reader.hpp \
	Descriptor_File_Data_Collector.hpp \
	Descriptor_File_Syntax_Controller.hpp \
	Git_File_List_Receiver.hpp \
	Source_File_Determiner.h \
	Header_File_Determiner.h \
	Project_Src_Code_Rdr.hpp \
	DirectoryOperations.h \
	StringOperator.h \
	CharOperator.h \
	Cpp_FileOperations.h

	g++ -std=c++17 -o Source_File_Processor.exe \
	  -I$(STRING_OPS)  -I$(CHAR_OPS)    -I$(FILE_OPRS) \
	  -I$(HEAD_DETR)   -I$(SOURCE_DETR) -I$(SRC_READER) \
	  -I$(GIT_LIST)    -I$(DES_READ)    -I$(DES_DATA_COL) \
	  -I$(DES_FILE_SYNT_COL) -I$(DIR_OPS) \
	  -L$(STRING_OPS)  -L$(CHAR_OPS)    -L$(FILE_OPRS) \
	  -L$(HEAD_DETR)   -L$(SOURCE_DETR) -L$(SRC_READER) \
	  -L$(GIT_LIST)    -L$(DES_READ)    -L$(DES_DATA_COL) \
	  -L$(DES_FILE_SYNT_COL)  -L$(DIR_OPS) \
		Source_File_Processor_Main_File.cpp Source_File_Processor.cpp \
		$(SRC_READER)\Project_Src_Code_Rdr.cpp \
		$(GIT_LIST)\Git_File_List_Receiver.cpp \
		$(DES_READ)\Descriptor_File_Reader.cpp \
		$(DES_DATA_COL)\Descriptor_File_Data_Collector.cpp \
		$(DES_FILE_SYNT_COL)\Descriptor_File_Syntax_Controller.cpp \
		$(HEAD_DETR)\Header_File_Determiner.cpp \
		$(SOURCE_DETR)\Source_File_Determiner.cpp \
		$(DIR_OPS)\DirectoryOperations.cpp \
		$(STRING_OPS)\StringOperator.cpp \
		$(CHAR_OPS)\CharOperator.cpp \
		$(FILE_OPRS)\Cpp_FileOperations.cpp \
		-include Source_File_Determiner.h \
		-include $(SRC_READER)\Project_Src_Code_Rdr.hpp \
		-include $(HEAD_DETR)\Header_File_Determiner.h \
		-include $(SOURCE_DETR)\Source_File_Determiner.h \
		-include $(GIT_LIST)\Git_File_List_Receiver.hpp \
		-include $(DES_READ)\Descriptor_File_Reader.hpp \
		-include $(DES_DATA_COL)\Descriptor_File_Data_Collector.hpp \
		-include $(DES_FILE_SYNT_COL)\Descriptor_File_Syntax_Controller.hpp \
		-include $(DIR_OPS)\DirectoryOperations.h \
		-include $(STRING_OPS)\StringOperator.h \
		-include $(CHAR_OPS)\CharOperator.h \
		-include $(FILE_OPRS)\Cpp_FileOperations.h
