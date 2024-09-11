

/*

 * Copyright (C) { Erkam Murat Bozkurt } - All Rights Reserved
 * 
 * This source code is protected under international copyright law.  All rights
 * reserved and protected by the copyright holders.
 * 
 * This file is confidential and only available to authorized individuals with the
 * permission of the copyright holders.  If you encounter this file and do not have
 * permission, please contact the copyright holders and delete this file.

*/

#include "Help_Page_Constructor.hpp"

BEGIN_EVENT_TABLE(Help_Page_Constructor,wxDialog)
    EVT_BUTTON(ID_CLOSE_HELP_PAGE_WINDOW,Help_Page_Constructor::CloseWindow)
    EVT_BUTTON(ID_SELECTION_INTRO_PAGE,Help_Page_Constructor::Open_Intro_Page)
    EVT_BUTTON(ID_SELECTION_WELCOME,Help_Page_Constructor::Open_Welcome_Page)

END_EVENT_TABLE()

Help_Page_Constructor::Help_Page_Constructor(wxWindow * parent, const wxString & message, 

    const wxString & message_title, wxWindowID id, const wxString & title, 
    
    const wxBitmap & bmp, const wxPoint & pos,
    
    const wxSize & size, long style, const wxString & name) : 

    wxDialog(parent, id, title, pos, size, style, name)
{
    this->Memory_Delete_Condition = false;

    this->yes_no_condition = false;

    this->SetDoubleBuffered(true);

    this->SetBackgroundStyle(wxBG_STYLE_PAINT);

    this->SetExtraStyle(wxCLIP_CHILDREN);

    this->SetExtraStyle(wxNO_FULL_REPAINT_ON_RESIZE);

    this->SetBackgroundColour(wxColour(240,240,240));

    this->GetEventHandler()->Bind(wxEVT_PAINT,&Help_Page_Constructor::OnPaint,this,wxID_ANY);

    this->GetEventHandler()->Bind(wxEVT_SIZE,&Help_Page_Constructor::OnSize,this,wxID_ANY);


    std::string face_name = "Calibri"; 

    this->Default_Font = new wxFont(12,wxFONTFAMILY_DEFAULT,wxFONTSTYLE_NORMAL,

                         wxFONTWEIGHT_NORMAL,false,wxString(face_name));

    this->SetFont(*this->Default_Font);


    this->figure_panel = new wxPanel(this,wxID_ANY,wxDefaultPosition,wxDefaultSize);

    this->text_title_panel = new wxPanel(this,wxID_ANY,wxDefaultPosition,wxDefaultSize);

    this->text_panel = new wxPanel(this,wxID_ANY,wxDefaultPosition,wxDefaultSize);



    int button_panel_size_x = this->GetSize().GetX()-150;
    
    wxSize button_panel_size = wxSize(button_panel_size_x,80);

    this->close_button_panel        = new wxPanel(this,wxID_ANY,wxDefaultPosition,button_panel_size);

    this->welcome_page_button_panel = new wxPanel(this,wxID_ANY,wxDefaultPosition,button_panel_size);

    this->intro_page_button_panel   = new wxPanel(this,wxID_ANY,wxDefaultPosition,button_panel_size); 
    

    this->figure_panel->SetBackgroundColour(wxColour(240,240,240));

    this->figure = new wxStaticBitmap(this->figure_panel,wxID_ANY,bmp);

    this->figure->SetBackgroundColour(wxColour(240,240,240));
    
    this->figure->Update();



    this->text_panel->SetBackgroundColour(wxColour(240,240,240));
    
    this->text_panel->Update();


    this->text   = new wxStaticText(this->text_panel ,wxID_ANY,message);

    this->text_title = new wxStaticText(this->text_title_panel ,wxID_ANY,message_title);


    this->text_title->SetForegroundColour(wxColour(100, 100, 110));

    wxFont Title_Font = text->GetFont();

    Title_Font.SetPointSize(13);

    this->text_title->SetFont(Title_Font.Bold());


    this->text->SetForegroundColour(wxColour(50,50,60));


    wxFont textFont = this->text_title->GetFont();

    this->text_title->SetFont(textFont);



    int button_size_x = button_panel_size_x-175;

       
    this->WelcomeButton  = new wxButton(this->welcome_page_button_panel,ID_SELECTION_WELCOME,
    
                         wxT("WELCOME PAGE"),wxDefaultPosition, wxSize(button_size_x,70));

    this->IntroButton    = new wxButton(this->intro_page_button_panel,ID_SELECTION_INTRO_PAGE,
    
                         wxT("INTRODUCTION"),wxDefaultPosition, wxSize(button_size_x,70));


    this->CloseButton    = new wxButton(this->close_button_panel,ID_CLOSE_HELP_PAGE_WINDOW,
     
                         wxT("CLOSE PAGE"),wxDefaultPosition, wxSize(button_size_x,70));
   
    

    this->WelcomeButton->CentreOnParent(wxBOTH);

    this->IntroButton->CentreOnParent(wxBOTH);

    this->CloseButton->CentreOnParent(wxBOTH);
   
    

    wxFont buttonFont = this->CloseButton->GetFont();




    //this->CloseButton->SetForegroundColour(wxColour(80,80,80));

    //this->IntroButton->SetForegroundColour(wxColour(80,80,80));

    //this->WelcomeButton->SetForegroundColour(wxColour(80,80,80));


    this->CloseButton->SetFont(buttonFont);

    this->IntroButton->SetFont(buttonFont);

    this->WelcomeButton->SetFont(buttonFont);


    wxBoxSizer * text_sizer = new wxBoxSizer(wxVERTICAL);

    text_sizer->Add(this->text_title_panel,0);

    text_sizer->Add(this->text_panel,1);



    wxBoxSizer * panel_sizer = new wxBoxSizer(wxHORIZONTAL);

    panel_sizer->Add(text_sizer,1,  wxALIGN_LEFT | wxALL, 50);

    panel_sizer->Add(this->figure_panel,1, wxRIGHT | wxTOP | wxBOTTOM,50);


    wxBoxSizer * button_sizer = new wxBoxSizer(wxVERTICAL);


    button_sizer->Add(this->welcome_page_button_panel,0,wxALIGN_CENTER_HORIZONTAL  | wxFIXED_MINSIZE | wxLEFT | wxRIGHT ,50);

    button_sizer->AddSpacer(10);

    button_sizer->Add(this->intro_page_button_panel,0,wxALIGN_CENTER_HORIZONTAL  | wxFIXED_MINSIZE | wxLEFT | wxRIGHT ,50);

    button_sizer->AddSpacer(10);

    button_sizer->Add(this->close_button_panel,0,wxALIGN_CENTER_HORIZONTAL  | wxFIXED_MINSIZE |  wxLEFT | wxRIGHT,50);
   
    button_sizer->AddSpacer(70);





    wxBoxSizer * topsizer = new wxBoxSizer(wxVERTICAL);

    topsizer->Add(panel_sizer,2, wxEXPAND | wxALL,0);

    topsizer->Add(button_sizer,0,wxALIGN_CENTER_HORIZONTAL | wxFIXED_MINSIZE | wxALL,0);


    topsizer->Layout();

    this->SetSizer(topsizer);

    topsizer->SetSizeHints(this);



    this->SetSize(size);

    this->SetMinSize(size);

    wxIcon Frame_Icon(wxT("C:\\Program Files\\Nwinix\\icons\\frame_icon.png"),wxBITMAP_TYPE_PNG,-1,-1);

    this->SetIcon(Frame_Icon);


    this->Centre(wxBOTH);

    this->Show();

    this->PaintNow(this);

    this->PaintNow(this->figure_panel);

    this->PaintNow(this->figure);

    this->figure_panel->Refresh();

    this->figure->SetBackgroundColour(wxColour(240,240,240));

    this->figure->Update();

    this->figure->Refresh();

    this->Update();

    wxBell();

}

Help_Page_Constructor::~Help_Page_Constructor()
{
     if(!this->Memory_Delete_Condition)
     {
         this->Memory_Delete_Condition = true;

     }
}






void Help_Page_Constructor::DrawBackground(wxDC& dc, wxWindow *  wnd, const wxRect& rect)
{
     dc.SetBrush(wxColour(240,240,240));

     dc.DrawRectangle(rect.GetX()-5, rect.GetY()-5, rect.GetWidth()+5,rect.GetHeight()+5);
}

void Help_Page_Constructor::PaintNow(wxWindow * wnd)
{
     wxClientDC dc(wnd);

     wxSize Rect_Size = wxSize(wnd->GetSize().x+5,wnd->GetSize().y+5);

     wxRect rect(Rect_Size);

     this->DrawBackground(dc,wnd,rect);
     
}


void Help_Page_Constructor::OnSize(wxSizeEvent & event){

     event.Skip(true);

     this->PaintNow(this);

     this->PaintNow(this->figure_panel);

     this->PaintNow(this->figure);

}



 void Help_Page_Constructor::OnPaint(wxPaintEvent & event){

      event.Skip(true);

      wxPaintDC dc(this);

      wxRect rect(this->GetSize());

      this->DrawBackground(dc,this,rect);
}


void Help_Page_Constructor::CloseWindow(wxCommandEvent & event)
{
     this->Destroy();
}

void Help_Page_Constructor::Open_Welcome_Page(wxCommandEvent & event){

     this->NoteBook_Ptr->OpenIntroPage();  

     this->Destroy();
}

void Help_Page_Constructor::Open_Intro_Page(wxCommandEvent & event){

     wxString Help_Page_Path = wxT("C:\\Program Files\\Nwinix\\introduction.txt");

     this->NoteBook_Ptr->Open_File(Help_Page_Path);

     size_t notebook_index = this->NoteBook_Ptr->GetIndex_FromPath(Help_Page_Path);

     this->NoteBook_Ptr->Get_NoteBook_Pointer()->SetPageText(notebook_index,wxT("Introduction"));

     this->Destroy();
}
