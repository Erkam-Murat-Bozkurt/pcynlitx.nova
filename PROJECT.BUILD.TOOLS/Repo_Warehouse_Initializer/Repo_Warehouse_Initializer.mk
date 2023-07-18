

DIR_OPS=D:\pcynlitx.build\BASIC.TOOLS\DirectoryOperations
STRING_OPS=D:\pcynlitx.build\BASIC.TOOLS\StringOperator
CHAR_OPS=D:\pcynlitx.build\BASIC.TOOLS\CharOperator
FILE_OPRS=D:\pcynlitx.build\BASIC.TOOLS\Cpp_FileOperations
HEAD_DET=D:\pcynlitx.build\SOURCE.FILE.DATA.COLLECTORS\Header_File_Determiner
DES_READ=D:\pcynlitx.build\DESCRIPTION.PROCESSING.SYSTEM\Description.Readers\Descriptor.File.Reader
DES_DATA_COL=D:\pcynlitx.build\DESCRIPTION.PROCESSING.SYSTEM\Description.Readers\Descriptor.File.Data.Collector
DES_SYN_CTR=D:\pcynlitx.build\DESCRIPTION.PROCESSING.SYSTEM\Description.Readers\Descriptor.File.Syntax.Controller
GIT_LIST=D:\pcynlitx.build\PROJECT.BUILD.TOOLS\Git_File_List_Receiver
SRC_DT_COL=D:\pcynlitx.build\SOURCE.FILE.DATA.COLLECTORS\Source_File_Data_Collector
FILE_DAT_COL=D:\pcynlitx.build\SOURCE.FILE.DATA.COLLECTORS\Project_Files_Data_Collector
DIR_LIST=D:\pcynlitx.build\SOURCE.FILE.DATA.COLLECTORS\Project_Files_Lister
SRC_DET=D:\pcynlitx.build\SOURCE.FILE.DATA.COLLECTORS\Source_File_Determiner
HEAD_DET=D:\pcynlitx.build\SOURCE.FILE.DATA.COLLECTORS\Header_File_Determiner
GIT_LIST_WRITER=D:\pcynlitx.build\PROJECT.BUILD.TOOLS\Git_File_List_Writer
GIT_IGN_LISTER=D:\pcynlitx.build\PROJECT.BUILD.TOOLS\Git_Ignoring_Files_Lister
CUST_SYS_INT=D:\pcynlitx.build\BASIC.TOOLS\Custom_System_Interface

VPATH = $(DIR_LIST) $(DIR_ENUM) $(DIR_OPS) \
		$(STRING_OPS) $(CHAR_OPS) $(FILE_OPRS) $(HEAD_DET) $(SRC_DET) \
		$(DES_READ) $(DES_DATA_COL) $(DES_SYN_CTR) $(GIT_LIST) \
		$(FILE_DAT_COL) $(SRC_DT_COL) $(GIT_LIST_WRITER) \
		$(HEAD_DET) $(CUST_SYS_INT) $(GIT_IGN_LISTER)

Repo_Warehouse_Initializer.exe: Repo_Warehouse_Initializer_Main_File.cpp \
	Repo_Warehouse_Initializer.cpp \
	Project_Files_Lister.cpp \
	Git_File_List_Receiver.cpp \
	Git_File_List_Writer.cpp \
	Git_Ignoring_Files_Lister.cpp \
	Descriptor_File_Reader.cpp \
	Descriptor_File_Data_Collector.cpp \
	Descriptor_File_Syntax_Controller.cpp \
	Project_Files_Data_Collector.cpp \
	Source_File_Data_Collector.cpp \
	Header_File_Determiner.cpp \
	Source_File_Determiner.cpp \
	StringOperator.cpp \
	Custom_System_Interface.cpp \
	Cpp_FileOperations.cpp \
	CharOperator.cpp \
	Repo_Warehouse_Initializer.h \
	Project_Files_Lister.h \
	Project_Files_Data_Collector.hpp \
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

	g++ -std=c++17 -o Repo_Warehouse_Initializer.exe  -I$(DIR_LIST) \
   -I$(DES_READ)   -I$(DES_DATA_COL) -I$(GIT_LIST)    -I$(FILE_DAT_COL)  \
   -I$(SRC_DT_COL) -I$(DIR_OPS)      -I$(STRING_OPS)  -I$(CHAR_OPS) \
   -I$(FILE_OPRS)  -I$(HEAD_DET)     -I$(SRC_DET)     -I$(DES_SYN_CTR) \
   -I$(GIT_LIST_WRITER) -I$(CUST_SYS_INT) -I$(GIT_IGN_LISTER) \
   -L$(DIR_LIST)   -L$(REPO_DET)     -L$(DIR_TREE)    -L$(DIR_OPS) \
   -L$(DES_READ)   -L$(DES_DATA_COL) -L$(GIT_LIST)    -L$(FILE_DAT_COL) \
   -L$(SRC_DT_COL) -L$(STRING_OPS)   -L$(CHAR_OPS)    -L$(FILE_OPRS)  \
   -L$(HEAD_DET)   -L$(SRC_DET)      -L$(DES_SYN_CTR) -L$(GIT_LIST_WRITER)\
   -L$(CUST_SYS_INT) -L$(GIT_IGN_LISTER) \
		Repo_Warehouse_Initializer_Main_File.cpp \
		Repo_Warehouse_Initializer.cpp \
		$(DIR_LIST)\Project_Files_Lister.cpp \
		$(GIT_LIST)\Git_File_List_Receiver.cpp  \
		$(GIT_LIST_WRITER)\Git_File_List_Writer.cpp  \
	    $(GIT_IGN_LISTER)\Git_Ignoring_Files_Lister.cpp \
		$(DES_READ)\Descriptor_File_Reader.cpp \
		$(DES_DATA_COL)\Descriptor_File_Data_Collector.cpp \
		$(DES_SYN_CTR)\Descriptor_File_Syntax_Controller.cpp \
		$(FILE_DAT_COL)\Project_Files_Data_Collector.cpp \
		$(SRC_DT_COL)\Source_File_Data_Collector.cpp \
		$(HEAD_DET)\Header_File_Determiner.cpp \
		$(SRC_DET)\Source_File_Determiner.cpp \
		$(DIR_OPS)\DirectoryOperations.cpp \
		$(STRING_OPS)\StringOperator.cpp \
		$(CUST_SYS_INT)\Custom_System_Interface.cpp \
		$(CHAR_OPS)\CharOperator.cpp \
		$(FILE_OPRS)\Cpp_FileOperations.cpp \
		-include Repo_Warehouse_Initializer.h \
		-include $(DIR_LIST)\Project_Files_Lister.h \
		-include $(GIT_LIST)\Git_File_List_Receiver.hpp \
		-include $(GIT_LIST_WRITER)\Git_File_List_Writer.hpp  \
		-include $(GIT_IGN_LISTER)\Git_Ignoring_Files_Lister.hpp \
		-include $(FILE_DAT_COL)\Project_Files_Data_Collector.hpp \
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
		-include $(FILE_OPRS)\Cpp_FileOperations.h
