





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
#include <wx\dir.h>
#include "GUI_List_Data_Recorder.hpp"
#include "Process_Manager.hpp"
#include "Custom_DataPanel.hpp"
#include "Custom_Message_Dialog.hpp"



enum
{
  ID_INSERT_ITEM_FOR_PATH  = 100,
  ID_INSERT_ITEM_FOR_NAME  = 101,  
  ID_SAVE_MAKE_FILE_DATA   = 102,

  ID_INSERT_GIT_REPO_DIR   = 103,
  ID_INSERT_CONSTRUCTION_POINT = 104,
  ID_INSERT_HEADER_FILE_LOCATION = 105,
  ID_INSERT_SRC_LOCATION  = 106,
  ID_INSERT_LIB_DIRECTORIES = 107,
  ID_INSERT_LIBRARIES = 108,
  ID_INSERT_STANDART = 109,
  ID_INSERT_OPTIONS  = 110,


  ID_SAVE_GIT_REPO_DIR   = 111,
  ID_SAVE_CONSTRUCTION_POINT = 112,
  ID_SAVE_HEADER_FILE_LOCATION = 113,
  ID_SAVE_SRC_LOCATION  = 114,
  ID_SAVE_LIB_DIRECTORY = 115,
  ID_SAVE_LIBRARY_NAME = 116,
  ID_SAVE_STANDART = 117,
  ID_SAVE_OPTIONS  = 118,

  ID_REMOVE_HEADER_FILE_LOCATION = 119,
  ID_REMOVE_SRC_LOCATION  = 120,
  ID_REMOVE_LIB_DIRECTORY = 121,
  ID_REMOVE_LIBRARY_NAME = 122,

  ID_CLEAR_HEADER_FILE_LOCATION = 123,
  ID_CLEAR_SRC_LOCATIONS  = 124,
  ID_CLEAR_LIB_DIRECTORIES = 125,
  ID_CLEAR_LIBRARY_NAMES = 126,
  
  ID_CLOSE_DESCRIPTION_PANEL = 127,
  ID_SAVE_PANEL_DESCRIPTIONS = 128,
  ID_CLEAR_PANEL_DESCRIPTIONS = 129
};


class Custom_Multi_DataPanel : public wxFrame 
{
public:
    Custom_Multi_DataPanel(wxFrame * parent, wxWindowID id=wxID_ANY, 
    
        const wxString & title=wxT(""), 

        const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxSize(1000,820), 
   
        long style=wxDEFAULT_FRAME_STYLE | wxSTAY_ON_TOP, char opr_sis='w');

    virtual ~Custom_Multi_DataPanel();

    void Receive_Descriptor_File_Path(wxString path);

    void Create_Exe_Script_Panel();

    bool Get_Data_Save_Status();

    void Load_Data_From_Descriptor_File_To_Panel();

    wxString ExeFileName;

    wxString FilePath;

    void Construct_MultiData_Panel(int num);

    void Construct_Description_Panel();

protected:

    void DrawBackground(wxDC & dc, wxWindow *  wnd, const wxRect& rect);

    void OnPaint(wxPaintEvent & event);

    void AppendDataItem(wxDataViewListCtrl * listctrl, wxString str);

    void Save_Data(wxDataViewListCtrl * listctrl, wxString DataType);

    void Construct_NewData_Panels();

    void Insert_Data_For_Path(wxCommandEvent & event);

    void Save_MakeFile_Data(wxCommandEvent & event);

    void Insert_Data_For_Name(wxCommandEvent & event);



    void Inser_Git_Repo_Dir(wxCommandEvent & event);

    void Insert_Construction_Point(wxCommandEvent & event);

    void Insert_Header_File_Location(wxCommandEvent & event);

    void Insert_Source_File_Location(wxCommandEvent & event);

    void Insert_Library_Location(wxCommandEvent & event);

    void Insert_Library(wxCommandEvent & event);

    void Insert_Standart(wxCommandEvent & event);

    void Insert_Option(wxCommandEvent & event);



    void Save_Git_Repo_Dir(wxCommandEvent & event);

    void Save_Construction_Point(wxCommandEvent & event);

    void Save_Header_File_Location(wxCommandEvent & event);

    void Save_Source_File_Location(wxCommandEvent & event);

    void Save_Library_Directory(wxCommandEvent & event);
    
    void Save_Library_Name(wxCommandEvent & event);
    
    void Save_Standart(wxCommandEvent & event);

    void Save_Option(wxCommandEvent & event);

    void Close_Description_Panel(wxCommandEvent & event);

    void Save_Panel_Descriptions(wxCommandEvent & event);

    void Clear_Panel_Descriptions(wxCommandEvent & event);


    void Remove_Header_File_Location(wxCommandEvent & event);

    void Remove_Source_File_Location(wxCommandEvent & event);

    void Remove_Library_Directory(wxCommandEvent & event);
    
    void Remove_Library_Name(wxCommandEvent & event);

    
    void Clear_Header_File_Locations(wxCommandEvent & event);

    void Clear_Source_File_Locations(wxCommandEvent & event);

    void Clear_Library_Directories(wxCommandEvent & event);

    void Clear_Library_Names(wxCommandEvent & event);

    void Load_Data_List_Ctrl(wxDataViewListCtrl * listctrl, 

         const std::vector<std::string> & vec);

    void Load_Data_List_Ctrl(wxDataViewListCtrl * listctrl, 

         std::string data);

    GUI_List_Data_Recorder Data_Recorder;

    Descriptor_File_Reader Des_Reader;

    wxString Descriptor_File_Path;

    wxString DataType;

    wxBitmap * exclamation_mark_bmp;

    Process_Manager * Process_Ptr;

    char opr_sis;

    bool Data_Save_Status;

    wxFrame * Parent_Frame;

    wxBoxSizer * Frame_Sizer;

    wxBoxSizer * Scrolled_Win_Sizer;

    int Panel_Number;

    wxScrolledWindow * scroll_win;

    wxDataViewListCtrl ** listctrls;

    wxButton ** Insert_Buttons;


    wxBoxSizer * Data_Panel_Sizer;

    wxBoxSizer ** DataPanel_Sizers;

    wxBoxSizer ** Buton_Sizers;

    wxBoxSizer ** List_Ctrl_Sizers;

    wxPanel ** Data_Panels;




    wxBoxSizer * DataPanel_Top_Sizer;

    wxDataViewListCtrl * listctrl_for_path;

    wxDataViewListCtrl * listctrl_for_name;


    wxDataViewListCtrl * listctrl_git_repo_path;

    wxDataViewListCtrl * listctrl_warehouse_location;

    wxDataViewListCtrl * listctrl_for_header_dir;

    wxDataViewListCtrl * listctrl_src_file_location;

    wxDataViewListCtrl * listctrl_library_dir;

    wxDataViewListCtrl * listctrl_library_name;

    wxDataViewListCtrl * listctrl_standard;

    wxDataViewListCtrl * listctrl_options;


    wxButton * InsertButton_for_git_repo_path;

    wxButton * InsertButton_for_warehouse_location;

    wxButton * InsertButton_for_header_file_location;

    wxButton * InsertButton_for_src_file_locations;

    wxButton * InsertButton_for_library_dir;

    wxButton * InsertButton_for_library_name;

    wxButton * InsertButton_for_standard;

    wxButton * InsertButton_for_options;



    wxButton * Save_Button_for_git_repo_path;

    wxButton * Save_Button_for_warehouse_location;

    wxButton * Save_Button_for_header_file_location;

    wxButton * Save_Button_for_src_file_locations;

    wxButton * Save_Button_for_library_dir;

    wxButton * Save_Button_for_library_name;

    wxButton * Save_Button_for_standard;

    wxButton * Save_Button_for_options;




    wxButton * Remove_Button_for_src_file_locations;

    wxButton * Remove_Button_for_header_file_locations;

    wxButton * Remove_Button_for_library_dir;

    wxButton * Remove_Button_for_library_name;




    wxButton * Clear_Button_for_header_file_locations;

    wxButton * Clear_Button_for_src_file_locations;

    wxButton * Clear_Button_for_library_dir;

    wxButton * Clear_Button_for_library_name;





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
