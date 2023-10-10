

add_library(script_writers 

    ${CMAKE_CURRENT_SOURCE_DIR}/Project_Script_Writer/Project_Script_Writer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Project_Script_Writer/Project_Script_Writer.h


    ${CMAKE_CURRENT_SOURCE_DIR}/Script_Data_Collector/Script_Data_Collector.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Script_Data_Collector/Script_Data_Collector.hpp

    ${CMAKE_CURRENT_SOURCE_DIR}/Script_Data_Processor/Script_Data_Processor.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Script_Data_Processor/Script_Data_Processor.hpp

    ${CMAKE_CURRENT_SOURCE_DIR}/Source_File_Script_Writer/Source_File_Script_Writer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Source_File_Script_Writer/Source_File_Script_Writer.hpp

    ${CMAKE_SOURCE_DIR}/BASIC.TOOLS/IntToCharTranslater    
)

target_include_directories(script_writers PUBLIC

    ${CMAKE_CURRENT_SOURCE_DIR}/Include_Dependency_Counter

    ${CMAKE_CURRENT_SOURCE_DIR}/Project_Script_Writer

    ${CMAKE_CURRENT_SOURCE_DIR}/Script_Data_Collector

    ${CMAKE_CURRENT_SOURCE_DIR}/Script_Data_Processor
 
    ${CMAKE_CURRENT_SOURCE_DIR}/Source_File_Script_Writer


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

    ${CMAKE_SOURCE_DIR}/SOURCE.FILE.PROCESSING.SYSTEM/Source_File_Dependency_ReOrderer

    ${CMAKE_SOURCE_DIR}/SOURCE.FILE.PROCESSING.SYSTEM/Quick_Src_Dependency_Extractor




    ${CMAKE_SOURCE_DIR}/SOURCE.FILE.PROCESSING.SYSTEM/Header_File_Determiner

    ${CMAKE_SOURCE_DIR}/SOURCE.FILE.PROCESSING.SYSTEM/Project_Files_Data_Collector

    ${CMAKE_SOURCE_DIR}/SOURCE.FILE.PROCESSING.SYSTEM/Project_Files_Lister

    ${CMAKE_SOURCE_DIR}/SOURCE.FILE.PROCESSING.SYSTEM/Source_File_Data_Collector

    ${CMAKE_SOURCE_DIR}/SOURCE.FILE.PROCESSING.SYSTEM/Source_File_Determiner


    ${CMAKE_SOURCE_DIR}/GIT.DATA.PROCESSING.SYSTEM/Git_Data_Processor

    ${CMAKE_SOURCE_DIR}/GIT.DATA.PROCESSING.SYSTEM/Git_File_List_Receiver

    ${CMAKE_SOURCE_DIR}/GIT.DATA.PROCESSING.SYSTEM/Git_File_List_Writer

    ${CMAKE_SOURCE_DIR}/GIT.DATA.PROCESSING.SYSTEM/Git_Ignoring_Files_Lister

    ${CMAKE_SOURCE_DIR}/GIT.DATA.PROCESSING.SYSTEM/Git_Modification_Lister

    ${CMAKE_SOURCE_DIR}/GIT.DATA.PROCESSING.SYSTEM/Git_Modification_Receiver




    ${CMAKE_SOURCE_DIR}/DESCRIPTION.PROCESSING.SYSTEM/Description.Readers/Descriptor.File.Data.Collector

    ${CMAKE_SOURCE_DIR}/DESCRIPTION.PROCESSING.SYSTEM/Description.Readers/Descriptor.File.Reader

    ${CMAKE_SOURCE_DIR}/DESCRIPTION.PROCESSING.SYSTEM/Description.Readers/Descriptor.File.Syntax.Controller


    ${CMAKE_SOURCE_DIR}/PROJECT.BUILD.TOOLS/Build_Tools_Initializer

    ${CMAKE_SOURCE_DIR}/PROJECT.BUILD.TOOLS/Directory_Enumerator

    ${CMAKE_SOURCE_DIR}/PROJECT.BUILD.TOOLS/Directory_Tree_Size_Determiner

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


target_link_directories(script_writers PUBLIC

    
    ${CMAKE_CURRENT_SOURCE_DIR}/Include_Dependency_Counter

    ${CMAKE_CURRENT_SOURCE_DIR}/Project_Script_Writer

    ${CMAKE_CURRENT_SOURCE_DIR}/Script_Data_Collector

    ${CMAKE_CURRENT_SOURCE_DIR}/Script_Data_Processor

    ${CMAKE_CURRENT_SOURCE_DIR}/Source_File_Script_Writer


    ${CMAKE_SOURCE_DIR}/SOURCE.FILE.PROCESSING.SYSTEM/Header_File_Processor

    ${CMAKE_SOURCE_DIR}/SOURCE.FILE.PROCESSING.SYSTEM/Source_File_Compiler_Data_Extractor

    ${CMAKE_SOURCE_DIR}/SOURCE.FILE.PROCESSING.SYSTEM/Source_File_Dependency_Determiner

    ${CMAKE_SOURCE_DIR}/SOURCE.FILE.PROCESSING.SYSTEM/Source_File_Dependency_Selector_For_Single_File

    ${CMAKE_SOURCE_DIR}/SOURCE.FILE.PROCESSING.SYSTEM/Source_File_Dependency_Selector

    ${CMAKE_SOURCE_DIR}/SOURCE.FILE.PROCESSING.SYSTEM/Dependency_Data_Extractor

    ${CMAKE_SOURCE_DIR}/SOURCE.FILE.PROCESSING.SYSTEM/Source_File_Information_Collector_For_Single_File

    ${CMAKE_SOURCE_DIR}/SOURCE.FILE.PROCESSING.SYSTEM/Source_File_Information_Collector

    ${CMAKE_SOURCE_DIR}/SOURCE.FILE.PROCESSING.SYSTEM/Source_File_Data_Setter

    ${CMAKE_SOURCE_DIR}/SOURCE.FILE.PROCESSING.SYSTEM/Source_File_Processor

    ${CMAKE_SOURCE_DIR}/SOURCE.FILE.PROCESSING.SYSTEM/Source_File_Dependency_ReOrderer


        
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





    ${CMAKE_SOURCE_DIR}/BASIC.TOOLS/ClassNameReader

    ${CMAKE_SOURCE_DIR}/BASIC.TOOLS/ClassSyntaxControl

    ${CMAKE_SOURCE_DIR}/BASIC.TOOLS/Cpp_FileOperations

    ${CMAKE_SOURCE_DIR}/BASIC.TOOLS/Custom_System_Interface

    ${CMAKE_SOURCE_DIR}/BASIC.TOOLS/DirectoryOperations

    ${CMAKE_SOURCE_DIR}/BASIC.TOOLS/IntToCharTranslater

    ${CMAKE_SOURCE_DIR}/BASIC.TOOLS/StringOperator

)



target_link_libraries(script_writers PUBLIC

                src_proc_sys src_dat_col proj_bld_tools git_data_processing_system des_reader basic_tools)