

STRING_OPS=D:\pcynlitx.build\BASIC.TOOLS\StringOperator
DIR_OPS=D:\pcynlitx.build\BASIC.TOOLS\DirectoryOperations
CHAR_OPS=D:\pcynlitx.build\BASIC.TOOLS\CharOperator
FILE_OPRS=D:\pcynlitx.build\BASIC.TOOLS\Cpp_FileOperations

VPATH = $(DIR_OPS) $(STRING_OPS) $(CHAR_OPS) $(FILE_OPRS)

Header_File_Determiner.exe: Header_File_Determiner_Main_File.cpp Header_File_Determiner.cpp \
	StringOperator.cpp CharOperator.cpp Cpp_FileOperations.cpp Header_File_Determiner.h \
	StringOperator.h CharOperator.h Cpp_FileOperations.h

	g++ -std=c++17 -o Header_File_Determiner.exe \
	  -I$(STRING_OPS) -I$(CHAR_OPS) -I$(FILE_OPRS) \
	  -L$(STRING_OPS) -L$(CHAR_OPS) -L$(FILE_OPRS) \
		Header_File_Determiner_Main_File.cpp Header_File_Determiner.cpp \
		$(STRING_OPS)\StringOperator.cpp \
		$(CHAR_OPS)\CharOperator.cpp $(FILE_OPRS)\Cpp_FileOperations.cpp \
		-include Header_File_Determiner.h \
		-include $(STRING_OPS)\StringOperator.h \
		-include $(CHAR_OPS)\CharOperator.h -include $(FILE_OPRS)\Cpp_FileOperations.h
