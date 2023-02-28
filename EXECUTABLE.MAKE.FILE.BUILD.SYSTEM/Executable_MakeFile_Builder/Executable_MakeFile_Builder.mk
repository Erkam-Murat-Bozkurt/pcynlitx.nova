

STRING_OPS=D:\pcynlitx.build\BASIC.TOOLS\StringOperator
DIR_OPS=D:\pcynlitx.build\BASIC.TOOLS\DirectoryOperations
CPP_OPS=D:\pcynlitx.build\BASIC.TOOLS\Cpp_FileOperations
CHAR_OPS=D:\pcynlitx.build\BASIC.TOOLS\CharOperator
INT_TO_CHAR=D:\pcynlitx.build\BASIC.TOOLS\IntToCharTranslater
HEAD_DET=D:\pcynlitx.build\SOURCE.FILE.DATA.COLLECTORS\Header_File_Determiner
FILE_LISTER=D:\pcynlitx.build\SOURCE.FILE.DATA.COLLECTORS\Project_Files_Lister
SOURCE_DETR=D:\pcynlitx.build\SOURCE.FILE.DATA.COLLECTORS\Source_File_Determiner
DES_READER=D:\pcynlitx.build\DESCRIPTION.PROCESSING.SYSTEM\Description.Readers\Descriptor.File.Reader
DES_DATA_COL=D:\pcynlitx.build\DESCRIPTION.PROCESSING.SYSTEM\Description.Readers\Descriptor.File.Data.Collector
DES_FILE_SYNT_COL=D:\pcynlitx.build\DESCRIPTION.PROCESSING.SYSTEM\Description.Readers\Descriptor.File.Syntax.Controller
GIT_LIST=D:\pcynlitx.build\PROJECT.BUILD.TOOLS\Git_File_List_Receiver
FILE_DAT_COL=D:\pcynlitx.build\SOURCE.FILE.DATA.COLLECTORS\Project_Files_Data_Collector
SRC_DT_COL=D:\pcynlitx.build\SOURCE.FILE.DATA.COLLECTORS\Source_File_Data_Collector
SRC_INF_COL=D:\pcynlitx.build\SOURCE.FILE.PROCESSING.SYSTEM\Source_File_Information_Collector
SRC_DEP_DTR=D:\pcynlitx.build\SOURCE.FILE.PROCESSING.SYSTEM\Source_File_Dependency_Determiner
SRC_DEP_SL=D:\pcynlitx.build\SOURCE.FILE.PROCESSING.SYSTEM\Source_File_Dependency_Selector
EXC_MKF_COM_CNSR=D:\pcynlitx.build\EXECUTABLE.MAKE.FILE.BUILD.SYSTEM\Executable_MakeFile_ComConstructor
SRC_DER_RORD=D:\pcynlitx.build\SOURCE.FILE.PROCESSING.SYSTEM\Source_File_Dependency_ReOrderer
SRC_COM_DT_EXT=D:\pcynlitx.build\SOURCE.FILE.PROCESSING.SYSTEM\Source_File_Compiler_Data_Extractor

VPATH = $(DIR_OPS) $(CPP_OPS) $(CHAR_OPS) \
	    $(SOURCE_DETR) \
	    $(STRING_OPS) $(HEAD_DET) $(FILE_LISTER) \
	    $(INT_TO_CHAR) $(DES_DATA_COL) $(DES_READER) \
	    $(GIT_LIST) $(FILE_DAT_COL) \
	    $(SRC_DT_COL) $(DES_FILE_SYNT_COL) $(SRC_INF_COL) \
	    $(SRC_DEP_DTR) $(SRC_DEP_SL) \
	    $(EXC_MKF_COM_CNSR) \
	    $(SRC_DER_RORD) $(SRC_COM_DT_EXT)


Executable_MakeFile_Builder.exe: Executable_MakeFile_Builder_Main_File.cpp \
	Executable_MakeFile_Builder.cpp \
	Executable_MakeFile_ComConstructor.cpp \
	Source_File_Dependency_Determiner.cpp \
	Source_File_Compiler_Data_Extractor.cpp \
	Source_File_Dependency_ReOrderer.cpp \
	Source_File_Dependency_Selector.cpp \
	Source_File_Information_Collector.cpp \
	Project_Files_Lister.cpp \
    Project_Files_Data_Collector.cpp \
	Source_File_Data_Collector.cpp \
	Git_File_List_Receiver.cpp \
	Source_File_Determiner.cpp \
	Header_File_Determiner.cpp \
	Descriptor_File_Reader.cpp \
	Descriptor_File_Data_Collector.cpp \
	Descriptor_File_Syntax_Controller.cpp \
	DirectoryOperations.cpp \
	StringOperator.cpp \
	CharOperator.cpp \
	IntToCharTranslater.cpp \
	Cpp_FileOperations.cpp \
	Executable_MakeFile_Builder.hpp \
	Executable_MakeFile_ComConstructor.hpp \
	Source_File_Dependency_Determiner.hpp \
	Source_File_Compiler_Data_Extractor.hpp \
	Source_File_Dependency_ReOrderer.hpp \
	Source_File_Dependency_Selector.hpp \
	Source_File_Information_Collector.hpp \
	Project_Files_Lister.h \
	Project_Files_Data_Collector.hpp \
	Source_File_Data_Collector.cpp \
	Git_File_List_Receiver.hpp \
	Descriptor_File_Reader.hpp \
	Descriptor_File_Data_Collector.hpp \
	Descriptor_File_Syntax_Controller.hpp \
	Source_File_Determiner.h \
	Header_File_Determiner.h \
	StringOperator.h \
	DirectoryOperations.h \
	CharOperator.h \
	IntToCharTranslater.h \
	Cpp_FileOperations.h

	g++ -std=c++17 -g -o Executable_MakeFile_Builder.exe \
	 -I$(DIR_OPS) -I$(CPP_OPS) -I$(CHAR_OPS) -I$(SRC_DEP_DTR) \
	 -I$(SRC_INF_COL) -I$(STRING_OPS) -I$(HEAD_DET) \
	 -I$(FILE_LISTER) -I$(SOURCE_DETR) -I$(GIT_LIST) \
	 -I$(INT_TO_CHAR) \
	 -I$(DES_DATA_COL) -I$(DES_READER) \
	 -I$(FILE_DAT_COL) \
	 -I$(SRC_DT_COL) -I$(DES_FILE_SYNT_COL) \
	 -I$(EXC_MKF_COM_CNSR) -I$(SRC_DEP_SL) \
	 -I$(SRC_DER_RORD) -I$(SRC_COM_DT_EXT) \
	 -L$(SRC_INF_COL) -L$(DIR_OPS) -L$(CPP_OPS) \
	 -L$(CHAR_OPS) -L$(INT_TO_CHAR) -L$(DES_DATA_COL) \
	 -L$(DES_READER) -L$(STRING_OPS) \
	 -L$(HEAD_DET) -L$(FILE_LISTER) \
	 -L$(SOURCE_DETR) \
	 -L$(GIT_LIST) -L$(FILE_DAT_COL) \
	 -L$(SRC_DT_COL) -L$(DES_FILE_SYNT_COL) \
	 -L$(SRC_DEP_DTR) -L$(EXC_MKF_COM_CNSR)\
	 -L$(SRC_DEP_SL) \
	 -L$(SRC_DER_RORD) -L$(SRC_COM_DT_EXT) \
		Executable_MakeFile_Builder_Main_File.cpp \
		Executable_MakeFile_Builder.cpp \
		$(EXC_MKF_COM_CNSR)\Executable_MakeFile_ComConstructor.cpp \
		$(SRC_DEP_DTR)\Source_File_Dependency_Determiner.cpp \
		$(SRC_COM_DT_EXT)\Source_File_Compiler_Data_Extractor.cpp \
	    $(SRC_DER_RORD)\Source_File_Dependency_ReOrderer.cpp \
		$(SRC_DEP_SL)\Source_File_Dependency_Selector.cpp \
		$(SRC_INF_COL)\Source_File_Information_Collector.cpp \
		$(FILE_LISTER)\Project_Files_Lister.cpp \
		$(FILE_DAT_COL)\Project_Files_Data_Collector.cpp \
		$(SRC_DT_COL)\Source_File_Data_Collector.cpp \
		$(GIT_LIST)\Git_File_List_Receiver.cpp \
		$(SOURCE_DETR)\Source_File_Determiner.cpp \
		$(DES_READER)\Descriptor_File_Reader.cpp \
		$(DES_DATA_COL)\Descriptor_File_Data_Collector.cpp \
		$(DES_FILE_SYNT_COL)\Descriptor_File_Syntax_Controller.cpp \
		$(HEAD_DET)\Header_File_Determiner.cpp \
		$(DIR_OPS)\DirectoryOperations.cpp \
		$(STRING_OPS)\StringOperator.cpp \
		$(CHAR_OPS)\CharOperator.cpp \
		$(CPP_OPS)\Cpp_FileOperations.cpp \
		$(INT_TO_CHAR)\IntToCharTranslater.cpp \
		-include Executable_MakeFile_Builder.hpp \
		-include $(EXC_MKF_COM_CNSR)\Executable_MakeFile_ComConstructor.hpp \
		-include $(SRC_DEP_DTR)\Source_File_Dependency_Determiner.hpp \
	    -include $(SRC_COM_DT_EXT)\Source_File_Compiler_Data_Extractor.hpp \
	    -include $(SRC_DER_RORD)\Source_File_Dependency_ReOrderer.hpp \
		-include $(SRC_DEP_SL)\Source_File_Dependency_Selector.hpp \
		-include $(SRC_INF_COL)\Source_File_Information_Collector.hpp \
		-include $(FILE_LISTER)\Project_Files_Lister.h \
		-include $(FILE_DAT_COL)\Project_Files_Data_Collector.hpp \
		-include $(SRC_DT_COL)\Source_File_Data_Collector.hpp \
		-include $(GIT_LIST)\Git_File_List_Receiver.hpp \
		-include $(DES_READER)\Descriptor_File_Reader.hpp \
		-include $(DES_DATA_COL)\Descriptor_File_Data_Collector.hpp \
		-include $(DES_FILE_SYNT_COL)\Descriptor_File_Syntax_Controller.hpp \
		-include $(SOURCE_DETR)\Source_File_Determiner.h \
		-include $(HEAD_DET)\Header_File_Determiner.h \
		-include $(STRING_OPS)\StringOperator.h \
		-include $(DIR_OPS)\DirectoryOperations.h \
	    -include $(CHAR_OPS)\CharOperator.h \
		-include $(CPP_OPS)\Cpp_FileOperations.h \
		-include $(INT_TO_CHAR)\IntToCharTranslater.h
