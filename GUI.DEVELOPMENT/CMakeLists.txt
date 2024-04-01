

add_library(BuildSystem_GUI

    ${CMAKE_CURRENT_SOURCE_DIR}/Custom_Close_Button/Custom_Close_Button.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Custom_Close_Button/Custom_Close_Button.h

    ${CMAKE_CURRENT_SOURCE_DIR}/Custom_DataPanel/Custom_DataPanel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Custom_DataPanel/Custom_DataPanel.hpp

    ${CMAKE_CURRENT_SOURCE_DIR}/Custom_Notebook/Custom_Notebook.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Custom_Notebook/Custom_Notebook.h

    ${CMAKE_CURRENT_SOURCE_DIR}/Custom_TabArt/Custom_TabArt.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Custom_TabArt/Custom_TabArt.h

    ${CMAKE_CURRENT_SOURCE_DIR}/Custom_TextCtrl/Custom_TextCtrl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Custom_TextCtrl/Custom_TextCtrl.h

    ${CMAKE_CURRENT_SOURCE_DIR}/Custom_Tree_View_Panel/Custom_Tree_View_Panel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Custom_Tree_View_Panel/Custom_Tree_View_Panel.h

    ${CMAKE_CURRENT_SOURCE_DIR}/Custom_Window/Custom_Window.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Custom_Window/Custom_Window.h


    ${CMAKE_CURRENT_SOURCE_DIR}/Gui_Shell_Script_Executer/Gui_Shell_Script_Executer.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Gui_Shell_Script_Executer/Gui_Shell_Script_Executer.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/Custom_ProcessOutput/Custom_ProcessOutput.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Custom_ProcessOutput/Custom_ProcessOutput.hpp

    ${CMAKE_CURRENT_SOURCE_DIR}/Custom_wxPanel/Custom_wxPanel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Custom_wxPanel/Custom_wxPanel.h

    ${CMAKE_CURRENT_SOURCE_DIR}/Custom_wxThread/Custom_wxThread.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Custom_wxThread/Custom_wxThread.hpp

    ${CMAKE_CURRENT_SOURCE_DIR}/Custom_wxTreeCtrl/Custom_wxTreeCtrl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Custom_wxTreeCtrl/Custom_wxTreeCtrl.h

    ${CMAKE_CURRENT_SOURCE_DIR}/GUI.Headers/Custom_DockArt.h
    ${CMAKE_CURRENT_SOURCE_DIR}/GUI.Headers/Event_ID_Numbers.h

    ${CMAKE_CURRENT_SOURCE_DIR}/GUI.Headers/Event_Table_Header.h
    ${CMAKE_CURRENT_SOURCE_DIR}/GUI.Headers/wxDirTraverser_executer.h

    ${CMAKE_CURRENT_SOURCE_DIR}/Intro_Page_Loader/Intro_Page_Loader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Intro_Page_Loader/Intro_Page_Loader.h

    ${CMAKE_CURRENT_SOURCE_DIR}/MainFrame/MainFrame.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/MainFrame/MainFrame.h

    ${CMAKE_CURRENT_SOURCE_DIR}/Menu_Bar_Options/Menu_Bar_Options.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Menu_Bar_Options/Menu_Bar_Options.h

    ${CMAKE_CURRENT_SOURCE_DIR}/Process_Manager/Process_Manager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Process_Manager/Process_Manager.hpp

    ${CMAKE_CURRENT_SOURCE_DIR}/Project_File_Selection_Dialog/Project_File_Selection_Dialog.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Project_File_Selection_Dialog/Project_File_Selection_Dialog.h

    ${CMAKE_CURRENT_SOURCE_DIR}/Project_Folder_Lister/Project_Folder_Lister.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Project_Folder_Lister/Project_Folder_Lister.h

    ${CMAKE_CURRENT_SOURCE_DIR}/Style_Loader/Style_loader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Style_Loader/Style_loader.h

    ${CMAKE_CURRENT_SOURCE_DIR}/ToolBar_Initializer/ToolBar_Initializer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ToolBar_Initializer/ToolBar_Initializer.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/Project_Descriptions_Printer/Project_Descriptions_Printer.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Project_Descriptions_Printer/Project_Descriptions_Printer.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/Custom_Multi_DataPanel/Custom_Multi_DataPanel.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Custom_Multi_DataPanel/Custom_Multi_DataPanel.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/Custom_Message_Dialog/Custom_Message_Dialog.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Custom_Message_Dialog/Custom_Message_Dialog.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/Help_Page_Constructor/Help_Page_Constructor.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Help_Page_Constructor/Help_Page_Constructor.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/Dependency_Tree_Printer/Dependency_Tree_Printer.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Dependency_Tree_Printer/Dependency_Tree_Printer.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/Custom_Progress_Dialog/Custom_Progress_Dialog.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Custom_Progress_Dialog/Custom_Progress_Dialog.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/Custom_wxDataViewTreeCtrl/Custom_wxDataViewTreeCtrl.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Custom_wxDataViewTreeCtrl/Custom_wxDataViewTreeCtrl.cpp

)


target_include_directories(BuildSystem_GUI PUBLIC

    ${CMAKE_CURRENT_SOURCE_DIR}/Custom_Close_Button

    ${CMAKE_CURRENT_SOURCE_DIR}/Custom_DataPanel

    ${CMAKE_CURRENT_SOURCE_DIR}/Custom_wxPanel

    ${CMAKE_CURRENT_SOURCE_DIR}/Custom_Notebook

    ${CMAKE_CURRENT_SOURCE_DIR}/Custom_TabArt

    ${CMAKE_CURRENT_SOURCE_DIR}/Custom_TextCtrl

    ${CMAKE_CURRENT_SOURCE_DIR}/Custom_Tree_View_Panel

    ${CMAKE_CURRENT_SOURCE_DIR}/Custom_Window

    ${CMAKE_CURRENT_SOURCE_DIR}/Custom_ProcessOutput

    ${CMAKE_CURRENT_SOURCE_DIR}/Custom_wxThread

    ${CMAKE_CURRENT_SOURCE_DIR}/Custom_wxTreeCtrl

    ${CMAKE_CURRENT_SOURCE_DIR}/GUI.Headers

    ${CMAKE_CURRENT_SOURCE_DIR}/Intro_Page_Loader

    ${CMAKE_CURRENT_SOURCE_DIR}/MainFrame

    ${CMAKE_CURRENT_SOURCE_DIR}/Menu_Bar_Options

    ${CMAKE_CURRENT_SOURCE_DIR}/Process_Manager

    ${CMAKE_CURRENT_SOURCE_DIR}/Project_File_Selection_Dialog

    ${CMAKE_CURRENT_SOURCE_DIR}/Project_Folder_Lister

    ${CMAKE_CURRENT_SOURCE_DIR}/Style_Loader

    ${CMAKE_CURRENT_SOURCE_DIR}/ToolBar_Initializer

    ${CMAKE_CURRENT_SOURCE_DIR}/Custom_Multi_DataPanel

    ${CMAKE_CURRENT_SOURCE_DIR}/Project_Descriptions_Printer

    ${CMAKE_CURRENT_SOURCE_DIR}/Custom_Message_Dialog

    ${CMAKE_CURRENT_SOURCE_DIR}/Help_Page_Constructor

    ${CMAKE_CURRENT_SOURCE_DIR}/Dependency_Tree_Printer

    ${CMAKE_CURRENT_SOURCE_DIR}/Custom_Progress_Dialog

    ${CMAKE_CURRENT_SOURCE_DIR}/Gui_Shell_Script_Executer

    ${CMAKE_CURRENT_SOURCE_DIR}/Custom_wxDataViewTreeCtrl




    ${CMAKE_SOURCE_DIR}/Descriptor.File.Data.Collector

    ${CMAKE_SOURCE_DIR}/Descriptor.File.Reader

    ${CMAKE_SOURCE_DIR}/Descriptor.File.Syntax.Controller

    
    ${CMAKE_SOURCE_DIR}/BASIC.TOOLS/Cpp_FileOperations

    ${CMAKE_SOURCE_DIR}/BASIC.TOOLS/Custom_System_Interface

    ${CMAKE_SOURCE_DIR}/BASIC.TOOLS/DirectoryOperations

    ${CMAKE_SOURCE_DIR}/BASIC.TOOLS/IntToCharTranslater

    ${CMAKE_SOURCE_DIR}/BASIC.TOOLS/StringOperator

    ${CMAKE_SOURCE_DIR}/BASIC.TOOLS/Custom_System_Interface

    

    D:/wxWidgets-3.2.4/include

    D:/wxWidgets-3.2.4/lib/gcc810_x64_dll/mswu
)


target_link_directories(BuildSystem_GUI PUBLIC

    ${CMAKE_CURRENT_SOURCE_DIR}/Custom_Close_Button

    ${CMAKE_CURRENT_SOURCE_DIR}/Custom_DataPanel

    ${CMAKE_CURRENT_SOURCE_DIR}/Custom_Notebook

    ${CMAKE_CURRENT_SOURCE_DIR}/Custom_TabArt

    ${CMAKE_CURRENT_SOURCE_DIR}/Custom_TextCtrl

    ${CMAKE_CURRENT_SOURCE_DIR}/Custom_Tree_View_Panel

    ${CMAKE_CURRENT_SOURCE_DIR}/Custom_Window

    ${CMAKE_CURRENT_SOURCE_DIR}/Custom_wxPanel

    ${CMAKE_CURRENT_SOURCE_DIR}/Custom_ProcessOutput

    ${CMAKE_CURRENT_SOURCE_DIR}/Custom_wxThread

    ${CMAKE_CURRENT_SOURCE_DIR}/Custom_wxTreeCtrl

    ${CMAKE_CURRENT_SOURCE_DIR}/GUI.Headers

    ${CMAKE_CURRENT_SOURCE_DIR}/Intro_Page_Loader

    ${CMAKE_CURRENT_SOURCE_DIR}/MainFrame

    ${CMAKE_CURRENT_SOURCE_DIR}/Menu_Bar_Options

    ${CMAKE_CURRENT_SOURCE_DIR}/Process_Manager

    ${CMAKE_CURRENT_SOURCE_DIR}/Project_File_Selection_Dialog

    ${CMAKE_CURRENT_SOURCE_DIR}/Project_Folder_Lister

    ${CMAKE_CURRENT_SOURCE_DIR}/Style_Loader

    ${CMAKE_CURRENT_SOURCE_DIR}/ToolBar_Initializer

    ${CMAKE_CURRENT_SOURCE_DIR}/Custom_Multi_DataPanel

    ${CMAKE_CURRENT_SOURCE_DIR}/Project_Descriptions_Printer

    ${CMAKE_CURRENT_SOURCE_DIR}/Custom_Message_Dialog

    ${CMAKE_CURRENT_SOURCE_DIR}/Help_Page_Constructor

    ${CMAKE_CURRENT_SOURCE_DIR}/Dependency_Tree_Printer

    ${CMAKE_CURRENT_SOURCE_DIR}/Custom_Progress_Dialog

    ${CMAKE_CURRENT_SOURCE_DIR}/Gui_Shell_Script_Executer

    ${CMAKE_CURRENT_SOURCE_DIR}/Custom_wxDataViewTreeCtrl


    ${CMAKE_SOURCE_DIR}/Descriptor.File.Data.Collector

    ${CMAKE_SOURCE_DIR}/Descriptor.File.Reader

    ${CMAKE_SOURCE_DIR}/Descriptor.File.Syntax.Controller

    
    ${CMAKE_SOURCE_DIR}/BASIC.TOOLS/Cpp_FileOperations

    ${CMAKE_SOURCE_DIR}/BASIC.TOOLS/Custom_System_Interface

    ${CMAKE_SOURCE_DIR}/BASIC.TOOLS/DirectoryOperations

    ${CMAKE_SOURCE_DIR}/BASIC.TOOLS/IntToCharTranslater

    ${CMAKE_SOURCE_DIR}/BASIC.TOOLS/StringOperator

    ${CMAKE_SOURCE_DIR}/BASIC.TOOLS/Custom_System_Interface



    D:/wxWidgets-3.2.4/lib/gcc810_x64_dll

    D:/mingw64/lib/gcc/x86_64-w64-mingw32/8.1.0

)


target_link_libraries(BuildSystem_GUI PUBLIC des_reader pthread wxmsw32u_core wxbase32u wxtiffd 
                      
                     wxjpeg wxpng wxzlib wxregexu wxexpat wxbase32u_xml wxmsw32u_aui
                
                     wxmsw32u_stc wxscintillad wxbase32u_net wxmsw32u_xrc wxmsw32u_richtext
        
                     wxmsw32u_webview wxmsw32u_ribbon wxmsw32u_propgrid wxmsw32u_html wxmsw32u_adv 
        
                     wxmsw32u_gl wxmsw32u_media kernel32 user32 gdi32 comdlg32 winspool winmm

                     shell32 comctl32 ole32 oleaut32 uuid rpcrt4 advapi32 wsock32 wininet uxtheme 

                     oleacc gcc stdc++ User32)


link_libraries( pthread libwxmsw32ud_core.a libwxbase32u.a libwxtiff.a 
                      
                libwxjpeg.a libwxpng.a libwxzlib.a libwxregexu.a libwxexpat.a libwxbase32u_xml.a libwxmsw32u_aui.a
                
                libwxmsw32u_stc.a libwxscintilla.a libwxbase32u_net.a libwxmsw32u_xrc.a libwxmsw32u_richtext.a
        
                libwxmsw32u_webview.a libwxmsw32u_ribbon.a libwxmsw32u_propgrid.a libwxmsw32u_html.a libwxmsw32u_adv.a 
        
                libwxmsw32u_gl.a libwxmsw32u_media.a libwxmsw32u_core.a kernel32 user32 gdi32 comdlg32 winspool winmm

                shell32 comctl32 ole32 oleaut32 uuid rpcrt4 advapi32 wsock32 wininet uxtheme oleacc User32
)

target_compile_options(BuildSystem_GUI PUBLIC -static-libgcc -static-libstdc++ 

        -O0 -mthreads -D__WXMSW__ -D_UNICODE -W -Wall -Wl,
        
        -Bstatic )

   

target_link_options(BuildSystem_GUI PUBLIC -Wl,--subsystem,windows -mwindows )

