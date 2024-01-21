

#ifndef CUSTOM_MESSAGE_DIALOG_HPP
#define CUSTOM_MESSAGE_DIALOG_HPP

#include <wx/wx.h>
#include <wx/sizer.h>
#include <wx/event.h>
#include <wx/gdicmn.h>
#include <wx/msgdlg.h>
#include <wx/dialog.h>
#include <wx/statbmp.h>
#include <wx/stattext.h>
#include <wx/utils.h> 




enum
{
  ID_CLOSE_MESSAGE_WINDOW = 90
};

class Custom_Message_Dialog : public wxDialog
{
public:
    Custom_Message_Dialog(wxWindow * parent, const wxString & message=wxT(""), 
    
    const wxString & message_title=wxT(""), wxWindowID id=wxID_ANY, 
    
    const wxString & title=wxT("NWINIX REPORT"), const wxBitmap & bmp=NULL,
    
    const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxSize(620,400),
    
    long style=wxDEFAULT_DIALOG_STYLE, const wxString &name=wxDialogNameStr);
    
    virtual ~Custom_Message_Dialog();
    
private:
    void DrawBackground(wxDC& dc, wxWindow *  wnd, const wxRect& rect);

    void OnSize(wxSizeEvent & event);

    void OnPaint(wxPaintEvent & event);

    void CloseWindow(wxCommandEvent & event);

    void PaintNow(wxWindow * wnd);

    wxStaticText * text;

    wxStaticText * text_title;

    wxStaticBitmap * figure;

    wxPanel *  text_title_panel;

    wxPanel *  text_panel;

    wxPanel *  figure_panel;

    wxPanel *  button_panel;

    wxFont * Default_Font;

    wxButton * CloseButton;

    bool Memory_Delete_Condition;

    DECLARE_EVENT_TABLE()
};


#endif /* CUSTOM_MESSAGE_DIALOG_HPP */
