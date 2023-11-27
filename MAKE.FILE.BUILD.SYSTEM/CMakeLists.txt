





add_library(make_fbld_sys 

    ${CMAKE_CURRENT_SOURCE_DIR}/Auto_MakeFile_Builder/Auto_MakeFile_Builder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Auto_MakeFile_Builder/Auto_MakeFile_Builder.h

    ${CMAKE_CURRENT_SOURCE_DIR}/Make_File_Builder/Make_File_Builder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Make_File_Builder/Make_File_Builder.h

    ${CMAKE_CURRENT_SOURCE_DIR}/Make_File_Cleaner/Make_File_Cleaner.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Make_File_Cleaner/Make_File_Cleaner.hpp

    ${CMAKE_CURRENT_SOURCE_DIR}/MakeFile_Path_Determiner/MakeFile_Path_Determiner.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/MakeFile_Path_Determiner/MakeFile_Path_Determiner.hpp

    ${CMAKE_CURRENT_SOURCE_DIR}/MakeFile_Data_Collector/MakeFile_Data_Collector.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/MakeFile_Data_Collector/MakeFile_Data_Collector.hpp
    

    ${CMAKE_CURRENT_SOURCE_DIR}/MakeFile_Directory_Constructor/MakeFile_Directory_Constructor.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/MakeFile_Directory_Constructor/MakeFile_Directory_Constructor.hpp
)

target_include_directories(make_fbld_sys PUBLIC

    ${CMAKE_CURRENT_SOURCE_DIR}/Auto_MakeFile_Builder    
    ${CMAKE_CURRENT_SOURCE_DIR}/Make_File_Builder    
    ${CMAKE_CURRENT_SOURCE_DIR}/MakeFile_Path_Determiner    
    ${CMAKE_CURRENT_SOURCE_DIR}/Make_File_Cleaner    
    ${CMAKE_CURRENT_SOURCE_DIR}/MakeFile_Data_Collector    
    ${CMAKE_CURRENT_SOURCE_DIR}/MakeFile_Directory_Constructor    


    ${CMAKE_SOURCE_DIR}/PROJECT.BUILD.TOOLS/Build_Tools_Initializer

    ${CMAKE_SOURCE_DIR}/PROJECT.BUILD.TOOLS/Directory_Enumerator

    ${CMAKE_SOURCE_DIR}/PROJECT.BUILD.TOOLS/Directory_Tree_Size_Determiner

    ${CMAKE_SOURCE_DIR}/PROJECT.BUILD.TOOLS/Library_Name_Extractor

    ${CMAKE_SOURCE_DIR}/PROJECT.BUILD.TOOLS/Library_Updater

    ${CMAKE_SOURCE_DIR}/PROJECT.BUILD.TOOLS/Project_Src_Code_Rdr

    ${CMAKE_SOURCE_DIR}/PROJECT.BUILD.TOOLS/Repo_Dir_Determiner

    ${CMAKE_SOURCE_DIR}/PROJECT.BUILD.TOOLS/Repo_Warehouse_Initializer




    ${CMAKE_SOURCE_DIR}/GIT.DATA.PROCESSING.SYSTEM/Git_Data_Processor

    ${CMAKE_SOURCE_DIR}/GIT.DATA.PROCESSING.SYSTEM/Git_File_List_Receiver

    ${CMAKE_SOURCE_DIR}/GIT.DATA.PROCESSING.SYSTEM/Git_File_List_Writer

    ${CMAKE_SOURCE_DIR}/GIT.DATA.PROCESSING.SYSTEM/Git_Ignoring_Files_Lister

    ${CMAKE_SOURCE_DIR}/GIT.DATA.PROCESSING.SYSTEM/Git_Modification_Lister

    ${CMAKE_SOURCE_DIR}/GIT.DATA.PROCESSING.SYSTEM/Git_Modification_Receiver



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


    ${CMAKE_SOURCE_DIR}/DESCRIPTION.PROCESSING.SYSTEM/Description.Readers/Descriptor.File.Data.Collector

    ${CMAKE_SOURCE_DIR}/DESCRIPTION.PROCESSING.SYSTEM/Description.Readers/Descriptor.File.Reader

    ${CMAKE_SOURCE_DIR}/DESCRIPTION.PROCESSING.SYSTEM/Description.Readers/Descriptor.File.Syntax.Controller


    ${CMAKE_SOURCE_DIR}/BASIC.TOOLS/Cpp_FileOperations

    ${CMAKE_SOURCE_DIR}/BASIC.TOOLS/Custom_System_Interface

    ${CMAKE_SOURCE_DIR}/BASIC.TOOLS/DirectoryOperations

    ${CMAKE_SOURCE_DIR}/BASIC.TOOLS/IntToCharTranslater

    ${CMAKE_SOURCE_DIR}/BASIC.TOOLS/StringOperator
)

target_link_directories(make_fbld_sys PUBLIC 

    ${CMAKE_CURRENT_SOURCE_DIR}/Auto_MakeFile_Builder    
    ${CMAKE_CURRENT_SOURCE_DIR}/Make_File_Builder    
    ${CMAKE_CURRENT_SOURCE_DIR}/Make_File_Cleaner    
    ${CMAKE_CURRENT_SOURCE_DIR}/MakeFile_Path_Determiner    
    ${CMAKE_CURRENT_SOURCE_DIR}/MakeFile_Data_Collector    
    ${CMAKE_CURRENT_SOURCE_DIR}/MakeFile_Directory_Constructor    


    ${CMAKE_SOURCE_DIR}/PROJECT.BUILD.TOOLS/Build_Tools_Initializer

    ${CMAKE_SOURCE_DIR}/PROJECT.BUILD.TOOLS/Directory_Enumerator

    ${CMAKE_SOURCE_DIR}/PROJECT.BUILD.TOOLS/Directory_Tree_Size_Determiner

    ${CMAKE_SOURCE_DIR}/PROJECT.BUILD.TOOLS/Library_Name_Extractor

    ${CMAKE_SOURCE_DIR}/PROJECT.BUILD.TOOLS/Library_Updater

    ${CMAKE_SOURCE_DIR}/PROJECT.BUILD.TOOLS/Project_Src_Code_Rdr

    ${CMAKE_SOURCE_DIR}/PROJECT.BUILD.TOOLS/Repo_Dir_Determiner

    ${CMAKE_SOURCE_DIR}/PROJECT.BUILD.TOOLS/Repo_Warehouse_Initializer



    ${CMAKE_SOURCE_DIR}/GIT.DATA.PROCESSING.SYSTEM/Git_Data_Processor

    ${CMAKE_SOURCE_DIR}/GIT.DATA.PROCESSING.SYSTEM/Git_File_List_Receiver

    ${CMAKE_SOURCE_DIR}/GIT.DATA.PROCESSING.SYSTEM/Git_File_List_Writer

    ${CMAKE_SOURCE_DIR}/GIT.DATA.PROCESSING.SYSTEM/Git_Ignoring_Files_Lister

    ${CMAKE_SOURCE_DIR}/GIT.DATA.PROCESSING.SYSTEM/Git_Modification_Lister

    ${CMAKE_SOURCE_DIR}/GIT.DATA.PROCESSING.SYSTEM/Git_Modification_Receiver




    ${CMAKE_SOURCE_DIR}/SOURCE.FILE.PROCESSING.SYSTEM/Header_File_Processor

    ${CMAKE_SOURCE_DIR}/SOURCE.FILE.PROCESSING.SYSTEM/Source_File_Compiler_Data_Extractor

    ${CMAKE_SOURCE_DIR}/SOURCE.FILE.PROCESSING.SYSTEM/Source_File_Dependency_Determiner

    ${CMAKE_SOURCE_DIR}/SOURCE.FILE.PROCESSING.SYSTEM/Source_File_Dependency_Selector_For_Single_File

    ${CMAKE_SOURCE_DIR}/SOURCE.FILE.PROCESSING.SYSTEM/Source_File_Dependency_Selector

    ${CMAKE_SOURCE_DIR}/SOURCE.FILE.PROCESSING.SYSTEM/Dependency_Data_Extractor

    ${CMAKE_SOURCE_DIR}/SOURCE.FILE.PROCESSING.SYSTEM/Source_File_Information_Collector_For_Single_File

    ${CMAKE_SOURCE_DIR}/SOURCE.FILE.PROCESSING.SYSTEM/Source_File_Information_Collector

    ${CMAKE_SOURCE_DIR}/SOURCE.FILE.PROCESSING.SYSTEM/Source_File_Processor

    ${CMAKE_SOURCE_DIR}/SOURCE.FILE.PROCESSING.SYSTEM/Dependency_Data_Stack_Container

    ${CMAKE_SOURCE_DIR}/SOURCE.FILE.PROCESSING.SYSTEM/Header_Dependency_Data_Extractor

    ${CMAKE_SOURCE_DIR}/SOURCE.FILE.PROCESSING.SYSTEM/Dependency_Data_Processor




    ${CMAKE_SOURCE_DIR}/DESCRIPTION.PROCESSING.SYSTEM/Description.Readers/Descriptor.File.Data.Collector

    ${CMAKE_SOURCE_DIR}/DESCRIPTION.PROCESSING.SYSTEM/Description.Readers/Descriptor.File.Reader

    ${CMAKE_SOURCE_DIR}/DESCRIPTION.PROCESSING.SYSTEM/Description.Readers/Descriptor.File.Syntax.Controller



    ${CMAKE_SOURCE_DIR}/BASIC.TOOLS/Cpp_FileOperations

    ${CMAKE_SOURCE_DIR}/BASIC.TOOLS/Custom_System_Interface

    ${CMAKE_SOURCE_DIR}/BASIC.TOOLS/DirectoryOperations

    ${CMAKE_SOURCE_DIR}/BASIC.TOOLS/IntToCharTranslater

    ${CMAKE_SOURCE_DIR}/BASIC.TOOLS/StringOperator

)

target_link_libraries(make_fbld_sys PUBLIC proj_bld_tools 

                    git_data_processing_system des_reader basic_tools)
