





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
  ID_SAVE_MAKE_FILE_DATA   = 102
};


class Custom_Multi_DataPanel : public wxDialog 
{
public:
    Custom_Multi_DataPanel(wxFrame * parent, wxWindowID id=wxID_ANY, const wxString & title=wxT(""), 

        const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxSize(900,770), 
   
        long style=wxDEFAULT_DIALOG_STYLE | wxSTAY_ON_TOP);

    virtual ~Custom_Multi_DataPanel();

    void Create_Exe_Script_Panel();

    bool Get_Data_Save_Status();

    wxString ExeFileName;

    wxString FilePath;


protected:

    void DrawBackground(wxDC & dc, wxWindow *  wnd, const wxRect& rect);

    void OnPaint(wxPaintEvent & event);

    void AppendDataItem(wxDataViewListCtrl * listctrl, wxString str);

    void Construct_NewData_Panels();

    void Insert_Data_For_Path(wxCommandEvent & event);

    void Save_MakeFile_Data(wxCommandEvent & event);

    void Insert_Data_For_Name(wxCommandEvent & event);

    bool Data_Save_Status;

    wxFrame * Parent_Frame;

    wxBoxSizer * Frame_Sizer;


    wxDataViewListCtrl * listctrl_for_path;

    wxDataViewListCtrl * listctrl_for_name;


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
