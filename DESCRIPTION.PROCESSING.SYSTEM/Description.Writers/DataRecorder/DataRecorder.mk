
STRING_OPS=D:\pcynlitx.build\BASIC.TOOLS\StringOperator
CHAR_OPS=D:\pcynlitx.build\BASIC.TOOLS\CharOperator
FILE_OPRS=D:\pcynlitx.build\BASIC.TOOLS\Cpp_FileOperations
DTR_REC=D:\pcynlitx.build\DESCRIPTION.PROCESSING.SYSTEM\Description.Writers\DataRecorder

VPATH = $(STRING_OPS) $(CHAR_OPS) $(FILE_OPRS) $(DTR_REC)

DataRecorder.exe : DataRecorder_Main_File.cpp DataRecorder.cpp DataRecorder.h \
	StringOperator.cpp CharOperator.cpp Cpp_FileOperations.cpp \
	StringOperator.h CharOperator.h Cpp_FileOperations.h

	g++ -std=c++17 -o DataRecorder.exe \
	-I$(STRING_OPS) -I$(CHAR_OPS) \
	-I$(FILE_OPRS) -I$(DTR_REC) \
	-L$(STRING_OPS) -L$(CHAR_OPS) \
	-L$(FILE_OPRS) -L$(DTR_REC) \
	$(DTR_REC)\DataRecorder_Main_File.cpp \
	$(DTR_REC)\DataRecorder.cpp \
	$(STRING_OPS)\StringOperator.cpp \
	$(CHAR_OPS)\CharOperator.cpp \
	$(FILE_OPRS)\Cpp_FileOperations.cpp \
	-include $(DTR_REC)\DataRecorder.h \
	-include $(STRING_OPS)\StringOperator.h \
	-include $(CHAR_OPS)\CharOperator.h \
	-include $(FILE_OPRS)\Cpp_FileOperations.h
