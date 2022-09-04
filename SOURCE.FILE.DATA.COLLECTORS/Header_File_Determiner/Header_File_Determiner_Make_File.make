

STRING_OPS=D:\pcynlitx.build\BASIC.TOOLS\StringOperator
DIR_OPS=D:\pcynlitx.build\BASIC.TOOLS\DirectoryOperations
CHAR_OPS=D:\pcynlitx.build\BASIC.TOOLS\CharOperator
FILE_OPRS=D:\pcynlitx.build\BASIC.TOOLS\Cpp_FileOperations
GIT_LIST=D:\pcynlitx.build\PROJECT.BUILD.TOOLS\Git_File_List_Receiver
DES_READ=D:\pcynlitx.build\DESCRIPTION.PROCESSING.SYSTEM\Description.Readers\Descriptor.File.Reader
DES_DATA_COL=D:\pcynlitx.build\DESCRIPTION.PROCESSING.SYSTEM\Description.Readers\Descriptor.File.Data.Collector
DES_SYN_CON=D:\pcynlitx.build\DESCRIPTION.PROCESSING.SYSTEM\Description.Readers\Descriptor.File.Syntax.Controller

VPATH = $(DIR_OPS) $(STRING_OPS) $(CHAR_OPS) $(FILE_OPRS) \
	      $(GIT_LIST) $(DES_READ) $(DES_DATA_COL) $(DES_SYN_CON)

Header_File_Determiner.exe: Header_File_Determiner_Main_File.cpp Header_File_Determiner.cpp \
	Descriptor_File_Reader.cpp Descriptor_File_Data_Collector.cpp Git_File_List_Receiver.cpp \
	StringOperator.cpp CharOperator.cpp Cpp_FileOperations.cpp Header_File_Determiner.h \
	Git_File_List_Receiver.hpp StringOperator.h CharOperator.h Cpp_FileOperations.h

	g++ -std=c++17 -o Header_File_Determiner.exe \
	  -I$(STRING_OPS) -I$(CHAR_OPS) -I$(FILE_OPRS) -I$(DES_READ) \
		-I$(DES_DATA_COL) -I$(GIT_LIST) -I$(DIR_OPS) -I$(DES_SYN_CON) \
	  -L$(STRING_OPS) -L$(CHAR_OPS) -L$(FILE_OPRS) -L$(DES_READ) \
		-L$(DES_DATA_COL) -L$(GIT_LIST) -L$(DIR_OPS) -L$(DES_SYN_CON) \
		Header_File_Determiner_Main_File.cpp Header_File_Determiner.cpp \
		$(GIT_LIST)\Git_File_List_Receiver.cpp \
		$(DES_READ)\Descriptor_File_Reader.cpp $(DES_DATA_COL)\Descriptor_File_Data_Collector.cpp \
		$(DES_SYN_CON)\Descriptor_File_Syntax_Controller.cpp \
		$(STRING_OPS)\StringOperator.cpp \
		$(DIR_OPS)\DirectoryOperations.cpp \
		$(CHAR_OPS)\CharOperator.cpp $(FILE_OPRS)\Cpp_FileOperations.cpp \
		-include Header_File_Determiner.h \
		-include $(GIT_LIST)\Git_File_List_Receiver.hpp \
		-include $(DES_READ)\Descriptor_File_Reader.hpp \
		-include $(DES_DATA_COL)\Descriptor_File_Data_Collector.hpp \
		-include $(DES_SYN_CON)\Descriptor_File_Syntax_Controller.hpp \
		-include $(GIT_LIST)\Git_File_List_Receiver.hpp \
		-include $(DIR_OPS)\DirectoryOperations.h \
		-include $(STRING_OPS)\StringOperator.h \
		-include $(CHAR_OPS)\CharOperator.h \
		-include $(FILE_OPRS)\Cpp_FileOperations.h
