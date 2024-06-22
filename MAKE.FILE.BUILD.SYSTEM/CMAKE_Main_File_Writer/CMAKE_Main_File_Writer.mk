




STRING_OPS=D:\pcynlitx.build\BASIC.TOOLS\StringOperator
DIR_OPS=D:\pcynlitx.build\BASIC.TOOLS\DirectoryOperations
CPP_OPS=D:\pcynlitx.build\BASIC.TOOLS\Cpp_FileOperations
CHAR_OPS=D:\pcynlitx.build\BASIC.TOOLS\CharOperator
INT_TO_CHAR=D:\pcynlitx.build\BASIC.TOOLS\IntToCharTranslater
SYS_INT=D:\pcynlitx.build\BASIC.TOOLS\Custom_System_Interface


HEAD_DET=D:\pcynlitx.build\SOURCE.FILE.DATA.COLLECTORS\Header_File_Determiner
SOURCE_DETR=D:\pcynlitx.build\SOURCE.FILE.DATA.COLLECTORS\Source_File_Determiner
SRC_DT_COL=D:\pcynlitx.build\SOURCE.FILE.DATA.COLLECTORS\Source_File_Data_Collector


DES_READER=D:\pcynlitx.build\DESCRIPTION.PROCESSING.SYSTEM\Description.Readers\Descriptor.File.Reader
DES_DATA_COL=D:\pcynlitx.build\DESCRIPTION.PROCESSING.SYSTEM\Description.Readers\Descriptor.File.Data.Collector
DES_SYN_CON=D:\pcynlitx.build\DESCRIPTION.PROCESSING.SYSTEM\Description.Readers\Descriptor.File.Syntax.Controller






GIT_PROC=D:\pcynlitx.build\GIT.DATA.PROCESSING.SYSTEM\Git_Data_Processor
GIT_LIST=D:\pcynlitx.build\GIT.DATA.PROCESSING.SYSTEM\Git_File_List_Writer
GIT_REC=D:\pcynlitx.build\GIT.DATA.PROCESSING.SYSTEM\Git_File_List_Receiver
GIT_IGN=D:\pcynlitx.build\GIT.DATA.PROCESSING.SYSTEM\Git_Ignoring_Files_Lister
GIT_MOD_LST=D:\pcynlitx.build\GIT.DATA.PROCESSING.SYSTEM\Git_Modification_Lister
GIT_MOD_RCV=D:\pcynlitx.build\GIT.DATA.PROCESSING.SYSTEM\Git_Modification_Receiver

SRC_INF_CL=D:\pcynlitx.build\SOURCE.FILE.PROCESSING.SYSTEM\Source_File_Information_Collector
SRC_DEP_SL=D:\pcynlitx.build\SOURCE.FILE.PROCESSING.SYSTEM\Source_File_Dependency_Selector
SRC_DEP_DT=D:\pcynlitx.build\SOURCE.FILE.PROCESSING.SYSTEM\Source_File_Dependency_Determiner
HDR_PROC=D:\pcynlitx.build\SOURCE.FILE.PROCESSING.SYSTEM\Header_File_Processor
SRC_READER=D:\pcynlitx.build\PROJECT.BUILD.TOOLS\Project_Src_Code_Rdr
SRC_COM_DT_EXT=D:\pcynlitx.build\SOURCE.FILE.PROCESSING.SYSTEM\Source_File_Compiler_Data_Extractor
DEP_DAT_EXT=D:\pcynlitx.build\SOURCE.FILE.PROCESSING.SYSTEM\Dependency_Data_Extractor
SRC_PROCESSOR=D:\pcynlitx.build\SOURCE.FILE.PROCESSING.SYSTEM\Source_File_Processor
SRC_DATA_SETTER=D:\pcynlitx.build\SOURCE.FILE.PROCESSING.SYSTEM\Source_File_Data_Setter
QUICK_SRC_EXT=D:\pcynlitx.build\SOURCE.FILE.PROCESSING.SYSTEM\Quick_Src_Dependency_Extractor
DEP_DAT_PROC=D:\pcynlitx.build\SOURCE.FILE.PROCESSING.SYSTEM\Dependency_Data_Processor
DEP_DAT_STCK=D:\pcynlitx.build\SOURCE.FILE.PROCESSING.SYSTEM\Dependency_Data_Stack_Container
HDR_DEP_EXT=D:\pcynlitx.build\SOURCE.FILE.PROCESSING.SYSTEM\Header_Dependency_Data_Extractor
SRC_INF_CL_SF=D:\pcynlitx.build\SOURCE.FILE.PROCESSING.SYSTEM\Source_File_Information_Collector_For_Single_File
SRC_DEP_SL_SF=D:\pcynlitx.build\SOURCE.FILE.PROCESSING.SYSTEM\Source_File_Dependency_Selector_For_Single_File



MAKE_DATA_COL=D:\pcynlitx.build\MAKE.FILE.BUILD.SYSTEM\MakeFile_Data_Collector
MAKE_FILE_PATH=D:\pcynlitx.build\MAKE.FILE.BUILD.SYSTEM\MakeFile_Path_Determiner




VPATH = $(DIR_OPS)        $(CPP_OPS)      $(CHAR_OPS) \
		$(DES_SYN_CON)    $(SOURCE_DETR)  \
		$(STRING_OPS)     $(HEAD_DET)     $(DES_READER) \
	    $(INT_TO_CHAR)    $(DES_DATA_COL) \
	    $(MAKE_DATA_COL)  $(SRC_DT_COL) \
		$(SRC_INF_CL)     $(SRC_DEP_SL)   $(SRC_DEP_DT) \
	    $(HDR_PROC)       $(SRC_READER)   $(SRC_READER) \
		$(SRC_COM_DT_EXT) $(DEP_DAT_EXT) \
		$(SRC_PROCESSOR)  $(SRC_DATA_SETTER) \
		$(QUICK_SRC_EXT)  $(DEP_DAT_PROC) \
		$(DEP_DAT_STCK)   $(HDR_DEP_EXT) \
		$(GIT_PROC) \
		$(GIT_LIST) \
		$(GIT_REC) \
		$(GIT_MOD_LST) \
		$(GIT_MOD_RCV) \
		$(GIT_IGN) \
		$(SRC_INF_CL_SF) \
		$(SRC_DEP_SL_SF) \
		$(SYS_INT) \
		$(MAKE_FILE_PATH)


CMAKE_Main_File_Writer.exe: CMAKE_Main_File_Writer_Main_File.cpp \
	CMAKE_Main_File_Writer.cpp \
    MakeFile_Path_Determiner.cpp \
    Source_File_Information_Collector.cpp \
	Source_File_Dependency_Determiner.cpp \
	Source_File_Dependency_Selector.cpp \
	Source_File_Dependency_Selector_For_Single_File.cpp \
	Source_File_Information_Collector_For_Single_File.cpp \
	Header_File_Processor.cpp \
	Project_Src_Code_Rdr.cpp \
	Source_File_Compiler_Data_Extractor.cpp \
	Dependency_Data_Extractor.cpp \
	Source_File_Processor.cpp \
	Git_Data_Processor.cpp \
	Git_File_List_Receiver.cpp \
	Git_File_List_Writer.cpp \
	Git_Ignoring_Files_Lister.cpp \
	Git_Modification_Lister.cpp \
	Git_Modification_Lister.cpp \
	MakeFile_Data_Collector.cpp \
	Source_File_Determiner.cpp \
	Header_File_Determiner.cpp \
	Descriptor_File_Reader.cpp \
	Descriptor_File_Data_Collector.cpp \
	DirectoryOperations.cpp \
	Custom_System_Interface.cpp \
	CharOperator.cpp \
	Cpp_FileOperations.cpp \
	CMAKE_Main_File_Writer.hpp \
	MakeFile_Path_Determiner.hpp \
	MakeFile_Data_Collector.hpp \
	Source_File_Dependency_Determiner.hpp \
	Source_File_Information_Collector.hpp \
	Source_File_Dependency_Selector.hpp \
	Source_File_Dependency_Selector_For_Single_File.cpp \
	Source_File_Information_Collector_For_Single_File.cpp \
	Header_File_Processor.hpp \
	Project_Src_Code_Rdr.hpp \
	Source_File_Compiler_Data_Extractor.hpp \
	Dependency_Data_Extractor.hpp \
	Source_File_Processor.hpp \
	Git_Data_Processor.hpp \
	Git_File_List_Receiver.hpp \
	Git_File_List_Writer.hpp \
	Git_Ignoring_Files_Lister.hpp \
	Git_Modification_Lister.hpp \
	Git_Modification_Lister.hpp \
	Descriptor_File_Reader.hpp \
	Descriptor_File_Data_Collector.hpp \
	Source_File_Determiner.h \
	Header_File_Determiner.h \
	Custom_System_Interface.h \
	DirectoryOperations.h \
	CharOperator.h \
	Cpp_FileOperations.h

	g++ -std=c++17 -g -o CMAKE_Main_File_Writer.exe \
	 -I$(DIR_OPS)        -I$(CPP_OPS)     -I$(CHAR_OPS) \
	 -I$(STRING_OPS)     -I$(HEAD_DET)    -I$(INT_TO_CHAR)\
	 -I$(SOURCE_DETR) \
	 -I$(DES_DATA_COL)   -I$(DES_READER)  -I$(MAKE_DATA_COL) \
	 -I$(SRC_DT_COL)     -I$(DES_SYN_CON) \
	 -I$(SRC_INF_CL)     -I$(SRC_DEP_SL)   -I$(SRC_DEP_DT) \
	 -I$(HDR_PROC)       -I$(SRC_READER)   -I$(SRC_READER) \
	 -I$(SRC_COM_DT_EXT) -I$(DEP_DAT_EXT) \
	 -I$(SRC_PROCESSOR) \
	 -I$(GIT_PROC) \
     -I$(GIT_LIST) \
	 -I$(GIT_REC) \
	 -I$(GIT_MOD_LST) \
	 -I$(GIT_MOD_RCV) \
	 -I$(GIT_IGN) \
	 -I$(SRC_INF_CL_SF) \
	 -I$(SRC_DEP_SL_SF) \
	 -I$(SRC_DATA_SETTER) \
	 -I$(QUICK_SRC_EXT) \
	 -I$(DEP_DAT_PROC) \
	 -I$(DEP_DAT_STCK) \
	 -I$(HDR_DEP_EXT) \
	 -I$(SRC_DEP_SL_SF) \
	 -I$(SYS_INT) \
	 -I$(MAKE_FILE_PATH) \
	 -L$(DIR_OPS)        -L$(CPP_OPS)       -L$(CHAR_OPS)\
	 -L$(INT_TO_CHAR)    -L$(DES_DATA_COL)  -L$(DES_READER)\
	 -L$(STRING_OPS)     -L$(HEAD_DET) \
	 -L$(SOURCE_DETR)    -L$(MAKE_DATA_COL) \
	 -L$(SRC_DT_COL)     -L$(DES_SYN_CON) \
	 \
	 -L$(SRC_INF_CL)     -L$(SRC_DEP_SL)   -L$(SRC_DEP_DT) \
	 -L$(HDR_PROC)       -L$(SRC_READER)   -L$(SRC_READER) \
	 -L$(SRC_COM_DT_EXT) -L$(DEP_DAT_EXT) \
	 -L$(SRC_PROCESSOR) \
	 -L$(GIT_PROC) \
	 -L$(GIT_LIST) \
	 -L$(GIT_REC) \
	 -L$(GIT_MOD_LST) \
	 -L$(GIT_MOD_RCV) \
	 -L$(GIT_IGN) \
	 -L$(SYS_INT) \
	 -L$(SRC_DEP_SL_SF) \
	 -L$(SRC_DATA_SETTER) \
	 -L$(QUICK_SRC_EXT) \
	 -L$(DEP_DAT_PROC) \
	 -L$(DEP_DAT_STCK) \
	 -L$(HDR_DEP_EXT) \
	 -L$(SRC_INF_CL_SF) \
	 -L$(SRC_DEP_SL_SF) \
	 -L$(MAKE_FILE_PATH) \
		CMAKE_Main_File_Writer_Main_File.cpp \
		CMAKE_Main_File_Writer.cpp \
		$(MAKE_FILE_PATH)\MakeFile_Path_Determiner.cpp \
	    $(MAKE_DATA_COL)\MakeFile_Data_Collector.cpp \
		$(SRC_DEP_DT)\Source_File_Dependency_Determiner.cpp \
		$(SRC_DEP_SL_SF)\Source_File_Dependency_Selector_For_Single_File.cpp \
		$(SRC_DEP_SL)\Source_File_Dependency_Selector.cpp \
		$(DEP_DAT_PROC)\Dependency_Data_Processor.cpp \
		$(HDR_DEP_EXT)\Header_Dependency_Data_Extractor.cpp \
		$(DEP_DAT_STCK)\Dependency_Data_Stack_Container.cpp \
		$(SRC_COM_DT_EXT)\Source_File_Compiler_Data_Extractor.cpp \
		$(DEP_DAT_EXT)\Dependency_Data_Extractor.cpp \
		$(SRC_INF_CL_SF)\Source_File_Information_Collector_For_Single_File.cpp \
		$(SRC_INF_CL)\Source_File_Information_Collector.cpp \
		$(QUICK_SRC_EXT)\Quick_Src_Dependency_Extractor.cpp \
		$(SRC_DATA_SETTER)\Source_File_Data_Setter.cpp \
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
		$(DES_READER)\Descriptor_File_Reader.cpp \
		$(DES_DATA_COL)\Descriptor_File_Data_Collector.cpp \
		$(DES_SYN_CON)\Descriptor_File_Syntax_Controller.cpp \
		$(HEAD_DET)\Header_File_Determiner.cpp \
		$(DIR_OPS)\DirectoryOperations.cpp \
		$(STRING_OPS)\StringOperator.cpp \
		$(CHAR_OPS)\CharOperator.cpp \
		$(SYS_INT)\Custom_System_Interface.cpp \
		$(CPP_OPS)\Cpp_FileOperations.cpp \
		$(INT_TO_CHAR)\IntToCharTranslater.cpp \
		-include CMAKE_Main_File_Writer.hpp \
		-include $(MAKE_FILE_PATH)\MakeFile_Path_Determiner.hpp \
	    -include $(MAKE_DATA_COL)\MakeFile_Data_Collector.hpp \
		-include $(SRC_DEP_DT)\Source_File_Dependency_Determiner.hpp \
        -include $(SRC_COM_DT_EXT)\Source_File_Compiler_Data_Extractor.hpp \
		-include $(SRC_DEP_SL_SF)\Source_File_Dependency_Selector_For_Single_File.hpp \
		-include $(SRC_DEP_SL)\Source_File_Dependency_Selector.hpp \
		-include $(DEP_DAT_PROC)\Dependency_Data_Processor.hpp \
		-include $(HDR_DEP_EXT)\Header_Dependency_Data_Extractor.hpp \
		-include $(DEP_DAT_STCK)\Dependency_Data_Stack_Container.hpp \
		-include $(SRC_INF_CL_SF)\Source_File_Information_Collector_For_Single_File.hpp \
		-include $(SRC_INF_CL)\Source_File_Information_Collector.hpp \
		-include $(QUICK_SRC_EXT)\Quick_Src_Dependency_Extractor.hpp \
		-include $(DEP_DAT_EXT)\Dependency_Data_Extractor.hpp \
		-include $(SRC_DATA_SETTER)\Source_File_Data_Setter.hpp \
		-include $(SRC_PROCESSOR)\Source_File_Processor.hpp \
		-include $(HDR_PROC)\Header_File_Processor.hpp \
		-include $(SRC_READER)\Project_Src_Code_Rdr.hpp \
		-include $(SRC_DT_COL)\Source_File_Data_Collector.hpp \
        -include $(GIT_PROC)\Git_Data_Processor.hpp \
		-include $(GIT_LIST)\Git_File_List_Writer.hpp \
		-include $(GIT_REC)\Git_File_List_Receiver.hpp \
		-include $(GIT_MOD_LST)\Git_Modification_Lister.hpp \
		-include $(GIT_MOD_RCV)\Git_Modification_Receiver.hpp \
		-include $(GIT_IGN)\Git_Ignoring_Files_Lister.hpp \
		-include $(DES_READER)\Descriptor_File_Reader.hpp \
		-include $(DES_DATA_COL)\Descriptor_File_Data_Collector.hpp \
		-include $(DES_SYN_CON)\Descriptor_File_Syntax_Controller.hpp \
		-include $(SOURCE_DETR)\Source_File_Determiner.h \
		-include $(HEAD_DET)\Header_File_Determiner.h \
		-include $(STRING_OPS)\StringOperator.h \
		-include $(DIR_OPS)\DirectoryOperations.h \
	    -include $(CHAR_OPS)\CharOperator.h \
		-include $(CPP_OPS)\Cpp_FileOperations.h \
	    -include $(SYS_INT)\Custom_System_Interface.h \
		-include $(INT_TO_CHAR)\IntToCharTranslater.h
