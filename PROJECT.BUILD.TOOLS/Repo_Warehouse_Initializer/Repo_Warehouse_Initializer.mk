
INT_TO_CHAR=D:\pcynlitx.build\BASIC.TOOLS\IntToCharTranslater
DIR_OPS=D:\pcynlitx.build\BASIC.TOOLS\DirectoryOperations
STRING_OPS=D:\pcynlitx.build\BASIC.TOOLS\StringOperator
CHAR_OPS=D:\pcynlitx.build\BASIC.TOOLS\CharOperator
FILE_OPRS=D:\pcynlitx.build\BASIC.TOOLS\Cpp_FileOperations
DES_READ=D:\pcynlitx.build\DESCRIPTION.PROCESSING.SYSTEM\Description.Readers\Descriptor.File.Reader
DES_DATA_COL=D:\pcynlitx.build\DESCRIPTION.PROCESSING.SYSTEM\Description.Readers\Descriptor.File.Data.Collector
DES_SYN_CTR=D:\pcynlitx.build\DESCRIPTION.PROCESSING.SYSTEM\Description.Readers\Descriptor.File.Syntax.Controller

SRC_DT_COL=D:\pcynlitx.build\SOURCE.FILE.DATA.COLLECTORS\Source_File_Data_Collector
SRC_DET=D:\pcynlitx.build\SOURCE.FILE.DATA.COLLECTORS\Source_File_Determiner
HEAD_DET=D:\pcynlitx.build\SOURCE.FILE.DATA.COLLECTORS\Header_File_Determiner
CUST_SYS_INT=D:\pcynlitx.build\BASIC.TOOLS\Custom_System_Interface
SRC_READER=D:\pcynlitx.build\PROJECT.BUILD.TOOLS\Project_Src_Code_Rdr



GIT_LIST=D:\pcynlitx.build\GIT.DATA.PROCESSING.SYSTEM\Git_File_List_Writer
GIT_REC=D:\pcynlitx.build\GIT.DATA.PROCESSING.SYSTEM\Git_File_List_Receiver
GIT_IGN=D:\pcynlitx.build\GIT.DATA.PROCESSING.SYSTEM\Git_Ignoring_Files_Lister
GIT_MOD_LST=D:\pcynlitx.build\GIT.DATA.PROCESSING.SYSTEM\Git_Modification_Lister
GIT_MOD_RCV=D:\pcynlitx.build\GIT.DATA.PROCESSING.SYSTEM\Git_Modification_Receiver
GIT_PROC=D:\pcynlitx.build\GIT.DATA.PROCESSING.SYSTEM\Git_data_Processor

SRC_DEP_DT=D:\pcynlitx.build\SOURCE.FILE.PROCESSING.SYSTEM\Source_File_Dependency_Determiner
SRC_INF_CL=D:\pcynlitx.build\SOURCE.FILE.PROCESSING.SYSTEM\Source_File_Information_Collector
SRC_COM_DT_EXT=D:\pcynlitx.build\SOURCE.FILE.PROCESSING.SYSTEM\Source_File_Compiler_Data_Extractor
SRC_DEP_SL=D:\pcynlitx.build\SOURCE.FILE.PROCESSING.SYSTEM\Source_File_Dependency_Selector
HDR_PROC=D:\pcynlitx.build\SOURCE.FILE.PROCESSING.SYSTEM\Header_File_Processor
DEP_DAT_EXT=D:\pcynlitx.build\SOURCE.FILE.PROCESSING.SYSTEM\Dependency_Data_Extractor
SRC_PROCESSOR=D:\pcynlitx.build\SOURCE.FILE.PROCESSING.SYSTEM\Source_File_Processor
SRC_INF_CL_SF=D:\pcynlitx.build\SOURCE.FILE.PROCESSING.SYSTEM\Source_File_Information_Collector_For_Single_File
SRC_DEP_SL_SF=D:\pcynlitx.build\SOURCE.FILE.PROCESSING.SYSTEM\Source_File_Dependency_Selector_For_Single_File
SRC_DT_SETTER=D:\pcynlitx.build\SOURCE.FILE.PROCESSING.SYSTEM\Source_File_Data_Setter


DEP_DAT_PROC=D:\pcynlitx.build\SOURCE.FILE.PROCESSING.SYSTEM\Dependency_Data_Processor
DEP_DAT_STCK=D:\pcynlitx.build\SOURCE.FILE.PROCESSING.SYSTEM\Dependency_Data_Stack_Container
HDR_DEP_EXT=D:\pcynlitx.build\SOURCE.FILE.PROCESSING.SYSTEM\Header_Dependency_Data_Extractor
QUICK_SRC_EXT=D:\pcynlitx.build\SOURCE.FILE.PROCESSING.SYSTEM\Quick_Src_Dependency_Extractor



VPATH = $(DIR_ENUM)      $(DIR_OPS) \
		$(STRING_OPS)    $(CHAR_OPS)        $(FILE_OPRS)   $(SRC_DET) \
		$(DES_READ)      $(DES_DATA_COL)    $(DES_SYN_CTR) $(GIT_LIST) \
		$(SRC_DT_COL)    $(GIT_REC)         $(GIT_MOD_LST) \
		$(HEAD_DET)      $(CUST_SYS_INT)    $(GIT_IGN)     $(GIT_MOD_RCV) \
		$(GIT_PROC) \
		$(SRC_INF_CL)    $(SRC_COM_DT_EXT)  $(SRC_DEP_SL) \
		$(HDR_PROC)      $(DEP_DAT_EXT)     $(SRC_PROCESSOR) \
		$(SRC_DEP_DT)    $(SRC_READER)      $(INT_TO_CHAR) \
		$(SRC_INF_CL_SF) $(SRC_DEP_SL_SF)   $(SRC_DT_SETTER) \
		$(DEP_DAT_PROC)  $(QUICK_SRC_EXT) \
		$(DEP_DAT_STCK) \
		$(HDR_DEP_EXT)

Repo_Warehouse_Initializer.exe: Repo_Warehouse_Initializer_Main_File.cpp \
	Repo_Warehouse_Initializer.cpp \
	Source_File_Dependency_Determiner.cpp \
	Source_File_Dependency_Selector_For_Single_File.cpp \
	Source_File_Information_Collector_For_Single_File.cpp \
	Source_File_Information_Collector.cpp \
	Source_File_Compiler_Data_Extractor.cpp \
	Source_File_Dependency_Selector.cpp \
	Quick_Src_Dependency_Extractor.cpp \
	Source_File_Data_Setter.cpp \
	Header_File_Processor.cpp \
	Dependency_Data_Extractor.cpp \
	Source_File_Processor.cpp \
	Git_Modification_Receiver.cpp \
	Git_Modification_Lister.cpp \
	Git_File_List_Receiver.cpp \
	Git_File_List_Writer.cpp \
	Git_Ignoring_Files_Lister.cpp \
	Project_Src_Code_Rdr.cpp \
	Descriptor_File_Reader.cpp \
	Descriptor_File_Data_Collector.cpp \
	Descriptor_File_Syntax_Controller.cpp \
	Source_File_Data_Collector.cpp \
	Header_File_Determiner.cpp \
	Source_File_Determiner.cpp \
	StringOperator.cpp \
	Custom_System_Interface.cpp \
	Cpp_FileOperations.cpp \
	CharOperator.cpp \
	Repo_Warehouse_Initializer.h \
	Source_File_Dependency_Determiner.hpp \
	Source_File_Dependency_Selector.hpp \
	Quick_Src_Dependency_Extractor.hpp \
	Source_File_Dependency_Selector_For_Single_File.hpp \
	Source_File_Information_Collector_For_Single_File.hpp \
	Source_File_Information_Collector.hpp \
	Source_File_Compiler_Data_Extractor.hpp \
	Source_File_Data_Setter.hpp \
	Header_File_Processor.hpp \
	Dependency_Data_Extractor.hpp \
	Source_File_Processor.hpp \
	Project_Src_Code_Rdr.hpp \
	Git_File_List_Receiver.hpp \
	Git_Ignoring_Files_Lister.hpp \
	Git_File_List_Writer.hpp \
	Descriptor_File_Reader.hpp \
	Descriptor_File_Data_Collector.hpp \
	Descriptor_File_Syntax_Controller.hpp \
	Source_File_Data_Collector.hpp \
	Source_File_Determiner.h \
	Header_File_Determiner.h \
	StringOperator.h \
	DirectoryOperations.h \
	Custom_System_Interface.h \
	CharOperator.h \
	Cpp_FileOperations.h

	g++ -std=c++17 -static-libgcc -static-libstdc++ -ggdb -o Repo_Warehouse_Initializer.exe \
   -I$(DES_READ)     -I$(DES_DATA_COL)    \
   -I$(SRC_DT_COL)   -I$(DIR_OPS)         -I$(STRING_OPS)    -I$(CHAR_OPS) \
   -I$(FILE_OPRS)    -I$(HEAD_DET)        -I$(SRC_DET)       -I$(DES_SYN_CTR) \
   -I$(GIT_LIST)     -I$(CUST_SYS_INT)    -I$(GIT_IGN) 	     -I$(GIT_MOD_LST)\
   -I$(GIT_MOD_RCV)  -I$(GIT_REC) 	      -I$(GIT_PROC) \
   -I$(SRC_INF_CL)   -I$(SRC_COM_DT_EXT)  -I$(SRC_DEP_SL)    -I$(SRC_DEP_DT) \
   -I$(HDR_PROC)     -I$(DEP_DAT_EXT)     -I$(SRC_PROCESSOR) -I$(SRC_READER) \
   -I$(INT_TO_CHAR)  -I$(SRC_INF_CL_SF)   -I$(SRC_DEP_SL_SF) -I$(SRC_DT_SETTER) \
   -I$(DEP_DAT_PROC) -I$(DEP_DAT_STCK)    -I$(HDR_DEP_EXT)   -I$(QUICK_SRC_EXT) \
   -L$(DIR_OPS) \
   -L$(DES_READ)     -L$(DES_DATA_COL)    -L$(GIT_LIST)      -L$(QUICK_SRC_EXT) \
   -L$(SRC_DT_COL)   -L$(STRING_OPS)      -L$(CHAR_OPS)      -L$(FILE_OPRS) \
   -L$(HEAD_DET)     -L$(SRC_DET)         -L$(DES_SYN_CTR) \
   -L$(CUST_SYS_INT) -L$(GIT_IGN)  	      -L$(GIT_MOD_LST) \
   -L$(GIT_MOD_RCV)  -L$(GIT_REC)         -L$(GIT_PROC) \
   -L$(SRC_INF_CL)   -L$(SRC_COM_DT_EXT)  -L$(SRC_DEP_SL)    -L$(SRC_READER) \
   -L$(HDR_PROC)     -L$(DEP_DAT_EXT)     -L$(SRC_PROCESSOR) -L$(SRC_DEP_DT) \
   -L$(INT_TO_CHAR)  -L$(SRC_INF_CL_SF)   -L$(SRC_DEP_SL_SF) -L$(SRC_DT_SETTER) \
   -L$(DEP_DAT_PROC) -L$(DEP_DAT_STCK)    -L$(HDR_DEP_EXT) \
		Repo_Warehouse_Initializer_Main_File.cpp \
		Repo_Warehouse_Initializer.cpp \
		$(SRC_DEP_DT)\Source_File_Dependency_Determiner.cpp \
		$(SRC_DEP_SL_SF)\Source_File_Dependency_Selector_For_Single_File.cpp \
		$(SRC_INF_CL_SF)\Source_File_Information_Collector_For_Single_File.cpp \
		$(SRC_INF_CL)\Source_File_Information_Collector.cpp \
		$(SRC_COM_DT_EXT)\Source_File_Compiler_Data_Extractor.cpp \
	    $(SRC_DEP_SL)\Source_File_Dependency_Selector.cpp \
		$(QUICK_SRC_EXT)\Quick_Src_Dependency_Extractor.cpp \
		$(DEP_DAT_PROC)\Dependency_Data_Processor.cpp \
		$(HDR_DEP_EXT)\Header_Dependency_Data_Extractor.cpp \
		$(DEP_DAT_STCK)\Dependency_Data_Stack_Container.cpp \
		$(SRC_DT_SETTER)\Source_File_Data_Setter.cpp \
		$(HDR_PROC)\Header_File_Processor.cpp \
		$(DEP_DAT_EXT)\Dependency_Data_Extractor.cpp \
		$(SRC_PROCESSOR)\Source_File_Processor.cpp \
		$(SRC_READER)\Project_Src_Code_Rdr.cpp \
		$(GIT_PROC)\Git_Data_Processor.cpp \
		$(GIT_MOD_LST)\Git_Modification_Lister.cpp \
		$(GIT_MOD_RCV)\Git_Modification_Receiver.cpp \
		$(GIT_REC)\Git_File_List_Receiver.cpp  \
		$(GIT_LIST)\Git_File_List_Writer.cpp  \
	    $(GIT_IGN)\Git_Ignoring_Files_Lister.cpp \
		$(DES_READ)\Descriptor_File_Reader.cpp \
		$(DES_DATA_COL)\Descriptor_File_Data_Collector.cpp \
		$(DES_SYN_CTR)\Descriptor_File_Syntax_Controller.cpp \
		$(SRC_DT_COL)\Source_File_Data_Collector.cpp \
		$(HEAD_DET)\Header_File_Determiner.cpp \
		$(SRC_DET)\Source_File_Determiner.cpp \
		$(DIR_OPS)\DirectoryOperations.cpp \
		$(STRING_OPS)\StringOperator.cpp \
		$(CUST_SYS_INT)\Custom_System_Interface.cpp \
		$(CHAR_OPS)\CharOperator.cpp \
		$(INT_TO_CHAR)\IntToCharTranslater.cpp \
		$(FILE_OPRS)\Cpp_FileOperations.cpp \
		-include Repo_Warehouse_Initializer.h \
		-include $(SRC_DEP_DT)\Source_File_Dependency_Determiner.hpp \
		-include $(SRC_DEP_SL_SF)\Source_File_Dependency_Selector_For_Single_File.hpp \
		-include $(SRC_INF_CL_SF)\Source_File_Information_Collector_For_Single_File.hpp \
		-include $(SRC_INF_CL)\Source_File_Information_Collector.hpp \
		-include $(SRC_COM_DT_EXT)\Source_File_Compiler_Data_Extractor.hpp \
		-include $(SRC_DEP_SL)\Source_File_Dependency_Selector.hpp \
		-include $(QUICK_SRC_EXT)\Quick_Src_Dependency_Extractor.hpp \
		-include $(DEP_DAT_PROC)\Dependency_Data_Processor.hpp \
		-include $(HDR_DEP_EXT)\Header_Dependency_Data_Extractor.hpp \
		-include $(DEP_DAT_STCK)\Dependency_Data_Stack_Container.hpp \
		-include $(SRC_DT_SETTER)\Source_File_Data_Setter.hpp \
		-include $(HDR_PROC)\Header_File_Processor.hpp \
		-include $(DEP_DAT_EXT)\Dependency_Data_Extractor.hpp \
		-include $(SRC_PROCESSOR)\Source_File_Processor.hpp \
		-include $(SRC_READER)\Project_Src_Code_Rdr.hpp \
		-include $(GIT_PROC)\Git_Data_Processor.hpp \
		-include $(GIT_MOD_LST)\Git_Modification_Lister.hpp \
		-include $(GIT_MOD_RCV)\Git_Modification_Receiver.hpp \
		-include $(GIT_REC)\Git_File_List_Receiver.hpp  \
		-include $(GIT_LIST)\Git_File_List_Writer.hpp  \
	    -include $(GIT_IGN)\Git_Ignoring_Files_Lister.hpp \
		-include $(SRC_DT_COL)\Source_File_Data_Collector.hpp \
		-include $(DES_READ)\Descriptor_File_Reader.hpp \
		-include $(DES_DATA_COL)\Descriptor_File_Data_Collector.hpp \
		-include $(DES_SYN_CTR)\Descriptor_File_Syntax_Controller.hpp \
		-include $(SRC_DET)\Source_File_Determiner.h \
		-include $(HEAD_DET)\Header_File_Determiner.h \
		-include $(STRING_OPS)\StringOperator.h \
		-include $(DIR_OPS)\DirectoryOperations.h \
		-include $(CUST_SYS_INT)\Custom_System_Interface.h \
		-include $(CHAR_OPS)\CharOperator.h \
		-include $(INT_TO_CHAR)\IntToCharTranslater.h \
		-include $(FILE_OPRS)\Cpp_FileOperations.h \
		-lpthread
