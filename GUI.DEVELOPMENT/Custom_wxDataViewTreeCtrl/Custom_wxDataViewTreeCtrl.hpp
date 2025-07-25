


#ifndef CUSTOM_WXDATAVIEWTREECTRL_HPP
#define CUSTOM_WXDATAVIEWTREECTRL_HPP



#include <wx\wx.h>
#include <wx\dataview.h>
#include <wx\dc.h>
#include <wx\dcclient.h>
#include <wx\frame.h>
#include <wx\panel.h>
#include <wx\event.h>
#include <wx\sizer.h>
#include <wx\gdicmn.h>
#include <wx\dc.h>
#include <iostream>


class Custom_wxDataViewTreeCtrl : public wxDataViewTreeCtrl
{
public:
  Custom_wxDataViewTreeCtrl(wxWindow * parent, wxWindowID id,

        const wxPoint & pos,

        const wxSize & size, long style);

  virtual ~Custom_wxDataViewTreeCtrl();

  void Size_Event(wxSizeEvent & event);

  void OnPaint(wxPaintEvent & event);

  void SetScrollPosition(wxScrollEvent& event);

  void DrawBackground(wxDC & dc, wxWindow *  wnd, const wxRect & rect);

  void PaintNow();

  void Receive_Position(wxPoint control_position);

  wxWindow * Parent_Window_Pointer;

  wxPoint Position;

  DECLARE_EVENT_TABLE()

};

#endif /* CUSTOM_WXDATAVIEWTREECTRL_HPP */