
INT_TRANS=D:\pcynlitx.build\BASIC.TOOLS\IntToCharTranslater
STRING_OPS=D:\pcynlitx.build\BASIC.TOOLS\StringOperator
DIR_OPS=D:\pcynlitx.build\BASIC.TOOLS\DirectoryOperations
CHAR_OPS=D:\pcynlitx.build\BASIC.TOOLS\CharOperator
FILE_OPRS=D:\pcynlitx.build\BASIC.TOOLS\Cpp_FileOperations
GIT_LIST=D:\pcynlitx.build\PROJECT.BUILD.TOOLS\Git_File_List_Receiver
DES_READ=D:\pcynlitx.build\DESCRIPTION.PROCESSING.SYSTEM\Description.Readers\Descriptor.File.Reader
DES_DATA_COL=D:\pcynlitx.build\DESCRIPTION.PROCESSING.SYSTEM\Description.Readers\Descriptor.File.Data.Collector
DES_SYN_CON=D:\pcynlitx.build\DESCRIPTION.PROCESSING.SYSTEM\Description.Readers\Descriptor.File.Syntax.Controller
SRC_DT_COL=D:\pcynlitx.build\SOURCE.FILE.DATA.COLLECTORS\Source_File_Data_Collector
FILE_DAT_COL=D:\pcynlitx.build\SOURCE.FILE.DATA.COLLECTORS\Project_Files_Data_Collector


VPATH = $(DIR_OPS) $(STRING_OPS) $(CHAR_OPS) $(FILE_OPRS) \
				$(DES_READ) $(DES_DATA_COL) $(GIT_LIST) $(SRC_DT_COL) \
				$(DES_SYN_CON) $(INT_TRANS) $(FILE_DAT_COL)

Source_File_Data_Collector.exe: Source_File_Data_Collector_Main_File.cpp \
	Source_File_Data_Collector.cpp  \
	Git_File_List_Receiver.cpp \
	Project_Files_Data_Collector.cpp \
	Descriptor_File_Reader.cpp \
	Descriptor_File_Data_Collector.cpp \
	Descriptor_File_Syntax_Controller.cpp \
	StringOperator.cpp \
	CharOperator.cpp \
	IntToCharTranslater.cpp \
	Cpp_FileOperations.cpp \
	Source_File_Data_Collector.hpp \
	Project_Files_Data_Collector.hpp \
	Git_File_List_Receiver.hpp \
	StringOperator.h \
	DirectoryOperations.h \
	CharOperator.h \
	IntToCharTranslater.h \
	Cpp_FileOperations.h

	g++ -std=c++17 -g -o Source_File_Data_Collector.exe \
	 -I. \
	 -I$(DIR_OPS) \
	 -I$(STRING_OPS) \
	 -I$(CHAR_OPS) \
	 -I$(FILE_OPRS) \
	 -I$(DES_READ) \
	 -I$(DES_DATA_COL) \
	 -I$(GIT_LIST) \
	 -I$(SRC_DT_COL) \
	 -I$(DES_SYN_CON) \
	 -I$(INT_TRANS) \
	 -I$(FILE_DAT_COL) \
	 -L$(DIR_OPS) \
	 -L$(STRING_OPS) \
	 -L$(GIT_LIST) \
	 -L$(CHAR_OPS) \
	 -L$(FILE_OPRS) \
	 -L$(DES_READ) \
	 -L$(DES_DATA_COL) \
	 -L$(SRC_DT_COL) \
	 -L$(DES_SYN_CON) \
	 -L$(INT_TRANS) \
	 -L$(FILE_DAT_COL) \
		$(SRC_DT_COL)\Source_File_Data_Collector_Main_File.cpp \
		$(SRC_DT_COL)\Source_File_Data_Collector.cpp \
		$(FILE_DAT_COL)\Project_Files_Data_Collector.cpp \
		$(DES_READ)\Descriptor_File_Reader.cpp \
		$(DES_DATA_COL)\Descriptor_File_Data_Collector.cpp \
		$(DES_SYN_CON)\Descriptor_File_Syntax_Controller.cpp \
		$(GIT_LIST)\Git_File_List_Receiver.cpp \
		$(DIR_OPS)\DirectoryOperations.cpp \
		$(STRING_OPS)\StringOperator.cpp \
		$(CHAR_OPS)\CharOperator.cpp \
		$(INT_TRANS)\IntToCharTranslater.cpp \
		$(FILE_OPRS)\Cpp_FileOperations.cpp \
		-include $(SRC_DT_COL)\Source_File_Data_Collector.hpp \
		-include $(GIT_LIST)\Git_File_List_Receiver.hpp \
		-include $(FILE_DAT_COL)\Project_Files_Data_Collector.hpp \
		-include $(DES_READ)\Descriptor_File_Reader.hpp \
		-include $(SRC_DT_COL)\Source_File_Data_Collector.hpp \
		-include $(DES_DATA_COL)\Descriptor_File_Data_Collector.hpp \
		-include $(DES_SYN_CON)\Descriptor_File_Syntax_Controller.hpp \
		-include $(STRING_OPS)\StringOperator.h \
		-include $(DIR_OPS)\DirectoryOperations.h \
		-include $(CHAR_OPS)\CharOperator.h \
		-include $(INT_TRANS)\IntToCharTranslater.h \
		-include $(FILE_OPRS)\Cpp_FileOperations.h
