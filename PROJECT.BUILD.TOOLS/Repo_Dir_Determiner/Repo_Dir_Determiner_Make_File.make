
DIR_OPS=D:\pcynlitx.build\BASIC.TOOLS\DirectoryOperations
STRING_OPS=D:\pcynlitx.build\BASIC.TOOLS\StringOperator
CHAR_OPS=D:\pcynlitx.build\BASIC.TOOLS\CharOperator
FILE_OPRS=D:\pcynlitx.build\BASIC.TOOLS\Cpp_FileOperations

VPATH = $(DIR_OPS) $(STRING_OPS) $(CHAR_OPS) $(FILE_OPRS)

Repo_Dir_Determiner.exe: Repo_Dir_Determiner_Main_File.cpp Repo_Dir_Determiner.cpp \
	DirectoryOperations.cpp StringOperator.cpp Cpp_FileOperations.cpp CharOperator.cpp \
	Repo_Dir_Determiner.h DirectoryOperations.h StringOperator.h CharOperator.h Cpp_FileOperations.h

	g++ -std=c++17 -o Repo_Dir_Determiner.exe -I$(DIR_OPS) -I$(STRING_OPS) -I$(CHAR_OPS) -I$(FILE_OPRS) \
	 -L$(DIR_OPS) -L$(STRING_OPS) -L$(CHAR_OPS) -L$(FILE_OPRS) \
		Repo_Dir_Determiner_Main_File.cpp Repo_Dir_Determiner.cpp \
		$(DIR_OPS)\DirectoryOperations.cpp  $(STRING_OPS)\StringOperator.cpp \
		$(CHAR_OPS)\CharOperator.cpp $(FILE_OPRS)\Cpp_FileOperations.cpp \
		-include Repo_Dir_Determiner.h -include $(DIR_OPS)\DirectoryOperations.h \
		-include $(STRING_OPS)\StringOperator.h -include $(CHAR_OPS)\CharOperator.h \
		-include $(FILE_OPRS)\Cpp_FileOperations.h
