

cmake_minimum_required(VERSION 4.1.2)

project(Pcynlitx VERSION 1.0)

set(CMAKE_BUILD_PARALLEL_LEVEL 8)

set(wxWidgets_USE_STATIC 1)
set(wxBUILD_SHARED OFF)
set(wxBUILD_MONOLITHIC OFF)
set(wxBUILD_PRECOMP ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


execute_process(COMMAND cmd /c echo %USERPROFILE%

   WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
   OUTPUT_VARIABLE USER_PROFILE_PATH
)

string(REPLACE "\n" "" USER_PROFILE_PATH "${USER_PROFILE_PATH}")

string(REPLACE "/" "\\" USER_PROFILE_PATH "${USER_PROFILE_PATH}")


if(NOT EXISTS "${USER_PROFILE_PATH}/Pcynlitx")

   execute_process(
        
        COMMAND ${CMAKE_COMMAND} -E make_directory 
   
        "${USER_PROFILE_PATH}/Pcynlitx"
    
        RESULT_VARIABLE directory_creation_result
   )

   execute_process(
        
        COMMAND ${CMAKE_COMMAND} -E make_directory 
   
        "${USER_PROFILE_PATH}/Pcynlitx/Workspace"
    
        RESULT_VARIABLE directory_creation_result
   )

endif()


set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


include(FetchContent)

FetchContent_Declare(
   wxWidgets
   GIT_REPOSITORY https://github.com/wxWidgets/wxWidgets.git
   GIT_TAG v3.3.1
   GIT_PROGRESS TRUE
)

FetchContent_GetProperties(wxwidgets)
FetchContent_MakeAvailable(wxwidgets)



add_subdirectory(SOURCE)

include("Executable_File_List.cmake")

include("GUI_build_settings.cmake")

include("Target_Link_Settings.cmake")


add_custom_command(
       TARGET Pcynlitx_Kernel
       POST_BUILD 
       COMMAND ${CMAKE_COMMAND}
       ARGS -E copy $<TARGET_FILE:Pcynlitx_Kernel> "${USER_PROFILE_PATH}/Pcynlitx"
       WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
       VERBATIM
       BYPRODUCTS
)

add_custom_command(
       TARGET Pcynlitx
       POST_BUILD 
       COMMAND ${CMAKE_COMMAND}
       ARGS -E copy $<TARGET_FILE:Pcynlitx> "${USER_PROFILE_PATH}/Pcynlitx"
       WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
       VERBATIM
       BYPRODUCTS
)


set(INSTALLER_DIR "${CMAKE_SOURCE_DIR}/SOURCE/INSTALLER.DEVELOPMENT")

add_custom_command(
       TARGET Pcynlitx_Kernel
       POST_BUILD 
       COMMAND ${CMAKE_COMMAND}
       ARGS -E copy $<TARGET_FILE:Pcynlitx_Kernel> "${INSTALLER_DIR}"
       WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
       VERBATIM
       BYPRODUCTS
)

add_custom_command(
       TARGET Pcynlitx
       POST_BUILD 
       COMMAND ${CMAKE_COMMAND}
       ARGS -E copy $<TARGET_FILE:Pcynlitx> "${INSTALLER_DIR}"
       WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
       VERBATIM
       BYPRODUCTS
)


