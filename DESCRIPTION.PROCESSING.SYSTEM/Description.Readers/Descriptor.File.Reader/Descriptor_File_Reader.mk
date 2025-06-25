
GUI_DES_RED=C:\Development.Files\pcynlitx.build\DESCRIPTION.PROCESSING.SYSTEM\Description.Readers\GUI.Descriptor.File.Reader
DES_RED=C:\Development.Files\pcynlitx.build\DESCRIPTION.PROCESSING.SYSTEM\Description.Readers\Descriptor.File.Reader
DES_COL=C:\Development.Files\pcynlitx.build\DESCRIPTION.PROCESSING.SYSTEM\Description.Readers\Descriptor.File.Data.Collector
SYN_CON=C:\Development.Files\pcynlitx.build\DESCRIPTION.PROCESSING.SYSTEM\Description.Readers\Descriptor.File.Syntax.Controller
NUM_DET=C:\Development.Files\pcynlitx.build\DESCRIPTION.PROCESSING.SYSTEM\Description.Readers\Record.Number.Determiner
LIN_RED=C:\Development.Files\pcynlitx.build\DESCRIPTION.PROCESSING.SYSTEM\Description.Readers\Descriptor.File.Line.Reader


CPP_OPS=C:\Development.Files\pcynlitx.build\BASIC.TOOLS\Cpp_FileOperations
STRING_OPS=C:\Development.Files\pcynlitx.build\BASIC.TOOLS\StringOperator
CHAR_OPS=C:\Development.Files\pcynlitx.build\BASIC.TOOLS\CharOperator


VPATH = $(DES_RED) \
	    $(DES_COL) \
		$(CPP_OPS) \
		$(STRING_OPS) \
		$(CHAR_OPS) \
		$(SYN_CON) \
		$(NUM_DET) \
		$(LIN_RED) \
		$(GUI_DES_RED)



GUI_Descriptor_File_Reader.exe : GUI_Descriptor_File_Reader_Main_File.cpp \
	GUI_Descriptor_File_Reader.o \
	Record_Number_Determiner.o \
	Descriptor_File_Line_Reader.o \
	Descriptor_File_Data_Collector.o \
	Descriptor_File_Syntax_Controller.o \
	StringOperator.o \
	CharOperator.o \
	Cpp_FileOperations.o \
	GUI_Descriptor_File_Reader.hpp \
    Descriptor_File_Reader.hpp \
	Record_Number_Determiner.hpp \
	Descriptor_File_Line_Reader.hpp \
	Descriptor_File_Data_Collector.hpp \
	Descriptor_File_Syntax_Controller.hpp \
	StringOperator.h CharOperator.h Cpp_FileOperations.h

	g++ -std=c++17 \
	  -o GUI_Descriptor_File_Reader.exe \
	  -I$(GUI_DES_RED) \
	  -I$(DES_RED) \
	  -I$(DES_COL) -I$(CPP_OPS) -I$(STRING_OPS) \
		-I$(SYN_CON) -I$(CHAR_OPS) \
		-I$(NUM_DET) -I$(LIN_RED) \
		-L$(CPP_OPS) -L$(STRING_OPS) \
		-L$(NUM_DET) -L$(LIN_RED) \
		-L$(CHAR_OPS) -L$(DES_COL) -L$(SYN_CON) \
		-L$(GUI_DES_RED) \
		GUI_Descriptor_File_Reader_Main_File.cpp \
		$(DES_RED)\GUI_Descriptor_File_Reader.o \
		$(DES_RED)\Descriptor_File_Data_Collector.o \
		$(DES_RED)\Descriptor_File_Syntax_Controller.o \
		$(DES_RED)\Record_Number_Determiner.o \
		$(DES_RED)\Descriptor_File_Line_Reader.o \
	    $(DES_RED)\StringOperator.o \
		$(DES_RED)\CharOperator.o \
		$(DES_RED)\Cpp_FileOperations.o \
		-include $(GUI_DES_RED)\GUI_Descriptor_File_Reader.hpp \
		-include $(DES_RED)\Descriptor_File_Reader.hpp \
		-include $(NUM_DET)\Record_Number_Determiner.hpp \
		-include $(LIN_RED)\Descriptor_File_Line_Reader.hpp \
		-include $(DES_COL)\Descriptor_File_Data_Collector.hpp \
		-include $(SYN_CON)\Descriptor_File_Syntax_Controller.hpp \
		-include $(STRING_OPS)\StringOperator.h \
		-include $(CHAR_OPS)\CharOperator.h \
		-include $(CPP_OPS)\Cpp_FileOperations.h




Descriptor_File_Reader.exe : Descriptor_File_Reader_Main_File.cpp \
	Descriptor_File_Reader.o \
	Record_Number_Determiner.o \
	Descriptor_File_Line_Reader.o \
	Descriptor_File_Data_Collector.o \
	Descriptor_File_Syntax_Controller.o \
	StringOperator.o \
	CharOperator.o \
	Cpp_FileOperations.o \
    Descriptor_File_Reader.hpp \
	Record_Number_Determiner.hpp \
	Descriptor_File_Line_Reader.hpp \
	Descriptor_File_Data_Collector.hpp \
	Descriptor_File_Syntax_Controller.hpp \
	StringOperator.h CharOperator.h Cpp_FileOperations.h

	g++ -std=c++17 \
	  -o Descriptor_File_Reader.exe \
	  -I$(DES_COL) -I$(CPP_OPS) -I$(STRING_OPS) \
		-I$(SYN_CON) -I$(CHAR_OPS) \
		-I$(NUM_DET) -I$(LIN_RED) \
		-L$(CPP_OPS) -L$(STRING_OPS) \
		-L$(NUM_DET) -L$(LIN_RED) \
		-L$(CHAR_OPS) -L$(DES_COL) -L$(SYN_CON) \
		GUI_Descriptor_File_Reader_Main_File.cpp \
		$(DES_RED)\Descriptor_File_Reader.o \
		$(DES_RED)\Descriptor_File_Data_Collector.o \
		$(DES_RED)\Descriptor_File_Syntax_Controller.o \
		$(DES_RED)\Record_Number_Determiner.o \
		$(DES_RED)\Descriptor_File_Line_Reader.o \
	    $(DES_RED)\StringOperator.o \
		$(DES_RED)\CharOperator.o \
		$(DES_RED)\Cpp_FileOperations.o \
		-include $(DES_RED)\Descriptor_File_Reader.hpp \
		-include $(NUM_DET)\Record_Number_Determiner.hpp \
		-include $(LIN_RED)\Descriptor_File_Line_Reader.hpp \
		-include $(DES_COL)\Descriptor_File_Data_Collector.hpp \
		-include $(SYN_CON)\Descriptor_File_Syntax_Controller.hpp \
		-include $(STRING_OPS)\StringOperator.h \
		-include $(CHAR_OPS)\CharOperator.h \
		-include $(CPP_OPS)\Cpp_FileOperations.h



GUI_Descriptor_File_Reader.o : GUI_Descriptor_File_Reader.cpp \
    GUI_Descriptor_File_Reader.hpp \
	Record_Number_Determiner.hpp \
	Descriptor_File_Line_Reader.hpp \
	Descriptor_File_Data_Collector.hpp \
	Descriptor_File_Syntax_Controller.hpp \
	StringOperator.h \
	CharOperator.h \
	Cpp_FileOperations.h

	g++ -std=c++17 -c \
	    -I$(DES_COL) -I$(CPP_OPS) -I$(STRING_OPS) \
		-I$(SYN_CON) -I$(CHAR_OPS) -I$(DES_RED) \
		-I$(NUM_DET) -I$(LIN_RED) \
		-I$(GUI_DES_RED) \
		-L$(CPP_OPS) -L$(STRING_OPS) \
		-L$(NUM_DET) -L$(LIN_RED) \
		-L$(CHAR_OPS) -L$(DES_COL) -L$(SYN_CON) \
		-L$(GUI_DES_RED) \
		$(GUI_DES_RED)\GUI_Descriptor_File_Reader.cpp \
		-include $(GUI_DES_RED)\GUI_Descriptor_File_Reader.hpp \
		-include $(DES_RED)\Descriptor_File_Reader.hpp \
		-include $(NUM_DET)\Record_Number_Determiner.hpp \
		-include $(LIN_RED)\Descriptor_File_Line_Reader.hpp \
		-include $(DES_COL)\Descriptor_File_Data_Collector.hpp \
		-include $(SYN_CON)\Descriptor_File_Syntax_Controller.hpp \
		-include $(STRING_OPS)\StringOperator.h \
		-include $(CHAR_OPS)\CharOperator.h \
		-include $(CPP_OPS)\Cpp_FileOperations.h



Descriptor_File_Reader.o : Descriptor_File_Reader.cpp \
    Descriptor_File_Reader.hpp \
	Record_Number_Determiner.hpp \
	Descriptor_File_Line_Reader.hpp \
	Descriptor_File_Data_Collector.hpp \
	Descriptor_File_Syntax_Controller.hpp \
	StringOperator.h \
	CharOperator.h \
	Cpp_FileOperations.h

	g++ -std=c++17 -c \
	  -I$(DES_COL) -I$(CPP_OPS) -I$(STRING_OPS) \
		-I$(SYN_CON) -I$(CHAR_OPS) \
		-I$(NUM_DET) -I$(LIN_RED) \
		-L$(CPP_OPS) -L$(STRING_OPS) \
		-L$(NUM_DET) -L$(LIN_RED) \
		-L$(CHAR_OPS) -L$(DES_COL) -L$(SYN_CON) \
		$(DES_RED)\Descriptor_File_Reader.cpp \
		-include $(DES_RED)\Descriptor_File_Reader.hpp \
		-include $(NUM_DET)\Record_Number_Determiner.hpp \
		-include $(LIN_RED)\Descriptor_File_Line_Reader.hpp \
		-include $(DES_COL)\Descriptor_File_Data_Collector.hpp \
		-include $(SYN_CON)\Descriptor_File_Syntax_Controller.hpp \
		-include $(STRING_OPS)\StringOperator.h \
		-include $(CHAR_OPS)\CharOperator.h \
		-include $(CPP_OPS)\Cpp_FileOperations.h


Record_Number_Determiner.o : Record_Number_Determiner.cpp \
	Record_Number_Determiner.hpp \
	Descriptor_File_Data_Collector.hpp \
	Descriptor_File_Syntax_Controller.hpp \
	StringOperator.h CharOperator.h Cpp_FileOperations.h

	g++ -std=c++17 -c \
	  -I$(DES_COL) -I$(CPP_OPS) -I$(STRING_OPS) \
		-I$(SYN_CON) -I$(CHAR_OPS) \
		-I$(NUM_DET) -I$(LIN_RED) \
		-L$(CPP_OPS) -L$(STRING_OPS) \
		-L$(NUM_DET) -L$(LIN_RED) \
		-L$(CHAR_OPS) -L$(DES_COL) -L$(SYN_CON) \
		$(NUM_DET)\Record_Number_Determiner.cpp \
		-include $(NUM_DET)\Record_Number_Determiner.hpp \
		-include $(DES_COL)\Descriptor_File_Data_Collector.hpp \
		-include $(SYN_CON)\Descriptor_File_Syntax_Controller.hpp \
		-include $(STRING_OPS)\StringOperator.h \
		-include $(CHAR_OPS)\CharOperator.h \
		-include $(CPP_OPS)\Cpp_FileOperations.h


Descriptor_File_Line_Reader.o : Descriptor_File_Line_Reader.cpp \
	Descriptor_File_Line_Reader.hpp \
	Descriptor_File_Data_Collector.hpp \
	Descriptor_File_Syntax_Controller.hpp \
	StringOperator.h \
	CharOperator.h \
	Cpp_FileOperations.h

	g++ -std=c++17 -c \
	    -I$(DES_COL) -I$(CPP_OPS) -I$(STRING_OPS) \
		-I$(SYN_CON) -I$(CHAR_OPS) \
		-I$(NUM_DET) -I$(LIN_RED) \
		-L$(CPP_OPS) -L$(STRING_OPS) \
		-L$(NUM_DET) -L$(LIN_RED) \
		-L$(CHAR_OPS) -L$(DES_COL) -L$(SYN_CON) \
		$(LIN_RED)\Descriptor_File_Line_Reader.cpp \
		-include $(LIN_RED)\Descriptor_File_Line_Reader.hpp \
		-include $(DES_COL)\Descriptor_File_Data_Collector.hpp \
		-include $(SYN_CON)\Descriptor_File_Syntax_Controller.hpp \
		-include $(STRING_OPS)\StringOperator.h \
		-include $(CHAR_OPS)\CharOperator.h \
		-include $(CPP_OPS)\Cpp_FileOperations.h



Descriptor_File_Data_Collector.o : Descriptor_File_Data_Collector.cpp \
	Descriptor_File_Data_Collector.hpp \
	Descriptor_File_Syntax_Controller.hpp \
	StringOperator.h \
	CharOperator.h \
	Cpp_FileOperations.h

	g++ -std=c++17 -c \
	  -I$(DES_COL) -I$(CPP_OPS) -I$(STRING_OPS) \
		-I$(SYN_CON) -I$(CHAR_OPS) \
		-I$(NUM_DET) -I$(LIN_RED) \
		-L$(CPP_OPS) -L$(STRING_OPS) \
		-L$(NUM_DET) -L$(LIN_RED) \
		-L$(CHAR_OPS) -L$(DES_COL) -L$(SYN_CON) \
		$(DES_COL)\Descriptor_File_Data_Collector.cpp \
		-include $(DES_COL)\Descriptor_File_Data_Collector.hpp \
		-include $(SYN_CON)\Descriptor_File_Syntax_Controller.hpp \
		-include $(STRING_OPS)\StringOperator.h \
		-include $(CHAR_OPS)\CharOperator.h \
		-include $(CPP_OPS)\Cpp_FileOperations.h




Descriptor_File_Syntax_Controller.o : Descriptor_File_Syntax_Controller.cpp \
	Descriptor_File_Syntax_Controller.hpp \
	StringOperator.h \
	CharOperator.h \
	Cpp_FileOperations.h

	g++ -std=c++17 -c \
	  -I$(DES_COL) -I$(CPP_OPS) -I$(STRING_OPS) \
		-I$(SYN_CON) -I$(CHAR_OPS) \
		-I$(NUM_DET) -I$(LIN_RED) \
		-L$(CPP_OPS) -L$(STRING_OPS) \
		-L$(NUM_DET) -L$(LIN_RED) \
		-L$(CHAR_OPS) -L$(DES_COL) -L$(SYN_CON) \
		$(SYN_CON)\Descriptor_File_Syntax_Controller.cpp \
		-include $(SYN_CON)\Descriptor_File_Syntax_Controller.hpp \
		-include $(STRING_OPS)\StringOperator.h \
		-include $(CHAR_OPS)\CharOperator.h \
		-include $(CPP_OPS)\Cpp_FileOperations.h



StringOperator.o : StringOperator.cpp \
	StringOperator.h \
	CharOperator.h \
	Cpp_FileOperations.h

	g++ -std=c++17 -c \
	    -I$(CPP_OPS) -I$(STRING_OPS) \
		-I$(CHAR_OPS) \
		-L$(CPP_OPS) -L$(STRING_OPS) \
		-L$(CHAR_OPS) \
		$(STRING_OPS)\StringOperator.cpp \
		-include $(STRING_OPS)\StringOperator.h \
		-include $(CHAR_OPS)\CharOperator.h \
		-include $(CPP_OPS)\Cpp_FileOperations.h



CharOperator.o : CharOperator.cpp \
	CharOperator.h \
	Cpp_FileOperations.h

	g++ -std=c++17 -c \
	    -I$(CPP_OPS) \
		-I$(CHAR_OPS) \
		-L$(CPP_OPS) \
		-L$(CHAR_OPS) \
		$(CHAR_OPS)\CharOperator.cpp \
		-include $(CHAR_OPS)\CharOperator.h \
		-include $(CPP_OPS)\Cpp_FileOperations.h



Cpp_FileOperations.o : Cpp_FileOperations.cpp \
	Cpp_FileOperations.h

	g++ -std=c++17 -c \
	   -I$(CPP_OPS) \
		-L$(CPP_OPS) \
		$(CPP_OPS)\Cpp_FileOperations.cpp \
		-include $(CPP_OPS)\Cpp_FileOperations.h