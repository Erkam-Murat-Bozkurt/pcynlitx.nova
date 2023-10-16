



add_library(git_data_processing_system 

    ${CMAKE_CURRENT_SOURCE_DIR}/Git_Data_Processor/Git_Data_Processor.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Git_Data_Processor/Git_Data_Processor.hpp

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
)

target_include_directories(git_data_processing_system PUBLIC


    ${CMAKE_CURRENT_SOURCE_DIR}/Git_Data_Processor

    ${CMAKE_CURRENT_SOURCE_DIR}/Git_File_List_Receiver

    ${CMAKE_CURRENT_SOURCE_DIR}/Git_File_List_Writer

    ${CMAKE_CURRENT_SOURCE_DIR}/Git_Ignoring_Files_Lister

    ${CMAKE_CURRENT_SOURCE_DIR}/Git_Modification_Lister

    ${CMAKE_CURRENT_SOURCE_DIR}/Git_Modification_Receiver



    ${CMAKE_SOURCE_DIR}/DESCRIPTION.PROCESSING.SYSTEM/Description.Readers/Descriptor.File.Data.Collector

    ${CMAKE_SOURCE_DIR}/DESCRIPTION.PROCESSING.SYSTEM/Description.Readers/Descriptor.File.Reader

    ${CMAKE_SOURCE_DIR}/DESCRIPTION.PROCESSING.SYSTEM/Description.Readers/Descriptor.File.Syntax.Controller



    ${CMAKE_SOURCE_DIR}/SOURCE.FILE.DATA.COLLECTORS/Header_File_Determiner

    ${CMAKE_SOURCE_DIR}/SOURCE.FILE.DATA.COLLECTORS/Source_File_Data_Collector

    ${CMAKE_SOURCE_DIR}/SOURCE.FILE.DATA.COLLECTORS/Source_File_Determiner


    ${CMAKE_SOURCE_DIR}/BASIC.TOOLS/Cpp_FileOperations

    ${CMAKE_SOURCE_DIR}/BASIC.TOOLS/Custom_System_Interface

    ${CMAKE_SOURCE_DIR}/BASIC.TOOLS/DirectoryOperations

    ${CMAKE_SOURCE_DIR}/BASIC.TOOLS/IntToCharTranslater

    ${CMAKE_SOURCE_DIR}/BASIC.TOOLS/StringOperator
)


target_link_directories(git_data_processing_system PUBLIC 


    ${CMAKE_CURRENT_SOURCE_DIR}/Git_Data_Processor

    ${CMAKE_CURRENT_SOURCE_DIR}/Git_File_List_Receiver

    ${CMAKE_CURRENT_SOURCE_DIR}/Git_File_List_Writer

    ${CMAKE_CURRENT_SOURCE_DIR}/Git_Ignoring_Files_Lister

    ${CMAKE_CURRENT_SOURCE_DIR}/Git_Modification_Lister

    ${CMAKE_CURRENT_SOURCE_DIR}/Git_Modification_Receiver



    ${CMAKE_SOURCE_DIR}/SOURCE.FILE.DATA.COLLECTORS/Header_File_Determiner

    ${CMAKE_SOURCE_DIR}/SOURCE.FILE.DATA.COLLECTORS/Project_Files_Data_Collector

    ${CMAKE_SOURCE_DIR}/SOURCE.FILE.DATA.COLLECTORS/Project_Files_Lister

    ${CMAKE_SOURCE_DIR}/SOURCE.FILE.DATA.COLLECTORS/Source_File_Data_Collector

    ${CMAKE_SOURCE_DIR}/SOURCE.FILE.DATA.COLLECTORS/Source_File_Determiner




    ${CMAKE_SOURCE_DIR}/DESCRIPTION.PROCESSING.SYSTEM/Description.Readers/Descriptor.File.Data.Collector

    ${CMAKE_SOURCE_DIR}/DESCRIPTION.PROCESSING.SYSTEM/Description.Readers/Descriptor.File.Reader

    ${CMAKE_SOURCE_DIR}/DESCRIPTION.PROCESSING.SYSTEM/Description.Readers/Descriptor.File.Syntax.Controller

    
    ${CMAKE_SOURCE_DIR}/BASIC.TOOLS/Cpp_FileOperations

    ${CMAKE_SOURCE_DIR}/BASIC.TOOLS/Custom_System_Interface

    ${CMAKE_SOURCE_DIR}/BASIC.TOOLS/DirectoryOperations

    ${CMAKE_SOURCE_DIR}/BASIC.TOOLS/IntToCharTranslater

    ${CMAKE_SOURCE_DIR}/BASIC.TOOLS/StringOperator
)



target_link_libraries(git_data_processing_system PUBLIC src_dat_col des_reader basic_tools)