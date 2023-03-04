
STRING_OPS=D:\pcynlitx.build\BASIC.TOOLS\StringOperator
DIR_OPS=D:\pcynlitx.build\BASIC.TOOLS\DirectoryOperations
CPP_OPS=D:\pcynlitx.build\BASIC.TOOLS\Cpp_FileOperations
CHAR_OPS=D:\pcynlitx.build\BASIC.TOOLS\CharOperator
INT_TO_CHAR=D:\pcynlitx.build\BASIC.TOOLS\IntToCharTranslater


HEAD_DET=D:\pcynlitx.build\SOURCE.FILE.DATA.COLLECTORS\Header_File_Determiner
FILE_LISTER=D:\pcynlitx.build\SOURCE.FILE.DATA.COLLECTORS\Project_Files_Lister
SOURCE_DETR=D:\pcynlitx.build\SOURCE.FILE.DATA.COLLECTORS\Source_File_Determiner
SRC_DT_COL=D:\pcynlitx.build\SOURCE.FILE.DATA.COLLECTORS\Source_File_Data_Collector
FILE_DAT_COL=D:\pcynlitx.build\SOURCE.FILE.DATA.COLLECTORS\Project_Files_Data_Collector


DES_READER=D:\pcynlitx.build\DESCRIPTION.PROCESSING.SYSTEM\Description.Readers\Descriptor.File.Reader
DES_DATA_COL=D:\pcynlitx.build\DESCRIPTION.PROCESSING.SYSTEM\Description.Readers\Descriptor.File.Data.Collector
DES_SYN_CON=D:\pcynlitx.build\DESCRIPTION.PROCESSING.SYSTEM\Description.Readers\Descriptor.File.Syntax.Controller


GIT_LIST=D:\pcynlitx.build\PROJECT.BUILD.TOOLS\Git_File_List_Receiver


MAKE_DATA_COL=D:\pcynlitx.build\MAKE.FILE.BUILD.SYSTEM\MakeFile_Data_Collector


VPATH = $(DIR_OPS)       $(CPP_OPS)      $(CHAR_OPS) \
		$(DES_SYN_CON)   $(SOURCE_DETR)  $(FILE_LISTER) \
		$(STRING_OPS)    $(HEAD_DET)     $(DES_READER) \
	    $(INT_TO_CHAR)   $(DES_DATA_COL) $(FILE_DAT_COL) \
	    $(MAKE_DATA_COL) $(GIT_LIST)     $(SRC_DT_COL) \
	    

Make_File_Builder.exe: Make_File_Builder_Main_File.cpp Make_File_Builder.cpp \
	Project_Files_Lister.cpp \
    Project_Files_Data_Collector.cpp \
	Git_File_List_Receiver.cpp \
	MakeFile_Data_Collector.cpp \
	Source_File_Determiner.cpp \
	Header_File_Determiner.cpp \
	Descriptor_File_Reader.cpp \
	Descriptor_File_Data_Collector.cpp \
	DirectoryOperations.cpp \
	CharOperator.cpp \
	Cpp_FileOperations.cpp \
	Make_File_Builder.h \
	Project_Files_Lister.h \
	Project_Files_Data_Collector.hpp \
	Git_File_List_Receiver.hpp \
	MakeFile_Data_Collector.hpp \
	Descriptor_File_Reader.hpp \
	Descriptor_File_Data_Collector.hpp \
	Source_File_Determiner.h \
	Header_File_Determiner.h \
	DirectoryOperations.h \
	CharOperator.h \
	Cpp_FileOperations.h

	g++ -std=c++17 -g -o Make_File_Builder.exe \
	 -I$(DIR_OPS)       -I$(CPP_OPS)     -I$(CHAR_OPS) \
	 -I$(STRING_OPS)    -I$(HEAD_DET)    -I$(INT_TO_CHAR)\
	 -I$(FILE_LISTER)   -I$(SOURCE_DETR) -I$(GIT_LIST) \
	 -I$(DES_DATA_COL)  -I$(DES_READER)  -I$(MAKE_DATA_COL) \
	 -I$(FILE_DAT_COL)  -I$(SRC_DT_COL)  -I$(DES_SYN_CON) \
	  \
	 -L$(DIR_OPS)      -L$(CPP_OPS)       -L$(CHAR_OPS)\
	 -L$(INT_TO_CHAR)  -L$(DES_DATA_COL)  -L$(DES_READER)\
	 -L$(STRING_OPS)   -L$(HEAD_DET)      -L$(FILE_LISTER)\
	 -L$(SOURCE_DETR)  -L$(MAKE_DATA_COL) -L$(GIT_LIST) \
	 -L$(FILE_DAT_COL) -L$(SRC_DT_COL)    -L$(DES_SYN_CON) \
	 \
		Make_File_Builder_Main_File.cpp \
		Make_File_Builder.cpp \
	    $(MAKE_DATA_COL)\MakeFile_Data_Collector.cpp \
		$(FILE_LISTER)\Project_Files_Lister.cpp \
		$(FILE_DAT_COL)\Project_Files_Data_Collector.cpp \
		$(SRC_DT_COL)\Source_File_Data_Collector.cpp \
		$(GIT_LIST)\Git_File_List_Receiver.cpp \
		$(SOURCE_DETR)\Source_File_Determiner.cpp \
		$(DES_READER)\Descriptor_File_Reader.cpp \
		$(DES_DATA_COL)\Descriptor_File_Data_Collector.cpp \
		$(DES_SYN_CON)\Descriptor_File_Syntax_Controller.cpp \
		$(HEAD_DET)\Header_File_Determiner.cpp \
		$(DIR_OPS)\DirectoryOperations.cpp \
		$(STRING_OPS)\StringOperator.cpp \
		$(CHAR_OPS)\CharOperator.cpp \
		$(CPP_OPS)\Cpp_FileOperations.cpp \
		$(INT_TO_CHAR)\IntToCharTranslater.cpp \
		-include Make_File_Builder.h \
		-include $(MAKE_DATA_COL)\MakeFile_Data_Collector.hpp \
		-include $(FILE_LISTER)\Project_Files_Lister.h \
		-include $(FILE_DAT_COL)\Project_Files_Data_Collector.hpp \
		-include $(SRC_DT_COL)\Source_File_Data_Collector.hpp \
		-include $(GIT_LIST)\Git_File_List_Receiver.hpp \
		-include $(DES_READER)\Descriptor_File_Reader.hpp \
		-include $(DES_DATA_COL)\Descriptor_File_Data_Collector.hpp \
		-include $(DES_SYN_CON)\Descriptor_File_Syntax_Controller.hpp \
		-include $(SOURCE_DETR)\Source_File_Determiner.h \
		-include $(HEAD_DET)\Header_File_Determiner.h \
		-include $(STRING_OPS)\StringOperator.h \
		-include $(DIR_OPS)\DirectoryOperations.h \
	    -include $(CHAR_OPS)\CharOperator.h \
		-include $(CPP_OPS)\Cpp_FileOperations.h \
		-include $(INT_TO_CHAR)\IntToCharTranslater.h
