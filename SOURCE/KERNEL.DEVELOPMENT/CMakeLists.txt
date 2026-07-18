

set(NOVA_SRC_DIR "${CMAKE_SOURCE_DIR}/SOURCE")


add_library(kernel 

    ${NOVA_SRC_DIR}/KERNEL.DEVELOPMENT/Kernel_Main_File.cpp

    ${NOVA_SRC_DIR}/KERNEL.DEVELOPMENT/Kernel.cpp

    ${NOVA_SRC_DIR}/KERNEL.DEVELOPMENT/Kernel.hpp
)


target_include_directories(kernel PUBLIC


    ${NOVA_SRC_DIR}/KERNEL.DEVELOPMENT

    ${NOVA_SRC_DIR}/Build_Tools_Initializer

    ${NOVA_SRC_DIR}/Directory_Enumerator

    ${NOVA_SRC_DIR}/Directory_Tree_Size_Determiner


    ${NOVA_SRC_DIR}/PROJECT.BUILD.TOOLS/Library_Name_Extractor

    ${NOVA_SRC_DIR}/PROJECT.BUILD.TOOLS/Library_Updater

    ${NOVA_SRC_DIR}/PROJECT.BUILD.TOOLS/Project_Src_Code_Rdr

    ${NOVA_SRC_DIR}/PROJECT.BUILD.TOOLS/Repo_Dir_Determiner

    ${NOVA_SRC_DIR}/PROJECT.BUILD.TOOLS/Repo_Warehouse_Initializer




    ${NOVA_SRC_DIR}/EXECUTABLE.MAKE.FILE.BUILD.SYSTEM/Executable_MakeFile_Builder
    
    ${NOVA_SRC_DIR}/EXECUTABLE.MAKE.FILE.BUILD.SYSTEM/Executable_MakeFile_ComConstructor
    
    ${NOVA_SRC_DIR}/EXECUTABLE.MAKE.FILE.BUILD.SYSTEM/Executable_MakeFile_Script_Builder

    

    ${NOVA_SRC_DIR}/DESCRIPTION.PROCESSING.SYSTEM/Description.Readers/Descriptor.File.Data.Collector

    ${NOVA_SRC_DIR}/DESCRIPTION.PROCESSING.SYSTEM/Description.Readers/Descriptor.File.Reader

    ${NOVA_SRC_DIR}/DESCRIPTION.PROCESSING.SYSTEM/Description.Readers/Descriptor.File.Syntax.Controller


    ${NOVA_SRC_DIR}/DESCRIPTION.PROCESSING.SYSTEM/Description.Writers/Empty.Descriptor.File.Builder

    ${NOVA_SRC_DIR}/DESCRIPTION.PROCESSING.SYSTEM/Description.Writers/DataRecorder



    ${NOVA_SRC_DIR}/SOURCE.FILE.PROCESSING.SYSTEM/Header_File_Processor

    ${NOVA_SRC_DIR}/SOURCE.FILE.PROCESSING.SYSTEM/Source_File_Compiler_Data_Extractor

    ${NOVA_SRC_DIR}/SOURCE.FILE.PROCESSING.SYSTEM/Source_File_Dependency_Determiner

    ${NOVA_SRC_DIR}/SOURCE.FILE.PROCESSING.SYSTEM/Source_File_Dependency_Selector_For_Single_File

    ${NOVA_SRC_DIR}/SOURCE.FILE.PROCESSING.SYSTEM/Source_File_Dependency_Selector

    ${NOVA_SRC_DIR}/SOURCE.FILE.PROCESSING.SYSTEM/Dependency_Data_Extractor

    ${NOVA_SRC_DIR}/SOURCE.FILE.PROCESSING.SYSTEM/Source_File_Information_Collector_For_Single_File

    ${NOVA_SRC_DIR}/SOURCE.FILE.PROCESSING.SYSTEM/Source_File_Data_Setter

    ${NOVA_SRC_DIR}/SOURCE.FILE.PROCESSING.SYSTEM/Source_File_Information_Collector

    ${NOVA_SRC_DIR}/SOURCE.FILE.PROCESSING.SYSTEM/Source_File_Processor

    ${NOVA_SRC_DIR}/SOURCE.FILE.PROCESSING.SYSTEM/Quick_Src_Dependency_Extractor

    ${NOVA_SRC_DIR}/SOURCE.FILE.PROCESSING.SYSTEM/Dependency_Data_Stack_Container

    ${NOVA_SRC_DIR}/SOURCE.FILE.PROCESSING.SYSTEM/Header_Dependency_Data_Extractor

    ${NOVA_SRC_DIR}/SOURCE.FILE.PROCESSING.SYSTEM/Dependency_Data_Processor



    ${NOVA_SRC_DIR}/SCRIPT.WRITERS/Include_Dependency_Counter

    ${NOVA_SRC_DIR}/SCRIPT.WRITERS/Project_Script_Writer

    ${NOVA_SRC_DIR}/SCRIPT.WRITERS/Script_Data_Collector

    ${NOVA_SRC_DIR}/SCRIPT.WRITERS/Script_Data_Processor

    ${NOVA_SRC_DIR}/SCRIPT.WRITERS/Source_File_Script_Writer



    ${NOVA_SRC_DIR}/GIT.DATA.PROCESSING.SYSTEM/Git_Data_Processor

    ${NOVA_SRC_DIR}/GIT.DATA.PROCESSING.SYSTEM/Git_File_List_Receiver

    ${NOVA_SRC_DIR}/GIT.DATA.PROCESSING.SYSTEM/Git_File_List_Writer

    ${NOVA_SRC_DIR}/GIT.DATA.PROCESSING.SYSTEM/Git_Ignoring_Files_Lister

    ${NOVA_SRC_DIR}/GIT.DATA.PROCESSING.SYSTEM/Git_Modification_Lister

    ${NOVA_SRC_DIR}/GIT.DATA.PROCESSING.SYSTEM/Git_Modification_Receiver



    ${NOVA_SRC_DIR}/SOURCE.FILE.DATA.COLLECTORS/Header_File_Determiner

    ${NOVA_SRC_DIR}/SOURCE.FILE.DATA.COLLECTORS/Source_File_Data_Collector

    ${NOVA_SRC_DIR}/SOURCE.FILE.DATA.COLLECTORS/Source_File_Determiner


    ${NOVA_SRC_DIR}/MAKE.FILE.BUILD.SYSTEM/Auto_MakeFile_Builder    

    ${NOVA_SRC_DIR}/MAKE.FILE.BUILD.SYSTEM/Make_File_Builder    

    ${NOVA_SRC_DIR}/MAKE.FILE.BUILD.SYSTEM/Make_File_Cleaner    

    ${NOVA_SRC_DIR}/MAKE.FILE.BUILD.SYSTEM/MakeFile_Data_Collector    

    ${NOVA_SRC_DIR}/MAKE.FILE.BUILD.SYSTEM/MakeFile_Directory_Constructor 

    ${NOVA_SRC_DIR}/MAKE.FILE.BUILD.SYSTEM/MakeFile_Path_Determiner    


    ${NOVA_SRC_DIR}/CMAKE.LISTS.FILE.BUILD.SYSTEM/CMAKE_Build_System_Generator

    ${NOVA_SRC_DIR}/CMAKE.LISTS.FILE.BUILD.SYSTEM/CMAKE_System_Constructor

    ${NOVA_SRC_DIR}/CMAKE.LISTS.FILE.BUILD.SYSTEM/CMAKE_Main_File_Writer

    ${NOVA_SRC_DIR}/CMAKE.LISTS.FILE.BUILD.SYSTEM/CMake_Target_Library_Builder    

    ${NOVA_SRC_DIR}/CMAKE.LISTS.FILE.BUILD.SYSTEM/CMAKE_Executable_Target_Constructor

    ${NOVA_SRC_DIR}/CMAKE.LISTS.FILE.BUILD.SYSTEM/CMAKE_Target_List_Data_Processor

    ${NOVA_SRC_DIR}/CMAKE.LISTS.FILE.BUILD.SYSTEM/CMAKE_Target_List_Determiner

    ${NOVA_SRC_DIR}/CMAKE.LISTS.FILE.BUILD.SYSTEM/Build_System_Meta_Data_Collector

    ${NOVA_SRC_DIR}/CMAKE.LISTS.FILE.BUILD.SYSTEM/CMAKE_Target_List_Data_Structure_Constructor



    ${NOVA_SRC_DIR}/BASIC.TOOLS/Cpp_FileOperations

    ${NOVA_SRC_DIR}/BASIC.TOOLS/Custom_System_Interface

    ${NOVA_SRC_DIR}/BASIC.TOOLS/DirectoryOperations

    ${NOVA_SRC_DIR}/BASIC.TOOLS/IntToCharTranslater

    ${NOVA_SRC_DIR}/BASIC.TOOLS/StringOperator

    ${NOVA_SRC_DIR}/BASIC.TOOLS/Custom_System_Interface

)


target_link_directories(kernel PUBLIC 


    ${NOVA_SRC_DIR}/KERNEL.DEVELOPMENT


    ${NOVA_SRC_DIR}/EXECUTABLE.MAKE.FILE.BUILD.SYSTEM/Executable_MakeFile_Builder
    
    ${NOVA_SRC_DIR}/EXECUTABLE.MAKE.FILE.BUILD.SYSTEM/Executable_MakeFile_ComConstructor

    ${NOVA_SRC_DIR}/EXECUTABLE.MAKE.FILE.BUILD.SYSTEM/Executable_MakeFile_Script_Builder


    ${NOVA_SRC_DIR}/SCRIPT.WRITERS/Include_Dependency_Counter

    ${NOVA_SRC_DIR}/SCRIPT.WRITERS/Project_Script_Writer

    ${NOVA_SRC_DIR}/SCRIPT.WRITERS/Script_Data_Collector

    ${NOVA_SRC_DIR}/SCRIPT.WRITERS/Script_Data_Processor

    ${NOVA_SRC_DIR}/SCRIPT.WRITERS/Source_File_Script_Writer


    ${NOVA_SRC_DIR}/SOURCE.FILE.DATA.COLLECTORS/Header_File_Determiner

    ${NOVA_SRC_DIR}/SOURCE.FILE.DATA.COLLECTORS/Source_File_Data_Collector

    ${NOVA_SRC_DIR}/SOURCE.FILE.DATA.COLLECTORS/Source_File_Determiner


    ${NOVA_SRC_DIR}/MAKE.FILE.BUILD.SYSTEM/Auto_MakeFile_Builder    

    ${NOVA_SRC_DIR}/MAKE.FILE.BUILD.SYSTEM/Make_File_Builder    

    ${NOVA_SRC_DIR}/MAKE.FILE.BUILD.SYSTEM/Make_File_Cleaner    

    ${NOVA_SRC_DIR}/MAKE.FILE.BUILD.SYSTEM/MakeFile_Path_Determiner    

    ${NOVA_SRC_DIR}/MAKE.FILE.BUILD.SYSTEM/MakeFile_Data_Collector    

    ${NOVA_SRC_DIR}/MAKE.FILE.BUILD.SYSTEM/MakeFile_Directory_Constructor 


    ${NOVA_SRC_DIR}/CMAKE.LISTS.FILE.BUILD.SYSTEM/CMAKE_Build_System_Generator

    ${NOVA_SRC_DIR}/CMAKE.LISTS.FILE.BUILD.SYSTEM/CMAKE_System_Constructor

    ${NOVA_SRC_DIR}/CMAKE.LISTS.FILE.BUILD.SYSTEM/CMAKE_Main_File_Writer

    ${NOVA_SRC_DIR}/CMAKE.LISTS.FILE.BUILD.SYSTEM/CMake_Target_Library_Builder    
    
    ${NOVA_SRC_DIR}/CMAKE.LISTS.FILE.BUILD.SYSTEM/CMAKE_Executable_Target_Constructor

    ${NOVA_SRC_DIR}/CMAKE.LISTS.FILE.BUILD.SYSTEM/CMAKE_Target_List_Data_Processor

    ${NOVA_SRC_DIR}/CMAKE.LISTS.FILE.BUILD.SYSTEM/CMAKE_Target_List_Determiner

    ${NOVA_SRC_DIR}/CMAKE.LISTS.FILE.BUILD.SYSTEM/Build_System_Meta_Data_Collector

    ${NOVA_SRC_DIR}/CMAKE.LISTS.FILE.BUILD.SYSTEM/CMAKE_Target_List_Data_Structure_Constructor


    ${NOVA_SRC_DIR}/SOURCE.FILE.PROCESSING.SYSTEM/Header_File_Processor

    ${NOVA_SRC_DIR}/SOURCE.FILE.PROCESSING.SYSTEM/Source_File_Compiler_Data_Extractor

    ${NOVA_SRC_DIR}/SOURCE.FILE.PROCESSING.SYSTEM/Source_File_Dependency_Determiner

    ${NOVA_SRC_DIR}/SOURCE.FILE.PROCESSING.SYSTEM/Source_File_Dependency_Selector_For_Single_File

    ${NOVA_SRC_DIR}/SOURCE.FILE.PROCESSING.SYSTEM/Source_File_Dependency_Selector

    ${NOVA_SRC_DIR}/SOURCE.FILE.PROCESSING.SYSTEM/Dependency_Data_Extractor

    ${NOVA_SRC_DIR}/SOURCE.FILE.PROCESSING.SYSTEM/Source_File_Information_Collector_For_Single_File

    ${NOVA_SRC_DIR}/SOURCE.FILE.PROCESSING.SYSTEM/Source_File_Data_Setter

    ${NOVA_SRC_DIR}/SOURCE.FILE.PROCESSING.SYSTEM/Source_File_Information_Collector

    ${NOVA_SRC_DIR}/SOURCE.FILE.PROCESSING.SYSTEM/Source_File_Processor

    ${NOVA_SRC_DIR}/SOURCE.FILE.PROCESSING.SYSTEM/Quick_Src_Dependency_Extractor

    ${NOVA_SRC_DIR}/SOURCE.FILE.PROCESSING.SYSTEM/Dependency_Data_Stack_Container

    ${NOVA_SRC_DIR}/SOURCE.FILE.PROCESSING.SYSTEM/Header_Dependency_Data_Extractor

    ${NOVA_SRC_DIR}/SOURCE.FILE.PROCESSING.SYSTEM/Dependency_Data_Processor



    ${NOVA_SRC_DIR}/GIT.DATA.PROCESSING.SYSTEM/Git_Data_Processor

    ${NOVA_SRC_DIR}/GIT.DATA.PROCESSING.SYSTEM/Git_File_List_Receiver

    ${NOVA_SRC_DIR}/GIT.DATA.PROCESSING.SYSTEM/Git_File_List_Writer

    ${NOVA_SRC_DIR}/GIT.DATA.PROCESSING.SYSTEM/Git_Ignoring_Files_Lister

    ${NOVA_SRC_DIR}/GIT.DATA.PROCESSING.SYSTEM/Git_Modification_Lister

    ${NOVA_SRC_DIR}/GIT.DATA.PROCESSING.SYSTEM/Git_Modification_Receiver




    ${NOVA_SRC_DIR}/PROJECT.BUILD.TOOLS/Build_Tools_Initializer

    ${NOVA_SRC_DIR}/PROJECT.BUILD.TOOLS/Directory_Enumerator

    ${NOVA_SRC_DIR}/PROJECT.BUILD.TOOLS/Directory_Tree_Size_Determiner

    ${NOVA_SRC_DIR}/PROJECT.BUILD.TOOLS/Library_Name_Extractor

    ${NOVA_SRC_DIR}/PROJECT.BUILD.TOOLS/Library_Updater

    ${NOVA_SRC_DIR}/PROJECT.BUILD.TOOLS/Project_Src_Code_Rdr

    ${NOVA_SRC_DIR}/PROJECT.BUILD.TOOLS/Repo_Dir_Determiner

    ${NOVA_SRC_DIR}/PROJECT.BUILD.TOOLS/Repo_Warehouse_Initializer


    ${NOVA_SRC_DIR}/DESCRIPTION.PROCESSING.SYSTEM/Description.Readers/Descriptor.File.Data.Collector

    ${NOVA_SRC_DIR}/DESCRIPTION.PROCESSING.SYSTEM/Description.Readers/Descriptor.File.Reader

    ${NOVA_SRC_DIR}/DESCRIPTION.PROCESSING.SYSTEM/Description.Readers/Descriptor.File.Syntax.Controller


    ${NOVA_SRC_DIR}/DESCRIPTION.PROCESSING.SYSTEM/Description.Writers/Empty.Descriptor.File.Builder

    ${NOVA_SRC_DIR}/DESCRIPTION.PROCESSING.SYSTEM/Description.Writers/DataRecorder

    
    ${NOVA_SRC_DIR}/BASIC.TOOLS/Cpp_FileOperations

    ${NOVA_SRC_DIR}/BASIC.TOOLS/Custom_System_Interface

    ${NOVA_SRC_DIR}/BASIC.TOOLS/DirectoryOperations

    ${NOVA_SRC_DIR}/BASIC.TOOLS/IntToCharTranslater

    ${NOVA_SRC_DIR}/BASIC.TOOLS/StringOperator

    ${NOVA_SRC_DIR}/BASIC.TOOLS/Custom_System_Interface

)


target_link_libraries(kernel PUBLIC proj_bld_tools exec_make_bld script_writers make_fbld_sys 

                      src_proc_sys git_data_processing_system src_dat_col des_reader des_writer basic_tools)


target_compile_options(kernel PUBLIC 

    -g

    -O0

    -std=c++17

    -fno-omit-frame-pointer

    -Wall

    -Bstatic


)

# -mwindows linking option for Mingw64 makes application as a GUI process and suspends the terminal output.
#  If you want to see the terminal output, "-mwindows" linking option must not be set on the executable link options.

target_link_options(src_dat_col PUBLIC

    -static-libgcc -static-libstdc++ -gdwarf-2 
)