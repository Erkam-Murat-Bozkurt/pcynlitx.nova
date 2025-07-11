
DIR_OPS=C:\Development.Files\pcynlitx.build\BASIC.TOOLS\DirectoryOperations
CPP_OPS=C:\Development.Files\pcynlitx.build\BASIC.TOOLS\Cpp_FileOperations
CHAR_OPS=C:\Development.Files\pcynlitx.build\BASIC.TOOLS\CharOperator
DOC_OPS=C:\Development.Files\pcynlitx.build\INSTALLER.DEVELOPMENT\COPYRIGHT.DOCUMENT.CONSTRUCTOR\Document_Builder

VPATH = $(DIR_OPS) $(CPP_OPS) $(CHAR_OPS) $(DOC_OPS)

Convert_Repo_To_Source.exe: Convert_Repo_To_Single_File_Main_File.cpp \
	Convert_Repo_To_Single_File.cpp Document_Builder.cpp DirectoryOperations.cpp CharOperator.cpp \
	Cpp_FileOperations.cpp Convert_Repo_To_Single_File.h Document_Builder.h DirectoryOperations.h \
	CharOperator.h Cpp_FileOperations.h\

	g++ -o Convert_Repo_To_Source.exe -I$(DIR_OPS) -I$(CPP_OPS) -I$(DOC_OPS) -I$(CHAR_OPS) \
	  -L$(DOC_OPS) -L$(DIR_OPS) -L$(CPP_OPS) -L$(CHAR_OPS) \
		Convert_Repo_To_Single_File_Main_File.cpp Convert_Repo_To_Single_File.cpp $(DOC_OPS)\Document_Builder.cpp  \
		$(DIR_OPS)\DirectoryOperations.cpp $(CHAR_OPS)\CharOperator.cpp \
		$(CPP_OPS)\Cpp_FileOperations.cpp -include Convert_Repo_To_Single_File.h \
		-include $(DOC_OPS)\Document_Builder.h -include $(DIR_OPS)\DirectoryOperations.h \
		-include $(CHAR_OPS)\CharOperator.h \
		-include $(CPP_OPS)\Cpp_FileOperations.h
