


CPP_OPS=D:\pcynlitx.build\BASIC.TOOLS\Cpp_FileOperations
STRING_OPS=D:\pcynlitx.build\BASIC.TOOLS\StringOperator
CHAR_OPS=D:\pcynlitx.build\BASIC.TOOLS\CharOperator


VPATH = $(CPP_OPS) $(STRING_OPS) $(CHAR_OPS)

Descriptor_File_Syntax_Controller.exe: Descriptor_File_Syntax_Controller_Main_File.cpp \
	Descriptor_File_Syntax_Controller.cpp Descriptor_File_Syntax_Controller.hpp \
	StringOperator.cpp CharOperator.cpp Cpp_FileOperations.cpp \
  StringOperator.h CharOperator.h Cpp_FileOperations.h

	g++ -std=c++17 -o Descriptor_File_Syntax_Controller.exe -I$(CPP_OPS) -I$(STRING_OPS) \
	  -I$(CHAR_OPS) -L$(CPP_OPS) -L$(STRING_OPS) -L$(CHAR_OPS) \
		Descriptor_File_Syntax_Controller_Main_File.cpp Descriptor_File_Syntax_Controller.cpp \
	  $(STRING_OPS)\StringOperator.cpp $(CHAR_OPS)\CharOperator.cpp \
		$(CPP_OPS)\Cpp_FileOperations.cpp \
		-include Descriptor_File_Syntax_Controller.hpp -include $(STRING_OPS)\StringOperator.h \
		-include $(CHAR_OPS)\CharOperator.h -include $(CPP_OPS)\Cpp_FileOperations.h
