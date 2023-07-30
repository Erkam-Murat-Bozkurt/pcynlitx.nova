

SYS_INT=D:\pcynlitx.build\BASIC.TOOLS\Custom_System_Interface
INT_TRANS=D:\pcynlitx.build\BASIC.TOOLS\IntToCharTranslater
STRING_OPS=D:\pcynlitx.build\BASIC.TOOLS\StringOperator
DIR_OPS=D:\pcynlitx.build\BASIC.TOOLS\DirectoryOperations
CHAR_OPS=D:\pcynlitx.build\BASIC.TOOLS\CharOperator
FILE_OPRS=D:\pcynlitx.build\BASIC.TOOLS\Cpp_FileOperations
DES_READ=D:\pcynlitx.build\DESCRIPTION.PROCESSING.SYSTEM\Description.Readers\Descriptor.File.Reader
DES_DATA_COL=D:\pcynlitx.build\DESCRIPTION.PROCESSING.SYSTEM\Description.Readers\Descriptor.File.Data.Collector
DES_SYN_CON=D:\pcynlitx.build\DESCRIPTION.PROCESSING.SYSTEM\Description.Readers\Descriptor.File.Syntax.Controller
GIT_LIST=D:\pcynlitx.build\GIT.DATA.PROCESSING.SYSTEM\Git_Modification_Lister


VPATH = $(DIR_OPS) $(STRING_OPS) $(CHAR_OPS) $(FILE_OPRS) \
				$(DES_READ) $(DES_DATA_COL) \
				$(GIT_LIST) $(DES_SYN_CON) \
				$(INT_TRANS) $(SYS_INT)


Git_FiGit_Modification_Listerle_List_Receiver.exe: Git_Modification_Lister_Main_File.cpp \
	Git_Modification_Lister.cpp  \
	Descriptor_File_Reader.cpp \
	Descriptor_File_Data_Collector.cpp \
	Descriptor_File_Syntax_Controller.cpp \
	StringOperator.cpp \
	CharOperator.cpp \
	IntToCharTranslater.cpp \
	Cpp_FileOperations.cpp \
	Custom_System_Interface.cpp \
	Git_Modification_Lister.hpp \
	Descriptor_File_Reader.hpp \
	Descriptor_File_Data_Collector.hpp \
	Descriptor_File_Syntax_Controller.hpp \
	StringOperator.h \
	DirectoryOperations.h \
	CharOperator.h \
	IntToCharTranslater.h \
	Cpp_FileOperations.h \
	Custom_System_Interface.h

	g++ -std=c++17 -static-libgcc -static-libstdc++ -ggdb -o Git_Modification_Lister.exe \
	 -I. \
	 -I$(DIR_OPS) \
	 -I$(STRING_OPS) \
	 -I$(CHAR_OPS) \
	 -I$(FILE_OPRS) \
	 -I$(CHAR_OPS) \
	 -I$(DES_READ) \
	 -I$(DES_DATA_COL) \
	 -I$(GIT_LIST) \
	 -I$(DES_SYN_CON) \
	 -I$(INT_TRANS) \
	 -I$(SYS_INT) \
	 -L$(DIR_OPS) \
	 -L$(STRING_OPS) \
	 -L$(GIT_LIST) \
	 -L$(CHAR_OPS) \
	 -L$(FILE_OPRS) \
	 -L$(DES_READ) \
	 -L$(DES_DATA_COL) \
	 -L$(DES_SYN_CON) \
	 -L$(INT_TRANS) \
	 -L$(SYS_INT) \
		Git_Modification_Lister_Main_File.cpp \
		Git_Modification_Lister.cpp \
		$(DES_READ)\Descriptor_File_Reader.cpp \
		$(DES_DATA_COL)\Descriptor_File_Data_Collector.cpp \
		$(DES_SYN_CON)\Descriptor_File_Syntax_Controller.cpp \
		$(DIR_OPS)\DirectoryOperations.cpp \
		$(STRING_OPS)\StringOperator.cpp \
		$(CHAR_OPS)\CharOperator.cpp \
		$(INT_TRANS)\IntToCharTranslater.cpp \
		$(FILE_OPRS)\Cpp_FileOperations.cpp \
		$(SYS_INT)\Custom_System_Interface.cpp \
		-include Git_Modification_Lister.hpp \
		-include $(DES_READ)\Descriptor_File_Reader.hpp \
		-include $(DES_DATA_COL)\Descriptor_File_Data_Collector.hpp \
		-include $(DES_SYN_CON)\Descriptor_File_Syntax_Controller.hpp \
		-include $(STRING_OPS)\StringOperator.h \
		-include $(DIR_OPS)\DirectoryOperations.h \
		-include $(CHAR_OPS)\CharOperator.h \
		-include $(INT_TRANS)\IntToCharTranslater.h \
		-include $(FILE_OPRS)\Cpp_FileOperations.h \
		-include $(SYS_INT)\Custom_System_Interface.h \
