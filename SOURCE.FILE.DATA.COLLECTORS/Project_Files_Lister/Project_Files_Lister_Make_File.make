
DIR_ENUM=D:\pcynlitx.build\PROJECT.BUILD.TOOLS\Directory_Enumerator
STRING_OPS=D:\pcynlitx.build\BASIC.TOOLS\StringOperator
DIR_OPS=D:\pcynlitx.build\BASIC.TOOLS\DirectoryOperations
CHAR_OPS=D:\pcynlitx.build\BASIC.TOOLS\CharOperator
FILE_OPRS=D:\pcynlitx.build\BASIC.TOOLS\Cpp_FileOperations
HEAD_DETR=D:\pcynlitx.build\PROJECT.BUILD.TOOLS\Header_File_Determiner
DES_READ=D:\pcynlitx.build\DESCRIPTION.PROCESSING.SYSTEM\Descriptor_File_Reader
DES_DATA_COL=D:\pcynlitx.build\DESCRIPTION.PROCESSING.SYSTEM\Descriptor_File_Data_Collector
GIT_LIST=D:\pcynlitx.build\PROJECT.BUILD.TOOLS\Git_File_List_Receiver
SRC_DT_COL=D:\pcynlitx.build\SOURCE.FILE.DATA.COLLECTORS\Source_File_Data_Collector
FILE_DAT_COL=D:\pcynlitx.build\SOURCE.FILE.DATA.COLLECTORS\Project_Files_Data_Collector
SOURCE_DETR=D:\pcynlitx.build\SOURCE.FILE.DATA.COLLECTORS\Source_File_Determiner

VPATH = $(DIR_OPS) $(STRING_OPS) $(CHAR_OPS) $(FILE_OPRS) \
				$(HEAD_DETR) $(SOURCE_DETR) $(DES_READ) $(DES_DATA_COL) \
				$(GIT_LIST) $(SRC_DT_COL) $(FILE_DAT_COL)

Project_Files_Lister.exe: Project_Files_Lister_Main_File.cpp Project_Files_Lister.cpp  \
	Project_Files_Data_Collector.cpp Source_File_Determiner.cpp \
	Header_File_Determiner.cpp StringOperator.cpp \
	Cpp_FileOperations.cpp CharOperator.cpp Project_Files_Lister.h \
	Project_Files_Data_Collector.hpp \
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
	 -L$(HEAD_DETR) -L$(SOURCE_DETR) -L$(DIR_OPS) \
	 -L$(STRING_OPS) -L$(GIT_LIST) -L$(FILE_DAT_COL) \
	 -L$(CHAR_OPS) -L$(FILE_OPRS) \
	 -L$(DES_READ) -L$(DES_DATA_COL) \
	 -L$(SRC_DT_COL) \
		Project_Files_Lister_Main_File.cpp Project_Files_Lister.cpp \
		$(FILE_DAT_COL)\Project_Files_Data_Collector.cpp \
		$(SOURCE_DETR)\Source_File_Determiner.cpp \
		$(HEAD_DETR)\Header_File_Determiner.cpp \
		$(DIR_ENUM)\Directory_Enumerator.cpp \
		$(DES_READ)\Descriptor_File_Reader.cpp \
		$(DES_DATA_COL)\Descriptor_File_Data_Collector.cpp \
		$(GIT_LIST)\Git_File_List_Receiver.cpp \
		$(SRC_DT_COL)\Source_File_Data_Collector.cpp \
		$(DIR_OPS)\DirectoryOperations.cpp \
		$(STRING_OPS)\StringOperator.cpp \
		$(CHAR_OPS)\CharOperator.cpp \
		$(FILE_OPRS)\Cpp_FileOperations.cpp \
		-include Project_Files_Lister.h \
		-include $(FILE_DAT_COL)\Project_Files_Data_Collector.hpp \
		-include $(SOURCE_DETR)\Source_File_Determiner.h \
		-include $(HEAD_DETR)\Header_File_Determiner.h \
		-include $(DES_READ)\Descriptor_File_Reader.hpp \
		-include $(SRC_DT_COL)\Source_File_Data_Collector.hpp \
		-include $(DES_DATA_COL)\Descriptor_File_Data_Collector.hpp \
		-include $(GIT_LIST)\Git_File_List_Receiver.hpp \
		-include $(STRING_OPS)\StringOperator.h \
		-include $(DIR_OPS)\DirectoryOperations.h \
		-include $(CHAR_OPS)\CharOperator.h \
		-include $(FILE_OPRS)\Cpp_FileOperations.h
