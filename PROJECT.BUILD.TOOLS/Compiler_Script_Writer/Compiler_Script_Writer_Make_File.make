
DIR_LIST=D:\pcynlitx.build\PROJECT.BUILD.TOOLS\Project_Files_Lister
DIR_ENUM=D:\pcynlitx.build\PROJECT.BUILD.TOOLS\Directory_Enumerator
REPO_DET=D:\pcynlitx.build\PROJECT.BUILD.TOOLS\Repo_Dir_Determiner
DIR_TREE=D:\pcynlitx.build\PROJECT.BUILD.TOOLS\Directory_Tree_Size_Determiner
STRING_OPS=D:\pcynlitx.build\BASIC.TOOLS\StringOperator
DIR_OPS=D:\pcynlitx.build\BASIC.TOOLS\DirectoryOperations
STRING_OPS=D:\pcynlitx.build\BASIC.TOOLS\StringOperator
CHAR_OPS=D:\pcynlitx.build\BASIC.TOOLS\CharOperator
FILE_OPRS=D:\pcynlitx.build\BASIC.TOOLS\Cpp_FileOperations
NAME_READER=D:\pcynlitx.build\BASIC.TOOLS\ClassNameReader
SYNTAX_READER=D:\pcynlitx.build\BASIC.TOOLS\ClassSyntaxControl
HEADER_DET=D:\pcynlitx.build\PROJECT.BUILD.TOOLS\Header_File_Determiner
SOURCE_DETR=D:\pcynlitx.build\PROJECT.BUILD.TOOLS\Source_File_Determiner
SRC_DAT_COL=D:\pcynlitx.build\PROJECT.BUILD.TOOLS\Source_File_Data_Collector
SRC_DAT_COL=D:\pcynlitx.build\PROJECT.BUILD.TOOLS\Source_File_Data_Collector
PRO_FILES_DAT_COL=D:\pcynlitx.build\PROJECT.BUILD.TOOLS\Project_Files_Data_Collector
DESCR_READ=D:\pcynlitx.build\DESCRIPTION.PROCESSING.SYSTEM\Descriptor_File_Reader
DESCR_DAT_COL=D:\pcynlitx.build\DESCRIPTION.PROCESSING.SYSTEM\Descriptor_File_Data_Collector
GIT_REC=D:\pcynlitx.build\PROJECT.BUILD.TOOLS\Git_File_List_Receiver


VPATH = $(DIR_LIST) $(REPO_DET) $(DIR_ENUM) $(DIR_TREE) \
				$(DIR_OPS) $(STRING_OPS) $(CHAR_OPS) $(FILE_OPRS) \
				$(NAME_READER) $(SYNTAX_READER) $(DESCR_READ) $(SRC_DAT_COL) \
				$(HEADER_DET) $(SOURCE_DETR) $(DESCR_DAT_COL) \
				$(GIT_REC) $(SRC_DAT_COL) $(PRO_FILES_DAT_COL)

Compiler_Script_Writer.exe: Compiler_Script_Writer_Main_File.cpp Compiler_Script_Writer.cpp \
	Project_Files_Lister.cpp Project_Files_Data_Collector.cpp \
	Git_File_List_Receiver.cpp Descriptor_File_Reader.cpp Descriptor_File_Data_Collector.cpp \
	Header_File_Determiner.cpp Source_File_Determiner.cpp \
	Repo_Dir_Determiner.cpp Directory_Enumerator.cpp \
	Directory_Enumerator.cpp Directory_Tree_Size_Determiner.cpp \
	ClassNameReader.cpp ClassSyntaxControl.cpp StringOperator.cpp \
  Cpp_FileOperations.cpp CharOperator.cpp Project_Files_Lister.h \
	Project_Files_Data_Collector.hpp \
	Git_File_List_Receiver.hpp Descriptor_File_Reader.hpp  \
	Descriptor_File_Data_Collector.hpp Source_File_Determiner.h \
	Header_File_Determiner.h Repo_Dir_Determiner.h \
	Directory_Enumerator.h ClassNameReader.h ClassSyntaxControl.h StringOperator.h  \
	DirectoryOperations.h CharOperator.h Cpp_FileOperations.h

	g++ -std=c++17 -o Compiler_Script_Writer.exe -I$(DIR_LIST) -I$(DIR_ENUM) \
	 -I$(REPO_DET) -I$(SOURCE_DETR) -I$(DIR_TREE) -I$(DIR_OPS) \
	 -I$(STRING_OPS) -I$(CHAR_OPS) -I$(FILE_OPRS) -I$(NAME_READER) \
	 -I$(DESCR_READ) -I$(DESCR_DAT_COL) -I$(SYNTAX_READER) -I$(GIT_REC) -I$(SRC_DAT_COL) \
	 -I$(HEADER_DET) -I$(PRO_FILES_DAT_COL) -L$(DIR_LIST) \
	 -L$(DIR_ENUM) -L$(DESCR_READ) -L$(DESCR_DAT_COL) -L$(PRO_FILES_DAT_COL) \
	 -L$(REPO_DET) -L$(DIR_TREE) -L$(DIR_OPS) -L$(STRING_OPS) -L$(CHAR_OPS) -L$(FILE_OPRS) \
	 -L$(NAME_READER) -L$(SYNTAX_READER) -L$(HEADER_DET) -L$(SOURCE_DETR) -L$(GIT_REC) \
		Compiler_Script_Writer_Main_File.cpp Compiler_Script_Writer.cpp \
		$(DIR_LIST)\Project_Files_Lister.cpp $(PRO_FILES_DAT_COL)\Project_Files_Data_Collector.cpp \
		$(SRC_DAT_COL)\Source_File_Data_Collector.cpp \
		$(GIT_REC)\Git_File_List_Receiver.cpp \
		$(DESCR_READ)\Descriptor_File_Reader.cpp \
		$(DESCR_DAT_COL)\Descriptor_File_Data_Collector.cpp \
		$(SOURCE_DETR)\Source_File_Determiner.cpp \
		$(HEADER_DET)\Header_File_Determiner.cpp \
		$(REPO_DET)\Repo_Dir_Determiner.cpp $(DIR_ENUM)\Directory_Enumerator.cpp \
		$(DIR_TREE)\Directory_Tree_Size_Determiner.cpp \
		$(NAME_READER)\ClassNameReader.cpp $(SYNTAX_READER)\ClassSyntaxControl.cpp \
		$(DIR_OPS)\DirectoryOperations.cpp $(STRING_OPS)\StringOperator.cpp \
		$(CHAR_OPS)\CharOperator.cpp $(FILE_OPRS)\Cpp_FileOperations.cpp \
		-include Compiler_Script_Writer.h -include $(DIR_LIST)\Project_Files_Lister.h \
		-include $(PRO_FILES_DAT_COL)\Project_Files_Data_Collector.hpp \
		-include $(SRC_DAT_COL)\Source_File_Data_Collector.hpp \
		-include $(GIT_REC)\Git_File_List_Receiver.hpp \
		-include $(DESCR_READ)\Descriptor_File_Reader.hpp \
		-include $(DESCR_DAT_COL)\Descriptor_File_Data_Collector.hpp \
		-include $(SOURCE_DETR)\Source_File_Determiner.h \
		-include $(HEADER_DET)\Header_File_Determiner.h \
		-include $(REPO_DET)\Repo_Dir_Determiner.h \
		-include $(DIR_ENUM)\Directory_Enumerator.h \
		-include $(DIR_TREE)\Directory_Tree_Size_Determiner.h \
		-include $(NAME_READER)\ClassNameReader.h \
		-include $(SYNTAX_READER)\ClassSyntaxControl.h \
		-include $(STRING_OPS)\StringOperator.h \
	  -include $(DIR_OPS)\DirectoryOperations.h \
		-include $(CHAR_OPS)\CharOperator.h \
		-include $(FILE_OPRS)\Cpp_FileOperations.h
