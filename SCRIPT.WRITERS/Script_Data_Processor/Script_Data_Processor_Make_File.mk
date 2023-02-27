DIR_ENUM=D:\pcynlitx.build\PROJECT.BUILD.TOOLS\Directory_Enumerator
REPO_DET=D:\pcynlitx.build\PROJECT.BUILD.TOOLS\Repo_Dir_Determiner
DIR_TREE=D:\pcynlitx.build\PROJECT.BUILD.TOOLS\Directory_Tree_Size_Determiner
INT_CHAR=D:\pcynlitx.build\BASIC.TOOLS\IntToCharTranslater
STRING_OPS=D:\pcynlitx.build\BASIC.TOOLS\StringOperator
DIR_OPS=D:\pcynlitx.build\BASIC.TOOLS\DirectoryOperations
STRING_OPS=D:\pcynlitx.build\BASIC.TOOLS\StringOperator
CHAR_OPS=D:\pcynlitx.build\BASIC.TOOLS\CharOperator
FILE_OPRS=D:\pcynlitx.build\BASIC.TOOLS\Cpp_FileOperations
NAME_READER=D:\pcynlitx.build\BASIC.TOOLS\ClassNameReader
SYNTAX_READER=D:\pcynlitx.build\BASIC.TOOLS\ClassSyntaxControl
HEADER_DET=D:\pcynlitx.build\SOURCE.FILE.DATA.COLLECTORS\Header_File_Determiner
SOURCE_DETR=D:\pcynlitx.build\SOURCE.FILE.DATA.COLLECTORS\Source_File_Determiner
SRC_DAT_COL=D:\pcynlitx.build\SOURCE.FILE.DATA.COLLECTORS\Source_File_Data_Collector
DIR_LIST=D:\pcynlitx.build\SOURCE.FILE.DATA.COLLECTORS\Project_Files_Lister
PRO_FILES_DAT_COL=D:\pcynlitx.build\SOURCE.FILE.DATA.COLLECTORS\Project_Files_Data_Collector
DESCR_READ=D:\pcynlitx.build\DESCRIPTION.PROCESSING.SYSTEM\Description.Readers\Descriptor.File.Reader
DESCR_DAT_COL=D:\pcynlitx.build\DESCRIPTION.PROCESSING.SYSTEM\Description.Readers\Descriptor.File.Data.Collector
DESCR_SYNT_COL=D:\pcynlitx.build\DESCRIPTION.PROCESSING.SYSTEM\Description.Readers\Descriptor.File.Syntax.Controller
GIT_REC=D:\pcynlitx.build\PROJECT.BUILD.TOOLS\Git_File_List_Receiver
SCRIPT_DAT=D:\pcynlitx.build\SCRIPT.WRITERS\Script_Data_Collector
SRC_SCRIPT_WRT=D:\pcynlitx.build\SCRIPT.WRITERS\Source_File_Script_Writer
DEP_CNTR=D:\pcynlitx.build\SCRIPT.WRITERS\Include_Dependency_Counter
SRC_INF_CL=D:\pcynlitx.build\SOURCE.FILE.PROCESSING.SYSTEM\Source_File_Information_Collector
SRC_DEP_SL=D:\pcynlitx.build\SOURCE.FILE.PROCESSING.SYSTEM\Source_File_Dependency_Selector
SRC_DEP_DT=D:\pcynlitx.build\SOURCE.FILE.PROCESSING.SYSTEM\Source_File_Dependency_Determiner


VPATH = $(DIR_LIST) $(REPO_DET) $(DIR_ENUM) $(DIR_TREE) \
				$(DIR_OPS) $(STRING_OPS) $(CHAR_OPS) $(FILE_OPRS) \
				$(NAME_READER) $(SYNTAX_READER) $(DESCR_READ) $(SRC_DAT_COL) \
				$(HEADER_DET) $(SOURCE_DETR) $(DESCR_DAT_COL) \
				$(GIT_REC) $(SRC_DAT_COL) $(PRO_FILES_DAT_COL) \
				$(SCRIPT_DAT) $(SRC_SCRIPT_WRT) $(INT_CHAR) $(DEP_CNTR) \
				$(DESCR_SYNT_COL) $(SRC_DEP_DT) $(SRC_DEP_SL) $(SRC_INF_CL)


Script_Data_Processor.exe: Script_Data_Processor_Main_File.cpp \
	Script_Data_Processor.cpp \
	Source_File_Script_Writer.cpp \
	Source_File_Dependency_Determiner.cpp \
	Source_File_Dependency_Selector.cpp \
	Source_File_Information_Collector.cpp \
	Script_Data_Collector.cpp \
	Include_Dependency_Counter.cpp \
	Project_Files_Lister.cpp \
	Project_Files_Data_Collector.cpp \
	Git_File_List_Receiver.cpp \
	Descriptor_File_Reader.cpp \
	Descriptor_File_Data_Collector.cpp \
	Descriptor_File_Syntax_Controller.cpp \
	Header_File_Determiner.cpp \
	Source_File_Determiner.cpp \
	Repo_Dir_Determiner.cpp \
	Directory_Enumerator.cpp \
	Directory_Enumerator.cpp \
	Directory_Tree_Size_Determiner.cpp \
	ClassNameReader.cpp \
	ClassSyntaxControl.cpp \
	StringOperator.cpp \
  Cpp_FileOperations.cpp \
	CharOperator.cpp \
	IntToCharTranslater.cpp \
	Script_Data_Processor.hpp \
	Source_File_Script_Writer.hpp \
	Script_Data_Collector.hpp \
	Include_Dependency_Counter.hpp \
	Source_File_Dependency_Determiner.hpp \
	Source_File_Dependency_Selector.hpp \
	Source_File_Information_Collector.hpp \
	Project_Files_Lister.h \
	Project_Files_Data_Collector.hpp \
	Git_File_List_Receiver.hpp \
	Descriptor_File_Reader.hpp  \
	Descriptor_File_Data_Collector.hpp \
	Source_File_Determiner.h \
	Header_File_Determiner.h \
	Repo_Dir_Determiner.h \
	Directory_Enumerator.h \
	ClassNameReader.h \
	ClassSyntaxControl.h \
	StringOperator.h  \
	DirectoryOperations.h \
	CharOperator.h \
	IntToCharTranslater.h \
	Cpp_FileOperations.h

	g++ -std=c++17 -g -o Script_Data_Processor.exe \
	 -I$(DIR_LIST) -I$(DIR_ENUM) \
	 -I$(REPO_DET) -I$(SOURCE_DETR) \
	 -I$(DIR_TREE) -I$(DIR_OPS) \
	 -I$(STRING_OPS) -I$(CHAR_OPS) \
	 -I$(FILE_OPRS) -I$(NAME_READER) \
	 -I$(DESCR_READ) -I$(DESCR_DAT_COL) \
	 -I$(SYNTAX_READER) -I$(GIT_REC) \
	 -I$(SRC_DAT_COL) -I$(SRC_SCRIPT_WRT) \
	 -I$(SCRIPT_DAT) -I$(HEADER_DET) \
	 -I$(PRO_FILES_DAT_COL) -I$(INT_CHAR) \
	 -I$(DEP_CNTR) -I$(DESCR_SYNT_COL) \
	 -I$(SRC_DEP_DT) -I$(SRC_DEP_SL) -I$(SRC_INF_CL) \
	 -L$(DIR_LIST) -L$(DIR_ENUM) \
	 -L$(DESCR_READ) -L$(DESCR_DAT_COL) \
	 -L$(PRO_FILES_DAT_COL) -L$(REPO_DET) \
	 -L$(DIR_TREE) -L$(DIR_OPS) \
	 -L$(STRING_OPS) -L$(CHAR_OPS) -L$(FILE_OPRS) \
	 -L$(NAME_READER) -L$(SYNTAX_READER) \
	 -L$(HEADER_DET) -L$(SOURCE_DETR) \
	 -L$(GIT_REC) -L$(SRC_SCRIPT_WRT) \
	 -L$(SRC_DAT_COL) -L$(INT_CHAR) \
	 -L$(DEP_CNTR) -L$(DESCR_SYNT_COL) \
	 -L$(SRC_DEP_DT) -L$(SRC_DEP_SL) -L$(SRC_INF_CL) \
		Script_Data_Processor_Main_File.cpp \
		Script_Data_Processor.cpp \
		$(SRC_SCRIPT_WRT)\Source_File_Script_Writer.cpp \
		$(SCRIPT_DAT)\Script_Data_Collector.cpp \
		$(SRC_DEP_DT)\Source_File_Dependency_Determiner.cpp \
		$(SRC_DEP_SL)\Source_File_Dependency_Selector.cpp \
		$(SRC_INF_CL)\Source_File_Information_Collector.cpp \
		$(DIR_LIST)\Project_Files_Lister.cpp \
		$(PRO_FILES_DAT_COL)\Project_Files_Data_Collector.cpp \
		$(SRC_DAT_COL)\Source_File_Data_Collector.cpp \
		$(DEP_CNTR)\Include_Dependency_Counter.cpp \
		$(GIT_REC)\Git_File_List_Receiver.cpp \
		$(DESCR_READ)\Descriptor_File_Reader.cpp \
		$(DESCR_DAT_COL)\Descriptor_File_Data_Collector.cpp \
		$(DESCR_SYNT_COL)\Descriptor_File_Syntax_Controller.cpp \
		$(SOURCE_DETR)\Source_File_Determiner.cpp \
		$(HEADER_DET)\Header_File_Determiner.cpp \
		$(REPO_DET)\Repo_Dir_Determiner.cpp \
		$(DIR_ENUM)\Directory_Enumerator.cpp \
		$(DIR_TREE)\Directory_Tree_Size_Determiner.cpp \
		$(NAME_READER)\ClassNameReader.cpp \
		$(SYNTAX_READER)\ClassSyntaxControl.cpp \
		$(DIR_OPS)\DirectoryOperations.cpp \
		$(STRING_OPS)\StringOperator.cpp \
		$(CHAR_OPS)\CharOperator.cpp \
		$(FILE_OPRS)\Cpp_FileOperations.cpp \
		$(INT_CHAR)\IntToCharTranslater.cpp \
		-include Script_Data_Processor.hpp \
		-include $(SRC_SCRIPT_WRT)\Source_File_Script_Writer.hpp \
		-include $(SCRIPT_DAT)\Script_Data_Collector.hpp \
		-include $(DEP_CNTR)\Include_Dependency_Counter.hpp \
		-include $(SRC_DEP_DT)\Source_File_Dependency_Determiner.hpp \
		-include $(SRC_DEP_SL)\Source_File_Dependency_Selector.hpp \
		-include $(SRC_INF_CL)\Source_File_Information_Collector.hpp \
		-include $(DIR_LIST)\Project_Files_Lister.h \
		-include $(PRO_FILES_DAT_COL)\Project_Files_Data_Collector.hpp \
		-include $(SRC_DAT_COL)\Source_File_Data_Collector.hpp \
		-include $(GIT_REC)\Git_File_List_Receiver.hpp \
		-include $(DESCR_READ)\Descriptor_File_Reader.hpp \
		-include $(DESCR_DAT_COL)\Descriptor_File_Data_Collector.hpp \
		-include $(DESCR_SYNT_COL)\Descriptor_File_Syntax_Controller.hpp \
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
		-include $(INT_CHAR)\IntToCharTranslater.h \
		-include $(FILE_OPRS)\Cpp_FileOperations.h
