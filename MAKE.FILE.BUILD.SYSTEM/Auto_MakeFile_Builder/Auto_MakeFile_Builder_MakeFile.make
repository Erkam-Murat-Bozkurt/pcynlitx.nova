
DIR_LIST=D:\pcynlitx.build\PROJECT.BUILD.TOOLS\Project_Files_Lister
DIR_ENUM=D:\pcynlitx.build\PROJECT.BUILD.TOOLS\Directory_Enumerator
REPO_DET=D:\pcynlitx.build\PROJECT.BUILD.TOOLS\Repo_Dir_Determiner
DIR_TREE=D:\pcynlitx.build\PROJECT.BUILD.TOOLS\Directory_Tree_Size_Determiner
MAKE_BLD=D:\pcynlitx.build\MAKE.FILE.BUILD.SYSTEM\Make_File_Builder
HEAD_DETER=D:\pcynlitx.build\PROJECT.BUILD.TOOLS\Header_File_Determiner
STRING_OPS=D:\pcynlitx.build\BASIC.TOOLS\StringOperator
DIR_OPS=D:\pcynlitx.build\BASIC.TOOLS\DirectoryOperations
STRING_OPS=D:\pcynlitx.build\BASIC.TOOLS\StringOperator
CHAR_OPS=D:\pcynlitx.build\BASIC.TOOLS\CharOperator
FILE_OPRS=D:\pcynlitx.build\BASIC.TOOLS\Cpp_FileOperations
CLASS_NAME=D:\pcynlitx.build\BASIC.TOOLS\ClassNameReader
CLASS_SYNTAX=D:\pcynlitx.build\BASIC.TOOLS\ClassSyntaxControl
SOURCE_DETR=D:\pcynlitx.build\PROJECT.BUILD.TOOLS\Source_File_Determiner
INT_TO_CHAR=D:\pcynlitx.build\BASIC.TOOLS\IntToCharTranslater
DES_READER=D:\pcynlitx.build\DESCRIPTION.PROCESSING.SYSTEM\Descriptor_File_Reader
DES_DATA_COL=D:\pcynlitx.build\DESCRIPTION.PROCESSING.SYSTEM\Descriptor_File_Data_Collector
MAKE_DATA_COL=D:\pcynlitx.build\MAKE.FILE.BUILD.SYSTEM\MakeFile_Data_Collector
GIT_LIST=D:\pcynlitx.build\PROJECT.BUILD.TOOLS\Git_File_List_Receiver
SRC_DT_COL=D:\pcynlitx.build\PROJECT.BUILD.TOOLS\Source_File_Data_Collector
FILE_DAT_COL=D:\pcynlitx.build\PROJECT.BUILD.TOOLS\Project_Files_Data_Collector
MK_FILE_CLNR=D:\pcynlitx.build\MAKE.FILE.BUILD.SYSTEM\Make_File_Cleaner

VPATH = $(DIR_LIST) $(DIR_ENUM) $(REPO_DET) $(DIR_TREE) $(DIR_OPS) \
	      $(STRING_OPS) $(CHAR_OPS) $(FILE_OPRS) $(MAKE_BLD) $(CLASS_NAME) \
				$(CLASS_SYNTAX) $(HEAD_DETER) $(SOURCE_DETR) $(INT_TO_CHAR) $(DES_READER) \
				$(DES_DATA_COL) $(MAKE_DATA_COL) $(GIT_LIST) $(SRC_DT_COL) \
				$(FILE_DAT_COL) $(MK_FILE_CLNR)

Auto_MakeFile_Builder.exe: Auto_MakeFile_Builder_Main_File.cpp Auto_MakeFile_Builder.cpp \
	Make_File_Builder.cpp MakeFile_Data_Collector.cpp Make_File_Cleaner.cpp \
	Project_Files_Lister.cpp Project_Files_Data_Collector.cpp Git_File_List_Receiver.cpp \
	Descriptor_File_Reader.cpp Descriptor_File_Data_Collector.cpp \
	Header_File_Determiner.cpp Directory_Enumerator.cpp Repo_Dir_Determiner.cpp \
	Directory_Tree_Size_Determiner.cpp ClassNameReader.cpp \
	ClassSyntaxControl.cpp StringOperator.cpp \
	Cpp_FileOperations.cpp CharOperator.cpp Auto_MakeFile_Builder.h \
	Make_File_Cleaner.hpp Descriptor_File_Reader.hpp Descriptor_File_Data_Collector.hpp \
	Project_Files_Lister.h Project_Files_Data_Collector.hpp Git_File_List_Receiver.hpp \
	Header_File_Determiner.h Directory_Enumerator.h \
	Repo_Dir_Determiner.h Make_File_Builder.h MakeFile_Data_Collector.hpp \
	ClassNameReader.h ClassSyntaxControl.h StringOperator.h \
	DirectoryOperations.h CharOperator.h Cpp_FileOperations.h

	g++ -std=c++17 -o Auto_MakeFile_Builder.exe \
	 -I$(DIR_LIST) -I$(MAKE_BLD) -I$(DIR_ENUM) \
	 -I$(REPO_DET) -I$(DIR_TREE) -I$(DIR_OPS) \
	 -I$(STRING_OPS) -I$(HEAD_DETER) -I$(SOURCE_DETR) \
   -I$(CHAR_OPS) -I$(FILE_OPRS) -I$(CLASS_NAME) \
	 -I$(CLASS_SYNTAX) -I$(INT_TO_CHAR) \
	 -I$(DES_READER) -I$(DES_DATA_COL) \
	 -I$(MAKE_DATA_COL) -I$(GIT_LIST) \
	 -I$(SRC_DT_COL) -I$(FILE_DAT_COL) \
	 -I$(MK_FILE_CLNR) -L$(DIR_LIST) \
	 -L$(MAKE_BLD) -L$(GIT_LIST) \
	 -L$(INT_TO_CHAR) -L$(DES_READER) \
	 -L$(DES_DATA_COL) -L$(MAKE_DATA_COL) \
	 -L$(DIR_ENUM) -L$(REPO_DET) \
	 -L$(DIR_TREE) -L$(DIR_OPS) \
	 -L$(STRING_OPS) -L$(CHAR_OPS) \
	 -L$(FILE_OPRS) -L$(CLASS_NAME) \
	 -L$(CLASS_SYNTAX) -L$(HEAD_DETER) \
	 -L$(SOURCE_DETR) -L$(SRC_DT_COL) \
	 -L$(FILE_DAT_COL) -L$(MK_FILE_CLNR) \
		Auto_MakeFile_Builder_Main_File.cpp Auto_MakeFile_Builder.cpp \
		$(MK_FILE_CLNR)\Make_File_Cleaner.cpp \
		$(DES_READER)\Descriptor_File_Reader.cpp \
		$(DES_DATA_COL)\Descriptor_File_Data_Collector.cpp \
		$(DIR_LIST)\Project_Files_Lister.cpp \
		$(FILE_DAT_COL)\Project_Files_Data_Collector.cpp \
		$(SRC_DT_COL)\Source_File_Data_Collector.cpp \
		$(GIT_LIST)\Git_File_List_Receiver.cpp \
		$(SOURCE_DETR)\Source_File_Determiner.cpp \
		$(HEAD_DETER)\Header_File_Determiner.cpp \
		$(MAKE_BLD)\Make_File_Builder.cpp \
		$(MAKE_DATA_COL)\MakeFile_Data_Collector.cpp  \
		$(DIR_ENUM)\Directory_Enumerator.cpp \
		$(REPO_DET)\Repo_Dir_Determiner.cpp \
		$(DIR_TREE)\Directory_Tree_Size_Determiner.cpp \
		$(CLASS_NAME)\ClassNameReader.cpp \
		$(CLASS_SYNTAX)\ClassSyntaxControl.cpp \
		$(DIR_OPS)\DirectoryOperations.cpp \
		$(STRING_OPS)\StringOperator.cpp \
		$(CHAR_OPS)\CharOperator.cpp \
		$(INT_TO_CHAR)\IntToCharTranslater.cpp \
		$(FILE_OPRS)\Cpp_FileOperations.cpp \
		-include Auto_MakeFile_Builder.h \
		-include $(MK_FILE_CLNR)\Make_File_Cleaner.hpp \
		-include $(DIR_LIST)\Project_Files_Lister.h \
		-include $(FILE_DAT_COL)\Project_Files_Data_Collector.hpp \
		-include $(SRC_DT_COL)\Source_File_Data_Collector.hpp \
		-include $(GIT_LIST)\Git_File_List_Receiver.hpp \
		-include $(DES_READER)\Descriptor_File_Reader.hpp \
		-include $(DES_DATA_COL)\Descriptor_File_Data_Collector.hpp \
		-include $(MAKE_BLD)\Make_File_Builder.h \
		-include $(MAKE_DATA_COL)\MakeFile_Data_Collector.hpp  \
		-include $(SOURCE_DETR)\Source_File_Determiner.h \
		-include $(HEAD_DETER)\Header_File_Determiner.h \
		-include $(DIR_ENUM)\Directory_Enumerator.h \
		-include $(REPO_DET)\Repo_Dir_Determiner.h \
		-include $(DIR_TREE)\Directory_Tree_Size_Determiner.h \
		-include $(CLASS_NAME)\ClassNameReader.h \
		-include $(CLASS_SYNTAX)\ClassSyntaxControl.h \
		-include $(STRING_OPS)\StringOperator.h \
		-include $(DIR_OPS)\DirectoryOperations.h \
		-include $(INT_TO_CHAR)\IntToCharTranslater.h \
		-include $(CHAR_OPS)\CharOperator.h \
		-include $(FILE_OPRS)\Cpp_FileOperations.h
