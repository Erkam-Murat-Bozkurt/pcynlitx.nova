

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