

STR_OPR=D:\pcynlitx.build\BASIC.TOOLS\StringOperator
DIR_OPS=D:\pcynlitx.build\BASIC.TOOLS\DirectoryOperations
FILE_OPRS=D:\pcynlitx.build\BASIC.TOOLS\Cpp_FileOperations
CHAR_OPR=D:\pcynlitx.build\BASIC.TOOLS\CharOperator
GIT_LIST=D:\pcynlitx.build\PROJECT.BUILD.TOOLS\Git_File_List_Receiver
DES_READ=D:\pcynlitx.build\DESCRIPTION.PROCESSING.SYSTEM\Description.Readers\Descriptor.File.Reader
DES_DATA_COL=D:\pcynlitx.build\DESCRIPTION.PROCESSING.SYSTEM\Description.Readers\Descriptor.File.Data.Collector
DES_SYNT_CON=D:\pcynlitx.build\DESCRIPTION.PROCESSING.SYSTEM\Description.Readers\Descriptor.File.Syntax.Controller

	VPATH = $(DIR_OPS) $(FILE_OPRS) $(GIT_LIST) $(DES_READ) \
					$(DES_DATA_COL) $(STR_OPR) $(CHAR_OPR) $(DES_SYNT_CON)

Project_Files_Data_Collector.exe: Project_Files_Data_Collector_Main_File.cpp \
	Project_Files_Data_Collector.cpp  \
	Git_File_List_Receiver.cpp  \
	Descriptor_File_Reader.cpp \
	Descriptor_File_Data_Collector.cpp \
	Descriptor_File_Syntax_Controller.cpp \
	DirectoryOperations.cpp \
	CharOperator.cpp \
	Cpp_FileOperations.cpp \
	Project_Files_Data_Collector.hpp \
	Git_File_List_Receiver.hpp \
	Descriptor_File_Reader.hpp \
	Descriptor_File_Data_Collector.hpp \
	Descriptor_File_Syntax_Controller.hpp \
	DirectoryOperations.h \
	CharOperator.h \
	Cpp_FileOperations.h

	g++ -std=c++17 -o Project_Files_Data_Collector.exe \
		-I$(GIT_LIST) -I$(DIR_OPS) -I$(FILE_OPRS) -I$(DES_READ) \
		-I$(DES_DATA_COL) -I$(STR_OPR) -I$(CHAR_OPR) -I$(DES_SYNT_CON) \
		-L$(GIT_LIST) -L$(DIR_OPS) -L$(FILE_OPRS) -L$(DES_READ) \
		-L$(DES_DATA_COL) -L$(STR_OPR) -L$(CHAR_OPR) -L$(DES_SYNT_CON) \
	 	Project_Files_Data_Collector_Main_File.cpp \
		Project_Files_Data_Collector.cpp \
		$(GIT_LIST)\Git_File_List_Receiver.cpp \
	 	$(DES_READ)\Descriptor_File_Reader.cpp \
	 	$(DES_DATA_COL)\Descriptor_File_Data_Collector.cpp \
		$(DES_SYNT_CON)\Descriptor_File_Syntax_Controller.cpp \
		$(STR_OPR)\StringOperator.cpp\
	 	$(DIR_OPS)\DirectoryOperations.cpp \
		$(CHAR_OPR)\CharOperator.cpp \
	 	$(FILE_OPRS)\Cpp_FileOperations.cpp \
		-include Project_Files_Data_Collector.hpp \
	 	-include $(GIT_LIST)\Git_File_List_Receiver.hpp \
		-include $(DES_READ)\Descriptor_File_Reader.hpp \
	 	-include $(STR_OPR)\StringOperator.h \
		-include $(DES_DATA_COL)\Descriptor_File_Data_Collector.hpp \
		-include $(DES_SYNT_CON)\Descriptor_File_Syntax_Controller.hpp \
	 	-include $(DIR_OPS)\DirectoryOperations.h \
		-include $(CHAR_OPR)\CharOperator.h \
	 	-include $(FILE_OPRS)\Cpp_FileOperations.h
