
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