STRING_OPS=D:\pcynlitx.build\BASIC.TOOLS\StringOperator
DIR_OPS=D:\pcynlitx.build\BASIC.TOOLS\DirectoryOperations
CHAR_OPS=D:\pcynlitx.build\BASIC.TOOLS\CharOperator
FILE_OPRS=D:\pcynlitx.build\BASIC.TOOLS\Cpp_FileOperations
DIR_ENUM=D:\pcynlitx.build\PROJECT.BUILD.TOOLS\Directory_Enumerator
GIT_LIST=D:\pcynlitx.build\PROJECT.BUILD.TOOLS\Git_File_List_Receiver
DES_READ=D:\pcynlitx.build\DESCRIPTION.PROCESSING.SYSTEM\Description.Readers\Descriptor.File.Reader
DES_DATA_COL=D:\pcynlitx.build\DESCRIPTION.PROCESSING.SYSTEM\Description.Readers\Descriptor.File.Data.Collector
DES_SYN_CON=D:\pcynlitx.build\DESCRIPTION.PROCESSING.SYSTEM\Description.Readers\Descriptor.File.Syntax.Controller
SRC_DT_COL=D:\pcynlitx.build\SOURCE.FILE.DATA.COLLECTORS\Source_File_Data_Collector
FILE_DAT_COL=D:\pcynlitx.build\SOURCE.FILE.DATA.COLLECTORS\Project_Files_Data_Collector
SOURCE_DETR=D:\pcynlitx.build\SOURCE.FILE.DATA.COLLECTORS\Source_File_Determiner
HEAD_DETR=D:\pcynlitx.build\SOURCE.FILE.DATA.COLLECTORS\Header_File_Determiner
SRC_INF_CL=D:\pcynlitx.build\SOURCE.FILE.PROCESSING.SYSTEM\Source_File_Information_Collector
SRC_DEP_SL=D:\pcynlitx.build\SOURCE.FILE.PROCESSING.SYSTEM\Source_File_Dependency_Selector
SRC_DEP_DT=D:\pcynlitx.build\SOURCE.FILE.PROCESSING.SYSTEM\Source_File_Dependency_Determiner


VPATH = $(DIR_OPS) $(STRING_OPS) $(CHAR_OPS) $(FILE_OPRS) \
				$(HEAD_DETR) $(SOURCE_DETR) $(DES_READ) $(DES_DATA_COL) \
				$(GIT_LIST) $(SRC_DT_COL) $(FILE_DAT_COL) $(DES_SYN_CON) \
				$(SRC_DEP_DT) $(SRC_DEP_SL) $(SRC_INF_CL)

Project_Files_Lister.exe: Project_Files_Lister_Main_File.cpp \
	Project_Files_Lister.cpp  \
	Project_Files_Data_Collector.cpp \
	Descriptor_File_Reader.cpp \
	Descriptor_File_Data_Collector.cpp \
	Descriptor_File_Syntax_Controller.cpp \
	Source_File_Dependency_Determiner.cpp \
	Source_File_Dependency_Selector.cpp \
	Source_File_Information_Collector.cpp \
	Source_File_Determiner.cpp \
	Header_File_Determiner.cpp \
	StringOperator.cpp \
	Cpp_FileOperations.cpp \
	CharOperator.cpp \
	Project_Files_Lister.h \
	Project_Files_Data_Collector.hpp \
	Source_File_Dependency_Determiner.hpp \
	Source_File_Dependency_Selector.hpp \
	Source_File_Information_Collector.hpp \
	Source_File_Determiner.h \
	Header_File_Determiner.h \
	StringOperator.h \
	DirectoryOperations.h \
	CharOperator.h \
	Cpp_FileOperations.h

	g++ -std=c++17 -o Project_Files_Lister.exe \
	 -I$(HEAD_DETR) -I$(SOURCE_DETR) \
	 -I$(DIR_OPS) -I$(STRING_OPS) \
	 -I$(CHAR_OPS) -I$(FILE_OPRS) \
	 -I$(CHAR_OPS) -I$(DES_READ) \
	 -I$(DES_DATA_COL) -I$(GIT_LIST) \
	 -I$(FILE_DAT_COL) -I$(SRC_DT_COL) \
	 -I$(DES_SYN_CON) \
	 -I$(SRC_DEP_DT) -I$(SRC_DEP_SL) -I$(SRC_INF_CL) \
	 -L$(HEAD_DETR) -L$(SOURCE_DETR) -L$(DIR_OPS) \
	 -L$(STRING_OPS) -L$(GIT_LIST) -L$(FILE_DAT_COL) \
	 -L$(CHAR_OPS) -L$(FILE_OPRS) \
	 -L$(DES_READ) -L$(DES_DATA_COL) \
	 -L$(SRC_DT_COL) -L$(DES_SYN_CON) \
	 -L$(SRC_DEP_DT) -L$(SRC_DEP_SL) -L$(SRC_INF_CL) \
		Project_Files_Lister_Main_File.cpp \
		Project_Files_Lister.cpp \
		$(FILE_DAT_COL)\Project_Files_Data_Collector.cpp \
		$(SRC_DEP_DT)\Source_File_Dependency_Determiner.cpp \
		$(SRC_DEP_SL)\Source_File_Dependency_Selector.cpp \
		$(SRC_INF_CL)\Source_File_Information_Collector.cpp \
		$(SOURCE_DETR)\Source_File_Determiner.cpp \
		$(HEAD_DETR)\Header_File_Determiner.cpp \
		$(DIR_ENUM)\Directory_Enumerator.cpp \
		$(DES_READ)\Descriptor_File_Reader.cpp \
		$(DES_DATA_COL)\Descriptor_File_Data_Collector.cpp \
		$(DES_SYN_CON)\Descriptor_File_Syntax_Controller.cpp \
		$(GIT_LIST)\Git_File_List_Receiver.cpp \
		$(SRC_DT_COL)\Source_File_Data_Collector.cpp \
		$(DIR_OPS)\DirectoryOperations.cpp \
		$(STRING_OPS)\StringOperator.cpp \
		$(CHAR_OPS)\CharOperator.cpp \
		$(FILE_OPRS)\Cpp_FileOperations.cpp \
		-include Project_Files_Lister.h \
		-include $(FILE_DAT_COL)\Project_Files_Data_Collector.hpp \
		-include $(SOURCE_DETR)\Source_File_Determiner.h \
		-include $(SRC_DEP_DT)\Source_File_Dependency_Determiner.hpp \
		-include $(SRC_DEP_SL)\Source_File_Dependency_Selector.hpp \
		-include $(SRC_INF_CL)\Source_File_Information_Collector.hpp \
		-include $(HEAD_DETR)\Header_File_Determiner.h \
		-include $(DES_READ)\Descriptor_File_Reader.hpp \
		-include $(SRC_DT_COL)\Source_File_Data_Collector.hpp \
		-include $(DES_DATA_COL)\Descriptor_File_Data_Collector.hpp \
		-include $(DES_SYN_CON)\Descriptor_File_Syntax_Controller.hpp \
		-include $(GIT_LIST)\Git_File_List_Receiver.hpp \
		-include $(STRING_OPS)\StringOperator.h \
		-include $(DIR_OPS)\DirectoryOperations.h \
		-include $(CHAR_OPS)\CharOperator.h \
		-include $(FILE_OPRS)\Cpp_FileOperations.h
