





#ifndef CUSTOM_MULTI_DATAPANEL_HPP
#define CUSTOM_MULTI_DATAPANEL_HPP

#include <wx\wx.h>
#include <wx\sizer.h>
#include <wx\event.h>
#include <wx\aui\aui.h>
#include <wx\aui\framemanager.h>
#include <wx\sizer.h>
#include <wx\dataview.h>
#include <wx\textdlg.h>
#include <wx\msgdlg.h>
#include "Process_Manager.hpp"
#include "Custom_DataPanel.hpp"




enum
{
  ID_INSERT_ITEM_FOR_PATH  = 100,
  ID_INSERT_ITEM_FOR_NAME  = 101,  
  ID_SAVE_MAKE_FILE_DATA   = 102,
  ID_INSERT_GIT_REPO_DIR   = 103,
  ID_INSERT_CONSTRUCTION_POINT = 104,
  ID_INSERT_SRC_LOCATION  = 105,
  ID_INSERT_LIB_DIRECTORIES = 106,
  ID_INSERT_LIBRARIES = 107,
  ID_INSERT_STANDART = 108,
  ID_INSERT_OPTIONS  = 109
};


class Custom_Multi_DataPanel : public wxFrame 
{
public:
    Custom_Multi_DataPanel(wxFrame * parent, wxWindowID id=wxID_ANY, 
    
        const wxString & title=wxT(""), 

        const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxSize(1100,800), 
   
        long style=wxDEFAULT_FRAME_STYLE | wxSTAY_ON_TOP);

    virtual ~Custom_Multi_DataPanel();

    void Create_Exe_Script_Panel();

    bool Get_Data_Save_Status();

    wxString ExeFileName;

    wxString FilePath;

    void Construct_MultiData_Panel(int num);

    void Construct_Description_Panel();

protected:

    void DrawBackground(wxDC & dc, wxWindow *  wnd, const wxRect& rect);

    void OnPaint(wxPaintEvent & event);

    void AppendDataItem(wxDataViewListCtrl * listctrl, wxString str);

    void Construct_NewData_Panels();

    void Insert_Data_For_Path(wxCommandEvent & event);

    void Save_MakeFile_Data(wxCommandEvent & event);

    void Insert_Data_For_Name(wxCommandEvent & event);

    void Inser_Git_Repo_Dir(wxCommandEvent & event);

    void Insert_Construction_Point(wxCommandEvent & event);

    void Insert_Source_File_Location(wxCommandEvent & event);

    void Insert_Library_Location(wxCommandEvent & event);

    void Insert_Library(wxCommandEvent & event);

    void Insert_Standart(wxCommandEvent & event);

    void Insert_Option(wxCommandEvent & event);

    bool Data_Save_Status;

    wxFrame * Parent_Frame;

    wxBoxSizer * Frame_Sizer;

    int Panel_Number;

    wxDataViewListCtrl ** listctrls;

    wxButton ** Insert_Buttons;


    wxBoxSizer ** DataPanel_Sizers;

    wxBoxSizer ** Buton_Sizers;

    wxBoxSizer ** List_Ctrl_Sizers;



    wxBoxSizer * DataPanel_Top_Sizer;

    wxDataViewListCtrl * listctrl_for_path;

    wxDataViewListCtrl * listctrl_for_name;


    wxDataViewListCtrl * listctrl_git_repo_path;

    wxDataViewListCtrl * listctrl_warehouse_location;

    wxDataViewListCtrl * listctrl_src_file_location;

    wxDataViewListCtrl * listctrl_library_dir;

    wxDataViewListCtrl * listctrl_library_name;

    wxDataViewListCtrl * listctrl_standard;

    wxDataViewListCtrl * listctrl_options;


    wxButton * InsertButton_for_git_repo_path;

    wxButton * InsertButton_for_warehouse_location;

    wxButton * InsertButton_for_src_file_locations;

    wxButton * InsertButton_for_library_dir;

    wxButton * InsertButton_for_library_name;

    wxButton * InsertButton_for_standard;

    wxButton * InsertButton_for_options;



    wxButton * Save_Button_for_git_repo_path;

    wxButton * Save_Button_for_warehouse_location;

    wxButton * Save_Button_for_src_file_locations;

    wxButton * Save_Button_for_library_dir;

    wxButton * Save_Button_for_library_name;

    wxButton * Save_Button_for_standard;

    wxButton * Save_Button_for_options;


    wxButton * InsertButton_for_path;

    wxButton * InsertButton_for_name;

    wxButton * Start_Button;

    wxBoxSizer * vbox_path;
    wxBoxSizer * hbox_path;

    wxBoxSizer * vbox_name;
    wxBoxSizer * hbox_name;

    DECLARE_EVENT_TABLE()
};


#endif /* CUSTOM_MULTI_DATAPANEL_HPP */
