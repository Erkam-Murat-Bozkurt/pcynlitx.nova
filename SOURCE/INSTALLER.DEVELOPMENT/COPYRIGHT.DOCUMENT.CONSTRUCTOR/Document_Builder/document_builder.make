
CPP_OPS=C:\Development.Files\pcynlitx.build\BASIC.TOOLS\Cpp_FileOperations
DOC_BUL=C:\Development.Files\pcynlitx.build\INSTALLER.DEVELOPMENT\COPYRIGHT.DOCUMENT.CONSTRUCTOR\Document_Builder

VPATH = $(CPP_OPS) $(DOC_BUL)

Document_Builder: Document_Builder_Main_File.cpp Document_Builder.cpp \
	Cpp_FileOperations.cpp  Document_Builder.h Cpp_FileOperations.h

	g++ -o Document_Builder.exe -I$(CPP_OPS) -I$(DOC_BUL) -L$(DOC_BUL) -L$(CPP_OPS) \
		Document_Builder_Main_File.cpp $(DOC_BUL)\Document_Builder.cpp \
		$(CPP_OPS)\Cpp_FileOperations.cpp \
		-include $(DOC_BUL)\Document_Builder.h -include $(CPP_OPS)\Cpp_FileOperations.h
