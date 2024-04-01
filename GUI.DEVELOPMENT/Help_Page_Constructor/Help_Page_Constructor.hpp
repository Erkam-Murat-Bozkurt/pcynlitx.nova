



#ifndef HELP_PAGE_CONSTRUCTOR_HPP
#define HELP_PAGE_CONSTRUCTOR_HPP

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
  ID_CLOSE_HELP_PAGE_WINDOW = 80,
  ID_SELECTION_INTRO_PAGE = 81,
  ID_SELECTION_WELCOME = 82
};

class Help_Page_Constructor : public wxDialog
{
public:
    Help_Page_Constructor(wxWindow * parent, const wxString & message=wxT(""), 
    
    const wxString & message_title=wxT(""), wxWindowID id=wxID_ANY, 
    
    const wxString & title=wxT("NWINIX REPORT"), const wxBitmap & bmp=NULL,
    
    const wxPoint &pos=wxDefaultPosition, 
    
    const wxSize &size=wxSize(720,1000),
    
    long style=wxDEFAULT_DIALOG_STYLE, const wxString &name=wxDialogNameStr);
    
    virtual ~Help_Page_Constructor();

    bool GetYesNoCond() const;
    
private:
    void DrawBackground(wxDC& dc, wxWindow *  wnd, const wxRect& rect);

    void OnSize(wxSizeEvent & event);

    void OnPaint(wxPaintEvent & event);

    void CloseWindow(wxCommandEvent & event);

    void PaintNow(wxWindow * wnd);

    void SetYes(wxCommandEvent & event);

    void SetNo(wxCommandEvent & event);

    bool yes_no_condition;

    wxStaticText * text;

    wxStaticText * text_title;

    wxStaticBitmap * figure;

    wxPanel *  text_title_panel;

    wxPanel *  text_panel;

    wxPanel *  figure_panel;

    wxPanel *  close_button_panel;

    wxPanel *  welcome_page_button_panel;

    wxPanel *  intro_page_button_panel;

    wxFont * Default_Font;

    wxButton * CloseButton;

    wxButton * WelcomeButton;

    wxButton * IntroButton;

    bool Memory_Delete_Condition;

    DECLARE_EVENT_TABLE()
};


#endif /* HELP_PAGE_CONSTRUCTOR_HPP */
