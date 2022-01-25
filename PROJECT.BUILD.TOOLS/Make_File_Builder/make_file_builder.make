
STRING_OPS=D:\pcynlitx.build\BASIC.TOOLS\StringOperator
DIR_OPS=D:\pcynlitx.build\BASIC.TOOLS\DirectoryOperations
CPP_OPS=D:\pcynlitx.build\BASIC.TOOLS\Cpp_FileOperations
CHAR_OPS=D:\pcynlitx.build\BASIC.TOOLS\CharOperator
CLASS_NAME=D:\pcynlitx.build\BASIC.TOOLS\ClassNameReader
CLASS_SYNTAX=D:\pcynlitx.build\BASIC.TOOLS\ClassSyntaxControl
DIR_ENUM=D:\pcynlitx.build\PROJECT.BUILD.TOOLS\Directory_Enumerator
HEAD_DET=D:\pcynlitx.build\PROJECT.BUILD.TOOLS\Header_File_Determiner
FILE_LISTER=D:\pcynlitx.build\PROJECT.BUILD.TOOLS\Project_Files_Lister
SOURCE_DETR=D:\pcynlitx.build\PROJECT.BUILD.TOOLS\Source_File_Determiner


VPATH = $(DIR_OPS) $(CPP_OPS) $(CHAR_OPS) $(CLASS_NAME) $(SOURCE_DETR) \
				$(CLASS_SYNTAX) $(DIR_ENUM) $(STRING_OPS) $(HEAD_DET) $(FILE_LISTER)

Make_File_Builder.exe: Make_File_Builder_Main_File.cpp Make_File_Builder.cpp \
	Project_Files_Lister.cpp Source_File_Determiner.cpp Header_File_Determiner.cpp \
	Directory_Enumerator.cpp ClassNameReader.cpp \
	ClassSyntaxControl.cpp DirectoryOperations.cpp \
	CharOperator.cpp Cpp_FileOperations.cpp Make_File_Builder.h Project_Files_Lister.h \
	Source_File_Determiner.h Header_File_Determiner.h Directory_Enumerator.h \
	DirectoryOperations.h CharOperator.h Cpp_FileOperations.h

	g++ -std=c++17 -g -o Make_File_Builder.exe -I$(DIR_OPS) -I$(CPP_OPS) -I$(CHAR_OPS) \
	 -I$(CLASS_NAME) -I$(STRING_OPS) -I$(HEAD_DET) -I$(FILE_LISTER) -I$(SOURCE_DETR) \
	 -I$(CLASS_SYNTAX) -I$(DIR_ENUM) -L$(DIR_ENUM) -L$(DIR_OPS) -L$(CPP_OPS) -L$(CHAR_OPS) \
	 -L$(CLASS_NAME) -L$(CLASS_SYNTAX) -L$(STRING_OPS) -L$(HEAD_DET) -L$(FILE_LISTER) -L$(SOURCE_DETR) \
		Make_File_Builder_Main_File.cpp Make_File_Builder.cpp $(FILE_LISTER)\Project_Files_Lister.cpp \
		$(SOURCE_DETR)\Source_File_Determiner.cpp $(DIR_ENUM)\Directory_Enumerator.cpp \
		$(HEAD_DET)\Header_File_Determiner.cpp \
		$(CLASS_NAME)\ClassNameReader.cpp \
		$(CLASS_SYNTAX)\ClassSyntaxControl.cpp \
		$(DIR_OPS)\DirectoryOperations.cpp $(STRING_OPS)\StringOperator.cpp \
		$(CHAR_OPS)\CharOperator.cpp $(CPP_OPS)\Cpp_FileOperations.cpp \
		-include Make_File_Builder.h -include $(FILE_LISTER)\Project_Files_Lister.h \
		-include $(SOURCE_DETR)\Source_File_Determiner.h \
		-include $(DIR_ENUM)\Directory_Enumerator.h \
		-include $(HEAD_DET)\Header_File_Determiner.h \
		-include $(CLASS_NAME)\ClassNameReader.h \
		-include $(CLASS_SYNTAX)\ClassSyntaxControl.h \
		-include $(STRING_OPS)\StringOperator.h -include $(DIR_OPS)\DirectoryOperations.h \
	  -include $(CHAR_OPS)\CharOperator.h -include $(CPP_OPS)\Cpp_FileOperations.h
