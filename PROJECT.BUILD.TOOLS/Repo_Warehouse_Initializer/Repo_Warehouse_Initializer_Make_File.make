

DIR_LIST=D:\pcynlitx.build\PROJECT.BUILD.TOOLS\Project_Directory_Lister
DIR_ENUM=D:\pcynlitx.build\PROJECT.BUILD.TOOLS\Directory_Enumerator
DIR_TREE=D:\pcynlitx.build\PROJECT.BUILD.TOOLS\Directory_Tree_Size_Determiner
DIR_OPS=D:\pcynlitx.build\BASIC.TOOLS\DirectoryOperations
STRING_OPS=D:\pcynlitx.build\BASIC.TOOLS\StringOperator
CHAR_OPS=D:\pcynlitx.build\BASIC.TOOLS\CharOperator
FILE_OPRS=D:\pcynlitx.build\BASIC.TOOLS\Cpp_FileOperations

VPATH = $(DIR_LIST) $(DIR_ENUM) $(DIR_TREE) $(DIR_OPS) $(STRING_OPS) $(CHAR_OPS) $(FILE_OPRS)

Repo_Warehouse_Initializer.exe: Repo_Warehouse_Initializer_Main_File.cpp Repo_Warehouse_Initializer.cpp \
	Project_Directory_Lister.cpp Directory_Enumerator.cpp \
	Directory_Tree_Size_Determiner.cpp StringOperator.cpp \
	Cpp_FileOperations.cpp CharOperator.cpp Repo_Warehouse_Initializer.h \
	Project_Directory_Lister.h Directory_Enumerator.h \
	StringOperator.h DirectoryOperations.h \
	CharOperator.h Cpp_FileOperations.h

	g++ -std=c++17 -o Repo_Warehouse_Initializer.exe -I$(DIR_LIST) -I$(DIR_ENUM) \
	 -I$(DIR_TREE) -I$(DIR_OPS) -I$(STRING_OPS) -I$(CHAR_OPS) -I$(FILE_OPRS) \
	 -L$(DIR_LIST) -L$(DIR_ENUM) -L$(REPO_DET) -L$(DIR_TREE) -L$(DIR_OPS) \
	 -L$(STRING_OPS) -L$(CHAR_OPS) -L$(FILE_OPRS) \
		Repo_Warehouse_Initializer_Main_File.cpp Repo_Warehouse_Initializer.cpp $(DIR_LIST)\Project_Directory_Lister.cpp \
		$(DIR_ENUM)\Directory_Enumerator.cpp $(DIR_TREE)\Directory_Tree_Size_Determiner.cpp  \
		$(DIR_OPS)\DirectoryOperations.cpp $(STRING_OPS)\StringOperator.cpp \
		$(CHAR_OPS)\CharOperator.cpp $(FILE_OPRS)\Cpp_FileOperations.cpp \
		-include Repo_Warehouse_Initializer.h -include $(DIR_LIST)\Project_Directory_Lister.h \
		-include $(DIR_ENUM)\Directory_Enumerator.h \
		-include $(DIR_TREE)\Directory_Tree_Size_Determiner.h \
		-include $(STRING_OPS)\StringOperator.h -include $(DIR_OPS)\DirectoryOperations.h \
		-include $(CHAR_OPS)\CharOperator.h -include $(FILE_OPRS)\Cpp_FileOperations.h
