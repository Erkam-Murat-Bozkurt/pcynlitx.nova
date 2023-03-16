

SYS_INT=D:\pcynlitx.build\BASIC.TOOLS\Custom_System_Interface
INT_TRANS=D:\pcynlitx.build\BASIC.TOOLS\IntToCharTranslater
STRING_OPS=D:\pcynlitx.build\BASIC.TOOLS\StringOperator
DIR_OPS=D:\pcynlitx.build\BASIC.TOOLS\DirectoryOperations
CHAR_OPS=D:\pcynlitx.build\BASIC.TOOLS\CharOperator
FILE_OPRS=D:\pcynlitx.build\BASIC.TOOLS\Cpp_FileOperations
DES_READ=D:\pcynlitx.build\DESCRIPTION.PROCESSING.SYSTEM\Description.Readers\Descriptor.File.Reader
DES_DATA_COL=D:\pcynlitx.build\DESCRIPTION.PROCESSING.SYSTEM\Description.Readers\Descriptor.File.Data.Collector
DES_SYN_CON=D:\pcynlitx.build\DESCRIPTION.PROCESSING.SYSTEM\Description.Readers\Descriptor.File.Syntax.Controller
GIT_LIST=D:\pcynlitx.build\PROJECT.BUILD.TOOLS\Git_File_List_Receiver
SOURCE_DETR=D:\pcynlitx.build\SOURCE.FILE.DATA.COLLECTORS\Source_File_Determiner
HEAD_DETR=D:\pcynlitx.build\SOURCE.FILE.DATA.COLLECTORS\Header_File_Determiner


VPATH = $(DIR_OPS)     $(STRING_OPS) \
	    $(DES_READ)    $(DES_DATA_COL) \
	    $(GIT_LIST)    $(DES_SYN_CON) \
		$(INT_TRANS)   $(SYS_INT) \
		$(SOURCE_DETR) $(HEAD_DETR) \
 	    $(CHAR_OPS)    $(FILE_OPRS) \

Project_Src_Code_Rdr.exe: Project_Src_Code_Rdr_Main_File.cpp \
    Project_Src_Code_Rdr.cpp \
	Git_File_List_Receiver.cpp  \
	Source_File_Determiner.cpp \
	Header_File_Determiner.cpp \
	Descriptor_File_Reader.cpp \
	Descriptor_File_Data_Collector.cpp \
	Descriptor_File_Syntax_Controller.cpp \
	StringOperator.cpp \
	CharOperator.cpp \
	IntToCharTranslater.cpp \
	Cpp_FileOperations.cpp \
	Custom_System_Interface.cpp \
	Project_Src_Code_Rdr.hpp \
	Git_File_List_Receiver.hpp  \
    Source_File_Determiner.h \
	Header_File_Determiner.h \
	StringOperator.h \
	DirectoryOperations.h \
	CharOperator.h \
	IntToCharTranslater.h \
	Cpp_FileOperations.h \
	Custom_System_Interface.h

	g++ -std=c++17 -static-libgcc -static-libstdc++ -ggdb -o Project_Src_Code_Rdr.exe \
	 -I. \
	 -I$(SOURCE_DETR) \
	 -I$(HEAD_DETR) \
	 -I$(DIR_OPS) \
	 -I$(STRING_OPS) \
	 -I$(CHAR_OPS) \
	 -I$(FILE_OPRS) \
	 -I$(CHAR_OPS) \
	 -I$(DES_READ) \
	 -I$(DES_DATA_COL) \
	 -I$(GIT_LIST) \
	 -I$(DES_SYN_CON) \
	 -I$(INT_TRANS) \
	 -I$(SYS_INT) \
	 -L$(DIR_OPS) \
	 -L$(STRING_OPS) \
	 -L$(GIT_LIST) \
	 -L$(CHAR_OPS) \
	 -L$(FILE_OPRS) \
	 -L$(DES_READ) \
	 -L$(DES_DATA_COL) \
	 -L$(DES_SYN_CON) \
	 -L$(INT_TRANS) \
	 -L$(SYS_INT) \
		Project_Src_Code_Rdr_Main_File.cpp \
		Project_Src_Code_Rdr.cpp \
		$(GIT_LIST)\Git_File_List_Receiver.cpp \
		$(SOURCE_DETR)\Source_File_Determiner.cpp \
	    $(HEAD_DETR)\Header_File_Determiner.cpp \
		$(DES_READ)\Descriptor_File_Reader.cpp \
		$(DES_DATA_COL)\Descriptor_File_Data_Collector.cpp \
		$(DES_SYN_CON)\Descriptor_File_Syntax_Controller.cpp \
		$(DIR_OPS)\DirectoryOperations.cpp \
		$(STRING_OPS)\StringOperator.cpp \
		$(CHAR_OPS)\CharOperator.cpp \
		$(INT_TRANS)\IntToCharTranslater.cpp \
		$(FILE_OPRS)\Cpp_FileOperations.cpp \
		$(SYS_INT)\Custom_System_Interface.cpp \
		-include $(GIT_LIST)\Git_File_List_Receiver.hpp \
	    -include $(SOURCE_DETR)\Source_File_Determiner.h \
	    -include $(HEAD_DETR)\Header_File_Determiner.h \
		-include $(DES_READ)\Descriptor_File_Reader.hpp \
		-include $(DES_DATA_COL)\Descriptor_File_Data_Collector.hpp \
		-include $(DES_SYN_CON)\Descriptor_File_Syntax_Controller.hpp \
		-include $(STRING_OPS)\StringOperator.h \
		-include $(DIR_OPS)\DirectoryOperations.h \
		-include $(CHAR_OPS)\CharOperator.h \
		-include $(INT_TRANS)\IntToCharTranslater.h \
		-include $(FILE_OPRS)\Cpp_FileOperations.h \
		-include $(SYS_INT)\Custom_System_Interface.h \
		-lpthread
