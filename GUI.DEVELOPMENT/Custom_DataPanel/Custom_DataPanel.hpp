



#ifndef CUSTOM_DATAPANEL_H
#define CUSTOM_DATAPANEL_H

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

enum
{
  ID_INSERT_ITEM = 70,
  ID_REMOVE_ITEM = 71,
  ID_SAVE_RECORDS = 72
};

class Custom_DataPanel: public wxFrame
{
public:
    Custom_DataPanel(wxFrame * frm, wxSize frame_size);
    virtual ~Custom_DataPanel();
    void Receive_Data_Type(wxString DataType);
    void Receive_Data(wxString Data);
    void AppendTextColumn(wxString text);
    void AppendDataItem(wxString str);
    void Insert_Data(wxCommandEvent & event);
    void Save_Data(wxCommandEvent & event);
    void Remove_Data(wxCommandEvent & event);
    void Receive_Descriptor_File_Path(wxString path);
    void File_Slection_Status(bool status);
    void Receive_Text_Enter_Status(bool status);
    wxDataViewListCtrl * GetDataViewListCtrl();
    void DrawBackground(wxDC & dc, wxWindow *  wnd, const wxRect& rect);
    void OnPaint(wxPaintEvent & event);   
protected:
    wxDialog * dlg_ptr;
    wxFrame  * frame_ptr;
    wxDataViewListCtrl * listctrl;
    Process_Manager * Process_Ptr;
    bool File_Slection;
    bool Text_Enter_Status;
    wxString Descriptor_File_Path;
    wxString Record_Data;
    wxString DataType;
    wxString Data;
    wxButton * InsertButton;
    wxButton * RemoveButton;
    wxButton * SaveButton;
    wxBoxSizer * vbox;
    wxBoxSizer * hbox;
    DECLARE_EVENT_TABLE()
};


#endif /* CUSTOM_DATAPANEL_H */
