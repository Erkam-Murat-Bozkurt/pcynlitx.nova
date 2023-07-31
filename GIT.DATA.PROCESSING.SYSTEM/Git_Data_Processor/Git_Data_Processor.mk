
SYS_INT=D:\pcynlitx.build\BASIC.TOOLS\Custom_System_Interface
INT_TRANS=D:\pcynlitx.build\BASIC.TOOLS\IntToCharTranslater
STRING_OPS=D:\pcynlitx.build\BASIC.TOOLS\StringOperator
DIR_OPS=D:\pcynlitx.build\BASIC.TOOLS\DirectoryOperations
CHAR_OPS=D:\pcynlitx.build\BASIC.TOOLS\CharOperator
FILE_OPRS=D:\pcynlitx.build\BASIC.TOOLS\Cpp_FileOperations
DES_READ=D:\pcynlitx.build\DESCRIPTION.PROCESSING.SYSTEM\Description.Readers\Descriptor.File.Reader
DES_DATA_COL=D:\pcynlitx.build\DESCRIPTION.PROCESSING.SYSTEM\Description.Readers\Descriptor.File.Data.Collector
DES_SYN_CON=D:\pcynlitx.build\DESCRIPTION.PROCESSING.SYSTEM\Description.Readers\Descriptor.File.Syntax.Controller
GIT_LIST=D:\pcynlitx.build\GIT.DATA.PROCESSING.SYSTEM\Git_File_List_Writer
GIT_REC=D:\pcynlitx.build\GIT.DATA.PROCESSING.SYSTEM\Git_File_List_Receiver
GIT_IGN=D:\pcynlitx.build\GIT.DATA.PROCESSING.SYSTEM\Git_Ignoring_Files_Lister
GIT_MOD_LST=D:\pcynlitx.build\GIT.DATA.PROCESSING.SYSTEM\Git_Modification_Lister
GIT_MOD_RCV=D:\pcynlitx.build\GIT.DATA.PROCESSING.SYSTEM\Git_Modification_Receiver
HEAD_DET=D:\pcynlitx.build\SOURCE.FILE.DATA.COLLECTORS\Header_File_Determiner
SRC_DET=D:\pcynlitx.build\SOURCE.FILE.DATA.COLLECTORS\Source_File_Determiner

VPATH = $(DIR_OPS)     $(STRING_OPS)   $(CHAR_OPS)  $(FILE_OPRS) \
		$(DES_READ)    $(DES_DATA_COL) $(GIT_LIST)  $(DES_SYN_CON) \
		$(GIT_LIST)    $(GIT_REC)      $(GIT_IGN)   $(GIT_MOD_LST) \
		$(GIT_MOD_RCV) $(INT_TRANS)    $(SYS_INT)   $(HEAD_DET) \
		$(SRC_DET)     $(SYS_INT)

Git_Data_Processor.exe: Git_Data_Processor_Main_File.cpp \
    Git_Data_Processor.cpp \
	Git_File_List_Writer.cpp  \
	Git_File_List_Receiver.cpp \
	Git_Modification_Lister.cpp \
	Git_Modification_Receiver.cpp \
	Git_Ignoring_Files_Lister.cpp \
	Source_File_Determiner.cpp \
	Header_File_Determiner.cpp \
	Descriptor_File_Reader.cpp \
	Descriptor_File_Data_Collector.cpp \
	Descriptor_File_Syntax_Controller.cpp \
	StringOperator.cpp \
	CharOperator.cpp \
	IntToCharTranslater.cpp \
	Cpp_FileOperations.cpp \
	Custom_System_Interface.cpp \
	Git_Data_Processor.hpp \
	Git_File_List_Writer.hpp  \
	Git_File_List_Receiver.hpp \
	Git_Modification_Lister.hpp \
	Git_Modification_Receiver.hpp \
	Git_Ignoring_Files_Lister.hpp \
	Source_File_Determiner.h \
	Header_File_Determiner.h \
	Descriptor_File_Reader.hpp \
	Descriptor_File_Data_Collector.hpp \
	Descriptor_File_Syntax_Controller.hpp \
	StringOperator.h \
	DirectoryOperations.h \
	CharOperator.h \
	IntToCharTranslater.h \
	Cpp_FileOperations.h \
	Custom_System_Interface.h

	g++ -std=c++17 -static-libgcc -static-libstdc++ -ggdb -o Git_File_List_Writer.exe \
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
	 -I$(GIT_LIST) \
	 -I$(GIT_REC) \
	 -I$(GIT_IGN) \
	 -I$(GIT_MOD_LST) \
	 -I$(GIT_MOD_RCV) \
	 -I$(SRC_DET) \
	 -I$(HEAD_DET) \
	 -L$(GIT_LIST) \
	 -L$(GIT_REC) \
	 -L$(GIT_IGN) \
	 -L$(GIT_MOD_LST) \
	 -L$(GIT_MOD_RCV) \
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
	 -L$(SRC_DET) \
	 -L$(HEAD_DET) \
		Git_Data_Processor_Main_File.cpp \
		Git_Data_Processor.cpp \
	    $(GIT_LIST)\Git_File_List_Writer.cpp \
	    $(GIT_REC)\Git_File_List_Receiver.cpp \
	    $(GIT_IGN)\Git_Ignoring_Files_Lister.cpp \
	    $(GIT_MOD_LST)\Git_Modification_Lister.cpp \
	    $(GIT_MOD_RCV)\Git_Modification_Receiver.cpp \
		$(SRC_DET)\Source_File_Determiner.cpp \
		$(HEAD_DET)\Header_File_Determiner.cpp \
		$(DES_READ)\Descriptor_File_Reader.cpp \
		$(DES_DATA_COL)\Descriptor_File_Data_Collector.cpp \
		$(DES_SYN_CON)\Descriptor_File_Syntax_Controller.cpp \
		$(DIR_OPS)\DirectoryOperations.cpp \
		$(STRING_OPS)\StringOperator.cpp \
		$(CHAR_OPS)\CharOperator.cpp \
		$(INT_TRANS)\IntToCharTranslater.cpp \
		$(FILE_OPRS)\Cpp_FileOperations.cpp \
		$(SYS_INT)\Custom_System_Interface.cpp \
		-include $(GIT_LIST)\Git_File_List_Writer.hpp \
	    -include $(GIT_REC)\Git_File_List_Receiver.hpp \
	    -include $(GIT_IGN)\Git_Ignoring_Files_Lister.hpp \
	    -include $(GIT_MOD_LST)\Git_Modification_Lister.hpp \
	    -include $(GIT_MOD_RCV)\Git_Modification_Receiver.hpp \
	    -include $(SRC_DET)\Source_File_Determiner.h \
		-include $(HEAD_DET)\Header_File_Determiner.h \
		-include $(DES_READ)\Descriptor_File_Reader.hpp \
		-include $(DES_DATA_COL)\Descriptor_File_Data_Collector.hpp \
		-include $(DES_SYN_CON)\Descriptor_File_Syntax_Controller.hpp \
		-include $(STRING_OPS)\StringOperator.h \
		-include $(DIR_OPS)\DirectoryOperations.h \
		-include $(CHAR_OPS)\CharOperator.h \
		-include $(INT_TRANS)\IntToCharTranslater.h \
		-include $(FILE_OPRS)\Cpp_FileOperations.h \
		-include $(SYS_INT)\Custom_System_Interface.h \
