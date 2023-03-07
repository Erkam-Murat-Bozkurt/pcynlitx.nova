

STRING_OPS=D:\pcynlitx.build\BASIC.TOOLS\StringOperator
DIR_OPS=D:\pcynlitx.build\BASIC.TOOLS\DirectoryOperations
CHAR_OPS=D:\pcynlitx.build\BASIC.TOOLS\CharOperator
FILE_OPRS=D:\pcynlitx.build\BASIC.TOOLS\Cpp_FileOperations
TRANSLATER=D:\pcynlitx.build\BASIC.TOOLS\IntToCharTranslater


GIT_LIST=D:\pcynlitx.build\PROJECT.BUILD.TOOLS\Git_File_List_Receiver
DIR_ENUM=D:\pcynlitx.build\PROJECT.BUILD.TOOLS\Directory_Enumerator


SRC_DT_COL=D:\pcynlitx.build\SOURCE.FILE.DATA.COLLECTORS\Source_File_Data_Collector
FILE_DAT_COL=D:\pcynlitx.build\SOURCE.FILE.DATA.COLLECTORS\Project_Files_Data_Collector
FILE_LISTER=D:\pcynlitx.build\SOURCE.FILE.DATA.COLLECTORS\Project_Files_Lister
HEAD_DETR=D:\pcynlitx.build\SOURCE.FILE.DATA.COLLECTORS\Header_File_Determiner
SOURCE_DETR=D:\pcynlitx.build\SOURCE.FILE.DATA.COLLECTORS\Source_File_Determiner

DES_RED=D:\pcynlitx.build\DESCRIPTION.PROCESSING.SYSTEM\Description.Readers\Descriptor.File.Reader
DES_DATA_COL=D:\pcynlitx.build\DESCRIPTION.PROCESSING.SYSTEM\Description.Readers\Descriptor.File.Data.Collector
DES_SYN_CON=D:\pcynlitx.build\DESCRIPTION.PROCESSING.SYSTEM\Description.Readers\Descriptor.File.Syntax.Controller


VPATH = $(DIR_OPS)   $(STRING_OPS)  $(CHAR_OPS)     $(FILE_OPRS) \
		$(HEAD_DETR) $(SOURCE_DETR) $(DES_RED)     $(DES_DATA_COL) \
	    $(GIT_LIST)  $(SRC_DT_COL)  $(FILE_DAT_COL) $(DES_SYN_CON)\
	    $(DIR_ENUM)  $(FILE_LISTER) $(TRANSLATER)

Make_File_Cleaner.exe: Make_File_Cleaner_Main_File.cpp \
	Make_File_Cleaner.cpp \
	Project_Files_Lister.cpp \
	Descriptor_File_Reader.cpp \
	Descriptor_File_Data_Collector.cpp \
	Descriptor_File_Syntax_Controller.cpp \
	Project_Files_Data_Collector.cpp \
	Source_File_Determiner.cpp \
	Header_File_Determiner.cpp \
	Directory_Enumerator.cpp \
	StringOperator.cpp \
	Cpp_FileOperations.cpp \
	CharOperator.cpp \
	IntToCharTranslater.cpp \
	Project_Files_Lister.h \
	Project_Files_Data_Collector.hpp \
	Source_File_Determiner.h \
	Header_File_Determiner.h \
	Descriptor_File_Reader.hpp \
	Descriptor_File_Data_Collector.hpp \
	Descriptor_File_Syntax_Controller.hpp \
	Directory_Enumerator.h \
	StringOperator.h \
	DirectoryOperations.h \
	CharOperator.h \
	IntToCharTranslater.h \
	Cpp_FileOperations.h

	g++ -std=c++17 -o Make_File_Cleaner.exe \
	 -I$(HEAD_DETR) \
	 -I$(SOURCE_DETR) \
	 -I$(DIR_OPS) \
	 -I$(STRING_OPS) \
	 -I$(CHAR_OPS) \
	 -I$(FILE_OPRS) \
	 -I$(DES_RED) \
	 -I$(DES_DATA_COL) \
	 -I$(GIT_LIST) \
	 -I$(FILE_DAT_COL) \
	 -I$(SRC_DT_COL) \
	 -I$(DIR_ENUM) \
	 -I$(FILE_LISTER) \
	 -I$(TRANSLATER) \
	 -I$(DES_SYN_CON) \
	 -L$(HEAD_DETR) \
	 -L$(SOURCE_DETR) \
	 -L$(DIR_OPS) \
	 -L$(STRING_OPS) \
	 -L$(GIT_LIST) \
	 -L$(FILE_DAT_COL) \
	 -L$(CHAR_OPS) \
	 -L$(FILE_OPRS) \
	 -L$(DES_RED) \
	 -L$(DES_DATA_COL) \
	 -L$(SRC_DT_COL) \
	 -L$(DIR_ENUM) \
	 -L$(FILE_LISTER) \
	 -L$(TRANSLATER) \
	 -L$(DES_SYN_CON) \
	  Make_File_Cleaner_Main_File.cpp \
	  Make_File_Cleaner.cpp \
		$(FILE_LISTER)\Project_Files_Lister.cpp \
		$(FILE_DAT_COL)\Project_Files_Data_Collector.cpp \
		$(SOURCE_DETR)\Source_File_Determiner.cpp \
		$(HEAD_DETR)\Header_File_Determiner.cpp \
		$(DIR_ENUM)\Directory_Enumerator.cpp \
		$(DES_RED)\Descriptor_File_Reader.cpp \
		$(DES_DATA_COL)\Descriptor_File_Data_Collector.cpp \
		$(DES_SYN_CON)\Descriptor_File_Syntax_Controller.cpp \
		$(GIT_LIST)\Git_File_List_Receiver.cpp \
		$(SRC_DT_COL)\Source_File_Data_Collector.cpp \
		$(DIR_OPS)\DirectoryOperations.cpp \
		$(STRING_OPS)\StringOperator.cpp \
		$(CHAR_OPS)\CharOperator.cpp \
		$(FILE_OPRS)\Cpp_FileOperations.cpp \
		$(TRANSLATER)\IntToCharTranslater.cpp\
		-include $(FILE_LISTER)\Project_Files_Lister.h \
		-include $(FILE_DAT_COL)\Project_Files_Data_Collector.hpp \
		-include $(SOURCE_DETR)\Source_File_Determiner.h \
		-include $(HEAD_DETR)\Header_File_Determiner.h \
		-include $(SRC_DT_COL)\Source_File_Data_Collector.hpp \
		-include $(DES_RED)\Descriptor_File_Reader.hpp \
		-include $(DES_DATA_COL)\Descriptor_File_Data_Collector.hpp \
		-include $(DES_SYN_CON)\Descriptor_File_Syntax_Controller.hpp \
		-include $(GIT_LIST)\Git_File_List_Receiver.hpp \
		-include $(DIR_ENUM)\Directory_Enumerator.h \
		-include $(STRING_OPS)\StringOperator.h \
		-include $(DIR_OPS)\DirectoryOperations.h \
		-include $(CHAR_OPS)\CharOperator.h \
		-include $(FILE_OPRS)\Cpp_FileOperations.h \
		-include $(TRANSLATER)\IntToCharTranslater.h
