


STRING_OPS=D:\pcynlitx.build\BASIC.TOOLS\StringOperator
DIR_OPS=D:\pcynlitx.build\BASIC.TOOLS\DirectoryOperations
CHAR_OPS=D:\pcynlitx.build\BASIC.TOOLS\CharOperator
FILE_OPRS=D:\pcynlitx.build\BASIC.TOOLS\Cpp_FileOperations
GIT_LIST=D:\pcynlitx.build\PROJECT.BUILD.TOOLS\Git_File_List_Receiver
DES_READ=D:\pcynlitx.build\DESCRIPTION.PROCESSING.SYSTEM\Description.Readers\Descriptor.File.Reader
DES_DATA_COL=D:\pcynlitx.build\DESCRIPTION.PROCESSING.SYSTEM\Description.Readers\Descriptor.File.Data.Collector
DES_SYN_CON=D:\pcynlitx.build\DESCRIPTION.PROCESSING.SYSTEM\Description.Readers\Descriptor.File.Syntax.Controller
SOURCE_DETR=D:\pcynlitx.build\SOURCE.FILE.DATA.COLLECTORS\Source_File_Determiner
HEAD_DETR=D:\pcynlitx.build\SOURCE.FILE.DATA.COLLECTORS\Header_File_Determiner
SRC_READER=D:\pcynlitx.build\PROJECT.BUILD.TOOLS\Project_Src_Code_Rdr


VPATH = $(DIR_OPS) $(STRING_OPS) $(CHAR_OPS) $(FILE_OPRS) \
	    $(GIT_LIST) $(DES_READ) $(DES_DATA_COL) $(DES_SYN_CON) \
		$(SRC_READER) $(SOURCE_DETR) $(HEAD_DETR)

Header_File_Processor.exe: Header_File_Processor_Main_File.cpp \
    Header_File_Processor.cpp \
	Project_Src_Code_Rdr.cpp \
	Descriptor_File_Reader.cpp \
	Descriptor_File_Data_Collector.cpp \
	Git_File_List_Receiver.cpp \
	Source_File_Determiner.cpp \
	Header_File_Determiner.cpp \
	StringOperator.cpp \
	CharOperator.cpp \
	Cpp_FileOperations.cpp \
	Header_File_Processor.hpp \
	Project_Src_Code_Rdr.hpp \
	Git_File_List_Receiver.hpp \
    Source_File_Determiner.h \
	Header_File_Determiner.h \
	StringOperator.h \
	CharOperator.h \
	Cpp_FileOperations.h

	g++ -std=c++17 -static-libgcc -static-libstdc++ -ggdb -o Header_File_Processor.exe \
		-I$(STRING_OPS)   -I$(CHAR_OPS) \
		-I$(FILE_OPRS)    -I$(DES_READ) \
		-I$(SOURCE_DETR)  -I$(HEAD_DETR) \
		-I$(DES_DATA_COL) -I$(GIT_LIST) \
		-I$(DIR_OPS)      -I$(DES_SYN_CON) \
		-I$(SRC_READER) \
	    -L$(STRING_OPS)   -L$(CHAR_OPS) \
		-L$(FILE_OPRS)    -L$(DES_READ) \
		-L$(DES_DATA_COL) -L$(GIT_LIST) \
		-L$(DIR_OPS)      -L$(DES_SYN_CON) \
		-L$(SRC_READER)   -L$(SOURCE_DETR)  \
		-L$(HEAD_DETR) \
		Header_File_Processor_Main_File.cpp \
		Header_File_Processor.cpp \
		$(SRC_READER)\Project_Src_Code_Rdr.cpp \
		$(GIT_LIST)\Git_File_List_Receiver.cpp \
		$(DES_READ)\Descriptor_File_Reader.cpp \
		$(DES_DATA_COL)\Descriptor_File_Data_Collector.cpp \
		$(DES_SYN_CON)\Descriptor_File_Syntax_Controller.cpp \
		$(SOURCE_DETR)\Source_File_Determiner.cpp \
		$(HEAD_DETR)\Header_File_Determiner.cpp \
		$(STRING_OPS)\StringOperator.cpp \
		$(DIR_OPS)\DirectoryOperations.cpp \
		$(CHAR_OPS)\CharOperator.cpp \
		$(FILE_OPRS)\Cpp_FileOperations.cpp \
		-include Header_File_Processor.hpp \
		-include $(SRC_READER)\Project_Src_Code_Rdr.hpp \
		-include $(GIT_LIST)\Git_File_List_Receiver.hpp \
		-include $(DES_READ)\Descriptor_File_Reader.hpp \
		-include $(DES_DATA_COL)\Descriptor_File_Data_Collector.hpp \
		-include $(DES_SYN_CON)\Descriptor_File_Syntax_Controller.hpp \
		-include $(GIT_LIST)\Git_File_List_Receiver.hpp \
	    -include $(SOURCE_DETR)\Source_File_Determiner.h \
		-include $(HEAD_DETR)\Header_File_Determiner.h \
		-include $(DIR_OPS)\DirectoryOperations.h \
		-include $(STRING_OPS)\StringOperator.h \
		-include $(CHAR_OPS)\CharOperator.h \
		-include $(FILE_OPRS)\Cpp_FileOperations.h \
		-lpthread
