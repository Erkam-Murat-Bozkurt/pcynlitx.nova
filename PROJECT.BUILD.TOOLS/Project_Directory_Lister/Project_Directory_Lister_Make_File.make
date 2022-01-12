
DIR_ENUM=D:\pcynlitx.build\PROJECT.BUILD.TOOLS\Directory_Enumerator
REPO_DET=D:\pcynlitx.build\PROJECT.BUILD.TOOLS\Repo_Dir_Determiner
DIR_TREE=D:\pcynlitx.build\PROJECT.BUILD.TOOLS\Directory_Tree_Size_Determiner
STRING_OPS=D:\pcynlitx.build\BASIC.TOOLS\StringOperator
DIR_OPS=D:\pcynlitx.build\BASIC.TOOLS\DirectoryOperations
STRING_OPS=D:\pcynlitx.build\BASIC.TOOLS\StringOperator
CHAR_OPS=D:\pcynlitx.build\BASIC.TOOLS\CharOperator
FILE_OPRS=D:\pcynlitx.build\BASIC.TOOLS\Cpp_FileOperations

VPATH = $(DIR_ENUM) $(REPO_DET) $(DIR_TREE) $(DIR_OPS) $(STRING_OPS) $(CHAR_OPS) $(FILE_OPRS)

Project_Directory_Lister.exe: Project_Directory_Lister_Main_File.cpp Project_Directory_Lister.cpp \
	Directory_Enumerator.cpp Repo_Dir_Determiner.cpp Directory_Tree_Size_Determiner.cpp StringOperator.cpp \
	Cpp_FileOperations.cpp CharOperator.cpp Project_Directory_Lister.h Directory_Enumerator.h \
	Repo_Dir_Determiner.h StringOperator.h DirectoryOperations.h \
	CharOperator.h Cpp_FileOperations.h

	g++ -std=c++17 -o Project_Directory_Lister.exe -I$(DIR_ENUM) -I$(REPO_DET) -I$(DIR_TREE) \
	 -I$(DIR_OPS) -I$(STRING_OPS) -I$(CHAR_OPS) -I$(FILE_OPRS) \
	 -L$(DIR_ENUM) -L$(REPO_DET) -L$(DIR_TREE) -L$(DIR_OPS) -L$(STRING_OPS) -L$(CHAR_OPS) -L$(FILE_OPRS) \
		Project_Directory_Lister_Main_File.cpp Project_Directory_Lister.cpp \
		$(DIR_ENUM)\Directory_Enumerator.cpp $(REPO_DET)\Repo_Dir_Determiner.cpp \
		$(DIR_TREE)\Directory_Tree_Size_Determiner.cpp \
		$(DIR_OPS)\DirectoryOperations.cpp $(STRING_OPS)\StringOperator.cpp \
		$(CHAR_OPS)\CharOperator.cpp $(FILE_OPRS)\Cpp_FileOperations.cpp \
		-include Project_Directory_Lister.h -include $(DIR_ENUM)\Directory_Enumerator.h \
		-include $(REPO_DET)\Repo_Dir_Determiner.h -include $(DIR_TREE)\Directory_Tree_Size_Determiner.h \
		-include $(STRING_OPS)\StringOperator.h -include $(DIR_OPS)\DirectoryOperations.h \
		-include $(CHAR_OPS)\CharOperator.h -include $(FILE_OPRS)\Cpp_FileOperations.h
