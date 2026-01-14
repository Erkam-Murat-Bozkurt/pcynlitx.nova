

STRING_OPS=D:\pcynlitx.build\BASIC.TOOLS\StringOperator
DIR_OPS=D:\pcynlitx.build\BASIC.TOOLS\DirectoryOperations
CHAR_OPS=D:\pcynlitx.build\BASIC.TOOLS\CharOperator
FILE_OPRS=D:\pcynlitx.build\BASIC.TOOLS\Cpp_FileOperations
DES_READ=D:\pcynlitx.build\DESCRIPTION.PROCESSING.SYSTEM\Description.Readers\Descriptor.File.Reader
DES_DATA_COL=D:\pcynlitx.build\DESCRIPTION.PROCESSING.SYSTEM\Description.Readers\Descriptor.File.Data.Collector
DES_SYN_CON=D:\pcynlitx.build\DESCRIPTION.PROCESSING.SYSTEM\Description.Readers\Descriptor.File.Syntax.Controller


GIT_PROC=D:\pcynlitx.build\GIT.DATA.PROCESSING.SYSTEM\Git_Data_Processor
GIT_LIST=D:\pcynlitx.build\GIT.DATA.PROCESSING.SYSTEM\Git_File_List_Writer
GIT_REC=D:\pcynlitx.build\GIT.DATA.PROCESSING.SYSTEM\Git_File_List_Receiver
GIT_IGN=D:\pcynlitx.build\GIT.DATA.PROCESSING.SYSTEM\Git_Ignoring_Files_Lister
GIT_MOD_LST=D:\pcynlitx.build\GIT.DATA.PROCESSING.SYSTEM\Git_Modification_Lister
GIT_MOD_RCV=D:\pcynlitx.build\GIT.DATA.PROCESSING.SYSTEM\Git_Modification_Receiver



SRC_DT_COL=D:\pcynlitx.build\SOURCE.FILE.DATA.COLLECTORS\Source_File_Data_Collector
SOURCE_DETR=D:\pcynlitx.build\SOURCE.FILE.DATA.COLLECTORS\Source_File_Determiner

VPATH = $(DIR_OPS) $(STRING_OPS) $(CHAR_OPS) $(FILE_OPRS) \
	    $(GIT_LIST) $(DES_READ) $(DES_DATA_COL) $(DES_SYN_CON) \
		$(GIT_PROC) \
		$(GIT_LIST) \
		$(GIT_REC) \
		$(GIT_MOD_LST) \
		$(GIT_MOD_RCV) \
		$(GIT_IGN) \
		$(SRC_DT_COL) \
		$(SOURCE_DETR)


Header_File_Determiner.exe: Header_File_Determiner_Main_File.cpp \
    Header_File_Determiner.cpp \
	Git_Data_Processor.cpp \
	Git_File_List_Receiver.cpp \
	Git_File_List_Writer.cpp \
	Git_Ignoring_Files_Lister.cpp \
	Git_Modification_Lister.cpp \
	Git_Modification_Lister.cpp \
	Source_File_Data_Collector.cpp \
	Source_File_Determiner.cpp \
	Descriptor_File_Reader.cpp \
	Descriptor_File_Data_Collector.cpp \
	Git_File_List_Receiver.cpp \
	StringOperator.cpp \
	CharOperator.cpp \
	Cpp_FileOperations.cpp \
	Header_File_Determiner.h \
	Git_Data_Processor.hpp \
	Git_File_List_Receiver.hpp \
	Git_File_List_Writer.hpp \
	Git_Ignoring_Files_Lister.hpp \
	Git_Modification_Lister.hpp \
	Git_Modification_Lister.hpp \
	Source_File_Data_Collector.hpp \
	Source_File_Determiner.h \
	StringOperator.h \
	CharOperator.h \
	Cpp_FileOperations.h

	g++ -std=c++17 -static-libgcc -static-libstdc++ -ggdb -o \
	   Header_File_Determiner.exe \
	  -I$(STRING_OPS) -I$(CHAR_OPS) -I$(FILE_OPRS) -I$(DES_READ) \
	  -I$(DES_DATA_COL) -I$(GIT_LIST) -I$(DIR_OPS) -I$(DES_SYN_CON) \
	  -I$(GIT_PROC) \
	  -I$(GIT_LIST) \
	  -I$(GIT_REC) \
	  -I$(GIT_MOD_LST) \
	  -I$(GIT_MOD_RCV) \
	  -I$(GIT_IGN) \
	  -I$(SRC_DT_COL) \
	  -I$(SOURCE_DETR) \
	  -L$(STRING_OPS) -L$(CHAR_OPS) -L$(FILE_OPRS) -L$(DES_READ) \
	  -L$(DES_DATA_COL) -L$(GIT_LIST) -L$(DIR_OPS) -L$(DES_SYN_CON) \
	  -L$(GIT_PROC) \
	  -L$(GIT_LIST) \
	  -L$(GIT_REC) \
	  -L$(GIT_MOD_LST) \
	  -L$(GIT_MOD_RCV) \
	  -L$(GIT_IGN) \
	  -L$(SRC_DT_COL) \
	  -L$(SOURCE_DETR) \
		Header_File_Determiner_Main_File.cpp \
		Header_File_Determiner.cpp \
	    $(GIT_PROC)\Git_Data_Processor.cpp \
		$(GIT_LIST)\Git_File_List_Writer.cpp \
		$(GIT_REC)\Git_File_List_Receiver.cpp \
		$(GIT_MOD_LST)\Git_Modification_Lister.cpp \
		$(GIT_MOD_RCV)\Git_Modification_Receiver.cpp \
		$(GIT_IGN)\Git_Ignoring_Files_Lister.cpp \
		$(SRC_DT_COL)\Source_File_Data_Collector.cpp \
		$(SOURCE_DETR)\Source_File_Determiner.cpp \
		$(DES_READ)\Descriptor_File_Reader.cpp \
		$(DES_DATA_COL)\Descriptor_File_Data_Collector.cpp \
		$(DES_SYN_CON)\Descriptor_File_Syntax_Controller.cpp \
		$(STRING_OPS)\StringOperator.cpp \
		$(DIR_OPS)\DirectoryOperations.cpp \
		$(CHAR_OPS)\CharOperator.cpp \
		$(FILE_OPRS)\Cpp_FileOperations.cpp \
		-include Header_File_Determiner.h \
        -include $(GIT_PROC)\Git_Data_Processor.hpp \
		-include $(GIT_LIST)\Git_File_List_Writer.hpp \
		-include $(GIT_REC)\Git_File_List_Receiver.hpp \
		-include $(GIT_MOD_LST)\Git_Modification_Lister.hpp \
		-include $(GIT_MOD_RCV)\Git_Modification_Receiver.hpp \
		-include $(GIT_IGN)\Git_Ignoring_Files_Lister.hpp \
		-include $(SRC_DT_COL)\Source_File_Data_Collector.cpp \	
		-include $(SOURCE_DETR)\Source_File_Determiner.h \
		-include $(DES_READ)\Descriptor_File_Reader.hpp \
		-include $(DES_DATA_COL)\Descriptor_File_Data_Collector.hpp \
		-include $(DES_SYN_CON)\Descriptor_File_Syntax_Controller.hpp \
		-include $(GIT_LIST)\Git_File_List_Receiver.hpp \
		-include $(DIR_OPS)\DirectoryOperations.h \
		-include $(STRING_OPS)\StringOperator.h \
		-include $(CHAR_OPS)\CharOperator.h \
		-include $(FILE_OPRS)\Cpp_FileOperations.h
