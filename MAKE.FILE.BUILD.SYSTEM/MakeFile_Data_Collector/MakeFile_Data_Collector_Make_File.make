
STRING_OPS=D:\pcynlitx.build\BASIC.TOOLS\StringOperator
DIR_OPS=D:\pcynlitx.build\BASIC.TOOLS\DirectoryOperations
CPP_OPS=D:\pcynlitx.build\BASIC.TOOLS\Cpp_FileOperations
CHAR_OPS=D:\pcynlitx.build\BASIC.TOOLS\CharOperator
CLASS_NAME=D:\pcynlitx.build\BASIC.TOOLS\ClassNameReader
CLASS_SYNTAX=D:\pcynlitx.build\BASIC.TOOLS\ClassSyntaxControl
DIR_ENUM=D:\pcynlitx.build\PROJECT.BUILD.TOOLS\Directory_Enumerator
HEAD_DET=D:\pcynlitx.build\PROJECT.BUILD.TOOLS\Header_File_Determiner
FILE_LISTER=D:\pcynlitx.build\PROJECT.BUILD.TOOLS\Project_Files_Lister
SOURCE_DETR=D:\pcynlitx.build\PROJECT.BUILD.TOOLS\Source_File_Determiner
INT_TO_CHAR=D:\pcynlitx.build\BASIC.TOOLS\IntToCharTranslater
DES_READER=D:\pcynlitx.build\DESCRIPTION.PROCESSING.SYSTEM\Descriptor_File_Reader
DES_DATA_COL=D:\pcynlitx.build\DESCRIPTION.PROCESSING.SYSTEM\Descriptor_File_Data_Collector
GIT_LIST=D:\pcynlitx.build\PROJECT.BUILD.TOOLS\Git_File_List_Receiver
SRC_COL=D:\pcynlitx.build\PROJECT.BUILD.TOOLS\Source_File_Data_Collector
PRJ_DAT_COL=D:\pcynlitx.build\PROJECT.BUILD.TOOLS\Project_Files_Data_Collector


VPATH = $(DIR_OPS) $(CPP_OPS) $(CHAR_OPS) $(CLASS_NAME) $(SOURCE_DETR) \
				$(CLASS_SYNTAX) $(DIR_ENUM) $(STRING_OPS) $(HEAD_DET) $(FILE_LISTER) \
				$(INT_TO_CHAR) $(DES_DATA_COL) $(DES_READER) $(GIT_LIST) $(SRC_COL) \
				$(PRJ_DAT_COL)

Make_File_Builder.exe: MakeFile_Data_Collector_Main_File.cpp MakeFile_Data_Collector.cpp \
	Project_Files_Lister.cpp Source_File_Data_Collector.cpp \
	Source_File_Determiner.cpp Header_File_Determiner.cpp \
	Git_File_List_Receiver.cpp Directory_Enumerator.cpp ClassNameReader.cpp \
	ClassSyntaxControl.cpp DirectoryOperations.cpp \
	CharOperator.cpp Cpp_FileOperations.cpp \
	MakeFile_Data_Collector.hpp Project_Files_Lister.h \
	Git_File_List_Receiver.hpp Source_File_Data_Collector.hpp \
	Source_File_Determiner.h Header_File_Determiner.h \
	Directory_Enumerator.h DirectoryOperations.h \
	CharOperator.h Cpp_FileOperations.h

	g++ -std=c++17 -g -o MakeFile_Data_Collector.exe \
	 -I$(DIR_OPS) -I$(CPP_OPS) -I$(CHAR_OPS) \
	 -I$(CLASS_NAME) -I$(STRING_OPS) -I$(HEAD_DET) \
	 -I$(FILE_LISTER) -I$(SOURCE_DETR) -I$(SRC_COL) \
	 -I$(CLASS_SYNTAX) -I$(DIR_ENUM) -I$(INT_TO_CHAR) \
	 -I$(DES_DATA_COL) -I$(DES_READER) -I$(GIT_LIST) -I$(PRJ_DAT_COL) \
	 -L$(DIR_ENUM) -L$(DIR_OPS) -L$(CPP_OPS) \
	 -L$(CHAR_OPS) -L$(INT_TO_CHAR) -L$(DES_DATA_COL) \
	 -L$(DES_READER) -L$(CLASS_NAME) -L$(CLASS_SYNTAX) \
	 -L$(STRING_OPS) -L$(HEAD_DET) -L$(FILE_LISTER) \
	 -L$(SOURCE_DETR) -L$(GIT_LIST) -L$(SRC_COL) -L$(PRJ_DAT_COL) \
		MakeFile_Data_Collector_Main_File.cpp MakeFile_Data_Collector.cpp \
		$(FILE_LISTER)\Project_Files_Lister.cpp $(GIT_LIST)\Git_File_List_Receiver.cpp \
		$(SRC_COL)\Source_File_Data_Collector.cpp \
		$(PRJ_DAT_COL)\Project_Files_Data_Collector.cpp \
		$(SOURCE_DETR)\Source_File_Determiner.cpp $(DIR_ENUM)\Directory_Enumerator.cpp \
		$(DES_READER)\Descriptor_File_Reader.cpp $(DES_DATA_COL)\Descriptor_File_Data_Collector.cpp \
		$(HEAD_DET)\Header_File_Determiner.cpp $(CLASS_NAME)\ClassNameReader.cpp \
		$(CLASS_SYNTAX)\ClassSyntaxControl.cpp \
		$(DIR_OPS)\DirectoryOperations.cpp $(STRING_OPS)\StringOperator.cpp \
		$(CHAR_OPS)\CharOperator.cpp $(CPP_OPS)\Cpp_FileOperations.cpp \
		$(INT_TO_CHAR)\IntToCharTranslater.cpp \
		-include MakeFile_Data_Collector.hpp \
		-include $(FILE_LISTER)\Project_Files_Lister.h \
		-include $(PRJ_DAT_COL)\Project_Files_Data_Collector.hpp \
		-include $(SRC_COL)\Source_File_Data_Collector.hpp \
		-include $(GIT_LIST)\Git_File_List_Receiver.hpp \
		-include $(SOURCE_DETR)\Source_File_Determiner.h \
		-include $(DIR_ENUM)\Directory_Enumerator.h \
		-include $(HEAD_DET)\Header_File_Determiner.h \
		-include $(CLASS_NAME)\ClassNameReader.h \
		-include $(CLASS_SYNTAX)\ClassSyntaxControl.h \
		-include $(STRING_OPS)\StringOperator.h \
		-include $(DIR_OPS)\DirectoryOperations.h \
	  -include $(CHAR_OPS)\CharOperator.h \
		-include $(CPP_OPS)\Cpp_FileOperations.h \
		-include $(INT_TO_CHAR)\IntToCharTranslater.h
