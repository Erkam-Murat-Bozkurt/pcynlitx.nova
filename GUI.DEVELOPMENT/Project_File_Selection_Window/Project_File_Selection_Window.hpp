






#ifndef PROJECT_FILE_SELECTION_WINDOW_HPP
#define PROJECT_FILE_SELECTION_WINDOW_HPP

#include <wx/wx.h>
#include <wx\sizer.h>
#include <wx\event.h>
#include <wx\aui\aui.h>
#include <wx\aui\framemanager.h>
#include <wx\sizer.h>
#include <wx\dataview.h>
#include <wx\textdlg.h>
#include <wx\msgdlg.h>
#include <wx\dir.h>
#include "Descriptor_File_Reader.hpp"
#include "Custom_Message_Dialog.hpp"



enum
{
  ID_CLOSE_PROJECT_FILE_SELECTION_PANEL = 200,
  ID_CONSTRUCT_EMPTY_PROJECT_FILE = 201,
  ID_SELECT_AN_EXISTING_PROJECT_FILE = 202
};


class Project_File_Selection_Window : public wxFrame 
{
public:
    Project_File_Selection_Window(wxFrame * parent, wxWindowID id=wxID_ANY, 
    
        const wxString & title=wxT(""), 

        const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxSize(800,420), 
   
        long style=wxDEFAULT_FRAME_STYLE | wxSTAY_ON_TOP, char opr_sis='w');

    virtual ~Project_File_Selection_Window();

    void Receive_Descriptor_File_Path(wxString path);

    bool Get_Data_Save_Status();

    wxString ExeFileName;

    wxString FilePath;



protected:

    void DrawBackground(wxDC & dc, wxWindow *  wnd, const wxRect& rect);

    void OnPaint(wxPaintEvent & event);

    void Close_Window(wxCommandEvent & event);



    void Clear_String_Memory(std::string & str);

    void Clear_Vector_Memory(std::vector<std::string> & vec);

    Descriptor_File_Reader Des_Reader;

    wxString Descriptor_File_Path;

    wxString DataType;

    wxBitmap * exclamation_mark_bmp;

    wxBitmap * save_bmp;

    char opr_sis;


    wxFrame * Parent_Frame;

    wxBoxSizer * Frame_Sizer;

    wxBoxSizer * EMPF_Cons_Panel_Sizer;

    wxBoxSizer * PRFS_Panel_Sizer;

    wxBoxSizer * EMPF_Cons_Buttom_Panel_Sizer;

    wxBoxSizer * PRFS_Button_Panel_Sizer;



    wxBoxSizer * Left_Panel_Sizer;

    wxBoxSizer * Right_Panel_Sizer;


    wxButton * Empty_Project_File_Button;

    wxButton * Project_File_Selection_Button;


    wxPanel  * Empty_Project_File_Panel;

    wxPanel  * Project_File_Selection_Panel;

    wxPanel  * Empty_Project_File_Button_Panel;

    wxPanel  * Project_File_Selection_Button_Panel;


    DECLARE_EVENT_TABLE()
};


#endif /* PROJECT_FILE_SELECTION_WINDOW_HPP */
