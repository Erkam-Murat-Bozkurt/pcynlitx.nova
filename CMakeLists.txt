



cmake_minimum_required(VERSION 4.1.2)

set(CMAKE_BUILD_PARALLEL_LEVEL 8)
set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")

set(wxWidgets_USE_STATIC 1)
set(wxBUILD_SHARED OFF)
set(wxWidgets_USE_STATIC ON)

set(CMAKE_CXX_STANDARD 14)
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



include(FetchContent)

FetchContent_Declare(
   wxWidgets
   GIT_REPOSITORY https://github.com/wxWidgets/wxWidgets.git
   GIT_TAG v3.3.1
)

FetchContent_GetProperties(wxwidgets)
FetchContent_MakeAvailable(wxwidgets)



project(Pcynlitx VERSION 1.0)

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


include_directories(

    C:/Development.Tools/wxWidgets-3.2.5/include

    C:/Development.Tools/wxWidgets-3.2.5/lib/gcc810_x64_dll/mswu
)

link_directories(

    C:/Development.Tools/wxWidgets-3.2.5/lib/gcc810_x64_dll

    C:/Development.Tools/Mingw64/lib/gcc/x86_64-w64-mingw32/8.1.0
)




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


add_executable(Pcynlitx

        ${CMAKE_CURRENT_SOURCE_DIR}/GUI.DEVELOPMENT/wxLauncher.cpp )



target_link_libraries(Project_Script_Writer PUBLIC 

        src_dat_col src_proc_sys proj_bld_tools git_data_processing_system des_reader basic_tools )

     

target_link_libraries(Build_Tools_Initializer PUBLIC 

        src_dat_col src_proc_sys proj_bld_tools git_data_processing_system des_reader basic_tools )


     
target_link_libraries(Executable_MakeFile_Builder PUBLIC exec_make_bld )



target_link_libraries(Auto_MakeFile_Builder PUBLIC make_fbld_sys proj_bld_tools 

                   git_data_processing_system des_reader basic_tools)


                   
target_link_libraries(Pcynlitx_Kernel PUBLIC kernel proj_bld_tools exec_make_bld script_writers make_fbld_sys 

                   src_proc_sys git_data_processing_system src_dat_col des_reader basic_tools)


target_link_libraries(CMAKE_Build PUBLIC proj_bld_tools  make_fbld_sys 

                   src_proc_sys git_data_processing_system src_dat_col des_reader basic_tools)


target_link_libraries(CMAKE_Build_Executable PUBLIC proj_bld_tools  make_fbld_sys 

                   src_proc_sys git_data_processing_system src_dat_col des_reader basic_tools)

target_link_libraries(Pcynlitx PUBLIC BuildSystem_GUI pthread 

                      wxcore wxnet wxbase wxstc wxscintilla wxaui wxrichtext
                          
                      gcc stdc++)