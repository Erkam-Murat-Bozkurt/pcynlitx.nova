
DIR_ENUM=D:\pcynlitx.build\PROJECT.BUILD.TOOLS\Directory_Enumerator
STRING_OPS=D:\pcynlitx.build\BASIC.TOOLS\StringOperator
DIR_OPS=D:\pcynlitx.build\BASIC.TOOLS\DirectoryOperations
STRING_OPS=D:\pcynlitx.build\BASIC.TOOLS\StringOperator
CHAR_OPS=D:\pcynlitx.build\BASIC.TOOLS\CharOperator
FILE_OPRS=D:\pcynlitx.build\BASIC.TOOLS\Cpp_FileOperations
HEAD_DETR=D:\pcynlitx.build\PROJECT.BUILD.TOOLS\Header_File_Determiner
SOURCE_DETR=D:\pcynlitx.build\PROJECT.BUILD.TOOLS\Source_File_Determiner

VPATH = $(DIR_OPS) $(STRING_OPS) $(CHAR_OPS) $(FILE_OPRS) $(HEAD_DETR) $(SOURCE_DETR)

Project_Files_Lister.exe: Project_Files_Lister_Main_File.cpp Project_Files_Lister.cpp  \
	Source_File_Determiner.cpp Header_File_Determiner.cpp StringOperator.cpp \
	Cpp_FileOperations.cpp CharOperator.cpp Project_Files_Lister.h Source_File_Determiner.h \
	Header_File_Determiner.h StringOperator.h DirectoryOperations.h \
	CharOperator.h Cpp_FileOperations.h

	g++ -std=c++17 -o Project_Files_Lister.exe \
	 -I$(HEAD_DETR) -I$(SOURCE_DETR) -I$(DIR_OPS) -I$(STRING_OPS) -I$(CHAR_OPS) -I$(FILE_OPRS) \
	 -L$(HEAD_DETR) -L$(SOURCE_DETR) -L$(DIR_OPS) -L$(STRING_OPS) -L$(CHAR_OPS) -L$(FILE_OPRS) \
		Project_Files_Lister_Main_File.cpp Project_Files_Lister.cpp \
		$(SOURCE_DETR)\Source_File_Determiner.cpp $(HEAD_DETR)\Header_File_Determiner.cpp \
		$(DIR_ENUM)\Directory_Enumerator.cpp \
		$(DIR_OPS)\DirectoryOperations.cpp $(STRING_OPS)\StringOperator.cpp \
		$(CHAR_OPS)\CharOperator.cpp $(FILE_OPRS)\Cpp_FileOperations.cpp \
		-include Project_Files_Lister.h -include $(SOURCE_DETR)\Source_File_Determiner.h \
		-include $(HEAD_DETR)\Header_File_Determiner.h \
		-include $(STRING_OPS)\StringOperator.h -include $(DIR_OPS)\DirectoryOperations.h \
		-include $(CHAR_OPS)\CharOperator.h -include $(FILE_OPRS)\Cpp_FileOperations.h
