
# ${NOVA_SRC_DIR} is defeined on the upper directory CMakeLists.txt file as  ${CMAKE_SOURCE_DIR}/SOURCE

add_library(cmake_target_lib_constructor_lib 


    ${NOVA_SRC_DIR}/MAKE.FILE.BUILD.SYSTEM/CMake_Target_Library_Builder/CMAKE_Target_Library_Builder.cpp

    ${NOVA_SRC_DIR}/MAKE.FILE.BUILD.SYSTEM/CMake_Target_Library_Builder/CMAKE_Target_Library_Builder.hpp


    ${NOVA_SRC_DIR}/MAKE.FILE.BUILD.SYSTEM/MakeFile_Path_Determiner/MakeFile_Path_Determiner.cpp

    ${NOVA_SRC_DIR}/MAKE.FILE.BUILD.SYSTEM/MakeFile_Path_Determiner/MakeFile_Path_Determiner.hpp


    ${NOVA_SRC_DIR}/MAKE.FILE.BUILD.SYSTEM/MakeFile_Directory_Constructor/MakeFile_Directory_Constructor.cpp

    ${NOVA_SRC_DIR}/MAKE.FILE.BUILD.SYSTEM/MakeFile_Directory_Constructor/MakeFile_Directory_Constructor.hpp


    ${NOVA_SRC_DIR}/MAKE.FILE.BUILD.SYSTEM/MakeFile_Data_Collector/MakeFile_Data_Collector.cpp

    ${NOVA_SRC_DIR}/MAKE.FILE.BUILD.SYSTEM/MakeFile_Data_Collector/MakeFile_Data_Collector.hpp
)





target_include_directories(cmake_target_lib_constructor_lib PUBLIC

    ${NOVA_SRC_DIR}/MAKE.FILE.BUILD.SYSTEM/CMake_Target_Library_Builder    


    ${NOVA_SRC_DIR}/MAKE.FILE.BUILD.SYSTEM/MakeFile_Path_Determiner

    ${NOVA_SRC_DIR}/MAKE.FILE.BUILD.SYSTEM/MakeFile_Directory_Constructor

    ${NOVA_SRC_DIR}/MAKE.FILE.BUILD.SYSTEM/MakeFile_Data_Collector



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

target_link_directories(cmake_target_lib_constructor_lib PUBLIC 

   
    ${NOVA_SRC_DIR}/MAKE.FILE.BUILD.SYSTEM/CMake_Target_Library_Builder  


    ${NOVA_SRC_DIR}/MAKE.FILE.BUILD.SYSTEM/MakeFile_Path_Determiner

    ${NOVA_SRC_DIR}/MAKE.FILE.BUILD.SYSTEM/MakeFile_Directory_Constructor

    ${NOVA_SRC_DIR}/MAKE.FILE.BUILD.SYSTEM/MakeFile_Data_Collector



    ${NOVA_SRC_DIR}/PROJECT.BUILD.TOOLS/Build_Tools_Initializer

    ${NOVA_SRC_DIR}PROJECT.BUILD.TOOLS/Directory_Enumerator

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

add_dependencies(cmake_target_lib_constructor_lib

                 proj_bld_tools 

                 git_data_processing_system 
                      
                 des_reader basic_tools
)

target_link_libraries(cmake_target_lib_constructor_lib PUBLIC 

                      proj_bld_tools 

                      git_data_processing_system 
                      
                      des_reader basic_tools
)