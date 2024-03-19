

/*

Copyright ©  2021,  Erkam Murat Bozkurt

This file is part of the research project which is carried by Erkam Murat Bozkurt.

This is a free software: you can redistribute it and/or modify it under the terms
of the GNU General Public License as published by the Free Software Foundation
either version 3 of the License, or any later version.

This software is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE.

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
this program. If not, see <http://www.gnu.org/licenses/>.

*/


#include "Custom_TabArt.h"


 Custom_TabArt::Custom_TabArt() : wxAuiDefaultTabArt()
 {
    this->page_close_icon = new wxBitmap(wxT("D:\\Pcynlitx_Build_Platform\\icons\\close_tab.png"),

                             wxBITMAP_TYPE_ANY);

    std::string tabart_font = "Segoe UI";

    this->Default_Font = new wxFont(9,wxFONTFAMILY_DEFAULT,wxFONTSTYLE_NORMAL,

                     wxFONTWEIGHT_NORMAL,false,wxString(tabart_font));

    this->m_tabCtrlHeight = 36;
 }

 wxAuiTabArt * Custom_TabArt::Clone() {

       Custom_TabArt * TabArt_Pointer = new Custom_TabArt();

       return TabArt_Pointer;
 }

 Custom_TabArt::~Custom_TabArt(){

      this->page_close_icon->~wxBitmap();
 }

 void Custom_TabArt::DrawBackground(wxDC& dc, wxWindow *  wnd, const wxRect & rect) {

      dc.SetBrush(wxColour(240,240,240));

      dc.DrawRectangle(rect.GetX()-1, rect.GetY()-1,rect.GetWidth()+2,rect.GetHeight()+2);
 }

 void Custom_TabArt::DrawTab(wxDC & dc, wxWindow *wnd, const wxAuiNotebookPage &page,

                 const wxRect & in_rect, int close_button_state,

                 wxRect * out_tab_rect, wxRect * out_button_rect, int * x_extent)
 {

       wxCoord normal_textx,   normal_texty;

       wxCoord selected_textx, selected_texty;

       wxCoord texty;

       wxString caption = page.caption;



       dc.SetFont(*this->Default_Font);

       dc.GetTextExtent(caption, &selected_textx, &selected_texty);

       dc.GetTextExtent(caption, &normal_textx, &normal_texty);
 
       //caption = caption + " "; // more area for the string must be allocted
       

       // figure out the size of the tab
       wxSize tab_size = this->GetTabSize(dc,wnd,caption,page.bitmap,

                                    page.active,close_button_state,x_extent);

       wxCoord tab_height = tab_size.y;

       wxCoord tab_width  = tab_size.x;

       wxCoord tab_x = in_rect.x+1;

       wxCoord tab_y = in_rect.y;


       wxFont bld = this->Default_Font->Bold();

       //wxFont normal = *this->Default_Font;


       if (page.active)
       {

           dc.SetFont(bld);

           texty = selected_texty;
       }
       else
       {
           dc.SetFont(bld);

           texty = normal_texty;
       }


       if (page.active)
       {
           // draw active tab

           // draw base background color

           wxRect r(tab_x, tab_y, tab_width-2, tab_height+15);


           //200,190,190
           //190, 190, 190

           //dc.SetPen(wxPen(wxColour(206,108,125)));

           //dc.SetBrush(wxBrush(wxColour(206,108,125)));

           dc.SetPen(wxPen(wxColour(185,70,107)));

           dc.SetBrush(wxBrush(wxColour(215, 169, 135)));
            

           


           // DrawRectangle member function: The first two parameters indicate the coordinates
           // of the top left corner of the rectangle

           dc.DrawRectangle(r.x, r.y, r.width, r.height);

        }
        else{

                // draw inactive tab

                wxRect r(tab_x, tab_y,tab_width-2, tab_height+15);


                //200,190,190
                //190, 190, 190

                dc.SetPen(wxPen(wxColour(150,150,150)));

                dc.SetBrush(wxBrush(wxColour(190, 190, 190)));

                // DrawRectangle member function: The first two parameters indicate the coordinates
                // of the top left corner of the rectangle

                dc.DrawRectangle(r.x, r.y, r.width, r.height);
        }


        // draw close button 
        if (close_button_state != wxAUI_BUTTON_STATE_HIDDEN)
         {
             wxBitmap bmp;

             if (page.active){

                 bmp = *this->page_close_icon;
             }
             else{

                 wxSize bmp_size = this->page_close_icon->GetScaledSize();
                 bmp = m_disabledCloseBmp.GetBitmap(bmp_size);
            }

             wxRect rect(tab_x + tab_width - bmp.GetScaledWidth() - 10,
                         tab_y + (tab_height/2) - (bmp.GetScaledHeight()/2)-2,
                         bmp.GetScaledWidth()-3,
                         tab_height - 1);

             DrawButtons(dc,wxSize(1, 1), rect, bmp, *wxWHITE, close_button_state);

             *out_button_rect = rect;
         }



         wxString draw_text = page.caption;

         wxSize Text_Extend = dc.GetTextExtent(draw_text);

         int text_offset = tab_x + (tab_width-Text_Extend.x)/2;



         if(page.active){

            //135,104,112
            //100,100,100

            //dc.SetTextForeground(wxColour(250,250,250));

            dc.SetTextForeground(wxColour(135,93,67));

         }
         else{

            //135,104,112
            //100,100,100

            dc.SetTextForeground(wxColour(110,110,120));
         }


         Text_Extend = dc.GetTextExtent(page.caption);

         if(page.active){

            text_offset = text_offset - 10;
         }
         else{

            text_offset = text_offset - 3;
         }



         dc.DrawText(draw_text,text_offset,

                 (tab_y + tab_height)/2 - (texty/2) + 2);


         *out_tab_rect = wxRect(tab_x, tab_y, tab_width, tab_height+14);

 }



 void Custom_TabArt::DrawButtons(wxDC& dc, const wxSize& offset,const wxRect& _rect,

                            const wxBitmap& bmp, const wxColour& bkcolour, int button_state)
  {
        wxRect rect = _rect;

        if (button_state == wxAUI_BUTTON_STATE_PRESSED)
        {
            rect.x += offset.x;
            rect.y += offset.y;
        }

        if (button_state == wxAUI_BUTTON_STATE_HOVER ||
            button_state == wxAUI_BUTTON_STATE_PRESSED)
        {
            dc.SetBrush(wxBrush(bkcolour.ChangeLightness(120)));
            dc.SetPen(wxPen(bkcolour.ChangeLightness(75)));

            // draw the background behind the button
            dc.DrawRectangle(rect.x, rect.y+7, bmp.GetScaledWidth()-offset.x-2,

                 bmp.GetScaledHeight()-offset.y);
        }

        // draw the button itself
        dc.DrawBitmap(bmp, rect.x, rect.y+6, true);
 }

 void Custom_TabArt::DrawButton(wxDC& dc,wxWindow* wnd,const wxRect& in_rect,

                    int bitmap_id,int button_state,int orientation, wxRect* out_rect)
 {

      wxBitmapBundle bb;
      wxRect rect;

      switch (bitmap_id)
      {
          case wxAUI_BUTTON_CLOSE:
              if (button_state & wxAUI_BUTTON_STATE_DISABLED)
                  bb = m_disabledCloseBmp;
              else
                  bb = m_activeCloseBmp;
              break;

          case wxAUI_BUTTON_LEFT:
              if (button_state & wxAUI_BUTTON_STATE_DISABLED)
                  bb = m_disabledLeftBmp;
              else
                  bb = m_activeLeftBmp;
              break;

          case wxAUI_BUTTON_RIGHT:
              if (button_state & wxAUI_BUTTON_STATE_DISABLED)
                  bb = m_disabledRightBmp;
              else
                  bb = m_activeRightBmp;
              break;

          case wxAUI_BUTTON_WINDOWLIST:
              if (button_state & wxAUI_BUTTON_STATE_DISABLED)
                  bb = m_disabledWindowListBmp;
              else
                  bb = m_activeWindowListBmp;
              break;
      }


      if (!bb.IsOk())
          return;


      const wxBitmap bmp = bb.GetBitmapFor(wnd);


      rect = in_rect;

      if (orientation == wxLEFT)
      {
          rect.SetX(in_rect.x);
          rect.SetY(((in_rect.y + in_rect.height)/2) - (bmp.GetScaledHeight()/2)-2);
          rect.SetWidth(bmp.GetScaledWidth());
          rect.SetHeight(bmp.GetScaledHeight());
      }
      else
      {
          rect = wxRect(in_rect.x + in_rect.width - bmp.GetScaledWidth(),
                      ((in_rect.y + in_rect.height)/2) - (bmp.GetScaledHeight()/2)-2,
                      bmp.GetScaledWidth(), bmp.GetScaledHeight());
      }


      this->DrawButtons(dc,wxSize(1,1), rect, bmp, *wxWHITE, button_state);

      *out_rect = rect;
 };
