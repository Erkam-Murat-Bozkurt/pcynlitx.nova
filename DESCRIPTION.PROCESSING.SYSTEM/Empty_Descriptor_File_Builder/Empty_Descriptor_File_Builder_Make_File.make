
EMP_DES=D:\pcynlitx.build\DESCRIPTION.PROCESSING.SYSTEM\Empty_Descriptor_File_Builder
CPP_OPS=D:\pcynlitx.build\BASIC.TOOLS\Cpp_FileOperations

VPATH = $(CPP_OPS)

Empty_Descriptor_File_Builder.exe: Empty_Descriptor_File_Builder_Main_File.cpp \
	Empty_Descriptor_File_Builder.cpp Cpp_FileOperations.cpp Empty_Descriptor_File_Builder.hpp \
  Cpp_FileOperations.h

	g++ -std=c++17 -o Empty_Descriptor_File_Builder.exe -I$(CPP_OPS) -L$(CPP_OPS) \
		Empty_Descriptor_File_Builder_Main_File.cpp Empty_Descriptor_File_Builder.cpp \
		$(CPP_OPS)\Cpp_FileOperations.cpp \
		-include Empty_Descriptor_File_Builder.hpp -include $(CPP_OPS)\Cpp_FileOperations.h
