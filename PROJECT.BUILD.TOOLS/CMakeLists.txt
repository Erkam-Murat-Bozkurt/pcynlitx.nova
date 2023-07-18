


add_library(proj_bld_tools 

    ${CMAKE_CURRENT_SOURCE_DIR}/Build_Tools_Initializer/Build_Tools_Initializer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Build_Tools_Initializer/Build_Tools_Initializer.h


    ${CMAKE_CURRENT_SOURCE_DIR}/Directory_Enumerator/Directory_Enumerator.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Directory_Enumerator/Directory_Enumerator.h


    ${CMAKE_CURRENT_SOURCE_DIR}/Directory_Tree_Size_Determiner/Directory_Tree_Size_Determiner.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Directory_Tree_Size_Determiner/Directory_Tree_Size_Determiner.h

    ${CMAKE_CURRENT_SOURCE_DIR}/Git_File_List_Receiver/Git_File_List_Receiver.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Git_File_List_Receiver/Git_File_List_Receiver.hpp

    ${CMAKE_CURRENT_SOURCE_DIR}/Git_File_List_Writer/Git_File_List_Writer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Git_File_List_Writer/Git_File_List_Writer.hpp


    ${CMAKE_CURRENT_SOURCE_DIR}/Git_Ignoring_Files_Lister/Git_Ignoring_Files_Lister.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Git_Ignoring_Files_Lister/Git_Ignoring_Files_Lister.hpp

    ${CMAKE_CURRENT_SOURCE_DIR}/Git_Modification_Lister/Git_Modification_Lister.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Git_Modification_Lister/Git_Modification_Lister.hpp

    ${CMAKE_CURRENT_SOURCE_DIR}/Git_Modification_Receiver/Git_Modification_Receiver.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Git_Modification_Receiver/Git_Modification_Receiver.hpp

    ${CMAKE_CURRENT_SOURCE_DIR}/Library_Name_Extractor/Library_Name_Extractor.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Library_Name_Extractor/Library_Name_Extractor.hpp
    
    ${CMAKE_CURRENT_SOURCE_DIR}/Library_Updater/Library_Updater.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Library_Updater/Library_Updater.h
    
    ${CMAKE_CURRENT_SOURCE_DIR}/Project_Src_Code_Rdr/Project_Src_Code_Rdr.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Project_Src_Code_Rdr/Project_Src_Code_Rdr.hpp


    ${CMAKE_CURRENT_SOURCE_DIR}/Repo_Dir_Determiner/Repo_Dir_Determiner.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Repo_Dir_Determiner/Repo_Dir_Determiner.h

    ${CMAKE_CURRENT_SOURCE_DIR}/Repo_Warehouse_Initializer/Repo_Warehouse_Initializer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Repo_Warehouse_Initializer/Repo_Warehouse_Initializer.h

)

target_include_directories(proj_bld_tools PUBLIC

    ${CMAKE_CURRENT_SOURCE_DIR}/Build_Tools_Initializer

    ${CMAKE_CURRENT_SOURCE_DIR}/Directory_Enumerator

    ${CMAKE_CURRENT_SOURCE_DIR}/Directory_Tree_Size_Determiner

    ${CMAKE_CURRENT_SOURCE_DIR}/Git_File_List_Receiver

    ${CMAKE_CURRENT_SOURCE_DIR}/Git_File_List_Writer

    ${CMAKE_CURRENT_SOURCE_DIR}/Git_Ignoring_Files_Lister

    ${CMAKE_CURRENT_SOURCE_DIR}/Git_Modification_Lister

    ${CMAKE_CURRENT_SOURCE_DIR}/Git_Modification_Receiver

    ${CMAKE_CURRENT_SOURCE_DIR}/Library_Name_Extractor

    ${CMAKE_CURRENT_SOURCE_DIR}/Library_Updater

    ${CMAKE_CURRENT_SOURCE_DIR}/Project_Src_Code_Rdr

    ${CMAKE_CURRENT_SOURCE_DIR}/Repo_Dir_Determiner

    ${CMAKE_CURRENT_SOURCE_DIR}/Repo_Warehouse_Initializer


    ${CMAKE_SOURCE_DIR}/DESCRIPTION.PROCESSING.SYSTEM/Description.Readers/Descriptor.File.Data.Collector

    ${CMAKE_SOURCE_DIR}/DESCRIPTION.PROCESSING.SYSTEM/Description.Readers/Descriptor.File.Reader

    ${CMAKE_SOURCE_DIR}/DESCRIPTION.PROCESSING.SYSTEM/Description.Readers/Descriptor.File.Syntax.Controller


    ${CMAKE_SOURCE_DIR}/SCRIPT.WRITERS/Include_Dependency_Counter

    ${CMAKE_SOURCE_DIR}/SCRIPT.WRITERS/Project_Script_Writer

    ${CMAKE_SOURCE_DIR}/SCRIPT.WRITERS/Script_Data_Collector

    ${CMAKE_SOURCE_DIR}/SCRIPT.WRITERS/Script_Data_Processor

    ${CMAKE_SOURCE_DIR}/SCRIPT.WRITERS/Source_File_Script_Writer



    ${CMAKE_SOURCE_DIR}/SOURCE.FILE.DATA.COLLECTORS/Header_File_Determiner

    ${CMAKE_SOURCE_DIR}/SOURCE.FILE.DATA.COLLECTORS/Project_Files_Data_Collector

    ${CMAKE_SOURCE_DIR}/SOURCE.FILE.DATA.COLLECTORS/Project_Files_Lister

    ${CMAKE_SOURCE_DIR}/SOURCE.FILE.DATA.COLLECTORS/Source_File_Data_Collector

    ${CMAKE_SOURCE_DIR}/SOURCE.FILE.DATA.COLLECTORS/Source_File_Determiner


    ${CMAKE_SOURCE_DIR}/MAKE.FILE.BUILD.SYSTEM/Auto_MakeFile_Builder    

    ${CMAKE_SOURCE_DIR}/MAKE.FILE.BUILD.SYSTEM/Make_File_Builder    

    ${CMAKE_SOURCE_DIR}/MAKE.FILE.BUILD.SYSTEM/Make_File_Cleaner    

    ${CMAKE_SOURCE_DIR}/MAKE.FILE.BUILD.SYSTEM/MakeFile_Data_Collector    


    ${CMAKE_SOURCE_DIR}/BASIC.TOOLS/Cpp_FileOperations

    ${CMAKE_SOURCE_DIR}/BASIC.TOOLS/Custom_System_Interface

    ${CMAKE_SOURCE_DIR}/BASIC.TOOLS/DirectoryOperations

    ${CMAKE_SOURCE_DIR}/BASIC.TOOLS/IntToCharTranslater

    ${CMAKE_SOURCE_DIR}/BASIC.TOOLS/StringOperator
)


target_link_directories(proj_bld_tools PUBLIC 


    ${CMAKE_SOURCE_DIR}/SCRIPT.WRITERS/Include_Dependency_Counter

    ${CMAKE_SOURCE_DIR}/SCRIPT.WRITERS/Project_Script_Writer

    ${CMAKE_SOURCE_DIR}/SCRIPT.WRITERS/Script_Data_Collector

    ${CMAKE_SOURCE_DIR}/SCRIPT.WRITERS/Script_Data_Processor

    ${CMAKE_SOURCE_DIR}/SCRIPT.WRITERS/Source_File_Script_Writer


    ${CMAKE_SOURCE_DIR}/SOURCE.FILE.DATA.COLLECTORS/Header_File_Determiner

    ${CMAKE_SOURCE_DIR}/SOURCE.FILE.DATA.COLLECTORS/Project_Files_Data_Collector

    ${CMAKE_SOURCE_DIR}/SOURCE.FILE.DATA.COLLECTORS/Project_Files_Lister

    ${CMAKE_SOURCE_DIR}/SOURCE.FILE.DATA.COLLECTORS/Source_File_Data_Collector

    ${CMAKE_SOURCE_DIR}/SOURCE.FILE.DATA.COLLECTORS/Source_File_Determiner


    ${CMAKE_SOURCE_DIR}/MAKE.FILE.BUILD.SYSTEM/Auto_MakeFile_Builder    

    ${CMAKE_SOURCE_DIR}/MAKE.FILE.BUILD.SYSTEM/Make_File_Builder    

    ${CMAKE_SOURCE_DIR}/MAKE.FILE.BUILD.SYSTEM/Make_File_Cleaner    

    ${CMAKE_SOURCE_DIR}/MAKE.FILE.BUILD.SYSTEM/MakeFile_Data_Collector    



    ${CMAKE_CURRENT_SOURCE_DIR}/Build_Tools_Initializer

    ${CMAKE_CURRENT_SOURCE_DIR}/Directory_Enumerator

    ${CMAKE_CURRENT_SOURCE_DIR}/Directory_Tree_Size_Determiner

    ${CMAKE_CURRENT_SOURCE_DIR}/Git_File_List_Receiver

    ${CMAKE_CURRENT_SOURCE_DIR}/Git_File_List_Writer

    ${CMAKE_CURRENT_SOURCE_DIR}/Git_Ignoring_Files_Lister

    ${CMAKE_CURRENT_SOURCE_DIR}/Git_Modification_Lister

    ${CMAKE_CURRENT_SOURCE_DIR}/Git_Modification_Receiver

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

target_link_libraries(proj_bld_tools PUBLIC script_writers make_fbld_sys src_dat_col des_reader basic_tools)