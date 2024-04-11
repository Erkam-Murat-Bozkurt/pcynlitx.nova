






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
#include <wx/dialog.h>
#include "Descriptor_File_Reader.hpp"
#include "Process_Manager.hpp"
#include "Custom_Message_Dialog.hpp"
#include "Cpp_FileOperations.h"



enum
{
  ID_CLOSE_PROJECT_FILE_SELECTION_PANEL = 200,
  ID_CONSTRUCT_EMPTY_PROJECT_FILE = 201,
  ID_SELECT_AN_EXISTING_PROJECT_FILE = 202
};


class Project_File_Selection_Window : public wxDialog 
{
public:
    Project_File_Selection_Window(wxWindow * parent, wxWindowID id, 
    
    const wxString & title=wxT("PROJECT FILE SELECTION PANEL"), 
    
    const wxPoint & pos=wxDefaultPosition, const wxSize & size=wxSize(700,400));

    virtual ~Project_File_Selection_Window();

    void Receive_Process_Manager(Process_Manager * Process_Ptr);

    void Receive_Descriptor_File_Path(wxString * DesPATH);

    bool get_Descriptor_File_Selection_Status() const;

    wxString ExeFileName;

    wxString FilePath;

protected:

    void DrawBackground(wxDC & dc, wxWindow *  wnd, const wxRect& rect);

    void OnPaint(wxPaintEvent & event);

    void Close_Window(wxCommandEvent & event);

    void Construct_Empty_Project_File(wxCommandEvent & event);

    void Select_Project_File(wxCommandEvent & event);

    void Clear_String_Memory(std::string & str);

    void Clear_Vector_Memory(std::vector<std::string> & vec);

    void Select_File();

    Cpp_FileOperations FileManager;

    Process_Manager * Process_Ptr;

    wxString * Descriptor_File_Path_Pointer;

    wxString DataType;

    wxBitmap * new_empty_file;

    wxBitmap * open_existing_file;

    char opr_sis;

    bool Descriptor_File_Selection_Status;


    wxWindow * Parent_Window;

    wxBoxSizer * Frame_Sizer;

    wxBoxSizer * EMPF_Cons_Panel_Sizer;

    wxBoxSizer * PRFS_Panel_Sizer;

    wxBoxSizer * EMPF_Cons_Buttom_Panel_Sizer;

    wxBoxSizer * PRFS_Button_Panel_Sizer;


    wxBoxSizer * EMPF_Cons_Text_Panel_Sizer;

    wxBoxSizer * PRFS_Text_Panel_Sizer;


    wxBoxSizer * Left_Panel_Sizer;

    wxBoxSizer * Right_Panel_Sizer;


    wxButton * Empty_Project_File_Button;

    wxButton * Project_File_Selection_Button;


    wxPanel  * Empty_Project_File_Panel;

    wxPanel  * Project_File_Selection_Panel;

    wxPanel  * Empty_Project_File_Button_Panel;

    wxPanel  * Project_File_Selection_Button_Panel;

    wxPanel  * Empty_Project_File_Text_Panel;

    wxPanel  * Project_File_Selection_Text_Panel;

    DECLARE_EVENT_TABLE()
};


#endif /* PROJECT_FILE_SELECTION_WINDOW_HPP */
