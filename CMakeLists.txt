


set( CMAKE_CXX_COMPILER "D:/mingw64/bin/g++.exe" )
set( CMAKE_C_COMPILER "D:/mingw64/bin/gcc.exe" )

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

cmake_minimum_required(VERSION 3.10)

project(pcynlitx.build VERSION 1.0)

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

        D:/wxWidgets-3.2.2.1/include

        D:/wxWidgets-3.2.2.1/lib/gcc1220_x64_dll/mswud/wx

        D:/wxWidgets-3.2.2.1/lib/gcc1220_x64_dll/mswud
)

link_directories(

        D:/wxWidgets-3.2.2.1/lib/gcc1220_x64_dll
)

link_libraries( pthread wxmsw32ud_core wxbase32ud wxtiffd 
                      
                wxjpegd wxpngd wxzlibd wxregexud wxexpatd wxbase32ud_xml wxmsw32ud_aui
                
                wxmsw32ud_stc wxscintillad wxbase32ud_net wxmsw32ud_xrc wxmsw32ud_richtext
        
                wxmsw32ud_webview wxmsw32ud_ribbon wxmsw32ud_propgrid wxmsw32ud_html wxmsw32ud_adv 
        
                wxmsw32ud_gl wxmsw32ud_media kernel32 user32 gdi32 comdlg32 winspool winmm

                shell32 comctl32 ole32 oleaut32 uuid rpcrt4 advapi32 wsock32 wininet uxtheme 

                oleacc gcc stdc++ 
)


add_executable(Project_Script_Writer 

        ${CMAKE_CURRENT_SOURCE_DIR}/SCRIPT.WRITERS/Project_Script_Writer/Project_Script_Writer_Main_File.cpp)



add_executable(Build_Tools_Initializer 

        ${CMAKE_CURRENT_SOURCE_DIR}/PROJECT.BUILD.TOOLS/Build_Tools_Initializer/Build_Tools_Initializer_Main_File.cpp)


add_executable(Executable_MakeFile_Builder 

        ${CMAKE_CURRENT_SOURCE_DIR}/EXECUTABLE.MAKE.FILE.BUILD.SYSTEM/Executable_MakeFile_Builder/Executable_MakeFile_Builder_Main_File.cpp)



add_executable(Auto_MakeFile_Builder  

        ${CMAKE_CURRENT_SOURCE_DIR}/MAKE.FILE.BUILD.SYSTEM/Auto_MakeFile_Builder/Auto_MakeFile_Builder_Main_File.cpp)


add_executable(BuildSystem

        ${CMAKE_CURRENT_SOURCE_DIR}/KERNEL.DEVELOPMENT/Kernel_Main_File.cpp)


add_executable(build_gui

        ${CMAKE_CURRENT_SOURCE_DIR}/GUI.DEVELOPMENT/wxLauncher.cpp)



target_link_libraries(Project_Script_Writer PUBLIC 

        src_dat_col src_proc_sys proj_bld_tools git_data_processing_system des_reader basic_tools )

     

target_link_libraries(Build_Tools_Initializer PUBLIC 

        src_dat_col src_proc_sys proj_bld_tools git_data_processing_system des_reader basic_tools )


     
target_link_libraries(Executable_MakeFile_Builder PUBLIC exec_make_bld )



target_link_libraries(Auto_MakeFile_Builder PUBLIC make_fbld_sys proj_bld_tools 

                   git_data_processing_system des_reader basic_tools)


                   
target_link_libraries(BuildSystem PUBLIC kernel proj_bld_tools exec_make_bld script_writers make_fbld_sys 

                   src_proc_sys git_data_processing_system src_dat_col des_reader basic_tools)


target_link_libraries(build_gui PUBLIC BuildSystem_GUI pthread wxmsw32ud_core wxbase32ud wxtiffd 
                      
                     wxjpegd wxpngd wxzlibd wxregexud wxexpatd wxbase32ud_xml wxmsw32ud_aui
                
                     wxmsw32ud_stc wxscintillad wxbase32ud_net wxmsw32ud_xrc wxmsw32ud_richtext
        
                     wxmsw32ud_webview wxmsw32ud_ribbon wxmsw32ud_propgrid wxmsw32ud_html wxmsw32ud_adv 
        
                     wxmsw32ud_gl wxmsw32ud_media kernel32 user32 gdi32 comdlg32 winspool winmm

                     shell32 comctl32 ole32 oleaut32 uuid rpcrt4 advapi32 wsock32 wininet uxtheme 

                     oleacc gcc stdc++ )