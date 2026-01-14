
add_library(basic_tools 


    ${CMAKE_CURRENT_SOURCE_DIR}/CharOperator/CharOperator.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/CharOperator/CharOperator.h

    
    ${CMAKE_CURRENT_SOURCE_DIR}/Cpp_FileOperations/Cpp_FileOperations.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Cpp_FileOperations/Cpp_FileOperations.h


    ${CMAKE_CURRENT_SOURCE_DIR}/Custom_System_Interface/Custom_System_Interface.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Custom_System_Interface/Custom_System_Interface.h

    
    ${CMAKE_CURRENT_SOURCE_DIR}/DirectoryOperations/DirectoryOperations.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/DirectoryOperations/DirectoryOperations.h

    
    ${CMAKE_CURRENT_SOURCE_DIR}/IntToCharTranslater/IntToCharTranslater.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/IntToCharTranslater/IntToCharTranslater.h

    
    ${CMAKE_CURRENT_SOURCE_DIR}/StringOperator/StringOperator.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/StringOperator/StringOperator.h

)

target_include_directories(basic_tools PUBLIC


    ${CMAKE_CURRENT_SOURCE_DIR}/CharOperator

    ${CMAKE_CURRENT_SOURCE_DIR}/Cpp_FileOperations

    ${CMAKE_CURRENT_SOURCE_DIR}/Custom_System_Interface

    ${CMAKE_CURRENT_SOURCE_DIR}/DirectoryOperations

    ${CMAKE_CURRENT_SOURCE_DIR}/IntToCharTranslater

    ${CMAKE_CURRENT_SOURCE_DIR}/StringOperator

)


target_link_directories(basic_tools PUBLIC


    ${CMAKE_CURRENT_SOURCE_DIR}/CharOperator

    ${CMAKE_CURRENT_SOURCE_DIR}/Cpp_FileOperations

    ${CMAKE_CURRENT_SOURCE_DIR}/Custom_System_Interface

    ${CMAKE_CURRENT_SOURCE_DIR}/DirectoryOperations

    ${CMAKE_CURRENT_SOURCE_DIR}/IntToCharTranslater

    ${CMAKE_CURRENT_SOURCE_DIR}/StringOperator

)