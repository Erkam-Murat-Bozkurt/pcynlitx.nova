



cmake_minimum_required(VERSION 4.1.2)

project(Pcynlitx VERSION 1.0)

set(CMAKE_BUILD_PARALLEL_LEVEL 8)

set(wxWidgets_USE_STATIC 1)
set(wxBUILD_SHARED OFF)
set(wxBUILD_MONOLITHIC OFF)
set(wxBUILD_PRECOMP ON)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)



if(MINGW)
   
   message("The mingw compiler toolchain detected")

else()

   message("The mingw compiler toolchain can not be detected")
   message("The mingw compiler will be installed")


   execute_process(COMMAND cmd /c echo %USERPROFILE%

     WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
     OUTPUT_VARIABLE USER_PROFILE_PATH
   )


   string(REPLACE "\n" "" USER_PROFILE_PATH "${USER_PROFILE_PATH}")

   string(REPLACE "/" "\\" USER_PROFILE_PATH "${USER_PROFILE_PATH}")


   file(DOWNLOAD  https://github.com/brechtsanders/winlibs_mingw/releases/download/15.2.0posix-13.0.0-msvcrt-r3/winlibs-x86_64-posix-seh-gcc-15.2.0-mingw-w64msvcrt-13.0.0-r3.zip ${USER_PROFILE_PATH}/winlibs-x86_64-posix-seh-gcc-15.2.0-mingw-w64msvcrt-13.0.0-r3.zip SHOW_PROGRESS)

   set(COMPILER_ZIP_PATH ${USER_PROFILE_PATH}/winlibs-x86_64-posix-seh-gcc-15.2.0-mingw-w64msvcrt-13.0.0-r3.zip)

   string(REPLACE "/" "\\" COMPILER_ZIP_PATH "${COMPILER_ZIP_PATH}")

   message("The directory ${COMPILER_ZIP_PATH}")


   file(ARCHIVE_EXTRACT INPUT ${COMPILER_ZIP_PATH} DESTINATION ${USER_PROFILE_PATH} VERBOSE)

   execute_process(COMMAND cmd /c echo %PATH% 

      WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
      OUTPUT_VARIABLE PATH_ENV
   )

   file(REMOVE ${USER_PROFILE_PATH}/winlibs-x86_64-posix-seh-gcc-15.2.0-mingw-w64msvcrt-13.0.0-r3.zip)

   string(REPLACE "\n" "" PATH_ENV "${PATH_ENV}")

   set(new_paths ";${USER_PROFILE_PATH}/mingw64")

   string(APPEND new_paths ";${USER_PROFILE_PATH}/mingw64/bin")

   string(APPEND new_paths ";${USER_PROFILE_PATH}/mingw64/include")

   string(APPEND new_paths ";${USER_PROFILE_PATH}/mingw64/lib")

   string(APPEND new_paths ";${USER_PROFILE_PATH}/mingw64/x86_64-w64-mingw32")

   string(APPEND new_paths ";${USER_PROFILE_PATH}/mingw64/x86_64-w64-mingw32/include")

   string(APPEND new_paths ";${USER_PROFILE_PATH}/mingw64/x86_64-w64-mingw32/lib")


   string(REPLACE "\n" "" new_paths "${new_paths}")

   string(REPLACE "/" "\\" new_paths "${new_paths}")


   execute_process(

       COMMAND cmd /c reg.exe add "HKEY_CURRENT_USER\\Environment" /v PATH /t REG_SZ /d "${PATH_ENV};${new_paths}" /f
       WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
       RESULT_VARIABLE REG_EXE_RETURN_VALUE
       OUTPUT_QUIET
   )

   if(REG_EXE_RETURN_VALUE EQUAL 0)

      message("The compiler paths are set")
   
   else()
   
      message("The compiler paths are not set successfuly")

   endif()

endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


include(FetchContent)

FetchContent_Declare(
   wxWidgets
   GIT_REPOSITORY https://github.com/wxWidgets/wxWidgets.git
   GIT_TAG v3.3.1
)

FetchContent_GetProperties(wxwidgets)
FetchContent_MakeAvailable(wxwidgets)



add_subdirectory(BASIC.TOOLS)

add_subdirectory(DESCRIPTION.PROCESSING.SYSTEM)

add_subdirectory(GIT.DATA.PROCESSING.SYSTEM)

add_subdirectory(SOURCE.FILE.DATA.COLLECTORS)

add_subdirectory(SOURCE.FILE.PROCESSING.SYSTEM)

add_subdirectory(MAKE.FILE.BUILD.SYSTEM)

add_subdirectory(SCRIPT.WRITERS)

add_subdirectory(PROJECT.BUILD.TOOLS)

add_subdirectory(EXECUTABLE.MAKE.FILE.BUILD.SYSTEM)

add_subdirectory(KERNEL.DEVELOPMENT)

add_subdirectory(GUI.DEVELOPMENT)



add_executable(Project_Script_Writer 

        ${CMAKE_CURRENT_SOURCE_DIR}/SCRIPT.WRITERS/Project_Script_Writer/Project_Script_Writer_Main_File.cpp)


add_executable(Build_Tools_Initializer 

        ${CMAKE_CURRENT_SOURCE_DIR}/PROJECT.BUILD.TOOLS/Build_Tools_Initializer/Build_Tools_Initializer_Main_File.cpp)


add_executable(Executable_MakeFile_Builder 

        ${CMAKE_CURRENT_SOURCE_DIR}/EXECUTABLE.MAKE.FILE.BUILD.SYSTEM/Executable_MakeFile_Builder/Executable_MakeFile_Builder_Main_File.cpp)


add_executable(Auto_MakeFile_Builder  

        ${CMAKE_CURRENT_SOURCE_DIR}/MAKE.FILE.BUILD.SYSTEM/Auto_MakeFile_Builder/Auto_MakeFile_Builder_Main_File.cpp)


add_executable(Pcynlitx_Kernel

        ${CMAKE_CURRENT_SOURCE_DIR}/KERNEL.DEVELOPMENT/Kernel_Main_File.cpp)

add_executable(CMAKE_Build

        ${CMAKE_CURRENT_SOURCE_DIR}/MAKE.FILE.BUILD.SYSTEM/CMAKE_Build_System_Generator/CMAKE_Build_System_Generator_Main_File.cpp)


add_executable(CMAKE_Build_Executable

        ${CMAKE_CURRENT_SOURCE_DIR}/MAKE.FILE.BUILD.SYSTEM/CMAKE_Executable_Target_Constructor/CMAKE_Executable_Target_Constructor_Main_File.cpp)


add_executable(Pcynlitx WIN32

        ${CMAKE_CURRENT_SOURCE_DIR}/GUI.DEVELOPMENT/wxLauncher.cpp
)


target_include_directories(Pcynlitx PUBLIC

    ${CMAKE_CURRENT_SOURCE_DIR}/GUI.DEVELOPMENT/MainFrame

    ${CMAKE_CURRENT_SOURCE_DIR}/GUI.DEVELOPMENT/Custom_Close_Button

    ${CMAKE_CURRENT_SOURCE_DIR}/GUI.DEVELOPMENT/Custom_DataPanel

    ${CMAKE_CURRENT_SOURCE_DIR}/GUI.DEVELOPMENT/Custom_wxPanel

    ${CMAKE_CURRENT_SOURCE_DIR}/GUI.DEVELOPMENT/Custom_Notebook

    ${CMAKE_CURRENT_SOURCE_DIR}/GUI.DEVELOPMENT/Custom_TabArt

    ${CMAKE_CURRENT_SOURCE_DIR}/GUI.DEVELOPMENT/Custom_TextCtrl

    ${CMAKE_CURRENT_SOURCE_DIR}/GUI.DEVELOPMENT/Custom_Tree_View_Panel

    ${CMAKE_CURRENT_SOURCE_DIR}/GUI.DEVELOPMENT/Custom_Window

    ${CMAKE_CURRENT_SOURCE_DIR}/GUI.DEVELOPMENT/Custom_ProcessOutput

    ${CMAKE_CURRENT_SOURCE_DIR}/GUI.DEVELOPMENT/Custom_wxThread

    ${CMAKE_CURRENT_SOURCE_DIR}/GUI.DEVELOPMENT/Custom_wxTreeCtrl

    ${CMAKE_CURRENT_SOURCE_DIR}/GUI.DEVELOPMENT/GUI.Headers

    ${CMAKE_CURRENT_SOURCE_DIR}/GUI.DEVELOPMENT/Intro_Page_Loader

    ${CMAKE_CURRENT_SOURCE_DIR}/GUI.DEVELOPMENT/MainFrame

    ${CMAKE_CURRENT_SOURCE_DIR}/GUI.DEVELOPMENT/Process_Manager

    ${CMAKE_CURRENT_SOURCE_DIR}/GUI.DEVELOPMENT/Project_File_Selection_Dialog

    ${CMAKE_CURRENT_SOURCE_DIR}/GUI.DEVELOPMENT/Project_Folder_Lister

    ${CMAKE_CURRENT_SOURCE_DIR}/GUI.DEVELOPMENT/Style_Loader

    ${CMAKE_CURRENT_SOURCE_DIR}/GUI.DEVELOPMENT/ToolBar_Initializer

    ${CMAKE_CURRENT_SOURCE_DIR}/GUI.DEVELOPMENT/Custom_Multi_DataPanel

    ${CMAKE_CURRENT_SOURCE_DIR}/GUI.DEVELOPMENT/Project_Descriptions_Printer

    ${CMAKE_CURRENT_SOURCE_DIR}/GUI.DEVELOPMENT/Custom_Message_Dialog

    ${CMAKE_CURRENT_SOURCE_DIR}/GUI.DEVELOPMENT/Help_Page_Constructor

    ${CMAKE_CURRENT_SOURCE_DIR}/GUI.DEVELOPMENT/Dependency_Tree_Printer

    ${CMAKE_CURRENT_SOURCE_DIR}/GUI.DEVELOPMENT/Custom_Progress_Dialog

    ${CMAKE_CURRENT_SOURCE_DIR}/GUI.DEVELOPMENT/Custom_wxDataViewTreeCtrl

    ${CMAKE_CURRENT_SOURCE_DIR}/GUI.DEVELOPMENT/GUI_List_Data_Recorder

    ${CMAKE_CURRENT_SOURCE_DIR}/GUI.DEVELOPMENT/Project_File_Selection_Window



    ${CMAKE_SOURCE_DIR}/DESCRIPTION.PROCESSING.SYSTEM/Description.Readers/Descriptor.File.Data.Collector

    ${CMAKE_SOURCE_DIR}/DESCRIPTION.PROCESSING.SYSTEM/Description.Readers/Descriptor.File.Reader

    ${CMAKE_SOURCE_DIR}/DESCRIPTION.PROCESSING.SYSTEM/Description.Readers/GUI.Descriptor.File.Reader

    ${CMAKE_SOURCE_DIR}/DESCRIPTION.PROCESSING.SYSTEM/Description.Readers/Descriptor.File.Syntax.Controller
    
    ${CMAKE_SOURCE_DIR}/DESCRIPTION.PROCESSING.SYSTEM/Description.Readers/Record.Number.Determiner

    ${CMAKE_SOURCE_DIR}/DESCRIPTION.PROCESSING.SYSTEM/Description.Readers/Descriptor.File.Line.Reader


    ${CMAKE_SOURCE_DIR}/BASIC.TOOLS/Cpp_FileOperations

    ${CMAKE_SOURCE_DIR}/BASIC.TOOLS/Custom_System_Interface

    ${CMAKE_SOURCE_DIR}/BASIC.TOOLS/DirectoryOperations

    ${CMAKE_SOURCE_DIR}/BASIC.TOOLS/IntToCharTranslater

    ${CMAKE_SOURCE_DIR}/BASIC.TOOLS/StringOperator

    ${CMAKE_SOURCE_DIR}/BASIC.TOOLS/Custom_System_Interface


    ${wxWidgets_BINARY_DIR}/lib/gcc_x64_lib/mswud

    ${wxWidgets_SOURCE_DIR}/include
)


target_link_directories(Pcynlitx PUBLIC

    ${CMAKE_CURRENT_SOURCE_DIR}/GUI.DEVELOPMENT

    ${wxWidgets_BINARY_DIR}/lib/gcc_x64_lib

    ${wxWidgets_SOURCE_DIR}/include
)


target_link_options(Pcynlitx PUBLIC  -Wl,--subsystem,windows -mwindows)


target_link_libraries(Pcynlitx PUBLIC BuildSystem_GUI des_reader pthread 

                     wxbase33ud

                     wxaui

                     wxmsw33ud_core

                     wxmsw33ud_adv 
                      
                     wxmsw33ud_aui

                     wxmsw33ud_stc 
                     
                     wxscintillad 
                                          
                     wxmsw33ud_richtext

                     wxxrc

                     wxstc

                     wxgl

                     wxnet

                     gcc stdc++
 )

target_compile_options(Pcynlitx PUBLIC -std=c++17 -Wall -Bstatic

       -g -O0 -mthreads -D__WXMSW__ -D_UNICODE -DWIN32 )


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