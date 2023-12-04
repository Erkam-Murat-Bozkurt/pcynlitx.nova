

add_library(des_writer 

    ${CMAKE_CURRENT_SOURCE_DIR}/DataRecorder/DataRecorder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/DataRecorder/DataRecorder.h

    ${CMAKE_CURRENT_SOURCE_DIR}/Empty.Descriptor.File.Builder/Empty_Descriptor_File_Builder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Empty.Descriptor.File.Builder/Empty_Descriptor_File_Builder.hpp
    
)

target_include_directories(des_writer PUBLIC

    ${CMAKE_CURRENT_SOURCE_DIR}/DataRecorder

    ${CMAKE_CURRENT_SOURCE_DIR}/Empty.Descriptor.File.Builder 

    ${CMAKE_SOURCE_DIR}/BASIC.TOOLS/Cpp_FileOperations

    ${CMAKE_SOURCE_DIR}/BASIC.TOOLS/Custom_System_Interface

    ${CMAKE_SOURCE_DIR}/BASIC.TOOLS/DirectoryOperations

    ${CMAKE_SOURCE_DIR}/BASIC.TOOLS/IntToCharTranslater

    ${CMAKE_SOURCE_DIR}/BASIC.TOOLS/StringOperator

    ${CMAKE_SOURCE_DIR}/DESCRIPTION.PROCESSING.SYSTEM/Description.Readers/Descriptor.File.Data.Collector

    ${CMAKE_SOURCE_DIR}/DESCRIPTION.PROCESSING.SYSTEM/Description.Readers/Descriptor.File.Syntax.Controller

    ${CMAKE_SOURCE_DIR}/DESCRIPTION.PROCESSING.SYSTEM/Description.Readers/Descriptor.File.Reader

)



target_link_directories(des_writer PUBLIC


    ${CMAKE_CURRENT_SOURCE_DIR}/DataRecorder

    ${CMAKE_CURRENT_SOURCE_DIR}/Empty.Descriptor.File.Builder 


    ${CMAKE_SOURCE_DIR}/BASIC.TOOLS/CharOperator

    ${CMAKE_SOURCE_DIR}/BASIC.TOOLS/Cpp_FileOperations

    ${CMAKE_SOURCE_DIR}/BASIC.TOOLS/Custom_System_Interface

    ${CMAKE_SOURCE_DIR}/BASIC.TOOLS/DirectoryOperations

    ${CMAKE_SOURCE_DIR}/BASIC.TOOLS/IntToCharTranslater

    ${CMAKE_SOURCE_DIR}/BASIC.TOOLS/StringOperator


    ${CMAKE_SOURCE_DIR}/DESCRIPTION.PROCESSING.SYSTEM/Description.Readers/Descriptor.File.Data.Collector

    ${CMAKE_SOURCE_DIR}/DESCRIPTION.PROCESSING.SYSTEM/Description.Readers/Descriptor.File.Syntax.Controller

    ${CMAKE_SOURCE_DIR}/DESCRIPTION.PROCESSING.SYSTEM/Description.Readers/Descriptor.File.Reader


)


target_link_libraries(des_writer PUBLIC basic_tools des_reader)