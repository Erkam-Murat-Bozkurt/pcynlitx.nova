


add_library(des_reader


    ${CMAKE_CURRENT_SOURCE_DIR}/Descriptor.File.Data.Collector/Descriptor_File_Data_Collector.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Descriptor.File.Data.Collector/Descriptor_File_Data_Collector.hpp

    ${CMAKE_CURRENT_SOURCE_DIR}/Record.Number.Determiner/Record_Number_Determiner.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Record.Number.Determiner/Record_Number_Determiner.hpp


    ${CMAKE_CURRENT_SOURCE_DIR}/Descriptor.File.Line.Reader/Descriptor_File_Line_Reader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Descriptor.File.Line.Reader/Descriptor_File_Line_Reader.hpp

    
    ${CMAKE_CURRENT_SOURCE_DIR}/GUI.Descriptor.File.Reader/GUI_Descriptor_File_Reader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GUI.Descriptor.File.Reader/GUI_Descriptor_File_Reader.hpp

    ${CMAKE_CURRENT_SOURCE_DIR}/Descriptor.File.Reader/Descriptor_File_Reader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Descriptor.File.Reader/Descriptor_File_Reader.hpp

    ${CMAKE_CURRENT_SOURCE_DIR}/Descriptor.File.Syntax.Controller/Descriptor_File_Syntax_Controller.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Descriptor.File.Syntax.Controller/Descriptor_File_Syntax_Controller.hpp
    
)

target_link_libraries(des_reader PUBLIC basic_tools)



target_include_directories(des_reader PUBLIC

    ${CMAKE_CURRENT_SOURCE_DIR}/Descriptor.File.Data.Collector

    ${CMAKE_CURRENT_SOURCE_DIR}/GUI.Descriptor.File.Reader

    ${CMAKE_CURRENT_SOURCE_DIR}/Descriptor.File.Reader

    ${CMAKE_CURRENT_SOURCE_DIR}/Descriptor.File.Syntax.Controller

    ${CMAKE_CURRENT_SOURCE_DIR}/Record.Number.Determiner

    ${CMAKE_CURRENT_SOURCE_DIR}/Descriptor.File.Line.Reader

    
    ${CMAKE_SOURCE_DIR}/BASIC.TOOLS/Cpp_FileOperations

    ${CMAKE_SOURCE_DIR}/BASIC.TOOLS/Custom_System_Interface

    ${CMAKE_SOURCE_DIR}/BASIC.TOOLS/DirectoryOperations

    ${CMAKE_SOURCE_DIR}/BASIC.TOOLS/IntToCharTranslater

    ${CMAKE_SOURCE_DIR}/BASIC.TOOLS/StringOperator



)


target_link_directories(des_reader PUBLIC

    ${CMAKE_CURRENT_SOURCE_DIR}/GUI.Descriptor.File.Reader

    ${CMAKE_CURRENT_SOURCE_DIR}/Descriptor.File.Data.Collector

    ${CMAKE_CURRENT_SOURCE_DIR}/Descriptor.File.Reader

    ${CMAKE_CURRENT_SOURCE_DIR}/Record.Number.Determiner

    ${CMAKE_CURRENT_SOURCE_DIR}/Descriptor.File.Line.Reader

    ${CMAKE_CURRENT_SOURCE_DIR}/Descriptor.File.Syntax.Controller



    ${CMAKE_SOURCE_DIR}/BASIC.TOOLS/CharOperator

    ${CMAKE_SOURCE_DIR}/BASIC.TOOLS/Cpp_FileOperations

    ${CMAKE_SOURCE_DIR}/BASIC.TOOLS/Custom_System_Interface

    ${CMAKE_SOURCE_DIR}/BASIC.TOOLS/DirectoryOperations

    ${CMAKE_SOURCE_DIR}/BASIC.TOOLS/IntToCharTranslater

    ${CMAKE_SOURCE_DIR}/BASIC.TOOLS/StringOperator


)


target_link_libraries(des_reader PUBLIC basic_tools)