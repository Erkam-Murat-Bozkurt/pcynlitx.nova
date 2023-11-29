



add_library(kernel 

    ${CMAKE_CURRENT_SOURCE_DIR}/Kernel_Main_File.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/Kernel.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/Kernel.hpp
)


target_include_directories(kernel PUBLIC


    ${CMAKE_CURRENT_SOURCE_DIR}/KERNEL.DEVELOPMENT

    ${CMAKE_SOURCE_DIR}/Build_Tools_Initializer

    ${CMAKE_SOURCE_DIR}/Directory_Enumerator

    ${CMAKE_SOURCE_DIR}/Directory_Tree_Size_Determiner


    ${CMAKE_SOURCE_DIR}/Library_Name_Extractor

    ${CMAKE_SOURCE_DIR}/Library_Updater

    ${CMAKE_SOURCE_DIR}/Project_Src_Code_Rdr

    ${CMAKE_SOURCE_DIR}/Repo_Dir_Determiner

    ${CMAKE_SOURCE_DIR}/Repo_Warehouse_Initializer


    ${CMAKE_SOURCE_DIR}/Executable_MakeFile_Builder
    
    ${CMAKE_SOURCE_DIR}/Executable_MakeFile_ComConstructor
    
    ${CMAKE_SOURCE_DIR}/Executable_MakeFile_Script_Builder

    

    ${CMAKE_SOURCE_DIR}/DESCRIPTION.PROCESSING.SYSTEM/Description.Readers/Descriptor.File.Data.Collector

    ${CMAKE_SOURCE_DIR}/DESCRIPTION.PROCESSING.SYSTEM/Description.Readers/Descriptor.File.Reader

    ${CMAKE_SOURCE_DIR}/DESCRIPTION.PROCESSING.SYSTEM/Description.Readers/Descriptor.File.Syntax.Controller


    ${CMAKE_SOURCE_DIR}/SOURCE.FILE.PROCESSING.SYSTEM/Header_File_Processor

    ${CMAKE_SOURCE_DIR}/SOURCE.FILE.PROCESSING.SYSTEM/Source_File_Compiler_Data_Extractor

    ${CMAKE_SOURCE_DIR}/SOURCE.FILE.PROCESSING.SYSTEM/Source_File_Dependency_Determiner

    ${CMAKE_SOURCE_DIR}/SOURCE.FILE.PROCESSING.SYSTEM/Source_File_Dependency_Selector_For_Single_File

    ${CMAKE_SOURCE_DIR}/SOURCE.FILE.PROCESSING.SYSTEM/Source_File_Dependency_Selector

    ${CMAKE_SOURCE_DIR}/SOURCE.FILE.PROCESSING.SYSTEM/Dependency_Data_Extractor

    ${CMAKE_SOURCE_DIR}/SOURCE.FILE.PROCESSING.SYSTEM/Source_File_Information_Collector_For_Single_File

    ${CMAKE_SOURCE_DIR}/SOURCE.FILE.PROCESSING.SYSTEM/Source_File_Data_Setter

    ${CMAKE_SOURCE_DIR}/SOURCE.FILE.PROCESSING.SYSTEM/Source_File_Information_Collector

    ${CMAKE_SOURCE_DIR}/SOURCE.FILE.PROCESSING.SYSTEM/Source_File_Processor

    ${CMAKE_SOURCE_DIR}/SOURCE.FILE.PROCESSING.SYSTEM/Quick_Src_Dependency_Extractor

    ${CMAKE_SOURCE_DIR}/SOURCE.FILE.PROCESSING.SYSTEM/Dependency_Data_Stack_Container

    ${CMAKE_SOURCE_DIR}/SOURCE.FILE.PROCESSING.SYSTEM/Header_Dependency_Data_Extractor

    ${CMAKE_SOURCE_DIR}/SOURCE.FILE.PROCESSING.SYSTEM/Dependency_Data_Processor



    ${CMAKE_SOURCE_DIR}/SCRIPT.WRITERS/Include_Dependency_Counter

    ${CMAKE_SOURCE_DIR}/SCRIPT.WRITERS/Project_Script_Writer

    ${CMAKE_SOURCE_DIR}/SCRIPT.WRITERS/Script_Data_Collector

    ${CMAKE_SOURCE_DIR}/SCRIPT.WRITERS/Script_Data_Processor

    ${CMAKE_SOURCE_DIR}/SCRIPT.WRITERS/Source_File_Script_Writer



    ${CMAKE_SOURCE_DIR}/GIT.DATA.PROCESSING.SYSTEM/Git_Data_Processor

    ${CMAKE_SOURCE_DIR}/GIT.DATA.PROCESSING.SYSTEM/Git_File_List_Receiver

    ${CMAKE_SOURCE_DIR}/GIT.DATA.PROCESSING.SYSTEM/Git_File_List_Writer

    ${CMAKE_SOURCE_DIR}/GIT.DATA.PROCESSING.SYSTEM/Git_Ignoring_Files_Lister

    ${CMAKE_SOURCE_DIR}/GIT.DATA.PROCESSING.SYSTEM/Git_Modification_Lister

    ${CMAKE_SOURCE_DIR}/GIT.DATA.PROCESSING.SYSTEM/Git_Modification_Receiver



    ${CMAKE_SOURCE_DIR}/SOURCE.FILE.DATA.COLLECTORS/Header_File_Determiner

    ${CMAKE_SOURCE_DIR}/SOURCE.FILE.DATA.COLLECTORS/Source_File_Data_Collector

    ${CMAKE_SOURCE_DIR}/SOURCE.FILE.DATA.COLLECTORS/Source_File_Determiner


    ${CMAKE_SOURCE_DIR}/MAKE.FILE.BUILD.SYSTEM/Auto_MakeFile_Builder    

    ${CMAKE_SOURCE_DIR}/MAKE.FILE.BUILD.SYSTEM/Make_File_Builder    

    ${CMAKE_SOURCE_DIR}/MAKE.FILE.BUILD.SYSTEM/Make_File_Cleaner    

    ${CMAKE_SOURCE_DIR}/MAKE.FILE.BUILD.SYSTEM/MakeFile_Data_Collector    

    ${CMAKE_SOURCE_DIR}/MAKE.FILE.BUILD.SYSTEM/MakeFile_Directory_Constructor 

    ${CMAKE_SOURCE_DIR}/MAKE.FILE.BUILD.SYSTEM/MakeFile_Path_Determiner    



    ${CMAKE_SOURCE_DIR}/BASIC.TOOLS/Cpp_FileOperations

    ${CMAKE_SOURCE_DIR}/BASIC.TOOLS/Custom_System_Interface

    ${CMAKE_SOURCE_DIR}/BASIC.TOOLS/DirectoryOperations

    ${CMAKE_SOURCE_DIR}/BASIC.TOOLS/IntToCharTranslater

    ${CMAKE_SOURCE_DIR}/BASIC.TOOLS/StringOperator
)


target_link_directories(kernel PUBLIC 


    ${CMAKE_CURRENT_SOURCE_DIR}/KERNEL.DEVELOPMENT


    ${CMAKE_SOURCE_DIR}/Executable_MakeFile_Builder
    
    ${CMAKE_SOURCE_DIR}/Executable_MakeFile_ComConstructor

    ${CMAKE_SOURCE_DIR}/Executable_MakeFile_Script_Builder


    ${CMAKE_SOURCE_DIR}/SCRIPT.WRITERS/Include_Dependency_Counter

    ${CMAKE_SOURCE_DIR}/SCRIPT.WRITERS/Project_Script_Writer

    ${CMAKE_SOURCE_DIR}/SCRIPT.WRITERS/Script_Data_Collector

    ${CMAKE_SOURCE_DIR}/SCRIPT.WRITERS/Script_Data_Processor

    ${CMAKE_SOURCE_DIR}/SCRIPT.WRITERS/Source_File_Script_Writer


    ${CMAKE_SOURCE_DIR}/SOURCE.FILE.DATA.COLLECTORS/Header_File_Determiner

    ${CMAKE_SOURCE_DIR}/SOURCE.FILE.DATA.COLLECTORS/Source_File_Data_Collector

    ${CMAKE_SOURCE_DIR}/SOURCE.FILE.DATA.COLLECTORS/Source_File_Determiner


    ${CMAKE_SOURCE_DIR}/MAKE.FILE.BUILD.SYSTEM/Auto_MakeFile_Builder    

    ${CMAKE_SOURCE_DIR}/MAKE.FILE.BUILD.SYSTEM/Make_File_Builder    

    ${CMAKE_SOURCE_DIR}/MAKE.FILE.BUILD.SYSTEM/Make_File_Cleaner    

    ${CMAKE_SOURCE_DIR}/MAKE.FILE.BUILD.SYSTEM/MakeFile_Path_Determiner    

    ${CMAKE_SOURCE_DIR}/MAKE.FILE.BUILD.SYSTEM/MakeFile_Data_Collector    

    ${CMAKE_SOURCE_DIR}/MAKE.FILE.BUILD.SYSTEM/MakeFile_Directory_Constructor 



    ${CMAKE_SOURCE_DIR}/SOURCE.FILE.PROCESSING.SYSTEM/Header_File_Processor

    ${CMAKE_SOURCE_DIR}/SOURCE.FILE.PROCESSING.SYSTEM/Source_File_Compiler_Data_Extractor

    ${CMAKE_SOURCE_DIR}/SOURCE.FILE.PROCESSING.SYSTEM/Source_File_Dependency_Determiner

    ${CMAKE_SOURCE_DIR}/SOURCE.FILE.PROCESSING.SYSTEM/Source_File_Dependency_Selector_For_Single_File

    ${CMAKE_SOURCE_DIR}/SOURCE.FILE.PROCESSING.SYSTEM/Source_File_Dependency_Selector

    ${CMAKE_SOURCE_DIR}/SOURCE.FILE.PROCESSING.SYSTEM/Dependency_Data_Extractor

    ${CMAKE_SOURCE_DIR}/SOURCE.FILE.PROCESSING.SYSTEM/Source_File_Information_Collector_For_Single_File

    ${CMAKE_SOURCE_DIR}/SOURCE.FILE.PROCESSING.SYSTEM/Source_File_Data_Setter

    ${CMAKE_SOURCE_DIR}/SOURCE.FILE.PROCESSING.SYSTEM/Source_File_Information_Collector

    ${CMAKE_SOURCE_DIR}/SOURCE.FILE.PROCESSING.SYSTEM/Source_File_Processor

    ${CMAKE_SOURCE_DIR}/SOURCE.FILE.PROCESSING.SYSTEM/Quick_Src_Dependency_Extractor

    ${CMAKE_SOURCE_DIR}/SOURCE.FILE.PROCESSING.SYSTEM/Dependency_Data_Stack_Container

    ${CMAKE_SOURCE_DIR}/SOURCE.FILE.PROCESSING.SYSTEM/Header_Dependency_Data_Extractor

    ${CMAKE_SOURCE_DIR}/SOURCE.FILE.PROCESSING.SYSTEM/Dependency_Data_Processor



    ${CMAKE_SOURCE_DIR}/GIT.DATA.PROCESSING.SYSTEM/Git_Data_Processor

    ${CMAKE_SOURCE_DIR}/GIT.DATA.PROCESSING.SYSTEM/Git_File_List_Receiver

    ${CMAKE_SOURCE_DIR}/GIT.DATA.PROCESSING.SYSTEM/Git_File_List_Writer

    ${CMAKE_SOURCE_DIR}/GIT.DATA.PROCESSING.SYSTEM/Git_Ignoring_Files_Lister

    ${CMAKE_SOURCE_DIR}/GIT.DATA.PROCESSING.SYSTEM/Git_Modification_Lister

    ${CMAKE_SOURCE_DIR}/GIT.DATA.PROCESSING.SYSTEM/Git_Modification_Receiver




    ${CMAKE_CURRENT_SOURCE_DIR}/Build_Tools_Initializer

    ${CMAKE_CURRENT_SOURCE_DIR}/Directory_Enumerator

    ${CMAKE_CURRENT_SOURCE_DIR}/Directory_Tree_Size_Determiner

    ${CMAKE_CURRENT_SOURCE_DIR}/Library_Name_Extractor

    ${CMAKE_CURRENT_SOURCE_DIR}/Library_Updater

    ${CMAKE_CURRENT_SOURCE_DIR}/Project_Src_Code_Rdr

    ${CMAKE_CURRENT_SOURCE_DIR}/Repo_Dir_Determiner

    ${CMAKE_CURRENT_SOURCE_DIR}/Repo_Warehouse_Initializer


    ${CMAKE_SOURCE_DIR}/DESCRIPTION.PROCESSING.SYSTEM/Description.Readers/Descriptor.File.Data.Collector

    ${CMAKE_SOURCE_DIR}/DESCRIPTION.PROCESSING.SYSTEM/Description.Readers/Descriptor.File.Reader

    ${CMAKE_SOURCE_DIR}/DESCRIPTION.PROCESSING.SYSTEM/Description.Readers/Descriptor.File.Syntax.Controller

    
    ${CMAKE_SOURCE_DIR}/BASIC.TOOLS/Cpp_FileOperations

    ${CMAKE_SOURCE_DIR}/BASIC.TOOLS/Custom_System_Interface

    ${CMAKE_SOURCE_DIR}/BASIC.TOOLS/DirectoryOperations

    ${CMAKE_SOURCE_DIR}/BASIC.TOOLS/IntToCharTranslater

    ${CMAKE_SOURCE_DIR}/BASIC.TOOLS/StringOperator

)


target_link_libraries(kernel PUBLIC proj_bld_tools exec_make_bld script_writers make_fbld_sys 

                      src_proc_sys git_data_processing_system src_dat_col des_reader basic_tools)