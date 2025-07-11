


set( CMAKE_CXX_COMPILER "C:/Development.Tools/Mingw64/bin/g++.exe" )
set( CMAKE_C_COMPILER "C:/Development.Tools/Mingw64/bin/gcc.exe" )

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set( CMAKE_BUILD_TYPE "Debug")



cmake_minimum_required(VERSION 3.30.2)

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

target_link_libraries(Pcynlitx PUBLIC BuildSystem_GUI pthread wxmsw32ud_core wxbase32ud  
                      
                      wxmsw32ud_aui wxmsw32ud_stc wxscintillad wxmsw32ud_richtext
                          
                      gcc stdc++)