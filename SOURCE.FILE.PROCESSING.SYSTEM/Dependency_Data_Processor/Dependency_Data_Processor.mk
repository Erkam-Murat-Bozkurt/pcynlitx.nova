



BOOST_LIB_DIR=D:\BOOST.LIB\libs
BOOST_BASE_DIR=D:\BOOST.LIB
BOOST_INC_1=D:\BOOST.LIB\boost
BOOST_INC_2=D:\BOOST.LIB\boost\sort
BOOST_INC_3=D:\BOOST.LIB\boost\sort\parallel_stable_sort


STRING_OPS=D:\pcynlitx.build\BASIC.TOOLS\StringOperator
DIR_OPS=D:\pcynlitx.build\BASIC.TOOLS\DirectoryOperations
CPP_OPS=D:\pcynlitx.build\BASIC.TOOLS\Cpp_FileOperations
CHAR_OPS=D:\pcynlitx.build\BASIC.TOOLS\CharOperator
DIR_ENUM=D:\pcynlitx.build\PROJECT.BUILD.TOOLS\Directory_Enumerator
HEAD_DET=D:\pcynlitx.build\SOURCE.FILE.DATA.COLLECTORS\Header_File_Determiner
SOURCE_DETR=D:\pcynlitx.build\SOURCE.FILE.DATA.COLLECTORS\Source_File_Determiner
INT_TO_CHAR=D:\pcynlitx.build\BASIC.TOOLS\IntToCharTranslater
DES_READER=D:\pcynlitx.build\DESCRIPTION.PROCESSING.SYSTEM\Description.Readers\Descriptor.File.Reader
DES_DATA_COL=D:\pcynlitx.build\DESCRIPTION.PROCESSING.SYSTEM\Description.Readers\Descriptor.File.Data.Collector
DES_FILE_SYNT_COL=D:\pcynlitx.build\DESCRIPTION.PROCESSING.SYSTEM\Description.Readers\Descriptor.File.Syntax.Controller
SRC_DT_COL=D:\pcynlitx.build\SOURCE.FILE.DATA.COLLECTORS\Source_File_Data_Collector
SRC_INF_COL=D:\pcynlitx.build\SOURCE.FILE.PROCESSING.SYSTEM\Source_File_Information_Collector
HDR_PROC=D:\pcynlitx.build\SOURCE.FILE.PROCESSING.SYSTEM\Header_File_Processor
SRC_PROCESSOR=D:\pcynlitx.build\SOURCE.FILE.PROCESSING.SYSTEM\Source_File_Processor
SRC_READER=D:\pcynlitx.build\PROJECT.BUILD.TOOLS\Project_Src_Code_Rdr
SYS_INT=D:\pcynlitx.build\BASIC.TOOLS\Custom_System_Interface


GIT_PROC=D:\pcynlitx.build\GIT.DATA.PROCESSING.SYSTEM\Git_Data_Processor
GIT_LIST=D:\pcynlitx.build\GIT.DATA.PROCESSING.SYSTEM\Git_File_List_Writer
GIT_REC=D:\pcynlitx.build\GIT.DATA.PROCESSING.SYSTEM\Git_File_List_Receiver
GIT_IGN=D:\pcynlitx.build\GIT.DATA.PROCESSING.SYSTEM\Git_Ignoring_Files_Lister
GIT_MOD_LST=D:\pcynlitx.build\GIT.DATA.PROCESSING.SYSTEM\Git_Modification_Lister
GIT_MOD_RCV=D:\pcynlitx.build\GIT.DATA.PROCESSING.SYSTEM\Git_Modification_Receiver

DEP_DAT_EXTR=D:\pcynlitx.build\SOURCE.FILE.PROCESSING.SYSTEM\Dependency_Data_Extractor
DEP_DAT_STCK=D:\pcynlitx.build\SOURCE.FILE.PROCESSING.SYSTEM\Dependency_Data_Stack_Container
HDR_DEP_EXT=D:\pcynlitx.build\SOURCE.FILE.PROCESSING.SYSTEM\Header_Dependency_Data_Extractor


VPATH = $(DIR_OPS)       $(CPP_OPS) $(CHAR_OPS) \
		$(SOURCE_DETR)   $(DIR_ENUM) \
	    $(STRING_OPS)    $(HEAD_DET) \
		$(INT_TO_CHAR)   $(DES_DATA_COL) $(DES_READER) \
		$(MAKE_DATA_COL) $(GIT_LIST) \
		$(SRC_DT_COL)    $(DES_FILE_SYNT_COL) $(SRC_INF_COL) \
		$(HDR_PROC)      $(SRC_READER) $(SRC_PROCESSOR) \
		$(GIT_PROC) \
		$(GIT_LIST) \
		$(GIT_REC) \
		$(GIT_MOD_LST) \
		$(GIT_MOD_RCV) \
		$(GIT_IGN) \
		$(SYS_INT) \
		$(DEP_DAT_EXTR) \
		$(DEP_DAT_STCK) \
		$(HDR_DEP_EXT) \
		$(BOOST_LIB_DIR) \
		$(BOOST_BASE_DIR) \
		$(BOOST_INC_1) \
		$(BOOST_INC_2) \
		$(BOOST_INC_3) \

Dependency_Data_Processor.exe: Dependency_Data_Processor_Main_File.cpp \
	Dependency_Data_Processor.cpp \
	Header_Dependency_Data_Extractor.cpp \
	Dependency_Data_Extractor.cpp \
	Dependency_Data_Stack_Container.cpp \
	Source_File_Information_Collector.cpp \
	Source_File_Processor.cpp \
	Header_File_Processor.cpp \
	Project_Src_Code_Rdr.cpp \
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
	Dependency_Data_Processor.hpp \
	Header_Dependency_Data_Extractor.hpp \
	Dependency_Data_Extractor.hpp \
	Dependency_Data_Stack_Container.hpp \
	Source_File_Information_Collector.hpp \
	Source_File_Processor.hpp \
	Header_File_Processor.hpp \
	Project_Src_Code_Rdr.hpp \
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

	g++ -fopenmp -std=c++17  -ggdb -o Dependency_Data_Processor.exe \
	 -I$(DIR_OPS)       -I$(CPP_OPS)     -I$(CHAR_OPS) \
	 -I$(SRC_INF_COL)   -I$(STRING_OPS)  -I$(HEAD_DET) \
	 -I$(SOURCE_DETR)   -I$(GIT_LIST) \
	 -I$(CLASS_SYNTAX)  -I$(DIR_ENUM)    -I$(INT_TO_CHAR) \
	 -I$(DES_DATA_COL)  -I$(DES_READER) \
	 -I$(MAKE_DATA_COL) \
	 -I$(SRC_DT_COL)    -I$(DES_FILE_SYNT_COL) \
	 -I$(HDR_PROC)      -I$(SRC_READER)  -I$(SRC_PROCESSOR) \
	 -I$(GIT_PROC) \
	 -I$(GIT_LIST) \
	 -I$(GIT_REC) \
	 -I$(GIT_MOD_LST) \
	 -I$(GIT_MOD_RCV) \
	 -I$(GIT_IGN) \
	 -I$(SYS_INT) \
	 -I$(DEP_DAT_EXTR) \
	 -I$(DEP_DAT_STCK) \
	 -I$(HDR_DEP_EXT) \
	 -I$(BOOST_BASE_DIR) \
	 -I$(BOOST_INC_1) \
	 -I$(BOOST_INC_2) \
	 -I$(BOOST_INC_3) \
	 -L$(SRC_INF_COL)   -L$(DIR_ENUM) \
	 -L$(DIR_OPS)       -L$(CPP_OPS) \
	 -L$(CHAR_OPS)      -L$(INT_TO_CHAR) \
	 -L$(DES_DATA_COL)  -L$(DES_READER)\
	 -L$(DES_READER)    -L$(STRING_OPS) \
	 -L$(HEAD_DET) \
	 -L$(SOURCE_DETR)   -L$(MAKE_DATA_COL) \
	 -L$(GIT_LIST) \
	 -L$(SRC_DT_COL)    -L$(DES_FILE_SYNT_COL) \
	 -L$(HDR_PROC)      -L$(SRC_READER)  -L$(SRC_PROCESSOR) \
	 -L$(GIT_PROC) \
	 -L$(GIT_LIST) \
	 -L$(GIT_REC) \
	 -L$(GIT_MOD_LST) \
	 -L$(GIT_MOD_RCV) \
	 -L$(GIT_IGN) \
	 -L$(SYS_INT) \
	 -L$(DEP_DAT_EXTR) \
	 -L$(DEP_DAT_STCK) \
     -L$(HDR_DEP_EXT) \
	 -L$(BOOST_LIB_DIR) \
	 -L$(BOOST_BASE_DIR) \
		Dependency_Data_Processor_Main_File.cpp \
		Dependency_Data_Processor.cpp \
		$(HDR_DEP_EXT)\Header_Dependency_Data_Extractor.cpp \
		$(DEP_DAT_EXTR)\Dependency_Data_Extractor.cpp \
		$(DEP_DAT_STCK)\Dependency_Data_Stack_Container.cpp \
		$(SRC_INF_COL)\Source_File_Information_Collector.cpp \
		$(SRC_PROCESSOR)\Source_File_Processor.cpp \
		$(HDR_PROC)\Header_File_Processor.cpp \
		$(SRC_READER)\Project_Src_Code_Rdr.cpp \
		$(SRC_DT_COL)\Source_File_Data_Collector.cpp \
 	    $(GIT_PROC)\Git_Data_Processor.cpp \
		$(GIT_LIST)\Git_File_List_Writer.cpp \
		$(GIT_REC)\Git_File_List_Receiver.cpp \
		$(GIT_MOD_LST)\Git_Modification_Lister.cpp \
		$(GIT_MOD_RCV)\Git_Modification_Receiver.cpp \
		$(GIT_IGN)\Git_Ignoring_Files_Lister.cpp \
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
		$(SYS_INT)\Custom_System_Interface.cpp \
		-include Dependency_Data_Processor.hpp \
		-include $(HDR_DEP_EXT)\Header_Dependency_Data_Extractor.hpp \
		-include $(DEP_DAT_EXTR)\Dependency_Data_Extractor.hpp \
		-include $(DEP_DAT_STCK)\Dependency_Data_Stack_Container.hpp \
		-include $(SRC_INF_COL)\Source_File_Information_Collector.hpp \
		-include $(SRC_PROCESSOR)\Source_File_Processor.hpp \
		-include $(HDR_PROC)\Header_File_Processor.hpp \
		-include $(SRC_READER)\Project_Src_Code_Rdr.hpp \
		-include $(GIT_PROC)\Git_Data_Processor.hpp \
		-include $(GIT_LIST)\Git_File_List_Writer.hpp \
		-include $(GIT_REC)\Git_File_List_Receiver.hpp \
		-include $(GIT_MOD_LST)\Git_Modification_Lister.hpp \
		-include $(GIT_MOD_RCV)\Git_Modification_Receiver.hpp \
		-include $(GIT_IGN)\Git_Ignoring_Files_Lister.hpp \
		-include $(SRC_DT_COL)\Source_File_Data_Collector.hpp \
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
		-include $(SYS_INT)\Custom_System_Interface.h \
		-include $(BOOST_INC_3)\parallel_stable_sort.hpp \
		-lpthread
