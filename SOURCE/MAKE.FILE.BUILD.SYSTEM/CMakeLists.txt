



set(NOVA_SRC_DIR "${CMAKE_SOURCE_DIR}/SOURCE")

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



    ${NOVA_SRC_DIR}/PROJECT.BUILD.TOOLS/Build_Tools_Initializer

    ${NOVA_SRC_DIR}/PROJECT.BUILD.TOOLS/Directory_Enumerator

    ${NOVA_SRC_DIR}/PROJECT.BUILD.TOOLS/Directory_Tree_Size_Determiner

    ${NOVA_SRC_DIR}/PROJECT.BUILD.TOOLS/Library_Name_Extractor

    ${NOVA_SRC_DIR}/PROJECT.BUILD.TOOLS/Library_Updater

    ${NOVA_SRC_DIR}/PROJECT.BUILD.TOOLS/Project_Src_Code_Rdr

    ${NOVA_SRC_DIR}/PROJECT.BUILD.TOOLS/Repo_Dir_Determiner

    ${NOVA_SRC_DIR}/PROJECT.BUILD.TOOLS/Repo_Warehouse_Initializer




    ${NOVA_SRC_DIR}/GIT.DATA.PROCESSING.SYSTEM/Git_Data_Processor

    ${NOVA_SRC_DIR}/GIT.DATA.PROCESSING.SYSTEM/Git_File_List_Receiver

    ${NOVA_SRC_DIR}/GIT.DATA.PROCESSING.SYSTEM/Git_File_List_Writer

    ${NOVA_SRC_DIR}/GIT.DATA.PROCESSING.SYSTEM/Git_Ignoring_Files_Lister

    ${NOVA_SRC_DIR}/GIT.DATA.PROCESSING.SYSTEM/Git_Modification_Lister

    ${NOVA_SRC_DIR}/GIT.DATA.PROCESSING.SYSTEM/Git_Modification_Receiver



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


    ${NOVA_SRC_DIR}/DESCRIPTION.PROCESSING.SYSTEM/Description.Readers/Descriptor.File.Data.Collector

    ${NOVA_SRC_DIR}/DESCRIPTION.PROCESSING.SYSTEM/Description.Readers/Descriptor.File.Reader

    ${NOVA_SRC_DIR}/DESCRIPTION.PROCESSING.SYSTEM/Description.Readers/Descriptor.File.Syntax.Controller


    ${NOVA_SRC_DIR}/BASIC.TOOLS/Cpp_FileOperations

    ${NOVA_SRC_DIR}/BASIC.TOOLS/Custom_System_Interface

    ${NOVA_SRC_DIR}/BASIC.TOOLS/DirectoryOperations

    ${NOVA_SRC_DIR}/BASIC.TOOLS/IntToCharTranslater

    ${NOVA_SRC_DIR}/BASIC.TOOLS/StringOperator
)

target_link_directories(make_fbld_sys PUBLIC 

    ${CMAKE_CURRENT_SOURCE_DIR}/Auto_MakeFile_Builder    

    ${CMAKE_CURRENT_SOURCE_DIR}/Make_File_Builder    

    ${CMAKE_CURRENT_SOURCE_DIR}/Make_File_Cleaner    

    ${CMAKE_CURRENT_SOURCE_DIR}/MakeFile_Path_Determiner    

    ${CMAKE_CURRENT_SOURCE_DIR}/MakeFile_Data_Collector    

    ${CMAKE_CURRENT_SOURCE_DIR}/MakeFile_Directory_Constructor    

    ${CMAKE_CURRENT_SOURCE_DIR}/CMake_Target_Library_Builder    

    ${CMAKE_CURRENT_SOURCE_DIR}/CMAKE_Build_System_Generator

    ${CMAKE_CURRENT_SOURCE_DIR}/CMAKE_System_Constructor

    ${CMAKE_CURRENT_SOURCE_DIR}/CMAKE_Main_File_Writer

    ${CMAKE_CURRENT_SOURCE_DIR}/CMAKE_Executable_Target_Constructor

    ${CMAKE_CURRENT_SOURCE_DIR}/Build_System_Meta_Data_Collector

    ${CMAKE_CURRENT_SOURCE_DIR}/CMAKE_Target_List_Determiner

    ${CMAKE_CURRENT_SOURCE_DIR}/CMAKE_Target_List_Data_Structure_Constructor
    

    ${NOVA_SRC_DIR}/PROJECT.BUILD.TOOLS/Build_Tools_Initializer

    ${NOVA_SRC_DIR}/PROJECT.BUILD.TOOLS/Directory_Enumerator

    ${NOVA_SRC_DIR}/PROJECT.BUILD.TOOLS/Directory_Tree_Size_Determiner

    ${NOVA_SRC_DIR}/PROJECT.BUILD.TOOLS/Library_Name_Extractor

    ${NOVA_SRC_DIR}/PROJECT.BUILD.TOOLS/Library_Updater

    ${NOVA_SRC_DIR}/PROJECT.BUILD.TOOLS/Project_Src_Code_Rdr

    ${NOVA_SRC_DIR}/PROJECT.BUILD.TOOLS/Repo_Dir_Determiner

    ${NOVA_SRC_DIR}/PROJECT.BUILD.TOOLS/Repo_Warehouse_Initializer



    ${NOVA_SRC_DIR}/GIT.DATA.PROCESSING.SYSTEM/Git_Data_Processor

    ${NOVA_SRC_DIR}/GIT.DATA.PROCESSING.SYSTEM/Git_File_List_Receiver

    ${NOVA_SRC_DIR}/GIT.DATA.PROCESSING.SYSTEM/Git_File_List_Writer

    ${NOVA_SRC_DIR}/GIT.DATA.PROCESSING.SYSTEM/Git_Ignoring_Files_Lister

    ${NOVA_SRC_DIR}/GIT.DATA.PROCESSING.SYSTEM/Git_Modification_Lister

    ${NOVA_SRC_DIR}/GIT.DATA.PROCESSING.SYSTEM/Git_Modification_Receiver




    ${NOVA_SRC_DIR}/SOURCE.FILE.PROCESSING.SYSTEM/Header_File_Processor

    ${NOVA_SRC_DIR}/SOURCE.FILE.PROCESSING.SYSTEM/Source_File_Compiler_Data_Extractor

    ${NOVA_SRC_DIR}/SOURCE.FILE.PROCESSING.SYSTEM/Source_File_Dependency_Determiner

    ${NOVA_SRC_DIR}/SOURCE.FILE.PROCESSING.SYSTEM/Source_File_Dependency_Selector_For_Single_File

    ${NOVA_SRC_DIR}/SOURCE.FILE.PROCESSING.SYSTEM/Source_File_Dependency_Selector

    ${NOVA_SRC_DIR}/SOURCE.FILE.PROCESSING.SYSTEM/Dependency_Data_Extractor

    ${NOVA_SRC_DIR}/SOURCE.FILE.PROCESSING.SYSTEM/Source_File_Information_Collector_For_Single_File

    ${NOVA_SRC_DIR}/SOURCE.FILE.PROCESSING.SYSTEM/Source_File_Information_Collector

    ${NOVA_SRC_DIR}/SOURCE.FILE.PROCESSING.SYSTEM/Source_File_Processor

    ${NOVA_SRC_DIR}/SOURCE/SOURCE.FILE.PROCESSING.SYSTEM/Dependency_Data_Stack_Container

    ${NOVA_SRC_DIR}/SOURCE/SOURCE.FILE.PROCESSING.SYSTEM/Header_Dependency_Data_Extractor

    ${NOVA_SRC_DIR}/SOURCE/SOURCE.FILE.PROCESSING.SYSTEM/Dependency_Data_Processor




    ${NOVA_SRC_DIR}/SOURCE/DESCRIPTION.PROCESSING.SYSTEM/Description.Readers/Descriptor.File.Data.Collector

    ${NOVA_SRC_DIR}/SOURCE/DESCRIPTION.PROCESSING.SYSTEM/Description.Readers/Descriptor.File.Reader

    ${NOVA_SRC_DIR}/SOURCE/DESCRIPTION.PROCESSING.SYSTEM/Description.Readers/Descriptor.File.Syntax.Controller



    ${NOVA_SRC_DIR}/SOURCE/BASIC.TOOLS/Cpp_FileOperations

    ${NOVA_SRC_DIR}/SOURCE/BASIC.TOOLS/Custom_System_Interface

    ${NOVA_SRC_DIR}/SOURCE/BASIC.TOOLS/DirectoryOperations

    ${NOVA_SRC_DIR}/SOURCE/BASIC.TOOLS/IntToCharTranslater

    ${NOVA_SRC_DIR}/SOURCE/BASIC.TOOLS/StringOperator

)

target_link_libraries(make_fbld_sys PUBLIC proj_bld_tools 

                    git_data_processing_system des_reader basic_tools)



target_compile_options(make_fbld_sys PUBLIC 

    -std=c++17

    -Wall

    -Bstatic

    -g

    -O0

    -mthreads

    -D__WXMSW__

    -D_UNICODE

    -DWIN32

)
