

DIR_ENUM=D:\pcynlitx.build\PROJECT.BUILD.TOOLS\Directory_Enumerator
STRING_OPS=D:\pcynlitx.build\BASIC.TOOLS\StringOperator
DIR_OPS=D:\pcynlitx.build\BASIC.TOOLS\DirectoryOperations
CHAR_OPS=D:\pcynlitx.build\BASIC.TOOLS\CharOperator
FILE_OPRS=D:\pcynlitx.build\BASIC.TOOLS\Cpp_FileOperations

VPATH = $(DIR_ENUM) $(DIR_OPS) $(STRING_OPS) $(CHAR_OPS) $(FILE_OPRS)

Directory_Tree_Size_Determiner.exe: Directory_Tree_Size_Determiner_Main_File.cpp Directory_Tree_Size_Determiner.cpp \
	Directory_Tree_Size_Determiner.cpp Directory_Enumerator.cpp StringOperator.cpp DirectoryOperations.cpp \
	Cpp_FileOperations.cpp CharOperator.cpp Directory_Tree_Size_Determiner.h Directory_Enumerator.h \
	StringOperator.h DirectoryOperations.h CharOperator.h Cpp_FileOperations.h

	g++ -std=c++17 -o Directory_Tree_Size_Determiner.exe -I$(DIR_ENUM) -I$(REPO_DET) \
	 -I$(DIR_OPS) -I$(STRING_OPS) -I$(CHAR_OPS) -I$(FILE_OPRS) \
	 -L$(DIR_ENUM) -L$(REPO_DET) -L$(DIR_OPS) -L$(STRING_OPS) -L$(CHAR_OPS) -L$(FILE_OPRS) \
		Directory_Tree_Size_Determiner_Main_File.cpp Directory_Tree_Size_Determiner.cpp \
		$(DIR_ENUM)\Directory_Enumerator.cpp \
		$(DIR_OPS)\DirectoryOperations.cpp $(STRING_OPS)\StringOperator.cpp \
		$(CHAR_OPS)\CharOperator.cpp $(FILE_OPRS)\Cpp_FileOperations.cpp \
		-include Directory_Tree_Size_Determiner.h -include $(DIR_ENUM)\Directory_Enumerator.h \
		-include $(STRING_OPS)\StringOperator.h -include $(DIR_OPS)\DirectoryOperations.h \
		-include $(CHAR_OPS)\CharOperator.h -include $(FILE_OPRS)\Cpp_FileOperations.h
