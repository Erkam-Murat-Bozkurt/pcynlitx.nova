
# The start of the basic tools path declerations
CLASS_NM=D:\pcynlitx.build\BASIC.TOOLS\ClassNameReader
CLASS_SY=D:\pcynlitx.build\BASIC.TOOLS\ClassSyntaxControl
DIR_OPS=D:\pcynlitx.build\BASIC.TOOLS\DirectoryOperations
STRING_OPS=D:\pcynlitx.build\BASIC.TOOLS\StringOperator
CHAR_OPS=D:\pcynlitx.build\BASIC.TOOLS\CharOperator
FILE_OPRS=D:\pcynlitx.build\BASIC.TOOLS\Cpp_FileOperations
TRANSLATER=D:\pcynlitx.build\BASIC.TOOLS\IntToCharTranslater


# The start of the script writer path declerations
PRJ_SCR_WRIT=D:\pcynlitx.build\SCRIPT.WRITERS\Project_Script_Writer
SCR_DATA_COL=D:\pcynlitx.build\SCRIPT.WRITERS\Script_Data_Collector
SRC_FLT_WRIT=D:\pcynlitx.build\SCRIPT.WRITERS\Source_File_Script_Writer
INC_DEP_CNT=D:\pcynlitx.build\SCRIPT.WRITERS\Include_Dependency_Counter


# The start of the warehouse manipulators path declerations
REPO_INI=D:\pcynlitx.build\PROJECT.BUILD.TOOLS\Repo_Warehouse_Initializer
DIR_ENUM=D:\pcynlitx.build\PROJECT.BUILD.TOOLS\Directory_Enumerator
DIR_TREE=D:\pcynlitx.build\PROJECT.BUILD.TOOLS\Directory_Tree_Size_Determiner
GIT_REC=D:\pcynlitx.build\PROJECT.BUILD.TOOLS\Git_File_List_Receiver

# The start of the description processign systm path declerations
DES_DAT_COL=D:\pcynlitx.build\DESCRIPTION.PROCESSING.SYSTEM\Descriptor_File_Data_Collector
DES_READ=D:\pcynlitx.build\DESCRIPTION.PROCESSING.SYSTEM\Descriptor_File_Reader

# The start of the make file build system classes path declerations
AUTO_MAK=D:\pcynlitx.build\MAKE.FILE.BUILD.SYSTEM\Auto_MakeFile_Builder
MAKE_BLD=D:\pcynlitx.build\MAKE.FILE.BUILD.SYSTEM\Make_File_Builder
MAKE_DAT=D:\pcynlitx.build\MAKE.FILE.BUILD.SYSTEM\MakeFile_Data_Collector
MK_FLN_CLN=D:\pcynlitx.build\MAKE.FILE.BUILD.SYSTEM\Make_File_Cleaner

# The start of the source file information collectors path declerations
DIR_LIST=D:\pcynlitx.build\SOURCE.FILE.DATA.COLLECTORS\Project_Files_Lister
SRC_DAT_COL=D:\pcynlitx.build\SOURCE.FILE.DATA.COLLECTORS\Source_File_Data_Collector
HEAD_FILE_DET=D:\pcynlitx.build\SOURCE.FILE.DATA.COLLECTORS\Header_File_Determiner
SOURCE_FILE_DET=D:\pcynlitx.build\SOURCE.FILE.DATA.COLLECTORS\Source_File_Determiner
PRO_FILE_DAT_COL=D:\pcynlitx.build\SOURCE.FILE.DATA.COLLECTORS\Project_Files_Data_Collector



VPATH = $(DIR_LIST) $(DIR_ENUM) $(DIR_TREE) $(DIR_OPS) \
				$(STRING_OPS) $(CHAR_OPS) $(FILE_OPRS) $(GIT_REC) \
				$(PRJ_SCR_WRIT) $(SCR_DATA_COL)	$(SRC_FLT_WRIT)	$(INC_DEP_CNT) \
				$(REPO_INI) $(AUTO_MAK) $(MAKE_BLD) $(CLASS_NM) \
				$(CLASS_SY) $(DES_DAT_COL) $(SRC_DAT_COL) $(PRO_FILE_DAT_COL) \
				$(DES_READ) $(HEAD_FILE_DET) $(SOURCE_FILE_DET) $(MAKE_DAT) \
				$(TRANSLATER) $(MK_FLN_CLN)

Build_Tools_Initializer.exe: Build_Tools_Initializer_Main_File.cpp Build_Tools_Initializer.cpp \
	Project_Script_Writer.cpp Script_Data_Collector.cpp \
	Source_File_Script_Writer.cpp Include_Dependency_Counter.cpp \
	Auto_MakeFile_Builder.cpp Repo_Warehouse_Initializer.cpp \
	Descriptor_File_Reader.cpp Descriptor_File_Data_Collector.cpp Project_Files_Lister.cpp \
	Source_File_Data_Collector.cpp Git_File_List_Receiver.cpp Directory_Enumerator.cpp \
	Directory_Tree_Size_Determiner.cpp Project_Files_Data_Collector.cpp \
	Make_File_Builder.cpp MakeFile_Data_Collector.cpp Make_File_Cleaner.cpp StringOperator.cpp \
	Cpp_FileOperations.cpp CharOperator.cpp IntToCharTranslater.cpp \
	Build_Tools_Initializer.h Auto_MakeFile_Builder.h \
	Repo_Warehouse_Initializer.h \
	Project_Script_Writer.h Script_Data_Collector.hpp \
	Source_File_Script_Writer.hpp Include_Dependency_Counter.hpp \
	Descriptor_File_Reader.hpp Descriptor_File_Data_Collector.hpp \
	Project_Files_Lister.h Source_File_Data_Collector.cpp Git_File_List_Receiver.hpp \
	Directory_Enumerator.h Make_File_Builder.h Make_File_Cleaner.hpp \
	Project_Files_Data_Collector.hpp MakeFile_Data_Collector.hpp \
	StringOperator.h DirectoryOperations.h \
	CharOperator.h Cpp_FileOperations.h IntToCharTranslater.h

	g++ -std=c++17 -o Build_Tools_Initializer.exe \
	 -I$(DIR_LIST) -I$(DIR_ENUM) \
	 -I$(DIR_TREE) -I$(DIR_OPS)  \
	 -I$(STRING_OPS) -I$(CHAR_OPS) \
	 -I$(PRJ_SCR_WRIT) -I$(SCR_DATA_COL) \
	 -I$(SRC_FLT_WRIT) -I$(INC_DEP_CNT) \
	 -I$(REPO_INI) -I$(AUTO_MAK) \
	 -I$(MAKE_BLD) -I$(CLASS_NM) -I$(CLASS_SY) \
	 -I$(DES_READ) -I$(DES_DAT_COL) \
	 -I$(HEAD_FILE_DET) -I$(SOURCE_FILE_DET) \
	 -I$(MAKE_DAT) -I$(GIT_REC) -I$(SRC_DAT_COL) \
	 -I$(PRO_FILE_DAT_COL) -I$(TRANSLATER) \
	 -I$(MK_FLN_CLN) -I$(FILE_OPRS) \
	 -L$(DIR_LIST) -L$(DIR_ENUM) -L$(REPO_DET) \
	 -L$(DIR_TREE) -L$(DIR_OPS) \
	 -L$(STRING_OPS) -L$(CHAR_OPS) \
	 -L$(FILE_OPRS) -L$(MAKE_BLD) -L$(MAKE_DAT) \
	 -L$(REPO_INI) -L$(AUTO_MAK) \
	 -L$(CLASS_NM) -L$(CLASS_SY) \
	 -L$(DES_READ) -L$(DES_DAT_COL) \
	 -L$(HEAD_FILE_DET) -L$(SOURCE_FILE_DET) \
	 -L$(GIT_REC) -L$(SRC_DAT_COL) \
	 -L$(PRO_FILE_DAT_COL) -L$(TRANSLATER) \
	 -L$(MK_FLN_CLN) \
	 -L$(PRJ_SCR_WRIT) -L$(SCR_DATA_COL) \
	 -L$(SRC_FLT_WRIT) -L$(INC_DEP_CNT) \
		Build_Tools_Initializer_Main_File.cpp \
		Build_Tools_Initializer.cpp \
		$(AUTO_MAK)\Auto_MakeFile_Builder.cpp \
		$(PRJ_SCR_WRIT)\Project_Script_Writer.cpp \
		$(SCR_DATA_COL)\Script_Data_Collector.cpp \
		$(SRC_FLT_WRIT)\Source_File_Script_Writer.cpp \
		$(INC_DEP_CNT)\Include_Dependency_Counter.cpp \
		$(REPO_INI)\Repo_Warehouse_Initializer.cpp \
		$(DIR_LIST)\Project_Files_Lister.cpp \
		$(SRC_DAT_COL)\Source_File_Data_Collector.cpp \
		$(GIT_REC)\Git_File_List_Receiver.cpp \
		$(DES_READ)\Descriptor_File_Reader.cpp \
		$(DES_DAT_COL)\Descriptor_File_Data_Collector.cpp \
		$(HEAD_FILE_DET)\Header_File_Determiner.cpp \
		$(SOURCE_FILE_DET)\Source_File_Determiner.cpp \
		$(DIR_ENUM)\Directory_Enumerator.cpp \
		$(DIR_TREE)\Directory_Tree_Size_Determiner.cpp  \
		$(DIR_OPS)\DirectoryOperations.cpp \
		$(MAKE_BLD)\Make_File_Builder.cpp \
		$(MAKE_DAT)\MakeFile_Data_Collector.cpp \
		$(MK_FLN_CLN)\Make_File_Cleaner.cpp \
		$(PRO_FILE_DAT_COL)\Project_Files_Data_Collector.cpp \
		$(STRING_OPS)\StringOperator.cpp \
		$(TRANSLATER)\IntToCharTranslater.cpp \
		$(CHAR_OPS)\CharOperator.cpp \
		$(FILE_OPRS)\Cpp_FileOperations.cpp \
		-include Build_Tools_Initializer.h \
		-include $(AUTO_MAK)\Auto_MakeFile_Builder.h \
		-include $(PRJ_SCR_WRIT)\Project_Script_Writer.h \
		-include $(SCR_DATA_COL)\Script_Data_Collector.hpp \
		-include $(SRC_FLT_WRIT)\Source_File_Script_Writer.hpp \
		-include $(INC_DEP_CNT)\Include_Dependency_Counter.hpp \
		-include $(REPO_INI)\Repo_Warehouse_Initializer.h \
		-include $(DIR_LIST)\Project_Files_Lister.h \
		-include $(SRC_DAT_COL)\Source_File_Data_Collector.hpp \
		-include $(GIT_REC)\Git_File_List_Receiver.hpp \
		-include $(DES_READ)\Descriptor_File_Reader.hpp \
		-include $(DES_DAT_COL)\Descriptor_File_Data_Collector.hpp \
		-include $(DIR_ENUM)\Directory_Enumerator.h \
		-include $(DIR_TREE)\Directory_Tree_Size_Determiner.h\
 		-include $(MAKE_BLD)\Make_File_Builder.h \
		-include $(MAKE_DAT)\MakeFile_Data_Collector.hpp \
		-include $(MK_FLN_CLN)\Make_File_Cleaner.hpp \
		-include $(HEAD_FILE_DET)\Header_File_Determiner.h \
		-include $(SOURCE_FILE_DET)\Source_File_Determiner.h \
		-include $(PRO_FILE_DAT_COL)\Project_Files_Data_Collector.hpp \
		-include $(STRING_OPS)\StringOperator.h \
		-include $(DIR_OPS)\DirectoryOperations.h \
		-include $(CHAR_OPS)\CharOperator.h \
		-include $(TRANSLATER)\IntToCharTranslater.h \
		-include $(FILE_OPRS)\Cpp_FileOperations.h
