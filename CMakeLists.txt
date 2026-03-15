

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

execute_process(
    COMMAND ${CMAKE_COMMAND} -E make_directory "${USER_PROFILE_PATH}/Pcynlitx"
    RESULT_VARIABLE directory_creation_result
)

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


add_executable(Project_Script_Writer 

        ${CMAKE_CURRENT_SOURCE_DIR}/SOURCE/SCRIPT.WRITERS/Project_Script_Writer/Project_Script_Writer_Main_File.cpp)


add_executable(Build_Tools_Initializer 

        ${CMAKE_CURRENT_SOURCE_DIR}/SOURCE/PROJECT.BUILD.TOOLS/Build_Tools_Initializer/Build_Tools_Initializer_Main_File.cpp)


add_executable(Executable_MakeFile_Builder 

        ${CMAKE_CURRENT_SOURCE_DIR}/SOURCE/EXECUTABLE.MAKE.FILE.BUILD.SYSTEM/Executable_MakeFile_Builder/Executable_MakeFile_Builder_Main_File.cpp)


add_executable(Auto_MakeFile_Builder  

        ${CMAKE_CURRENT_SOURCE_DIR}/SOURCE/MAKE.FILE.BUILD.SYSTEM/Auto_MakeFile_Builder/Auto_MakeFile_Builder_Main_File.cpp)


add_executable(Pcynlitx_Kernel

        ${CMAKE_CURRENT_SOURCE_DIR}/SOURCE/KERNEL.DEVELOPMENT/Kernel_Main_File.cpp)

add_executable(CMAKE_Build

        ${CMAKE_CURRENT_SOURCE_DIR}/SOURCE/MAKE.FILE.BUILD.SYSTEM/CMAKE_Build_System_Generator/CMAKE_Build_System_Generator_Main_File.cpp)


add_executable(CMAKE_Build_Executable

        ${CMAKE_CURRENT_SOURCE_DIR}/SOURCE/MAKE.FILE.BUILD.SYSTEM/CMAKE_Executable_Target_Constructor/CMAKE_Executable_Target_Constructor_Main_File.cpp)


add_executable(Pcynlitx WIN32

        ${CMAKE_CURRENT_SOURCE_DIR}/SOURCE/GUI.DEVELOPMENT/wxLauncher.cpp pcynlitx_resource.rc 

        ${CMAKE_CURRENT_SOURCE_DIR}/SOURCE/GUI.DEVELOPMENT/Icon_Designs/png_files/pcynlitx_png_resource.rc

        ${CMAKE_CURRENT_SOURCE_DIR}/SOURCE/GUI.DEVELOPMENT/Icon_Designs/png_files/build_system_generator.png
)

include("GUI_build_settings.cmake")


target_link_libraries(Pcynlitx PUBLIC BuildSystem_GUI des_reader pthread 

                     wxbase33ud

                     wxaui

                     wxmsw33ud_core

                     wxmsw33ud_adv 
                      
                     wxmsw33ud_aui

                     wxmsw33ud_stc 
                     
                     wxscintillad 
                                          
                     wxmsw33ud_richtext

                     wxmsw33ud_xrc

                     wxxrc

                     wxstc

                     wxgl

                     wxnet

                     gcc stdc++
)


target_link_libraries(Project_Script_Writer PUBLIC 

        src_dat_col src_proc_sys proj_bld_tools git_data_processing_system des_reader basic_tools )

target_link_libraries(Build_Tools_Initializer PUBLIC 

        src_dat_col src_proc_sys proj_bld_tools git_data_processing_system des_reader basic_tools )


target_link_libraries(Executable_MakeFile_Builder PUBLIC exec_make_bld )


target_link_libraries(Auto_MakeFile_Builder PUBLIC make_fbld_sys proj_bld_tools 

                   git_data_processing_system des_reader basic_tools)


target_link_libraries(Pcynlitx_Kernel PUBLIC kernel proj_bld_tools exec_make_bld script_writers make_fbld_sys 

                   src_proc_sys git_data_processing_system src_dat_col des_reader basic_tools)


target_link_libraries(CMAKE_Build PUBLIC proj_bld_tools make_fbld_sys 

                   src_proc_sys git_data_processing_system src_dat_col des_reader basic_tools)


target_link_libraries(CMAKE_Build_Executable PUBLIC proj_bld_tools make_fbld_sys 

                      src_proc_sys git_data_processing_system src_dat_col des_reader basic_tools)

add_dependencies(BuildSystem_GUI wxbase wxcore wxaui wxadv wxstc wxrc wxrichtext wxgl wxnet)

add_dependencies(Pcynlitx BuildSystem_GUI)


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


