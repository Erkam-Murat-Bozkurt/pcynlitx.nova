
STRING_OPS=D:\pcynlitx.build\BASIC.TOOLS\StringOperator
DIR_OPS=D:\pcynlitx.build\BASIC.TOOLS\DirectoryOperations
CHAR_OPS=D:\pcynlitx.build\BASIC.TOOLS\CharOperator
FILE_OPRS=D:\pcynlitx.build\BASIC.TOOLS\Cpp_FileOperations
INT_TO_CHAR=D:\pcynlitx.build\BASIC.TOOLS\IntToCharTranslater
DES_READER=D:\pcynlitx.build\DESCRIPTION.PROCESSING.SYSTEM\Description.Readers\Descriptor.File.Reader
DES_DATA_COL=D:\pcynlitx.build\DESCRIPTION.PROCESSING.SYSTEM\Description.Readers\Descriptor.File.Data.Collector
DES_SYN_CON=D:\pcynlitx.build\DESCRIPTION.PROCESSING.SYSTEM\Description.Readers\Descriptor.File.Syntax.Controller
DIR_ENUM=D:\pcynlitx.build\PROJECT.BUILD.TOOLS\Directory_Enumerator
GIT_LIST=D:\pcynlitx.build\PROJECT.BUILD.TOOLS\Git_File_List_Receiver
MAKE_DATA_COL=D:\pcynlitx.build\MAKE.FILE.BUILD.SYSTEM\MakeFile_Data_Collector
MAKE_BLD=D:\pcynlitx.build\MAKE.FILE.BUILD.SYSTEM\Make_File_Builder
MK_FILE_CLNR=D:\pcynlitx.build\MAKE.FILE.BUILD.SYSTEM\Make_File_Cleaner
SRC_DT_COL=D:\pcynlitx.build\SOURCE.FILE.DATA.COLLECTORS\Source_File_Data_Collector
FILE_DAT_COL=D:\pcynlitx.build\SOURCE.FILE.DATA.COLLECTORS\Project_Files_Data_Collector
DIR_LIST=D:\pcynlitx.build\SOURCE.FILE.DATA.COLLECTORS\Project_Files_Lister
SOURCE_DETR=D:\pcynlitx.build\SOURCE.FILE.DATA.COLLECTORS\Source_File_Determiner
HEAD_DETER=D:\pcynlitx.build\SOURCE.FILE.DATA.COLLECTORS\Header_File_Determiner


VPATH = $(INT_TO_CHAR)    $(FILE_OPRS)    $(DIR_OPS)   \
	    $(STRING_OPS)     $(CHAR_OPS)     $(MAKE_BLD)   \
	    $(MAKE_DATA_COL)  $(MK_FILE_CLNR) $(HEAD_DETER) \
	    $(SOURCE_DETR)    $(DES_READER)   $(DES_DATA_COL) \
	    $(DES_SYN_CON)    $(GIT_LIST)     $(SRC_DT_COL) \
		$(DIR_LIST)       $(FILE_DAT_COL) $(DIR_ENUM) 
	    

Auto_MakeFile_Builder.exe: Auto_MakeFile_Builder_Main_File.cpp \
	Auto_MakeFile_Builder.cpp \
	Make_File_Builder.cpp \
	MakeFile_Data_Collector.cpp \
	Make_File_Cleaner.cpp \
	Project_Files_Lister.cpp \
	Project_Files_Data_Collector.cpp \
	Source_File_Determiner.cpp \
	Source_File_Data_Collector.cpp \
	Git_File_List_Receiver.cpp \
	Descriptor_File_Reader.cpp \
	Descriptor_File_Data_Collector.cpp \
	Descriptor_File_Syntax_Controller.cpp \
	Header_File_Determiner.cpp \
	Directory_Enumerator.cpp \
	DirectoryOperations.cpp \
	StringOperator.cpp \
	IntToCharTranslater.cpp \
	Cpp_FileOperations.cpp \
	CharOperator.cpp \
	Auto_MakeFile_Builder.h \
	Make_File_Builder.h \
	MakeFile_Data_Collector.hpp \
	Make_File_Cleaner.hpp \
	Source_File_Determiner.h \
	Source_File_Data_Collector.hpp \
	Descriptor_File_Reader.hpp \
	Descriptor_File_Data_Collector.hpp \
	Descriptor_File_Syntax_Controller.hpp \
	Project_Files_Lister.h \
	Project_Files_Data_Collector.hpp \
	Git_File_List_Receiver.hpp \
	Header_File_Determiner.h \
	Directory_Enumerator.h \
	StringOperator.h \
	DirectoryOperations.h \
	IntToCharTranslater.h \
	CharOperator.h \
	Cpp_FileOperations.h

	g++ -std=c++17 -o Auto_MakeFile_Builder.exe \
	-I$(DES_READER) \
	-I$(DES_DATA_COL) \
	-I$(DES_SYN_CON) \
	-I$(DIR_LIST) \
	-I$(MAKE_BLD) \
	-I$(MAKE_DATA_COL) \
	-I$(MK_FILE_CLNR) \
	-I$(DIR_ENUM) \
	-I$(DIR_OPS) \
	-I$(STRING_OPS) \
	-I$(HEAD_DETER) \
	-I$(SOURCE_DETR) \
	-I$(INT_TO_CHAR) \
	-I$(CHAR_OPS) \
	-I$(GIT_LIST) \
	-I$(SRC_DT_COL) \
	-I$(FILE_DAT_COL) \
    -I$(FILE_OPRS) \
	-L$(DIR_LIST) \
	-L$(MAKE_BLD) \
	-L$(MAKE_DATA_COL) \
	-L$(MK_FILE_CLNR) \
	-L$(GIT_LIST) \
	-L$(INT_TO_CHAR) \
	-L$(DES_READER) \
	-L$(DES_DATA_COL) \
	-L$(DES_SYN_CON) \
	-L$(DIR_ENUM) \
	-L$(DIR_OPS) \
	-L$(STRING_OPS) \
	-L$(CHAR_OPS) \
	-L$(FILE_OPRS) \
	-L$(HEAD_DETER) \
	-L$(SOURCE_DETR) \
	-L$(SRC_DT_COL) \
	-L$(FILE_DAT_COL) \
	Auto_MakeFile_Builder_Main_File.cpp \
	Auto_MakeFile_Builder.cpp \
	$(MAKE_BLD)\Make_File_Builder.cpp \
	$(MAKE_DATA_COL)\MakeFile_Data_Collector.cpp  \
	$(MK_FILE_CLNR)\Make_File_Cleaner.cpp \
	$(DES_READER)\Descriptor_File_Reader.cpp \
	$(DES_DATA_COL)\Descriptor_File_Data_Collector.cpp \
	$(DES_SYN_CON)\Descriptor_File_Syntax_Controller.cpp \
	$(DIR_LIST)\Project_Files_Lister.cpp \
	$(FILE_DAT_COL)\Project_Files_Data_Collector.cpp \
	$(SOURCE_DETR)\Source_File_Determiner.cpp \
	$(SRC_DT_COL)\Source_File_Data_Collector.cpp \
	$(GIT_LIST)\Git_File_List_Receiver.cpp \
	$(HEAD_DETER)\Header_File_Determiner.cpp \
	$(DIR_ENUM)\Directory_Enumerator.cpp \
	$(DIR_OPS)\DirectoryOperations.cpp \
	$(STRING_OPS)\StringOperator.cpp \
	$(CHAR_OPS)\CharOperator.cpp \
	$(INT_TO_CHAR)\IntToCharTranslater.cpp \
	$(FILE_OPRS)\Cpp_FileOperations.cpp \
	-include Auto_MakeFile_Builder.h \
	-include $(MAKE_BLD)\Make_File_Builder.h \
	-include $(MAKE_DATA_COL)\MakeFile_Data_Collector.hpp  \
	-include $(MK_FILE_CLNR)\Make_File_Cleaner.hpp \
	-include $(DIR_LIST)\Project_Files_Lister.h \
	-include $(FILE_DAT_COL)\Project_Files_Data_Collector.hpp \
	-include $(SOURCE_DETR)\Source_File_Determiner.h \
	-include $(SRC_DT_COL)\Source_File_Data_Collector.hpp \
	-include $(GIT_LIST)\Git_File_List_Receiver.hpp \
	-include $(DES_READER)\Descriptor_File_Reader.hpp \
	-include $(DES_DATA_COL)\Descriptor_File_Data_Collector.hpp \
	-include $(DES_SYN_CON)\Descriptor_File_Syntax_Controller.hpp \
	-include $(HEAD_DETER)\Header_File_Determiner.h \
	-include $(DIR_ENUM)\Directory_Enumerator.h \
	-include $(STRING_OPS)\StringOperator.h \
	-include $(DIR_OPS)\DirectoryOperations.h \
	-include $(INT_TO_CHAR)\IntToCharTranslater.h \
	-include $(CHAR_OPS)\CharOperator.h \
	-include $(FILE_OPRS)\Cpp_FileOperations.h
