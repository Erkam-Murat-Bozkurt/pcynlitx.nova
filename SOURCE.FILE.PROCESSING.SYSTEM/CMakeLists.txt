



add_library(src_proc_sys 


    ${CMAKE_CURRENT_SOURCE_DIR}/Header_File_Processor/Header_File_Processor.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Header_File_Processor/Header_File_Processor.hpp


    ${CMAKE_CURRENT_SOURCE_DIR}/Source_File_Compiler_Data_Extractor/Source_File_Compiler_Data_Extractor.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Source_File_Compiler_Data_Extractor/Source_File_Compiler_Data_Extractor.hpp


    ${CMAKE_CURRENT_SOURCE_DIR}/Source_File_Dependency_Determiner/Source_File_Dependency_Determiner.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Source_File_Dependency_Determiner/Source_File_Dependency_Determiner.hpp

    ${CMAKE_CURRENT_SOURCE_DIR}/Dependency_Data_Extractor/Dependency_Data_Extractor.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Dependency_Data_Extractor/Dependency_Data_Extractor.hpp

    ${CMAKE_CURRENT_SOURCE_DIR}/Source_File_Dependency_Selector_For_Single_File/Source_File_Dependency_Selector_For_Single_File.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Source_File_Dependency_Selector_For_Single_File/Source_File_Dependency_Selector_For_Single_File.hpp

    ${CMAKE_CURRENT_SOURCE_DIR}/Source_File_Dependency_Selector/Source_File_Dependency_Selector.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Source_File_Dependency_Selector/Source_File_Dependency_Selector.hpp


    ${CMAKE_CURRENT_SOURCE_DIR}/Source_File_Dependency_ReOrderer/Source_File_Dependency_ReOrderer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Source_File_Dependency_ReOrderer/Source_File_Dependency_ReOrderer.hpp


    ${CMAKE_CURRENT_SOURCE_DIR}/Source_File_Information_Collector_For_Single_File/Source_File_Information_Collector_For_Single_File.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Source_File_Information_Collector_For_Single_File/Source_File_Information_Collector_For_Single_File.hpp

    ${CMAKE_CURRENT_SOURCE_DIR}/Source_File_Data_Setter/Source_File_Data_Setter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Source_File_Data_Setter/Source_File_Data_Setter.hpp

    ${CMAKE_CURRENT_SOURCE_DIR}/Source_File_Information_Collector/Source_File_Information_Collector.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Source_File_Information_Collector/Source_File_Information_Collector.hpp
    
    ${CMAKE_CURRENT_SOURCE_DIR}/Source_File_Processor/Source_File_Processor.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Source_File_Processor/Source_File_Processor.hpp
)



target_include_directories(src_proc_sys PUBLIC



    ${CMAKE_CURRENT_SOURCE_DIR}/Header_File_Processor

    ${CMAKE_CURRENT_SOURCE_DIR}/Source_File_Compiler_Data_Extractor

    ${CMAKE_CURRENT_SOURCE_DIR}/Source_File_Dependency_Determiner

    ${CMAKE_CURRENT_SOURCE_DIR}/Source_File_Dependency_Selector_For_Single_File

    ${CMAKE_CURRENT_SOURCE_DIR}/Source_File_Dependency_Selector

    ${CMAKE_CURRENT_SOURCE_DIR}/Source_File_Information_Collector

    ${CMAKE_CURRENT_SOURCE_DIR}/Source_File_Information_Collector_For_Single_File

    ${CMAKE_CURRENT_SOURCE_DIR}/Source_File_Processor

    ${CMAKE_CURRENT_SOURCE_DIR}/Source_File_Dependency_ReOrderer
    
    ${CMAKE_CURRENT_SOURCE_DIR}/Dependency_Data_Extractor

    ${CMAKE_CURRENT_SOURCE_DIR}/Source_File_Data_Setter



    ${CMAKE_SOURCE_DIR}/SOURCE.FILE.DATA.COLLECTORS/Header_File_Determiner

    ${CMAKE_SOURCE_DIR}/SOURCE.FILE.DATA.COLLECTORS/Project_Files_Data_Collector

    ${CMAKE_SOURCE_DIR}/SOURCE.FILE.DATA.COLLECTORS/Project_Files_Lister

    ${CMAKE_SOURCE_DIR}/SOURCE.FILE.DATA.COLLECTORS/Source_File_Data_Collector

    ${CMAKE_SOURCE_DIR}/SOURCE.FILE.DATA.COLLECTORS/Source_File_Determiner





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




    ${CMAKE_SOURCE_DIR}/BASIC.TOOLS/Cpp_FileOperations

    ${CMAKE_SOURCE_DIR}/BASIC.TOOLS/Custom_System_Interface

    ${CMAKE_SOURCE_DIR}/BASIC.TOOLS/DirectoryOperations

    ${CMAKE_SOURCE_DIR}/BASIC.TOOLS/IntToCharTranslater

    ${CMAKE_SOURCE_DIR}/BASIC.TOOLS/StringOperator
)


target_link_directories(src_proc_sys PUBLIC 


    ${CMAKE_CURRENT_SOURCE_DIR}/Header_File_Processor

    ${CMAKE_CURRENT_SOURCE_DIR}/Source_File_Compiler_Data_Extractor

    ${CMAKE_CURRENT_SOURCE_DIR}/Source_File_Dependency_Determiner

    ${CMAKE_CURRENT_SOURCE_DIR}/Source_File_Dependency_Selector_For_Single_File

    ${CMAKE_CURRENT_SOURCE_DIR}/Source_File_Dependency_Selector

    ${CMAKE_CURRENT_SOURCE_DIR}/Source_File_Information_Collector_For_Single_File

    ${CMAKE_CURRENT_SOURCE_DIR}/Source_File_Information_Collector

    ${CMAKE_CURRENT_SOURCE_DIR}/Source_File_Processor

    ${CMAKE_CURRENT_SOURCE_DIR}/Source_File_Dependency_ReOrderer

    ${CMAKE_CURRENT_SOURCE_DIR}/Dependency_Data_Extractor




    
    ${CMAKE_SOURCE_DIR}/SOURCE.FILE.DATA.COLLECTORS/Header_File_Determiner

    ${CMAKE_SOURCE_DIR}/SOURCE.FILE.DATA.COLLECTORS/Project_Files_Data_Collector

    ${CMAKE_SOURCE_DIR}/SOURCE.FILE.DATA.COLLECTORS/Project_Files_Lister

    ${CMAKE_SOURCE_DIR}/SOURCE.FILE.DATA.COLLECTORS/Source_File_Data_Collector

    ${CMAKE_SOURCE_DIR}/SOURCE.FILE.DATA.COLLECTORS/Source_File_Determiner



    ${CMAKE_SOURCE_DIR}/DESCRIPTION.PROCESSING.SYSTEM/Description.Readers/Descriptor.File.Data.Collector

    ${CMAKE_SOURCE_DIR}/DESCRIPTION.PROCESSING.SYSTEM/Description.Readers/Descriptor.File.Reader

    ${CMAKE_SOURCE_DIR}/DESCRIPTION.PROCESSING.SYSTEM/Description.Readers/Descriptor.File.Syntax.Controller


    ${CMAKE_SOURCE_DIR}/PROJECT.BUILD.TOOLS/Build_Tools_Initializer

    ${CMAKE_SOURCE_DIR}/PROJECT.BUILD.TOOLS/Directory_Enumerator

    ${CMAKE_SOURCE_DIR}/PROJECT.BUILD.TOOLS/Directory_Tree_Size_Determiner



    ${CMAKE_SOURCE_DIR}/GIT.DATA.PROCESSING.SYSTEM/Git_Data_Processor

    ${CMAKE_SOURCE_DIR}/GIT.DATA.PROCESSING.SYSTEM/Git_File_List_Receiver

    ${CMAKE_SOURCE_DIR}/GIT.DATA.PROCESSING.SYSTEM/Git_File_List_Writer

    ${CMAKE_SOURCE_DIR}/GIT.DATA.PROCESSING.SYSTEM/Git_Ignoring_Files_Lister

    ${CMAKE_SOURCE_DIR}/GIT.DATA.PROCESSING.SYSTEM/Git_Modification_Lister

    ${CMAKE_SOURCE_DIR}/GIT.DATA.PROCESSING.SYSTEM/Git_Modification_Receiver



    ${CMAKE_SOURCE_DIR}/PROJECT.BUILD.TOOLS/Library_Name_Extractor

    ${CMAKE_SOURCE_DIR}/PROJECT.BUILD.TOOLS/Library_Updater

    ${CMAKE_SOURCE_DIR}/PROJECT.BUILD.TOOLS/Project_Src_Code_Rdr

    ${CMAKE_SOURCE_DIR}/PROJECT.BUILD.TOOLS/Repo_Dir_Determiner

    ${CMAKE_SOURCE_DIR}/PROJECT.BUILD.TOOLS/Repo_Warehouse_Initializer



    ${CMAKE_SOURCE_DIR}/BASIC.TOOLS/Cpp_FileOperations

    ${CMAKE_SOURCE_DIR}/BASIC.TOOLS/Custom_System_Interface

    ${CMAKE_SOURCE_DIR}/BASIC.TOOLS/DirectoryOperations

    ${CMAKE_SOURCE_DIR}/BASIC.TOOLS/IntToCharTranslater

    ${CMAKE_SOURCE_DIR}/BASIC.TOOLS/StringOperator
)


target_link_libraries(src_proc_sys PUBLIC src_dat_col proj_bld_tools

                        git_data_processing_system des_reader basic_tools)