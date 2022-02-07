
DES_DAT_COL=D:\pcynlitx.build\DESCRIPTION.PROCESSING.SYSTEM\Descriptor_File_Data_Collector
DES_READ=D:\pcynlitx.build\DESCRIPTION.PROCESSING.SYSTEM\Descriptor_File_Reader
SCR_WRIT=D:\pcynlitx.build\PROJECT.BUILD.TOOLS\Compiler_Script_Writer
REPO_INI=D:\pcynlitx.build\PROJECT.BUILD.TOOLS\Repo_Warehouse_Initializer
AUTO_MAK=D:\pcynlitx.build\PROJECT.BUILD.TOOLS\Auto_MakeFile_Builder
DIR_LIST=D:\pcynlitx.build\PROJECT.BUILD.TOOLS\Project_Files_Lister
DIR_ENUM=D:\pcynlitx.build\PROJECT.BUILD.TOOLS\Directory_Enumerator
DIR_TREE=D:\pcynlitx.build\PROJECT.BUILD.TOOLS\Directory_Tree_Size_Determiner
MAKE_BLD=D:\pcynlitx.build\PROJECT.BUILD.TOOLS\Make_File_Builder
HEAD_FILE_DET=D:\pcynlitx.build\PROJECT.BUILD.TOOLS\Header_File_Determiner
SOURCE_FILE_DET=D:\pcynlitx.build\PROJECT.BUILD.TOOLS\Source_File_Determiner
CLASS_NM=D:\pcynlitx.build\BASIC.TOOLS\ClassNameReader
CLASS_SY=D:\pcynlitx.build\BASIC.TOOLS\ClassSyntaxControl
DIR_OPS=D:\pcynlitx.build\BASIC.TOOLS\DirectoryOperations
STRING_OPS=D:\pcynlitx.build\BASIC.TOOLS\StringOperator
CHAR_OPS=D:\pcynlitx.build\BASIC.TOOLS\CharOperator
FILE_OPRS=D:\pcynlitx.build\BASIC.TOOLS\Cpp_FileOperations

VPATH = $(DIR_LIST) $(DIR_ENUM) $(DIR_TREE) $(DIR_OPS) $(STRING_OPS) $(CHAR_OPS) $(FILE_OPRS) \
				$(SCR_WRIT) $(REPO_INI) $(AUTO_MAK) $(MAKE_BLD) $(CLASS_NM) $(CLASS_SY) $(DES_DAT_COL) \
				$(DES_READ) $(HEAD_FILE_DET) $(SOURCE_FILE_DET)

Build_Tools_Initializer.exe: Build_Tools_Initializer_Main_File.cpp Build_Tools_Initializer.cpp \
	Auto_MakeFile_Builder.cpp Compiler_Script_Writer.cpp Repo_Warehouse_Initializer.cpp \
	Descriptor_File_Reader.cpp Descriptor_File_Data_Collector.cpp Project_Files_Lister.cpp \
	Directory_Enumerator.cpp Directory_Tree_Size_Determiner.cpp \
	Make_File_Builder.cpp StringOperator.cpp Cpp_FileOperations.cpp CharOperator.cpp \
	Build_Tools_Initializer.h Auto_MakeFile_Builder.h \
	Compiler_Script_Writer.h Repo_Warehouse_Initializer.h \
	Descriptor_File_Reader.hpp Descriptor_File_Data_Collector.hpp \
	Project_Files_Lister.h Directory_Enumerator.h Make_File_Builder.h \
	StringOperator.h DirectoryOperations.h \
	CharOperator.h Cpp_FileOperations.h

	g++ -std=c++17 -o Build_Tools_Initializer.exe -I$(DIR_LIST) -I$(DIR_ENUM) \
	 -I$(DIR_TREE) -I$(DIR_OPS) -I$(STRING_OPS) -I$(CHAR_OPS) -I$(FILE_OPRS) \
	 -I$(SCR_WRIT) -I$(REPO_INI) -I$(AUTO_MAK) -I$(MAKE_BLD) -I$(CLASS_NM) -I$(CLASS_SY) \
	 -I$(DES_READ) -I$(DES_DAT_COL) -I$(HEAD_FILE_DET) -I$(SOURCE_FILE_DET) \
	 -L$(DIR_LIST) -L$(DIR_ENUM) -L$(REPO_DET) -L$(DIR_TREE) -L$(DIR_OPS) \
	 -L$(STRING_OPS) -L$(CHAR_OPS) -L$(FILE_OPRS) -L$(MAKE_BLD) \
	 -L$(SCR_WRIT) -L$(REPO_INI) -L$(AUTO_MAK) -L$(CLASS_NM) -L$(CLASS_SY) \
	 -L$(DES_READ) -L$(DES_DAT_COL) -L$(HEAD_FILE_DET) -L$(SOURCE_FILE_DET)\
		Build_Tools_Initializer_Main_File.cpp Build_Tools_Initializer.cpp \
		$(AUTO_MAK)\Auto_MakeFile_Builder.cpp $(SCR_WRIT)\Compiler_Script_Writer.cpp \
		$(REPO_INI)\Repo_Warehouse_Initializer.cpp $(DIR_LIST)\Project_Files_Lister.cpp \
		$(DES_READ)\Descriptor_File_Reader.cpp $(DES_DAT_COL)\Descriptor_File_Data_Collector.cpp \
		$(HEAD_FILE_DET)\Header_File_Determiner.cpp $(SOURCE_FILE_DET)\Source_File_Determiner.cpp \
		$(DIR_ENUM)\Directory_Enumerator.cpp $(DIR_TREE)\Directory_Tree_Size_Determiner.cpp  \
		$(DIR_OPS)\DirectoryOperations.cpp $(MAKE_BLD)\Make_File_Builder.cpp \
		$(STRING_OPS)\StringOperator.cpp \
		$(CHAR_OPS)\CharOperator.cpp $(FILE_OPRS)\Cpp_FileOperations.cpp \
		-include Build_Tools_Initializer.h -include $(AUTO_MAK)\Auto_MakeFile_Builder.h \
		-include $(SCR_WRIT)\Compiler_Script_Writer.h \
		-include $(REPO_INI)\Repo_Warehouse_Initializer.h -include $(DIR_LIST)\Project_Files_Lister.h \
		-include $(DES_READ)\Descriptor_File_Reader.hpp -include $(DES_DAT_COL)\Descriptor_File_Data_Collector.hpp \
		-include $(DIR_ENUM)\Directory_Enumerator.h -include $(DIR_TREE)\Directory_Tree_Size_Determiner.h\
 		-include $(MAKE_BLD)\Make_File_Builder.h -include $(HEAD_FILE_DET)\Header_File_Determiner.h \
		-include $(SOURCE_FILE_DET)\Source_File_Determiner.h \
		-include $(STRING_OPS)\StringOperator.h -include $(DIR_OPS)\DirectoryOperations.h \
		-include $(CHAR_OPS)\CharOperator.h -include $(FILE_OPRS)\Cpp_FileOperations.h
