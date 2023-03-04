

STRING_OPS=D:\pcynlitx.build\BASIC.TOOLS\StringOperator
DIR_OPS=D:\pcynlitx.build\BASIC.TOOLS\DirectoryOperations
CPP_OPS=D:\pcynlitx.build\BASIC.TOOLS\Cpp_FileOperations
CHAR_OPS=D:\pcynlitx.build\BASIC.TOOLS\CharOperator
INT_TO_CHAR=D:\pcynlitx.build\BASIC.TOOLS\IntToCharTranslater

HEAD_DET=D:\pcynlitx.build\SOURCE.FILE.DATA.COLLECTORS\Header_File_Determiner
FILE_LISTER=D:\pcynlitx.build\SOURCE.FILE.DATA.COLLECTORS\Project_Files_Lister
SOURCE_DETR=D:\pcynlitx.build\SOURCE.FILE.DATA.COLLECTORS\Source_File_Determiner
SRC_COL=D:\pcynlitx.build\SOURCE.FILE.DATA.COLLECTORS\Source_File_Data_Collector
PRJ_DAT_COL=D:\pcynlitx.build\SOURCE.FILE.DATA.COLLECTORS\Project_Files_Data_Collector


DES_READER=D:\pcynlitx.build\DESCRIPTION.PROCESSING.SYSTEM\Description.Readers\Descriptor.File.Reader
DES_DATA_COL=D:\pcynlitx.build\DESCRIPTION.PROCESSING.SYSTEM\Description.Readers\Descriptor.File.Data.Collector
DES_SYN_CON=D:\pcynlitx.build\DESCRIPTION.PROCESSING.SYSTEM\Description.Readers\Descriptor.File.Syntax.Controller

GIT_LIST=D:\pcynlitx.build\PROJECT.BUILD.TOOLS\Git_File_List_Receiver


VPATH = $(DIR_OPS)     $(CPP_OPS)      $(CHAR_OPS)   \
		$(STRING_OPS)  $(HEAD_DET)     $(FILE_LISTER) \
		$(INT_TO_CHAR) $(DES_DATA_COL) $(DES_READER) \
		$(GIT_LIST)    $(SRC_COL)      $(SOURCE_DETR)\
		$(PRJ_DAT_COL) $(DES_SYN_CON)


MakeFile_Data_Collector.exe: MakeFile_Data_Collector_Main_File.cpp \
	MakeFile_Data_Collector.cpp \
	Project_Files_Lister.cpp \
	Project_Files_Data_Collector.cpp \
	Source_File_Data_Collector.cpp \
	Source_File_Determiner.cpp \
	Header_File_Determiner.cpp \
	Git_File_List_Receiver.cpp \
	Descriptor_File_Reader.cpp \
	Descriptor_File_Data_Collector.cpp \
	Descriptor_File_Syntax_Controller.cpp \
	DirectoryOperations.cpp \
	StringOperator.cpp \
	CharOperator.cpp \
	Cpp_FileOperations.cpp \
	IntToCharTranslater.cpp \
	MakeFile_Data_Collector.hpp \
	Project_Files_Lister.h \
	Git_File_List_Receiver.hpp \
	Source_File_Data_Collector.hpp \
	Source_File_Determiner.h \
	Header_File_Determiner.h \
	Descriptor_File_Reader.hpp \
	Descriptor_File_Data_Collector.hpp \
	Descriptor_File_Syntax_Controller.hpp \
	DirectoryOperations.h \
	StringOperator.h \
	CharOperator.h \
	IntToCharTranslater.h \
	Cpp_FileOperations.h

	g++ -std=c++17 -g -o MakeFile_Data_Collector.exe -I$(HEAD_DET) \
	  -I$(FILE_LISTER)  -I$(SOURCE_DETR) -I$(SRC_COL)     -I$(INT_TO_CHAR) \
	  -I$(DES_DATA_COL) -I$(DES_READER)  -I$(DES_SYN_CON) -I$(GIT_LIST) \
	  -I$(PRJ_DAT_COL)  -I$(DIR_OPS)     -I$(CPP_OPS)     -I$(CHAR_OPS) \
	  -I$(STRING_OPS) \
	  -L$(DES_DATA_COL) -L$(DES_READER)  -L$(STRING_OPS)  -L$(HEAD_DET) \
	  -L$(FILE_LISTER)  -L$(SOURCE_DETR) -L$(GIT_LIST)    -L$(SRC_COL) \
	  -L$(PRJ_DAT_COL)  -L$(DES_SYN_CON) -L$(DIR_OPS)     -L$(CPP_OPS) \
	  -L$(CHAR_OPS)     -L$(INT_TO_CHAR) \
		\
		MakeFile_Data_Collector_Main_File.cpp \
		MakeFile_Data_Collector.cpp \
		$(FILE_LISTER)\Project_Files_Lister.cpp \
		$(GIT_LIST)\Git_File_List_Receiver.cpp \
		$(SRC_COL)\Source_File_Data_Collector.cpp \
		$(PRJ_DAT_COL)\Project_Files_Data_Collector.cpp \
		$(SOURCE_DETR)\Source_File_Determiner.cpp \
		$(DES_READER)\Descriptor_File_Reader.cpp \
		$(DES_DATA_COL)\Descriptor_File_Data_Collector.cpp \
		$(DES_SYN_CON)\Descriptor_File_Syntax_Controller.cpp \
		$(HEAD_DET)\Header_File_Determiner.cpp \
		$(DIR_OPS)\DirectoryOperations.cpp \
		$(STRING_OPS)\StringOperator.cpp \
		$(CHAR_OPS)\CharOperator.cpp \
		$(CPP_OPS)\Cpp_FileOperations.cpp \
		$(INT_TO_CHAR)\IntToCharTranslater.cpp \
		-include MakeFile_Data_Collector.hpp \
		-include $(FILE_LISTER)\Project_Files_Lister.h \
		-include $(PRJ_DAT_COL)\Project_Files_Data_Collector.hpp \
		-include $(SRC_COL)\Source_File_Data_Collector.hpp \
		-include $(GIT_LIST)\Git_File_List_Receiver.hpp \
		-include $(SOURCE_DETR)\Source_File_Determiner.h \
		-include $(DES_READER)\Descriptor_File_Reader.hpp \
		-include $(DES_DATA_COL)\Descriptor_File_Data_Collector.hpp \
		-include $(DES_SYN_CON)\Descriptor_File_Syntax_Controller.hpp \
		-include $(HEAD_DET)\Header_File_Determiner.h \
		-include $(STRING_OPS)\StringOperator.h \
		-include $(DIR_OPS)\DirectoryOperations.h \
	    -include $(CHAR_OPS)\CharOperator.h \
		-include $(CPP_OPS)\Cpp_FileOperations.h \
		-include $(INT_TO_CHAR)\IntToCharTranslater.h
