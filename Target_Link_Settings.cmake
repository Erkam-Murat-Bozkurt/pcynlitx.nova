

add_dependencies(BuildSystem_GUI wxbase wxcore wxaui)

add_dependencies(Pcynlitx BuildSystem_GUI)

target_link_libraries(Pcynlitx PUBLIC BuildSystem_GUI des_reader pthread 

	wxzlib
	wxregex
	wxbase
	webpencode
	webpdecode
	sharpyuv
	webpdsp
	webputils
	webp
	webpdemux
	wxpng
	wxjpeg
	wxtiff
	wxcore
	wxaui
	wxnet
	wxstc
	wxrichtext
	wxwebview
	wxgl 
	wxmedia
	wxribbon
	
	imm32
	gcc 
	stdc++

	kernel32 
	user32 
	gdi32 
	gdiplus 
	msimg32 
	comdlg32
	winspool 
	winmm 
	shell32 
	shlwapi
	comctl32 
	ole32 
	oleaut32 
	uuid 
	rpcrt4 
	advapi32 
	version 
	ws2_32 
	wininet 
	oleacc 
	uxtheme

)


target_link_libraries(Project_Script_Writer PUBLIC 

        src_dat_col src_proc_sys proj_bld_tools git_data_processing_system des_reader basic_tools )

target_link_libraries(Build_Tools_Initializer PUBLIC 

        src_dat_col src_proc_sys proj_bld_tools git_data_processing_system des_reader basic_tools )


target_link_libraries(Executable_MakeFile_Builder PUBLIC exec_make_bld )


target_link_libraries(Auto_MakeFile_Builder PUBLIC make_fbld_sys proj_bld_tools 

                      git_data_processing_system des_reader basic_tools)


# -mwindows linking option for Mingw64 makes application as a GUI process and suspends the terminal output.
#  If you want to see the terminal output, "-mwindows" linking option must not be set on the executable link options.

target_link_libraries(Pcynlitx_Kernel PUBLIC kernel proj_bld_tools exec_make_bld script_writers cmake_lists_file_bld_sys 

                   make_fbld_sys src_proc_sys git_data_processing_system src_dat_col des_reader basic_tools)


target_link_libraries(CMAKE_Build PUBLIC proj_bld_tools cmake_lists_file_bld_sys 

                   src_proc_sys git_data_processing_system src_dat_col des_reader basic_tools)


target_link_libraries(CMAKE_Build_Executable PUBLIC proj_bld_tools cmake_lists_file_bld_sys 

                      src_proc_sys git_data_processing_system src_dat_col des_reader basic_tools)

