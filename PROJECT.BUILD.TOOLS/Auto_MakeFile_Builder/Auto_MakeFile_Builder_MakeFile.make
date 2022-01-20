
DIR_LIST=D:\pcynlitx.build\PROJECT.BUILD.TOOLS\Project_Files_Lister
DIR_ENUM=D:\pcynlitx.build\PROJECT.BUILD.TOOLS\Directory_Enumerator
REPO_DET=D:\pcynlitx.build\PROJECT.BUILD.TOOLS\Repo_Dir_Determiner
DIR_TREE=D:\pcynlitx.build\PROJECT.BUILD.TOOLS\Directory_Tree_Size_Determiner
MAKE_BLD=D:\pcynlitx.build\PROJECT.BUILD.TOOLS\Make_File_Builder
HEAD_DETER=D:\pcynlitx.build\PROJECT.BUILD.TOOLS\Header_File_Determiner
STRING_OPS=D:\pcynlitx.build\BASIC.TOOLS\StringOperator
DIR_OPS=D:\pcynlitx.build\BASIC.TOOLS\DirectoryOperations
STRING_OPS=D:\pcynlitx.build\BASIC.TOOLS\StringOperator
CHAR_OPS=D:\pcynlitx.build\BASIC.TOOLS\CharOperator
FILE_OPRS=D:\pcynlitx.build\BASIC.TOOLS\Cpp_FileOperations
CLASS_NAME=D:\pcynlitx.build\BASIC.TOOLS\ClassNameReader
CLASS_SYNTAX=D:\pcynlitx.build\BASIC.TOOLS\ClassSyntaxControl


VPATH = $(DIR_LIST) $(DIR_ENUM) $(REPO_DET) $(DIR_TREE) $(DIR_OPS) \
$(STRING_OPS) $(CHAR_OPS) $(FILE_OPRS) $(MAKE_BLD) $(CLASS_NAME) $(CLASS_SYNTAX) $(HEAD_DETER)

Auto_MakeFile_Builder.exe: Auto_MakeFile_Builder_Main_File.cpp Auto_MakeFile_Builder.cpp \
	Project_Files_Lister.cpp Header_File_Determiner.cpp Directory_Enumerator.cpp Repo_Dir_Determiner.cpp \
	Directory_Tree_Size_Determiner.cpp Make_File_Builder.cpp ClassNameReader.cpp \
	ClassSyntaxControl.cpp StringOperator.cpp \
	Cpp_FileOperations.cpp CharOperator.cpp Auto_MakeFile_Builder.h \
	Project_Files_Lister.h Header_File_Determiner.h Directory_Enumerator.h \
	Repo_Dir_Determiner.h Make_File_Builder.h ClassNameReader.h ClassSyntaxControl.h StringOperator.h \
	DirectoryOperations.h CharOperator.h Cpp_FileOperations.h

	g++ -std=c++17 -o Auto_MakeFile_Builder.exe -I$(DIR_LIST) -I$(MAKE_BLD) -I$(DIR_ENUM) \
	 -I$(REPO_DET) -I$(DIR_TREE) -I$(DIR_OPS) -I$(STRING_OPS) -I$(HEAD_DETER) \
   -I$(CHAR_OPS) -I$(FILE_OPRS) -I$(CLASS_NAME) -I$(CLASS_SYNTAX) \
	 -L$(DIR_LIST) -L$(MAKE_BLD) -L$(DIR_ENUM) -L$(REPO_DET) -L$(DIR_TREE) -L$(DIR_OPS) \
	 -L$(STRING_OPS) -L$(CHAR_OPS) -L$(FILE_OPRS) -L$(CLASS_NAME) -L$(CLASS_SYNTAX) -L$(HEAD_DETER) \
		Auto_MakeFile_Builder_Main_File.cpp Auto_MakeFile_Builder.cpp $(DIR_LIST)\Project_Files_Lister.cpp \
		$(HEAD_DETER)\Header_File_Determiner.cpp $(MAKE_BLD)\Make_File_Builder.cpp \
		$(DIR_ENUM)\Directory_Enumerator.cpp $(REPO_DET)\Repo_Dir_Determiner.cpp \
		$(DIR_TREE)\Directory_Tree_Size_Determiner.cpp $(CLASS_NAME)\ClassNameReader.cpp \
		$(CLASS_SYNTAX)\ClassSyntaxControl.cpp $(DIR_OPS)\DirectoryOperations.cpp $(STRING_OPS)\StringOperator.cpp \
		$(CHAR_OPS)\CharOperator.cpp $(FILE_OPRS)\Cpp_FileOperations.cpp \
		-include Auto_MakeFile_Builder.h -include $(DIR_LIST)\Project_Files_Lister.h \
		-include $(HEAD_DETER)\Header_File_Determiner.h -include $(DIR_ENUM)\Directory_Enumerator.h \
		-include $(REPO_DET)\Repo_Dir_Determiner.h -include $(DIR_TREE)\Directory_Tree_Size_Determiner.h \
		-include $(CLASS_NAME)\ClassNameReader.h -include $(CLASS_SYNTAX)\ClassSyntaxControl.h \
		-include $(STRING_OPS)\StringOperator.h -include $(DIR_OPS)\DirectoryOperations.h \
		-include $(CHAR_OPS)\CharOperator.h -include $(FILE_OPRS)\Cpp_FileOperations.h
