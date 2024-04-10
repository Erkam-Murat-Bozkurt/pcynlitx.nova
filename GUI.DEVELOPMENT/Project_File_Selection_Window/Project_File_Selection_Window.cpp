


#include "Project_File_Selection_Window.hpp"


BEGIN_EVENT_TABLE(Project_File_Selection_Window,wxFrame )

    EVT_BUTTON(ID_CLOSE_PROJECT_FILE_SELECTION_PANEL,Project_File_Selection_Window::Close_Window)

    EVT_PAINT(Project_File_Selection_Window::OnPaint)

END_EVENT_TABLE()



Project_File_Selection_Window::Project_File_Selection_Window(wxFrame * parent, wxWindowID id, const wxString & title, 

   const wxPoint & pos, const wxSize & size, long style, char opr_sis) : 
   
   wxFrame(parent,id,title,pos,size, style),  Des_Reader(opr_sis)
{
     this->Parent_Frame = parent;

     this->Des_Reader.Set_Gui_Read_Status(true);

     wxIcon Frame_Icon(wxT("D:\\Pcynlitx_Build_Platform\\icons\\frame_icon.png"),wxBITMAP_TYPE_PNG,-1,-1);

     this->SetIcon(Frame_Icon);

     this->SetTitle(wxT("NWINIX BUILD SYSTEM DESCRIPTION PANEL"));


     this->save_bmp 
  
      = new wxBitmap(wxT("D:\\Pcynlitx_Build_Platform\\icons\\save_success_icon.png"),wxBITMAP_TYPE_ANY);

     this->exclamation_mark_bmp 
  
      = new wxBitmap(wxT("D:\\Pcynlitx_Build_Platform\\icons\\exclamation_icon.png"),wxBITMAP_TYPE_ANY);

     this->SetBackgroundColour(wxColour(250,250,250));

     
     this->Project_File_Selection_Panel  = new wxPanel(this,wxID_ANY,wxDefaultPosition,wxSize(400,320));

     this->Project_File_Selection_Panel->SetMinSize(wxSize(400,320));

     this->Project_File_Selection_Panel->SetBackgroundColour(wxColour(200,200,220));


     this->Empty_Project_File_Panel  = new wxPanel(this,wxID_ANY,wxDefaultPosition,wxSize(400,320));

     this->Empty_Project_File_Panel->SetMinSize(wxSize(400,320));

     this->Empty_Project_File_Panel->SetBackgroundColour(wxColour(175,175,185));



     this->EMPF_Cons_Panel_Sizer = new wxBoxSizer(wxHORIZONTAL);

     this->EMPF_Cons_Panel_Sizer->Add(this->Empty_Project_File_Panel,1,wxEXPAND | wxALL,0);



     this->PRFS_Panel_Sizer = new wxBoxSizer(wxHORIZONTAL);

     this->PRFS_Panel_Sizer->Add(this->Project_File_Selection_Panel,1,wxEXPAND | wxALL,0);




     this->Empty_Project_File_Button_Panel     = new wxPanel(this,wxID_ANY,wxDefaultPosition,wxSize(-1,-1));

     this->Project_File_Selection_Button_Panel = new wxPanel(this,wxID_ANY,wxDefaultPosition,wxSize(-1,-1));


     this->Empty_Project_File_Button     = new wxButton(this->Empty_Project_File_Button_Panel,ID_CONSTRUCT_EMPTY_PROJECT_FILE,
     
                                         wxT("NEW PROJECT FILE"), wxDefaultPosition,   wxSize(200, 60));

     this->Project_File_Selection_Button = new wxButton(this->Project_File_Selection_Button_Panel,ID_SELECT_AN_EXISTING_PROJECT_FILE,
     
                                         wxT("SELECT PROJECT FILE"),wxDefaultPosition, wxSize(200, 60));


     this->EMPF_Cons_Buttom_Panel_Sizer = new wxBoxSizer(wxHORIZONTAL);

     this->PRFS_Button_Panel_Sizer      = new wxBoxSizer(wxHORIZONTAL);



     this->EMPF_Cons_Buttom_Panel_Sizer->Add(this->Empty_Project_File_Button_Panel,0,  wxEXPAND  |  wxALL,0);

     this->PRFS_Button_Panel_Sizer->Add(this->Project_File_Selection_Button_Panel, 0,  wxEXPAND  | wxALL,0);



     this->Left_Panel_Sizer = new wxBoxSizer(wxVERTICAL);

     this->Left_Panel_Sizer->Add(this->EMPF_Cons_Panel_Sizer,1,wxEXPAND | wxTOP | wxALL ,0);

     this->Left_Panel_Sizer->Add(this->EMPF_Cons_Buttom_Panel_Sizer,0, wxALIGN_CENTER_HORIZONTAL | wxFIXED_MINSIZE  | wxBOTTOM  | wxALL ,0);


     this->Right_Panel_Sizer = new wxBoxSizer(wxVERTICAL);

     this->Right_Panel_Sizer->Add(this->PRFS_Panel_Sizer,1,wxEXPAND | wxALL ,0);

     this->Right_Panel_Sizer->Add(this->PRFS_Button_Panel_Sizer,0,  wxALIGN_CENTER_HORIZONTAL | wxFIXED_MINSIZE  | wxBOTTOM  | wxALL ,0);

     




     this->Frame_Sizer = new wxBoxSizer(wxHORIZONTAL);

     this->Frame_Sizer->Add(this->Left_Panel_Sizer, 1,wxEXPAND | wxALL,20);

     this->Frame_Sizer->Add(this->Right_Panel_Sizer,1,wxEXPAND | wxALL,20);

     this->SetSizer(this->Frame_Sizer);

     this->Frame_Sizer->SetSizeHints(this);

     this->Fit();

     this->Empty_Project_File_Panel->Show(true);

     this->Project_File_Selection_Panel->Show(true);

     this->Empty_Project_File_Panel->SetAutoLayout(true);

     this->Project_File_Selection_Panel->SetAutoLayout(true);

     this->Centre();

     this->CentreOnParent(wxBOTH);

     this->SetAutoLayout(true);

     this->Refresh();

     this->Update();

     this->Show(true);
}


Project_File_Selection_Window::~Project_File_Selection_Window(){

}

void Project_File_Selection_Window::DrawBackground(wxDC & dc, wxWindow *  wnd, const wxRect& rect)
{
     dc.SetBrush(wxColour(220,220,220));

     dc.DrawRectangle(rect.GetX()-5, rect.GetY()-5, rect.GetWidth()+5,rect.GetHeight()+5);
}

void Project_File_Selection_Window::OnPaint(wxPaintEvent & event)
{
     event.Skip(false);

     wxPaintDC dc(this);

     wxRect rect(this->GetSize());

     this->DrawBackground(dc,this,rect);
}


void Project_File_Selection_Window::Receive_Descriptor_File_Path(wxString path){

     this->Descriptor_File_Path = path;

     this->Des_Reader.Receive_Descriptor_File_Path(path.ToStdString());
}


void Project_File_Selection_Window::Close_Window(wxCommandEvent & event){

     if(event.GetId() == ID_CLOSE_PROJECT_FILE_SELECTION_PANEL ){

        event.Skip(true);

        this->Destroy();
     }
}


void Project_File_Selection_Window::Clear_Vector_Memory(std::vector<std::string> & vec){

     vec.shrink_to_fit();

     size_t vector_size = vec.size();

     for(size_t i=0;i<vector_size;i++){

        this->Clear_String_Memory(vec.at(i));
     }

     vec.shrink_to_fit();
}

void Project_File_Selection_Window::Clear_String_Memory(std::string & str){

     str.clear();

     str.shrink_to_fit();
}

