
/*
 *
 * Copyright ©  2025,  Erkam Murat Bozkurt
 *
 * This file is part of the research project which is carried by Erkam Murat Bozkurt.
 * 
 * This is a free software: you can redistribute it and/or modify it under the terms
 * of the GNU General Public License as published by the Free Software Foundation
 * either version 3 of the License, or any later version.
 * 
 * This software is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.
 *
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 *
 */



#include "Custom_TabArt.h"


 Custom_TabArt::Custom_TabArt(wxColour clr) : wxAuiFlatTabArt()
 {


    this->page_close_icon =
    
    this->Rsc_Loader.CreateBitmapFromPngResource(wxString("CLOSE_TAB"));
    

    std::string tabart_font = "Segoe UI";

    this->Default_Font = new wxFont(9,wxFONTFAMILY_DEFAULT,wxFONTSTYLE_NORMAL,

                     wxFONTWEIGHT_LIGHT ,false,wxString(tabart_font));

    //this->m_tabCtrlHeight = 48;

    this->theme_clr = clr;

    this->SetNormalFont(*this->Default_Font);

    this->SetSelectedFont(*this->Default_Font);
 }

 wxAuiTabArt * Custom_TabArt::Clone() {

       Custom_TabArt * TabArt_Pointer = new Custom_TabArt(this->theme_clr);

       return TabArt_Pointer;
 }

 Custom_TabArt::~Custom_TabArt(){

      this->page_close_icon->~wxBitmap();
 }

 void Custom_TabArt::DrawBackground(wxDC& dc, wxWindow *  wnd, const wxRect & rect) {

      dc.SetPen(wxPen(wxColour(240,240,240,0xff)));

      dc.SetBrush(wxColour(240,240,240,0xff));

      dc.DrawRectangle(rect.GetX(), rect.GetY(),rect.GetWidth(),rect.GetHeight());
 }


int Custom_TabArt::DrawPageTab(wxDC& dc, wxWindow* wnd, wxAuiNotebookPage& page,
                             
    const wxRect& rect)
{
    static const int MARGIN = 3;
    static const int PADDING_X = 8;
    
    wxColour m_fgActive = wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOWTEXT);

    wxColour m_fgNormal = m_fgActive;    
        
    // Clip everything we do here to the provided rectangle.
    wxDCClipper clip(dc, rect);

    // Compute the size of the tab.
    int xExtent = 0;
    const wxSize size = GetPageTabSize(dc, wnd, page, &xExtent);

    wxPoint TabPosition = rect.GetPosition();

    int difference = 45 - size.GetHeight();

    TabPosition = wxPoint(TabPosition.x, TabPosition.y+difference);

    page.rect = wxRect(TabPosition,size);

    // Draw the tab background and highlight it if it's active.
    if ( page.active )
    {
        const wxColour bg = wxColour(255,255,255,0xff);
        dc.SetBrush(bg);
        dc.SetPen(*wxTRANSPARENT_PEN);
        dc.DrawRectangle(page.rect);
    }
    else{

        const wxColour bg = wxColour(225,225,225,0xff);
        dc.SetBrush(bg);
        dc.SetPen(*wxTRANSPARENT_PEN);
        dc.DrawRectangle(page.rect);
    }
    // Draw the outline only on the left/top sides to avoid double borders.
    dc.SetPen(wxPen(wxColour(240,240,240,0xff)));
    dc.DrawLine(page.rect.GetLeft(), page.rect.GetTop(),
                page.rect.GetLeft(), page.rect.GetBottom());
    dc.DrawLine(page.rect.GetLeft(), page.rect.GetTop(),
                page.rect.GetRight(), page.rect.GetTop());

    if ( page.active )
    {
        dc.SetBrush(wxColour(242,165,49,0xff));
        dc.SetPen(*wxTRANSPARENT_PEN);

        // 1px border is too thin to be noticeable, so make it thicker.
        const int THICKNESS = wnd->FromDIP(2);

        const int y = m_flags & wxAUI_NB_BOTTOM
                        ? page.rect.GetBottom() - THICKNESS
                        : page.rect.GetTop();

        dc.DrawRectangle(page.rect.GetLeft() + 1, y,
                         page.rect.GetWidth() - 1, THICKNESS);
    }

    // Draw the icon, if any.
    int xStart = rect.x + wnd->FromDIP(PADDING_X);
    if ( page.bitmap.IsOk() )
    {
        const wxBitmap bmp = page.bitmap.GetBitmapFor(wnd);
        const wxSize bitmapSize = bmp.GetLogicalSize();

        dc.DrawBitmap(bmp,
                      xStart,
                      rect.y + (size.y - bitmapSize.y - 1)/2+ difference,
                      true /* use mask */);

        xStart += bitmapSize.x + wnd->FromDIP(MARGIN);
    }

    // Draw buttons: start by computing their total width (note that we don't
    // use any margin between them currently because the bitmaps we use don't
    // need it as they have sufficient padding already).
    int buttonsWidth = 0;
    for ( const auto& button : page.buttons )
    {
        const wxBitmapBundle* const bb = GetButtonBitmapBundle(button);
        if ( !bb )
            continue;

        buttonsWidth += bb->GetBitmapFor(wnd).GetLogicalWidth();
    }

    // Now draw them and update their rectangles.
    int xEnd = rect.x + size.x - wnd->FromDIP(PADDING_X);
    if ( buttonsWidth )
    {
        xEnd -= buttonsWidth;

        int buttonX = xEnd;
        for ( auto& button : page.buttons )
        {
            const wxBitmapBundle* const bb = GetButtonBitmapBundle(button);
            if ( !bb )
                continue;

            const wxBitmap bmp = bb->GetBitmapFor(wnd);

            const wxSize buttonSize = bmp.GetLogicalSize();

            button.rect.x = buttonX;
            button.rect.y = rect.y + (size.y - buttonSize.y - 1)/2+ difference;
            button.rect.width = buttonSize.x;
            button.rect.height = buttonSize.y;

            IndentPressedBitmap(wnd, &button.rect, button.curState);
            dc.DrawBitmap(bmp, button.rect.GetPosition(), true);

            buttonX += buttonSize.x;
        }

        xEnd -= wnd->FromDIP(MARGIN);
    }

    // Finally draw tab text.
    dc.SetFont(page.active ? m_selectedFont : m_normalFont);
    dc.SetTextForeground(page.active ? m_fgActive : m_fgNormal);

    const wxString& text = wxControl::Ellipsize(page.caption,
                                                dc,
                                                wxELLIPSIZE_END,
                                                xEnd - xStart);

    const int textHeight = dc.GetTextExtent(text).y;
    dc.DrawText(text, xStart, rect.y + (size.y - textHeight - 1)/2 + difference);

    return xExtent;
}


 /*
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

       wxCoord tab_height = tab_size.y+14;

       wxCoord tab_x = in_rect.x+1;

       wxCoord tab_y = in_rect.y+25;

       wxCoord tab_width  = normal_textx+40;


       *x_extent = tab_width+1;




       wxFont active_font = *this->Default_Font;
       
       active_font.SetFaceName(wxT("Segoe UI"));

       active_font.SetWeight(wxFONTWEIGHT_LIGHT);


       wxFont normal = *this->Default_Font;

       normal.SetFaceName(wxT("Segoe UI"));


       if (page.active)
       {
           dc.SetFont(active_font);

           texty = selected_texty;
       }
       else
       {
           dc.SetFont(normal);

           texty = normal_texty;
       }


       if (page.active)
       {
           // draw active tab

           // draw base background color

           wxRect r(tab_x, tab_y, tab_width, tab_height-3);

           dc.SetPen(wxPen(wxColour(200,200,165,0xff)));
            
           dc.SetBrush(wxColour(200,200,185,0xff));

           


           // DrawRectangle member function: The first two parameters indicate the coordinates
           // of the top left corner of the rectangle

           dc.DrawRectangle(r.x, r.y, r.width, r.height);

        }
        else{

                // draw inactive tab

                wxRect r(tab_x, tab_y,tab_width, tab_height-3);

                dc.SetPen(wxPen(wxColour(180, 180, 180)));

                dc.SetBrush(wxBrush(wxColour(210, 210, 210)));

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
                         tab_y + (tab_height/2) - (bmp.GetScaledHeight()/2)-10,
                         bmp.GetScaledWidth()-3,
                         tab_height - 1);

             DrawButtons(dc,wxSize(1, 1), rect, bmp, *wxWHITE, close_button_state);

             *out_button_rect = rect;
         }



         wxString draw_text = page.caption;

         wxSize Text_Extend = dc.GetTextExtent(draw_text);

         int text_offset = tab_x + (tab_width-Text_Extend.x)/2;



         if(page.active){

            dc.SetTextForeground(wxColour(50,50,100));
         }
         else{

            dc.SetTextForeground(wxColour(50,50,100));
         }


         Text_Extend = dc.GetTextExtent(page.caption);

         if(page.active){

            text_offset = text_offset - 10;
         }
         else{

            text_offset = text_offset - 3;
         }



         dc.DrawText(draw_text,text_offset,

                 (tab_y + tab_height)/2 - (texty/2) + 1);


         *out_tab_rect = wxRect(tab_x, tab_y+15, tab_width, tab_height+25);

 }

 */

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


 