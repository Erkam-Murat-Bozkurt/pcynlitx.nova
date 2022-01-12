
STRING_OPS=D:\pcynlitx.build\BASIC.TOOLS\StringOperator
DIR_OPS=D:\pcynlitx.build\BASIC.TOOLS\DirectoryOperations
CPP_OPS=D:pcynlitx.build\BASIC.TOOLS\Cpp_FileOperations
CHAR_OPS=D:\pcynlitx.build\BASIC.TOOLS\CharOperator
CLASS_NAME=D:\pcynlitx.build\BASIC.TOOLS\ClassNameReader
CLASS_SYNTAX=D:\pcynlitx.build\BASIC.TOOLS\ClassSyntaxControl
DIR_ENUM=D:\pcynlitx.build\PROJECT.BUILD.TOOLS\Directory_Enumerator


VPATH = $(DIR_OPS) $(CPP_OPS) $(CHAR_OPS) $(CLASS_NAME) $(CLASS_SYNTAX) $(DIR_ENUM) $(STRING_OPS)

Make_File_Builder.exe: Make_File_Builder_Main_File.cpp Make_File_Builder.cpp \
	Directory_Enumerator.cpp ClassNameReader.cpp ClassSyntaxControl.cpp DirectoryOperations.cpp \
	Cpp_FileOperations.cpp CharOperator.cpp Make_File_Builder.h Directory_Enumerator.h  \
	DirectoryOperations.h Cpp_FileOperations.h CharOperator.h

	g++ -std=c++17 -o Make_File_Builder.exe -I$(DIR_OPS) -I$(CPP_OPS) -I$(CHAR_OPS) -I$(CLASS_NAME) -I$(STRING_OPS) \
	 -I$(CLASS_SYNTAX) -I$(DIR_ENUM) -L$(DIR_ENUM) -L$(DIR_OPS) -L$(CPP_OPS) -L$(CHAR_OPS) \
	 -L$(CLASS_NAME) -L$(CLASS_SYNTAX) -L$(STRING_OPS) \
		Make_File_Builder_Main_File.cpp Make_File_Builder.cpp $(DIR_ENUM)\Directory_Enumerator.cpp \
		$(CLASS_NAME)\ClassNameReader.cpp $(CLASS_SYNTAX)\ClassSyntaxControl.cpp \
		$(DIR_OPS)\DirectoryOperations.cpp $(STRING_OPS)\StringOperator.cpp \
		$(CPP_OPS)\Cpp_FileOperations.cpp $(CHAR_OPS)\CharOperator.cpp \
		-include Make_File_Builder.h -include $(DIR_ENUM)\Directory_Enumerator.h \
		-include $(CLASS_NAME)\ClassNameReader.h -include $(CLASS_SYNTAX)\ClassSyntaxControl.h \
		-include $(STRING_OPS)\StringOperator.h -include $(DIR_OPS)\DirectoryOperations.h \
	  -include $(CHAR_OPS)\CharOperator.h -include $(CPP_OPS)\Cpp_FileOperations.h
