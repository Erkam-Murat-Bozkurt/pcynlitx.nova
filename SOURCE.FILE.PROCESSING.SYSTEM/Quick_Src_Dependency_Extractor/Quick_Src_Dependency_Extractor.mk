




STRING_OPS=D:\pcynlitx.build\BASIC.TOOLS\StringOperator
DIR_OPS=D:\pcynlitx.build\BASIC.TOOLS\DirectoryOperations
CPP_OPS=D:\pcynlitx.build\BASIC.TOOLS\Cpp_FileOperations
CHAR_OPS=D:\pcynlitx.build\BASIC.TOOLS\CharOperator
DIR_ENUM=D:\pcynlitx.build\PROJECT.BUILD.TOOLS\Directory_Enumerator
SYS_INT=D:\pcynlitx.build\BASIC.TOOLS\Custom_System_Interface


HEAD_DET=D:\pcynlitx.build\SOURCE.FILE.DATA.COLLECTORS\Header_File_Determiner
FILE_LISTER=D:\pcynlitx.build\SOURCE.FILE.DATA.COLLECTORS\Project_Files_Lister
SOURCE_DETR=D:\pcynlitx.build\SOURCE.FILE.DATA.COLLECTORS\Source_File_Determiner
INT_TO_CHAR=D:\pcynlitx.build\BASIC.TOOLS\IntToCharTranslater
DES_READER=D:\pcynlitx.build\DESCRIPTION.PROCESSING.SYSTEM\Description.Readers\Descriptor.File.Reader
DES_DATA_COL=D:\pcynlitx.build\DESCRIPTION.PROCESSING.SYSTEM\Description.Readers\Descriptor.File.Data.Collector
DES_FILE_SYNT_COL=D:\pcynlitx.build\DESCRIPTION.PROCESSING.SYSTEM\Description.Readers\Descriptor.File.Syntax.Controller
FILE_DAT_COL=D:\pcynlitx.build\SOURCE.FILE.DATA.COLLECTORS\Project_Files_Data_Collector
SRC_DT_COL=D:\pcynlitx.build\SOURCE.FILE.DATA.COLLECTORS\Source_File_Data_Collector
HDR_PROC=D:\pcynlitx.build\SOURCE.FILE.PROCESSING.SYSTEM\Header_File_Processor
SOURCE_DETR=D:\pcynlitx.build\SOURCE.FILE.DATA.COLLECTORS\Source_File_Determiner
HEAD_DETR=D:\pcynlitx.build\SOURCE.FILE.DATA.COLLECTORS\Header_File_Determiner
SRC_READER=D:\pcynlitx.build\PROJECT.BUILD.TOOLS\Project_Src_Code_Rdr
SRC_FILE_PROC=D:\pcynlitx.build\SOURCE.FILE.PROCESSING.SYSTEM\Source_File_Processor

GIT_PROC=D:\pcynlitx.build\GIT.DATA.PROCESSING.SYSTEM\Git_Data_Processor
GIT_LIST=D:\pcynlitx.build\GIT.DATA.PROCESSING.SYSTEM\Git_File_List_Writer
GIT_REC=D:\pcynlitx.build\GIT.DATA.PROCESSING.SYSTEM\Git_File_List_Receiver
GIT_IGN=D:\pcynlitx.build\GIT.DATA.PROCESSING.SYSTEM\Git_Ignoring_Files_Lister
GIT_MOD_LST=D:\pcynlitx.build\GIT.DATA.PROCESSING.SYSTEM\Git_Modification_Lister
GIT_MOD_RCV=D:\pcynlitx.build\GIT.DATA.PROCESSING.SYSTEM\Git_Modification_Receiver

SRC_INF_COL= D:\pcynlitx.build\SOURCE.FILE.PROCESSING.SYSTEM\Source_File_Information_Collector
DEP_DATA_EXT=D:\pcynlitx.build\SOURCE.FILE.PROCESSING.SYSTEM\Dependency_Data_Extractor
SRC_DATA_SETTER=D:\pcynlitx.build\SOURCE.FILE.PROCESSING.SYSTEM\Source_File_Data_Setter



VPATH = $(DIR_OPS) $(CPP_OPS) $(CHAR_OPS) \
	    $(SOURCE_DETR) $(DIR_ENUM) $(SYS_INT) \
	    $(STRING_OPS) $(HEAD_DET) $(FILE_LISTER) \
	    $(INT_TO_CHAR) $(DES_DATA_COL) $(DES_READER) \
	    $(FILE_DAT_COL) \
	    $(SRC_DT_COL) $(DES_FILE_SYNT_COL) \
		$(HDR_PROC) $(SRC_READER) $(SRC_FILE_PROC) \
		$(GIT_PROC) \
		$(GIT_LIST) \
		$(GIT_REC) \
		$(GIT_MOD_LST) \
		$(GIT_MOD_RCV) \
		$(GIT_IGN) \
		$(SRC_INF_COL) \
		$(DEP_DATA_EXT) \
		$(SRC_DATA_SETTER)

Quick_Src_Dependency_Extractor.exe: Quick_Src_Dependency_Extractor_Main_File.cpp \
	Quick_Src_Dependency_Extractor.cpp \
	Source_File_Information_Collector.cpp \
	Dependency_Data_Extractor.cpp \
	Source_File_Processor.cpp \
	Header_File_Processor.cpp \
	Project_Src_Code_Rdr.cpp \
	Source_File_Data_Setter.cpp \
	Project_Files_Lister.cpp \
	Project_Files_Data_Collector.cpp \
	Source_File_Data_Collector.cpp \
	Source_File_Determiner.cpp \
	Header_File_Determiner.cpp \
	Git_Data_Processor.cpp \
	Git_File_List_Writer.cpp \
	Git_File_List_Receiver.cpp \
	Git_Modification_Lister.cpp \
	Git_Modification_Receiver.cpp \
	Git_Ignoring_Files_Lister.cpp \
	Descriptor_File_Reader.cpp \
	Descriptor_File_Data_Collector.cpp \
	Descriptor_File_Syntax_Controller.cpp \
	Directory_Enumerator.cpp \
	DirectoryOperations.cpp \
	StringOperator.cpp \
	CharOperator.cpp \
	Cpp_FileOperations.cpp \
	Quick_Src_Dependency_Extractor.hpp \
	Source_File_Information_Collector.hpp \
	Source_File_Data_Setter.hpp \
	Dependency_Data_Extractor.hpp \
	Source_File_Processor.hpp \
	Header_File_Processor.hpp \
	Project_Src_Code_Rdr.hpp \
	Project_Files_Lister.h \
	Project_Files_Data_Collector.hpp \
	Source_File_Data_Collector.cpp \
	Git_Data_Processor.hpp \
	Git_File_List_Writer.hpp \
	Git_File_List_Receiver.hpp \
	Git_Modification_Lister.hpp \
	Git_Modification_Receiver.hpp \
	Git_Ignoring_Files_Lister.hpp \
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

	g++ -std=c++17 -static-libgcc -static-libstdc++ -ggdb \
	-o Quick_Src_Dependency_Extractor.exe \
	 -I$(DIR_OPS)      -I$(CPP_OPS) -I$(CHAR_OPS) \
	 -I$(STRING_OPS)   -I$(HEAD_DET) \
	 -I$(FILE_LISTER)  -I$(SOURCE_DETR) -I$(GIT_LIST) \
	 -I$(CLASS_SYNTAX) -I$(DIR_ENUM) -I$(INT_TO_CHAR) \
	 -I$(DES_DATA_COL) -I$(DES_READER) \
	 -I$(FILE_DAT_COL) -I$(HDR_PROC) \
	 -I$(SRC_DT_COL)   -I$(DES_FILE_SYNT_COL) \
	 -I$(SRC_READER)   -I$(SRC_FILE_PROC) -I$(SYS_INT) \
	 -I$(GIT_PROC) \
	 -I$(GIT_LIST) \
	 -I$(GIT_REC) \
	 -I$(GIT_MOD_LST) \
	 -I$(GIT_MOD_RCV) \
	 -I$(GIT_IGN) \
	 -I$(SYS_INT) \
	 -I$(SRC_INF_COL) \
	 -I$(DEP_DATA_EXT) \
	 -I$(SRC_DATA_SETTER) \
	 -L$(DIR_ENUM)     -L$(DIR_OPS)     -L$(CPP_OPS) \
	 -L$(CHAR_OPS)     -L$(INT_TO_CHAR) -L$(DES_DATA_COL) \
	 -L$(DES_READER)   -L$(STRING_OPS) \
	 -L$(HEAD_DET)     -L$(FILE_LISTER) \
	 -L$(SOURCE_DETR)  -L$(HDR_PROC) \
	 -L$(GIT_LIST)     -L$(FILE_DAT_COL) \
	 -L$(SRC_DT_COL)   -L$(DES_FILE_SYNT_COL) \
	 -L$(SRC_READER)   -L$(SRC_FILE_PROC) -L$(SYS_INT) \
	 -L$(GIT_PROC) \
	 -L$(GIT_LIST) \
	 -L$(GIT_REC) \
	 -L$(GIT_MOD_LST) \
	 -L$(GIT_MOD_RCV) \
	 -L$(GIT_IGN) \
	 -L$(SYS_INT) \
	 -L$(SRC_INF_COL) \
	 -L$(DEP_DATA_EXT) \
	 -L$(SRC_DATA_SETTER)\
		Quick_Src_Dependency_Extractor_Main_File.cpp \
		Quick_Src_Dependency_Extractor.cpp \
		$(SRC_INF_COL)\Source_File_Information_Collector.cpp \
		$(DEP_DATA_EXT)\Dependency_Data_Extractor.cpp \
		$(SRC_DATA_SETTER)\Source_File_Data_Setter.cpp \
		$(SRC_FILE_PROC)\Source_File_Processor.cpp \
		$(HDR_PROC)\Header_File_Processor.cpp \
		$(SRC_READER)\Project_Src_Code_Rdr.cpp \
		$(FILE_LISTER)\Project_Files_Lister.cpp \
		$(FILE_DAT_COL)\Project_Files_Data_Collector.cpp \
		$(SRC_DT_COL)\Source_File_Data_Collector.cpp \
	    $(GIT_PROC)\Git_Data_Processor.cpp \
		$(GIT_LIST)\Git_File_List_Writer.cpp \
		$(GIT_REC)\Git_File_List_Receiver.cpp \
		$(GIT_MOD_LST)\Git_Modification_Lister.cpp \
		$(GIT_MOD_RCV)\Git_Modification_Receiver.cpp \
		$(GIT_IGN)\Git_Ignoring_Files_Lister.cpp \
		$(SOURCE_DETR)\Source_File_Determiner.cpp \
	    $(HEAD_DET)\Header_File_Determiner.cpp \
		$(DIR_ENUM)\Directory_Enumerator.cpp \
		$(DES_READER)\Descriptor_File_Reader.cpp \
		$(DES_DATA_COL)\Descriptor_File_Data_Collector.cpp \
		$(DES_FILE_SYNT_COL)\Descriptor_File_Syntax_Controller.cpp \
		$(DIR_OPS)\DirectoryOperations.cpp \
		$(STRING_OPS)\StringOperator.cpp \
		$(CHAR_OPS)\CharOperator.cpp \
		$(CPP_OPS)\Cpp_FileOperations.cpp \
		$(INT_TO_CHAR)\IntToCharTranslater.cpp \
    	$(SYS_INT)\Custom_System_Interface.cpp \
		-include Quick_Src_Dependency_Extractor.hpp \
		-include $(SRC_INF_COL)\Source_File_Information_Collector.hpp \
		-include $(DEP_DATA_EXT)\Dependency_Data_Extractor.hpp \
		-include $(SRC_DATA_SETTER)\Source_File_Data_Setter.hpp \
		-include $(SRC_FILE_PROC)\Source_File_Processor.hpp \
		-include $(HDR_PROC)\Header_File_Processor.hpp \
		-include $(SRC_READER)\Project_Src_Code_Rdr.hpp \
		-include $(FILE_LISTER)\Project_Files_Lister.h \
		-include $(FILE_DAT_COL)\Project_Files_Data_Collector.hpp \
		-include $(SRC_DT_COL)\Source_File_Data_Collector.hpp \
        -include $(GIT_PROC)\Git_Data_Processor.hpp \
		-include $(GIT_LIST)\Git_File_List_Writer.hpp \
		-include $(GIT_REC)\Git_File_List_Receiver.hpp \
		-include $(GIT_MOD_LST)\Git_Modification_Lister.hpp \
		-include $(GIT_MOD_RCV)\Git_Modification_Receiver.hpp \
		-include $(GIT_IGN)\Git_Ignoring_Files_Lister.hpp \
		-include $(DES_READER)\Descriptor_File_Reader.hpp \
		-include $(DES_DATA_COL)\Descriptor_File_Data_Collector.hpp \
		-include $(DES_FILE_SYNT_COL)\Descriptor_File_Syntax_Controller.hpp \
		-include $(SOURCE_DETR)\Source_File_Determiner.h \
		-include $(HEAD_DET)\Header_File_Determiner.h \
		-include $(DIR_ENUM)\Directory_Enumerator.h \
		-include $(STRING_OPS)\StringOperator.h \
		-include $(DIR_OPS)\DirectoryOperations.h \
	    -include $(CHAR_OPS)\CharOperator.h \
		-include $(CPP_OPS)\Cpp_FileOperations.h \
		-include $(INT_TO_CHAR)\IntToCharTranslater.h \
	    -include $(SYS_INT)\Custom_System_Interface.h \
		-lpthread
