


STRING_OPS=D:\pcynlitx.build\BASIC.TOOLS\StringOperator
DIR_OPS=D:\pcynlitx.build\BASIC.TOOLS\DirectoryOperations
CHAR_OPS=D:\pcynlitx.build\BASIC.TOOLS\CharOperator
FILE_OPRS=D:\pcynlitx.build\BASIC.TOOLS\Cpp_FileOperations
INT_TO_CHAR=D:\pcynlitx.build\BASIC.TOOLS\IntToCharTranslater
SYS_INT=D:\pcynlitx.build\BASIC.TOOLS\Custom_System_Interface



DES_READER=D:\pcynlitx.build\DESCRIPTION.PROCESSING.SYSTEM\Description.Readers\Descriptor.File.Reader
DES_DATA_COL=D:\pcynlitx.build\DESCRIPTION.PROCESSING.SYSTEM\Description.Readers\Descriptor.File.Data.Collector
DES_SYN_CON=D:\pcynlitx.build\DESCRIPTION.PROCESSING.SYSTEM\Description.Readers\Descriptor.File.Syntax.Controller
DIR_ENUM=D:\pcynlitx.build\PROJECT.BUILD.TOOLS\Directory_Enumerator
MAKE_DATA_COL=D:\pcynlitx.build\MAKE.FILE.BUILD.SYSTEM\MakeFile_Data_Collector
MAKE_BLD=D:\pcynlitx.build\MAKE.FILE.BUILD.SYSTEM\CMake_Target_Library_Builder
MK_FILE_CLNR=D:\pcynlitx.build\MAKE.FILE.BUILD.SYSTEM\Make_File_Cleaner
SRC_DT_COL=D:\pcynlitx.build\SOURCE.FILE.DATA.COLLECTORS\Source_File_Data_Collector
SOURCE_DETR=D:\pcynlitx.build\SOURCE.FILE.DATA.COLLECTORS\Source_File_Determiner
HEAD_DETER=D:\pcynlitx.build\SOURCE.FILE.DATA.COLLECTORS\Header_File_Determiner



SRC_INF_CL=D:\pcynlitx.build\SOURCE.FILE.PROCESSING.SYSTEM\Source_File_Information_Collector
SRC_DEP_SL=D:\pcynlitx.build\SOURCE.FILE.PROCESSING.SYSTEM\Source_File_Dependency_Selector
SRC_DEP_DT=D:\pcynlitx.build\SOURCE.FILE.PROCESSING.SYSTEM\Source_File_Dependency_Determiner
HDR_PROC=D:\pcynlitx.build\SOURCE.FILE.PROCESSING.SYSTEM\Header_File_Processor
SRC_READER=D:\pcynlitx.build\PROJECT.BUILD.TOOLS\Project_Src_Code_Rdr
SRC_COM_DT_EXT=D:\pcynlitx.build\SOURCE.FILE.PROCESSING.SYSTEM\Source_File_Compiler_Data_Extractor
SRC_DER_RORD=D:\pcynlitx.build\SOURCE.FILE.PROCESSING.SYSTEM\Source_File_Dependency_ReOrderer
DEP_DAT_EXT=D:\pcynlitx.build\SOURCE.FILE.PROCESSING.SYSTEM\Dependency_Data_Extractor
SRC_PROCESSOR=D:\pcynlitx.build\SOURCE.FILE.PROCESSING.SYSTEM\Source_File_Processor
SRC_INF_CL_SF=D:\pcynlitx.build\SOURCE.FILE.PROCESSING.SYSTEM\Source_File_Information_Collector_For_Single_File
SRC_DEP_SL_SF=D:\pcynlitx.build\SOURCE.FILE.PROCESSING.SYSTEM\Source_File_Dependency_Selector_For_Single_File
SRC_DATA_SETTER=D:\pcynlitx.build\SOURCE.FILE.PROCESSING.SYSTEM\Source_File_Data_Setter
QUICK_SRC_EXT=D:\pcynlitx.build\SOURCE.FILE.PROCESSING.SYSTEM\Quick_Src_Dependency_Extractor
DEP_DAT_PROC=D:\pcynlitx.build\SOURCE.FILE.PROCESSING.SYSTEM\Dependency_Data_Processor


MAKE_FILE_PATH=D:\pcynlitx.build\MAKE.FILE.BUILD.SYSTEM\MakeFile_Path_Determiner


GIT_PROC=D:\pcynlitx.build\GIT.DATA.PROCESSING.SYSTEM\Git_Data_Processor
GIT_REC=D:\pcynlitx.build\GIT.DATA.PROCESSING.SYSTEM\Git_File_List_Receiver
GIT_IGN=D:\pcynlitx.build\GIT.DATA.PROCESSING.SYSTEM\Git_Ignoring_Files_Lister
GIT_MOD_LST=D:\pcynlitx.build\GIT.DATA.PROCESSING.SYSTEM\Git_Modification_Lister
GIT_MOD_RCV=D:\pcynlitx.build\GIT.DATA.PROCESSING.SYSTEM\Git_Modification_Receiver
GIT_LIST=D:\pcynlitx.build\GIT.DATA.PROCESSING.SYSTEM\Git_File_List_Writer



DEP_DAT_STCK=D:\pcynlitx.build\SOURCE.FILE.PROCESSING.SYSTEM\Dependency_Data_Stack_Container
HDR_DEP_EXT=D:\pcynlitx.build\SOURCE.FILE.PROCESSING.SYSTEM\Header_Dependency_Data_Extractor


MAKE_FILE_DIR_CON=D:\pcynlitx.build\MAKE.FILE.BUILD.SYSTEM\MakeFile_Directory_Constructor

CMAKE_SYS_CON=D:\pcynlitx.build\MAKE.FILE.BUILD.SYSTEM\CMAKE_System_Constructor

CMAKE_MN_FL_WR=D:\pcynlitx.build\MAKE.FILE.BUILD.SYSTEM\CMAKE_Main_File_Writer



VPATH = $(INT_TO_CHAR)    $(FILE_OPRS)    $(DIR_OPS)   \
	    $(STRING_OPS)     $(CHAR_OPS)     $(MAKE_BLD)   \
	    $(MAKE_DATA_COL)  $(MK_FILE_CLNR) $(HEAD_DETER) \
	    $(SOURCE_DETR)    $(DES_READER)   $(DES_DATA_COL) \
	    $(DES_SYN_CON)    $(GIT_LIST)     $(SRC_DT_COL) \
		$(DIR_ENUM)       $(MAKE_FILE_PATH) \
		$(SRC_INF_CL)     $(SRC_DEP_SL)   $(SRC_DEP_DT) \
		$(HDR_PROC)       $(SRC_READER)   $(SRC_COM_DT_EXT) \
		$(SRC_DER_RORD)   $(DEP_DAT_EXT)  $(SRC_PROCESSOR) \
		$(GIT_PROC) \
		$(GIT_REC) \
		$(GIT_MOD_LST) \
		$(GIT_MOD_RCV) \
		$(GIT_IGN) \
		$(SRC_INF_CL_SF) \
		$(SRC_DEP_SL_SF) \
		$(SRC_DATA_SETTER) \
		$(QUICK_SRC_EXT) \
		$(DEP_DAT_PROC) \
		$(DEP_DAT_STCK) \
		$(HDR_DEP_EXT) \
		$(SYS_INT) \
		$(MAKE_FILE_DIR_CON) \
		$(CMAKE_SYS_CON) \
		$(CMAKE_MN_FL_WR)
	    

CMAKE_Build_System_Generator.exe: CMAKE_Build_System_Generator_Main_File.cpp \
	CMAKE_Build_System_Generator.cpp \
	CMAKE_Main_File_Writer.cpp \
	CMAKE_System_Constructor.cpp \
	CMAKE_Target_Library_Builder.cpp \
	MakeFile_Path_Determiner.cpp \
	MakeFile_Data_Collector.cpp \
	Source_File_Dependency_Determiner.cpp \
	Source_File_Compiler_Data_Extractor.cpp \
	Source_File_Dependency_Selector.cpp \
	Source_File_Information_Collector.cpp \
	Dependency_Data_Extractor.cpp \
	Source_File_Processor.cpp \
	Header_File_Processor.cpp \
	Project_Src_Code_Rdr.cpp \
	Make_File_Cleaner.cpp \
	Source_File_Determiner.cpp \
	Source_File_Data_Collector.cpp \
	Git_Data_Processor.cpp \
	Git_File_List_Receiver.cpp \
	Git_File_List_Writer.cpp \
	Git_Ignoring_Files_Lister.cpp \
	Git_Modification_Lister.cpp \
	Git_File_List_Receiver.cpp \
	Descriptor_File_Reader.cpp \
	Descriptor_File_Data_Collector.cpp \
	Descriptor_File_Syntax_Controller.cpp \
	Header_File_Determiner.cpp \
	Directory_Enumerator.cpp \
	DirectoryOperations.cpp \
	StringOperator.cpp \
	IntToCharTranslater.cpp \
	Cpp_FileOperations.cpp \
	CharOperator.cpp \
	CMAKE_Build_System_Generator.hpp \
	CMAKE_System_Constructor.hpp \
	CMAKE_System_Constructor.hpp \
	CMAKE_Target_Library_Builder.hpp \
	MakeFile_Path_Determiner.hpp \
	MakeFile_Data_Collector.hpp \
	Source_File_Dependency_Determiner.hpp \
	Source_File_Compiler_Data_Extractor.hpp \
	Source_File_Dependency_Selector.hpp \
	Source_File_Information_Collector.hpp \
	Dependency_Data_Extractor.hpp \
	Source_File_Processor.hpp \
	Header_File_Processor.hpp \
	Project_Src_Code_Rdr.hpp \
	Make_File_Cleaner.hpp \
	Source_File_Determiner.h \
	Source_File_Data_Collector.hpp \
	Descriptor_File_Reader.hpp \
	Descriptor_File_Data_Collector.hpp \
	Descriptor_File_Syntax_Controller.hpp \
	Git_Data_Processor.hpp \
	Git_File_List_Receiver.hpp \
	Git_File_List_Writer.hpp \
	Git_Ignoring_Files_Lister.hpp \
	Git_Modification_Lister.hpp \
	Header_File_Determiner.h \
	Directory_Enumerator.h \
	StringOperator.h \
	DirectoryOperations.h \
	IntToCharTranslater.h \
	CharOperator.h \
	Cpp_FileOperations.h

	g++ -std=c++17 -o CMAKE_Build_System_Generator.exe \
	-I$(DES_READER) \
	-I$(DES_DATA_COL) \
	-I$(DES_SYN_CON) \
	-I$(MAKE_BLD) \
	-I$(MAKE_DATA_COL) \
	-I$(MK_FILE_CLNR) \
	-I$(MAKE_FILE_PATH) \
	-I$(DIR_ENUM) \
	-I$(DIR_OPS) \
	-I$(STRING_OPS) \
	-I$(HEAD_DETER) \
	-I$(SOURCE_DETR) \
	-I$(INT_TO_CHAR) \
	-I$(CHAR_OPS) \
	-I$(GIT_LIST) \
	-I$(GIT_PROC) \
	-I$(GIT_REC) \
	-I$(GIT_MOD_LST) \
	-I$(GIT_MOD_RCV) \
	-I$(GIT_IGN) \
	-I$(SRC_DT_COL) \
    -I$(FILE_OPRS) \
	-I$(SRC_INF_CL) \
	-I$(SRC_DEP_SL) \
	-I$(SRC_DEP_DT) \
	-I$(SRC_INF_CL_SF) \
	-I$(SRC_DEP_SL_SF) \
	-I$(HDR_PROC) \
	-I$(SRC_READER) \
	-I$(SRC_COM_DT_EXT) \
	-I$(SRC_DER_RORD) \
	-I$(DEP_DAT_EXT) \
	-I$(SRC_PROCESSOR) \
	-I$(SRC_DATA_SETTER) \
	-I$(QUICK_SRC_EXT) \
	-I$(DEP_DAT_PROC) \
	-I$(DEP_DAT_STCK) \
	-I$(HDR_DEP_EXT) \
	-I$(SYS_INT) \
	-I$(MAKE_FILE_DIR_CON) \
	-I$(CMAKE_SYS_CON) \
	-I$(CMAKE_MN_FL_WR) \
	-L$(MAKE_BLD) \
	-L$(MAKE_DATA_COL) \
	-L$(MAKE_FILE_PATH) \
	-L$(MK_FILE_CLNR) \
	-L$(GIT_LIST) \
	-L$(GIT_PROC) \
	-L$(GIT_REC) \
	-L$(GIT_MOD_LST) \
	-L$(GIT_MOD_RCV) \
	-L$(GIT_IGN) \
	-L$(INT_TO_CHAR) \
	-L$(DES_READER) \
	-L$(DES_DATA_COL) \
	-L$(DES_SYN_CON) \
	-L$(DIR_ENUM) \
	-L$(DIR_OPS) \
	-L$(STRING_OPS) \
	-L$(CHAR_OPS) \
	-L$(FILE_OPRS) \
	-L$(HEAD_DETER) \
	-L$(SOURCE_DETR) \
	-L$(SRC_DT_COL) \
	-L$(SRC_INF_CL) \
	-L$(SRC_DEP_SL) \
	-L$(SRC_DEP_DT) \
	-L$(SRC_INF_CL_SF) \
	-L$(SRC_DEP_SL_SF) \
	-L$(HDR_PROC) \
	-L$(SRC_READER) \
	-L$(SRC_COM_DT_EXT) \
	-L$(SRC_DER_RORD) \
	-L$(DEP_DAT_EXT) \
	-L$(SRC_PROCESSOR) \
	-L$(SRC_DATA_SETTER) \
	-L$(QUICK_SRC_EXT) \
	-L$(DEP_DAT_PROC) \
	-L$(DEP_DAT_STCK) \
	-L$(HDR_DEP_EXT) \
	-L$(SYS_INT) \
	-L$(MAKE_FILE_DIR_CON) \
	-L$(CMAKE_SYS_CON) \
	-L$(CMAKE_MN_FL_WR) \
	CMAKE_Build_System_Generator_Main_File.cpp \
	CMAKE_Build_System_Generator.cpp \
	$(CMAKE_SYS_CON)\CMAKE_System_Constructor.cpp \
	$(CMAKE_MN_FL_WR)\CMAKE_Main_File_Writer.cpp \
	$(MAKE_BLD)\CMAKE_Target_Library_Builder.cpp \
	$(MAKE_DATA_COL)\MakeFile_Data_Collector.cpp  \
	$(MAKE_FILE_PATH)\MakeFile_Path_Determiner.cpp \
	$(MAKE_FILE_DIR_CON)\MakeFile_Directory_Constructor.cpp \
	$(SRC_DEP_DT)\Source_File_Dependency_Determiner.cpp \
	$(SRC_COM_DT_EXT)\Source_File_Compiler_Data_Extractor.cpp \
	$(SRC_DEP_SL)\Source_File_Dependency_Selector.cpp \
	$(SRC_INF_CL)\Source_File_Information_Collector.cpp \
	$(SRC_DATA_SETTER)\Source_File_Data_Setter.cpp \
	$(DEP_DAT_EXT)\Dependency_Data_Extractor.cpp \
	$(SRC_PROCESSOR)\Source_File_Processor.cpp \
	$(HDR_PROC)\Header_File_Processor.cpp \
	$(SRC_READER)\Project_Src_Code_Rdr.cpp \
	$(MK_FILE_CLNR)\Make_File_Cleaner.cpp \
	$(DES_READER)\Descriptor_File_Reader.cpp \
	$(DES_DATA_COL)\Descriptor_File_Data_Collector.cpp \
	$(DES_SYN_CON)\Descriptor_File_Syntax_Controller.cpp \
	$(SOURCE_DETR)\Source_File_Determiner.cpp \
	$(SRC_DT_COL)\Source_File_Data_Collector.cpp \
	$(SRC_DEP_SL_SF)\Source_File_Dependency_Selector_For_Single_File.cpp \
	$(SRC_INF_CL_SF)\Source_File_Information_Collector_For_Single_File.cpp \
	$(QUICK_SRC_EXT)\Quick_Src_Dependency_Extractor.cpp \
	$(DEP_DAT_PROC)\Dependency_Data_Processor.cpp \
	$(DEP_DAT_STCK)\Dependency_Data_Stack_Container.cpp \
	$(HDR_DEP_EXT)\Header_Dependency_Data_Extractor.cpp \
	$(GIT_PROC)\Git_Data_Processor.cpp \
	$(GIT_LIST)\Git_File_List_Writer.cpp \
	$(GIT_REC)\Git_File_List_Receiver.cpp \
	$(GIT_MOD_LST)\Git_Modification_Lister.cpp \
	$(GIT_MOD_RCV)\Git_Modification_Receiver.cpp \
	$(GIT_IGN)\Git_Ignoring_Files_Lister.cpp \
	$(HEAD_DETER)\Header_File_Determiner.cpp \
	$(DIR_ENUM)\Directory_Enumerator.cpp \
	$(DIR_OPS)\DirectoryOperations.cpp \
	$(STRING_OPS)\StringOperator.cpp \
	$(CHAR_OPS)\CharOperator.cpp \
	$(INT_TO_CHAR)\IntToCharTranslater.cpp \
	$(FILE_OPRS)\Cpp_FileOperations.cpp \
	$(SYS_INT)\Custom_System_Interface.cpp \
	-include CMAKE_Build_System_Generator.hpp \
	-include $(CMAKE_SYS_CON)\CMAKE_System_Constructor.hpp \
	-include $(CMAKE_MN_FL_WR)\CMAKE_Main_File_Writer.hpp \
	-include $(MAKE_BLD)\CMAKE_Target_Library_Builder.hpp \
	-include $(MAKE_DATA_COL)\MakeFile_Data_Collector.hpp  \
	-include $(MAKE_FILE_DIR_CON)\MakeFile_Directory_Constructor.hpp \
	-include $(SRC_DEP_DT)\Source_File_Dependency_Determiner.hpp \
	-include $(SRC_COM_DT_EXT)\Source_File_Compiler_Data_Extractor.hpp \
	-include $(SRC_DEP_SL)\Source_File_Dependency_Selector.hpp \
	-include $(SRC_DEP_SL_SF)\Source_File_Dependency_Selector_For_Single_File.hpp \
	-include $(SRC_INF_CL)\Source_File_Information_Collector.hpp \
	-include $(SRC_DATA_SETTER)\Source_File_Data_Setter.hpp \
	-include $(SRC_INF_CL_SF)\Source_File_Information_Collector_For_Single_File.hpp \
	-include $(DEP_DAT_EXT)\Dependency_Data_Extractor.hpp \
	-include $(DEP_DAT_PROC)\Dependency_Data_Processor.hpp \
	-include $(QUICK_SRC_EXT)\Quick_Src_Dependency_Extractor.hpp \
	-include $(DEP_DAT_STCK)\Dependency_Data_Stack_Container.hpp \
	-include $(HDR_DEP_EXT)\Header_Dependency_Data_Extractor.hpp \
	-include $(SRC_PROCESSOR)\Source_File_Processor.hpp \
	-include $(HDR_PROC)\Header_File_Processor.hpp \
	-include $(SRC_READER)\Project_Src_Code_Rdr.hpp \
	-include $(MK_FILE_CLNR)\Make_File_Cleaner.hpp \
	-include $(SOURCE_DETR)\Source_File_Determiner.h \
	-include $(SRC_DT_COL)\Source_File_Data_Collector.hpp \
	-include $(GIT_REC)\Git_File_List_Receiver.hpp \
	-include $(GIT_PROC)\Git_Data_Processor.hpp \
	-include $(GIT_LIST)\Git_File_List_Writer.hpp \
	-include $(GIT_MOD_LST)\Git_Modification_Lister.hpp \
	-include $(GIT_MOD_RCV)\Git_Modification_Receiver.hpp \
	-include $(GIT_IGN)\Git_Ignoring_Files_Lister.hpp \
	-include $(DES_READER)\Descriptor_File_Reader.hpp \
	-include $(DES_DATA_COL)\Descriptor_File_Data_Collector.hpp \
	-include $(DES_SYN_CON)\Descriptor_File_Syntax_Controller.hpp \
	-include $(HEAD_DETER)\Header_File_Determiner.h \
	-include $(DIR_ENUM)\Directory_Enumerator.h \
	-include $(STRING_OPS)\StringOperator.h \
	-include $(DIR_OPS)\DirectoryOperations.h \
	-include $(INT_TO_CHAR)\IntToCharTranslater.h \
	-include $(CHAR_OPS)\CharOperator.h \
	-include $(FILE_OPRS)\Cpp_FileOperations.h \
	-include $(SYS_INT)\Custom_System_Interface.h \
	-lpthread
