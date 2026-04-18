


#ifndef CUSTOM_TABART_H
#define CUSTOM_TABART_H

#include <wx\wx.h>
#include <wx\frame.h>
#include <wx\panel.h>
#include <wx\aui\aui.h>
#include <wx\aui\tabart.h>
#include <wx\aui\auibook.h>
#include <wx\aui\framemanager.h>
#include <wx\aui\dockart.h>
#include <wx\event.h>
#include <wx\font.h>
#include <wx\fontdata.h>
#include <wx\fontdlg.h>
#include <string>
#include <wx/fontutil.h>
#include "Resource_Loader.hpp"



// Custom TabArt decleration .........

class Custom_TabArt : public 	wxAuiFlatTabArt
{
public:

  Custom_TabArt(wxColour clr);

  wxAuiTabArt * Clone();

  virtual ~Custom_TabArt();

  void DrawBackground(wxDC& dc, wxWindow *  wnd, const wxRect & _rect);

  static void IndentPressedBitmap(wxWindow* wnd, wxRect* rect, int button_state)
  {
    if (button_state & wxAUI_BUTTON_STATE_PRESSED)
    {
        rect->Offset(wnd->FromDIP(wxPoint(1, 1)));
    }
  }
  
  int DrawPageTab(wxDC& dc, wxWindow* wnd, wxAuiNotebookPage& page, const wxRect& rect);

  static void DrawButtons(wxDC& dc,const wxSize & offset,const wxRect & _rect,

                          const wxBitmap & bmp,const wxColour & bkcolour, int button_state);



  void DrawButton(wxDC & dc,wxWindow* wnd,const wxRect & in_rect,

                    int bitmap_id,int button_state,int orientation, wxRect* out_rect);

  Resource_Loader Rsc_Loader;

  wxBitmap * page_close_icon;

  wxFont * Default_Font;

  wxColour theme_clr;
};

#endif /* CUSTOM_TABART_H */
