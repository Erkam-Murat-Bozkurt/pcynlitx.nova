
STRING_OPS=D:\pcynlitx.build\BASIC.TOOLS\StringOperator
CHAR_OPS=D:\pcynlitx.build\BASIC.TOOLS\CharOperator
FILE_OPRS=D:\pcynlitx.build\BASIC.TOOLS\Cpp_FileOperations
DIR_OPS=D:\pcynlitx.build\BASIC.TOOLS\DirectoryOperations
GIT_LIST=D:\pcynlitx.build\PROJECT.BUILD.TOOLS\Git_File_List_Receiver
DES_READ=D:\pcynlitx.build\DESCRIPTION.PROCESSING.SYSTEM\Description.Readers\Descriptor.File.Reader
DES_DATA_COL=D:\pcynlitx.build\DESCRIPTION.PROCESSING.SYSTEM\Description.Readers\Descriptor.File.Data.Collector
DES_SYN_CON=D:\pcynlitx.build\DESCRIPTION.PROCESSING.SYSTEM\Description.Readers\Descriptor.File.Syntax.Controller
SRC_DT_COL=D:\pcynlitx.build\SOURCE.FILE.DATA.COLLECTORS\Source_File_Data_Collector
SOURCE_DETR=D:\pcynlitx.build\SOURCE.FILE.DATA.COLLECTORS\Source_File_Determiner
HEAD_DETR=D:\pcynlitx.build\SOURCE.FILE.DATA.COLLECTORS\Header_File_Determiner

VPATH = $(STRING_OPS) $(CHAR_OPS) $(FILE_OPRS) \
				$(HEAD_DETR) $(SOURCE_DETR) $(DES_READ) \
				$(DES_DATA_COL) $(GIT_LIST) $(SRC_DT_COL) \
				$(DES_SYN_CON) $(DIR_OPS)


Project_Files_Lister.exe: Project_Files_Lister_Main_File.cpp \
	Project_Files_Lister.cpp  \
	Git_File_List_Receiver.cpp \
	Descriptor_File_Reader.cpp \
	Descriptor_File_Data_Collector.cpp \
	Descriptor_File_Syntax_Controller.cpp \
	Source_File_Data_Collector.cpp \
	Source_File_Determiner.cpp \
	Header_File_Determiner.cpp \
	StringOperator.cpp \
	DirectoryOperations.cpp \
	CharOperator.cpp \
	Cpp_FileOperations.cpp \
	Project_Files_Lister.h \
	Git_File_List_Receiver.hpp \
	Source_File_Data_Collector.hpp \
	Source_File_Determiner.h \
	Header_File_Determiner.h \
	StringOperator.h \
	DirectoryOperations.h \
	CharOperator.h \
	Cpp_FileOperations.h

	g++ -std=c++17 -static-libgcc -static-libstdc++ -ggdb -o Project_Files_Lister.exe \
	 -I. \
	 -I$(HEAD_DETR) \
	 -I$(SOURCE_DETR) \
	 -I$(STRING_OPS) \
	 -I$(FILE_OPRS) \
	 -I$(CHAR_OPS) \
	 -I$(DES_READ) \
	 -I$(DES_DATA_COL) \
	 -I$(DES_SYN_CON) \
	 -I$(GIT_LIST) \
	 -I$(SRC_DT_COL) \
	 -I$(DIR_OPS) \
	 -L$(HEAD_DETR) \
	 -L$(SOURCE_DETR) \
	 -L$(STRING_OPS) \
	 -L$(GIT_LIST) \
	 -L$(CHAR_OPS) \
	 -L$(FILE_OPRS) \
	 -L$(DES_READ) \
	 -L$(DES_DATA_COL) \
	 -L$(SRC_DT_COL) \
	 -L$(DES_SYN_CON) \
	 -L$(DIR_OPS) \
		Project_Files_Lister_Main_File.cpp \
		Project_Files_Lister.cpp \
		$(GIT_LIST)\Git_File_List_Receiver.cpp \
		$(SOURCE_DETR)\Source_File_Determiner.cpp \
		$(SRC_DT_COL)\Source_File_Data_Collector.cpp \
		$(HEAD_DETR)\Header_File_Determiner.cpp \
		$(DES_READ)\Descriptor_File_Reader.cpp \
		$(DES_DATA_COL)\Descriptor_File_Data_Collector.cpp \
		$(DES_SYN_CON)\Descriptor_File_Syntax_Controller.cpp \
		$(STRING_OPS)\StringOperator.cpp \
		$(DIR_OPS)\DirectoryOperations.cpp \
		$(CHAR_OPS)\CharOperator.cpp \
		$(FILE_OPRS)\Cpp_FileOperations.cpp \
		-include Project_Files_Lister.h \
		-include $(GIT_LIST)\Git_File_List_Receiver.hpp \
		-include $(SOURCE_DETR)\Source_File_Determiner.h \
		-include $(HEAD_DETR)\Header_File_Determiner.h \
		-include $(DES_READ)\Descriptor_File_Reader.hpp \
		-include $(SRC_DT_COL)\Source_File_Data_Collector.hpp \
		-include $(DES_DATA_COL)\Descriptor_File_Data_Collector.hpp \
		-include $(DES_SYN_CON)\Descriptor_File_Syntax_Controller.hpp \
		-include $(STRING_OPS)\StringOperator.h \
		-include $(DIR_OPS)\DirectoryOperations.h \
		-include $(CHAR_OPS)\CharOperator.h \
		-include $(FILE_OPRS)\Cpp_FileOperations.h
