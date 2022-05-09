
# DEPENDEND FILES APTH DECLERATIONS

CPP_OPR=D:\pcynlitx.build\BASIC.TOOLS\Cpp_FileOperations
SYS_INT=D:\pcynlitx.build\BASIC.TOOLS\Custom_System_Interface
DIR_OPR=D:\pcynlitx.build\BASIC.TOOLS\DirectoryOperations
STR_OPR=D:\pcynlitx.build\BASIC.TOOLS\StringOperator
CHR_OPR=D:\pcynlitx.build\BASIC.TOOLS\CharOperator
LIB_UPD=D:\pcynlitx.build\PROJECT.BUILD.TOOLS\Library_Updater
DES_RED=D:\pcynlitx.build\DESCRIPTION.PROCESSING.SYSTEM\Descriptor_File_Reader
DES_DAT=D:\pcynlitx.build\DESCRIPTION.PROCESSING.SYSTEM\Descriptor_File_Data_Collector


VPATH = $(CPP_OPR) $(SYS_INT) $(DIR_OPR) $(CHR_OPR) \
				$(LIB_UPD) $(DES_RED) $(DES_DAT) $(STR_OPR)

Library_Updater.exe: Library_Updater_Main_File.cpp \
	Library_Updater.cpp \
	Descriptor_File_Reader.cpp \
	Descriptor_File_Data_Collector.cpp \
	DirectoryOperations.cpp \
	Cpp_FileOperations.cpp \
	Custom_System_Interface.cpp \
	Library_Updater.h \
	Descriptor_File_Reader.hpp \
	Descriptor_File_Data_Collector.hpp \
	DirectoryOperations.h \
	Cpp_FileOperations.h \
	Custom_System_Interface.h

	g++ -Wall -std=c++17 -o Library_Updater.exe \
	-I$(CPP_OPR) -I$(SYS_INT) \
	-I$(DIR_OPR) -I$(LIB_UPD) \
	-I$(DES_RED) -I$(DES_DAT) \
	-I$(STR_OPR) -I$(CHR_OPR) \
	-L$(STR_OPR) -L$(CHR_OPR) \
	-L$(CPP_OPR) -L$(SYS_INT) \
	-L$(DIR_OPR) -L$(LIB_UPD) \
	-L$(DES_RED) -L$(DES_DAT) \
	 $(LIB_UPD)\Library_Updater_Main_File.cpp \
	 $(LIB_UPD)\Library_Updater.cpp \
	 $(DES_RED)\Descriptor_File_Reader.cpp \
	 $(DES_DAT)\Descriptor_File_Data_Collector.cpp \
	 $(DIR_OPR)\DirectoryOperations.cpp \
	 $(STR_OPR)\StringOperator.cpp \
	 $(CHR_OPR)\CharOperator.cpp \
 	 $(CPP_OPR)\Cpp_FileOperations.cpp \
	 $(SYS_INT)\Custom_System_Interface.cpp \
	-include $(LIB_UPD)\Library_Updater.h \
	-include $(DES_RED)\Descriptor_File_Reader.hpp \
	-include $(DES_DAT)\Descriptor_File_Data_Collector.hpp \
	-include $(DIR_OPR)\DirectoryOperations.h \
	-include $(STR_OPR)\StringOperator.h \
	-include $(CHR_OPR)\CharOperator.h \
	-include $(CPP_OPR)\Cpp_FileOperations.h \
	-include $(SYS_INT)\Custom_System_Interface.h \
	-lshlwapi
