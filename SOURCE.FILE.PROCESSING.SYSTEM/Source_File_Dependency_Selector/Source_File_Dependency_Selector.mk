

STRING_OPS=D:\pcynlitx.build\BASIC.TOOLS\StringOperator
DIR_OPS=D:\pcynlitx.build\BASIC.TOOLS\DirectoryOperations
CPP_OPS=D:\pcynlitx.build\BASIC.TOOLS\Cpp_FileOperations
CHAR_OPS=D:\pcynlitx.build\BASIC.TOOLS\CharOperator
DIR_ENUM=D:\pcynlitx.build\PROJECT.BUILD.TOOLS\Directory_Enumerator
HEAD_DET=D:\pcynlitx.build\SOURCE.FILE.DATA.COLLECTORS\Header_File_Determiner
FILE_LISTER=D:\pcynlitx.build\SOURCE.FILE.DATA.COLLECTORS\Project_Files_Lister
SOURCE_DETR=D:\pcynlitx.build\SOURCE.FILE.DATA.COLLECTORS\Source_File_Determiner
INT_TO_CHAR=D:\pcynlitx.build\BASIC.TOOLS\IntToCharTranslater
DES_READER=D:\pcynlitx.build\DESCRIPTION.PROCESSING.SYSTEM\Description.Readers\Descriptor.File.Reader
DES_DATA_COL=D:\pcynlitx.build\DESCRIPTION.PROCESSING.SYSTEM\Description.Readers\Descriptor.File.Data.Collector
DES_FILE_SYNT_COL=D:\pcynlitx.build\DESCRIPTION.PROCESSING.SYSTEM\Description.Readers\Descriptor.File.Syntax.Controller
GIT_LIST=D:\pcynlitx.build\PROJECT.BUILD.TOOLS\Git_File_List_Receiver
FILE_DAT_COL=D:\pcynlitx.build\SOURCE.FILE.DATA.COLLECTORS\Project_Files_Data_Collector
SRC_DT_COL=D:\pcynlitx.build\SOURCE.FILE.DATA.COLLECTORS\Source_File_Data_Collector
SRC_INF_COL=D:\pcynlitx.build\SOURCE.FILE.PROCESSING.SYSTEM\Source_File_Information_Collector
HDR_PROC=D:\pcynlitx.build\SOURCE.FILE.PROCESSING.SYSTEM\Header_File_Processor
SRC_READER=D:\pcynlitx.build\PROJECT.BUILD.TOOLS\Project_Src_Code_Rdr


VPATH = $(DIR_OPS) $(CPP_OPS) $(CHAR_OPS) \
		$(SOURCE_DETR) $(DIR_ENUM) \
	    $(STRING_OPS) $(HEAD_DET) $(FILE_LISTER) \
		$(INT_TO_CHAR) $(DES_DATA_COL) $(DES_READER) \
		$(MAKE_DATA_COL) $(GIT_LIST) $(FILE_DAT_COL) \
		$(SRC_DT_COL) $(DES_FILE_SYNT_COL) $(SRC_INF_COL) \
		$(HDR_PROC) $(SRC_READER)

Source_File_Dependency_Selector.exe: Source_File_Dependency_Selector_Main_File.cpp \
	Source_File_Dependency_Selector.cpp \
	Source_File_Information_Collector.cpp \
	Header_File_Processor.cpp \
	Project_Src_Code_Rdr.cpp \
	Project_Files_Lister.cpp \
    Project_Files_Data_Collector.cpp \
	Source_File_Data_Collector.cpp \
	Git_File_List_Receiver.cpp \
	Source_File_Determiner.cpp \
	Header_File_Determiner.cpp \
	Descriptor_File_Reader.cpp \
	Descriptor_File_Data_Collector.cpp \
	Descriptor_File_Syntax_Controller.cpp \
	Directory_Enumerator.cpp \
	DirectoryOperations.cpp \
	StringOperator.cpp \
	CharOperator.cpp \
	Cpp_FileOperations.cpp \
	Source_File_Dependency_Selector.hpp \
	Source_File_Information_Collector.hpp \
	Header_File_Processor.hpp \
	Project_Src_Code_Rdr.hpp \
	Project_Files_Lister.h \
	Project_Files_Data_Collector.hpp \
	Source_File_Data_Collector.cpp \
	Git_File_List_Receiver.hpp \
	Descriptor_File_Reader.hpp \
	Descriptor_File_Data_Collector.hpp \
	Descriptor_File_Syntax_Controller.hpp \
	Source_File_Determiner.h \
	Header_File_Determiner.h \
	Directory_Enumerator.h \
	StringOperator.h \
	DirectoryOperations.h \
	CharOperator.h \
	Cpp_FileOperations.h

	g++ -std=c++17 -g -o Source_File_Dependency_Selector.exe \
	 -I$(DIR_OPS) -I$(CPP_OPS) -I$(CHAR_OPS) \
	 -I$(SRC_INF_COL)   -I$(STRING_OPS)  -I$(HEAD_DET) \
	 -I$(FILE_LISTER)   -I$(SOURCE_DETR) -I$(GIT_LIST) \
	 -I$(CLASS_SYNTAX)  -I$(DIR_ENUM)    -I$(INT_TO_CHAR) \
	 -I$(DES_DATA_COL)  -I$(DES_READER) \
	 -I$(MAKE_DATA_COL) -I$(FILE_DAT_COL) \
	 -I$(SRC_DT_COL)    -I$(DES_FILE_SYNT_COL) \
	 -I$(HDR_PROC)      -I$(SRC_READER) \
	 -L$(SRC_INF_COL)   -L$(DIR_ENUM) \
	 -L$(DIR_OPS)       -L$(CPP_OPS) \
	 -L$(CHAR_OPS)      -L$(INT_TO_CHAR) \
	 -L$(DES_DATA_COL)  -L$(DES_READER)\
	 -L$(DES_READER)    -L$(STRING_OPS) \
	 -L$(HEAD_DET)      -L$(FILE_LISTER) \
	 -L$(SOURCE_DETR)   -L$(MAKE_DATA_COL) \
	 -L$(GIT_LIST)      -L$(FILE_DAT_COL) \
	 -L$(SRC_DT_COL)    -L$(DES_FILE_SYNT_COL) \
	 -L$(HDR_PROC)      -L$(SRC_READER) \
		Source_File_Dependency_Selector_Main_File.cpp \
		Source_File_Dependency_Selector.cpp \
		$(SRC_INF_COL)\Source_File_Information_Collector.cpp \
		$(HDR_PROC)\Header_File_Processor.cpp \
		$(SRC_READER)\Project_Src_Code_Rdr.cpp \
		$(FILE_LISTER)\Project_Files_Lister.cpp \
		$(FILE_DAT_COL)\Project_Files_Data_Collector.cpp \
		$(SRC_DT_COL)\Source_File_Data_Collector.cpp \
		$(GIT_LIST)\Git_File_List_Receiver.cpp \
		$(SOURCE_DETR)\Source_File_Determiner.cpp \
		$(DIR_ENUM)\Directory_Enumerator.cpp \
		$(DES_READER)\Descriptor_File_Reader.cpp \
		$(DES_DATA_COL)\Descriptor_File_Data_Collector.cpp \
		$(DES_FILE_SYNT_COL)\Descriptor_File_Syntax_Controller.cpp \
		$(HEAD_DET)\Header_File_Determiner.cpp \
		$(DIR_OPS)\DirectoryOperations.cpp \
		$(STRING_OPS)\StringOperator.cpp \
		$(CHAR_OPS)\CharOperator.cpp \
		$(CPP_OPS)\Cpp_FileOperations.cpp \
		$(INT_TO_CHAR)\IntToCharTranslater.cpp \
		-include Source_File_Dependency_Selector.hpp \
		-include $(SRC_INF_COL)\Source_File_Information_Collector.hpp \
		-include $(HDR_PROC)\Header_File_Processor.hpp \
		-include $(SRC_READER)\Project_Src_Code_Rdr.hpp \
		-include $(FILE_LISTER)\Project_Files_Lister.h \
		-include $(FILE_DAT_COL)\Project_Files_Data_Collector.hpp \
		-include $(SRC_DT_COL)\Source_File_Data_Collector.hpp \
		-include $(GIT_LIST)\Git_File_List_Receiver.hpp \
		-include $(DES_READER)\Descriptor_File_Reader.hpp \
		-include $(DES_DATA_COL)\Descriptor_File_Data_Collector.hpp \
		-include $(DES_FILE_SYNT_COL)\Descriptor_File_Syntax_Controller.hpp \
		-include $(SOURCE_DETR)\Source_File_Determiner.h \
		-include $(DIR_ENUM)\Directory_Enumerator.h \
		-include $(HEAD_DET)\Header_File_Determiner.h \
		-include $(STRING_OPS)\StringOperator.h \
		-include $(DIR_OPS)\DirectoryOperations.h \
	    -include $(CHAR_OPS)\CharOperator.h \
		-include $(CPP_OPS)\Cpp_FileOperations.h \
		-include $(INT_TO_CHAR)\IntToCharTranslater.h \
		-lpthread
