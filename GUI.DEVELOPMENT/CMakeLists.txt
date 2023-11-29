

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

)


target_include_directories(BuildSystem_GUI PUBLIC

    ${CMAKE_CURRENT_SOURCE_DIR}/Custom_Close_Button

    ${CMAKE_CURRENT_SOURCE_DIR}/Custom_DataPanel

    ${CMAKE_CURRENT_SOURCE_DIR}/Custom_Notebook

    ${CMAKE_CURRENT_SOURCE_DIR}/Custom_TabArt

    ${CMAKE_CURRENT_SOURCE_DIR}/Custom_TextCtrl

    ${CMAKE_CURRENT_SOURCE_DIR}/Custom_Tree_View_Panel

    ${CMAKE_CURRENT_SOURCE_DIR}/Custom_Window

    ${CMAKE_CURRENT_SOURCE_DIR}/Custom_wxPanel

    ${CMAKE_CURRENT_SOURCE_DIR}/Custom_wxThread

    ${CMAKE_CURRENT_SOURCE_DIR}/Custom_wxTreeCtrl

    ${CMAKE_CURRENT_SOURCE_DIR}/GUI.Headers

    ${CMAKE_CURRENT_SOURCE_DIR}/Intro_Page_Loader

    ${CMAKE_CURRENT_SOURCE_DIR}/MainFrame

    ${CMAKE_CURRENT_SOURCE_DIR}/Menu_Bar_Options

    ${CMAKE_CURRENT_SOURCE_DIR}/Process_Manager

    ${CMAKE_CURRENT_SOURCE_DIR}/Project_File_Selection_Dialog

    ${CMAKE_CURRENT_SOURCE_DIR}/Project_Folder_Lister

    D:/wxWidgets-3.2.2.1/include

    D:/wxWidgets-3.2.2.1/lib/gcc1220_x64_dll/mswud/wx

    D:/wxWidgets-3.2.2.1/lib/gcc1220_x64_dll/mswud
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

    ${CMAKE_CURRENT_SOURCE_DIR}/Custom_wxThread

    ${CMAKE_CURRENT_SOURCE_DIR}/Custom_wxTreeCtrl

    ${CMAKE_CURRENT_SOURCE_DIR}/GUI.Headers

    ${CMAKE_CURRENT_SOURCE_DIR}/Intro_Page_Loader

    ${CMAKE_CURRENT_SOURCE_DIR}/MainFrame

    ${CMAKE_CURRENT_SOURCE_DIR}/Menu_Bar_Options

    ${CMAKE_CURRENT_SOURCE_DIR}/Process_Manager

    ${CMAKE_CURRENT_SOURCE_DIR}/Project_File_Selection_Dialog

    ${CMAKE_CURRENT_SOURCE_DIR}/Project_Folder_Lister
)