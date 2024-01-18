


#include "Project_Descriptions_Printer.hpp"


BEGIN_EVENT_TABLE(Project_Descriptions_Printer,wxFrame)
    EVT_BUTTON(ID_CLOSE_DESCRIPTION_WINDOW,Project_Descriptions_Printer::CloseWindow)
END_EVENT_TABLE()

Project_Descriptions_Printer::Project_Descriptions_Printer(wxFrame *parent, wxWindowID id, const wxString & title, 

   const wxPoint &pos, const wxSize &size, 
   
   long style) : wxFrame(parent,id,title,pos,size,
   
   wxSYSTEM_MENU | wxCAPTION | wxCLOSE_BOX | wxCLIP_CHILDREN | wxSTAY_ON_TOP)
{

     this->log_num =0;

     this->Default_Font = new wxFont(10,wxFONTFAMILY_MODERN ,wxFONTSTYLE_NORMAL,

                     wxFONTWEIGHT_NORMAL,false,"Segoe UI");

     this->SetFont(*(this->Default_Font));

     this->Memory_Delete_Condition = false;

     wxIcon Frame_Icon(wxT("D:\\Pcynlitx_Build_Platform\\icons\\frame_icon.png"),wxBITMAP_TYPE_PNG,-1,-1);

     this->SetIcon(Frame_Icon);

     this->SetBackgroundStyle(wxBG_STYLE_PAINT);

     this->SetExtraStyle(wxFULL_REPAINT_ON_RESIZE);

     this->GetEventHandler()->Bind(wxEVT_SIZE,&Project_Descriptions_Printer::OnSize,this,wxID_ANY);


     this->SetThemeEnabled(true);

     this->SetDoubleBuffered(true);

     this->SetExtraStyle(wxCLIP_CHILDREN);


     this->SetBackgroundStyle(wxBG_STYLE_PAINT);

     this->Centre(wxBOTH);

     this->CentreOnParent(wxBOTH);

     this->Fit();


     this->SetAutoLayout(true);

     this->ClearBackground();

     this->Construct_Text_Panel();

     this->PaintNow(this);

     this->Show(true);

     this->window_open_status = true;

}



Project_Descriptions_Printer::~Project_Descriptions_Printer(){


}


void Project_Descriptions_Printer::Receive_Descriptor_File_Reader(Descriptor_File_Reader * ptr){

     this->Des_Reader = ptr;
}

void Project_Descriptions_Printer::Construct_Text_Panel(){


     this->text_ctrl_panel = new wxPanel(this,wxID_ANY,wxDefaultPosition,wxSize(900,600));

     this->close_panel     = new wxPanel(this,wxID_ANY,wxDefaultPosition,wxSize(900,70));

     this->CloseButton     = new wxButton(this,ID_CLOSE_DESCRIPTION_WINDOW,wxT("CLOSE"),wxDefaultPosition, wxSize(80, 40));



     this->textctrl = new wxTextCtrl(this->text_ctrl_panel,wxID_ANY, wxT(""), 
     
                      wxDefaultPosition, wxSize(900,600), wxTE_MULTILINE | wxTE_RICH);



     this->ctrl_box = new wxBoxSizer(wxHORIZONTAL);

     this->ctrl_box->Add(this->text_ctrl_panel,1,wxEXPAND,2);

     this->ctrl_box->Layout();


     this->close_button_sizer = new wxBoxSizer(wxVERTICAL);

     this->close_button_sizer->AddStretchSpacer();

     this->close_button_sizer->Add(this->CloseButton,0, wxALIGN_CENTER_HORIZONTAL | wxFIXED_MINSIZE  | wxALL,5);

     this->close_button_sizer->AddStretchSpacer();

     this->close_button_sizer->Layout();

     

     this->frame_box = new wxBoxSizer(wxVERTICAL);

     this->frame_box->Add(this->ctrl_box,1,    wxEXPAND | wxTOP    |  wxALL,5);
 
     this->frame_box->Add(this->close_button_sizer,0,   wxEXPAND | wxBOTTOM  | wxALL,5);



     this->frame_box->Layout();


     this->SetSizer(this->frame_box);

     this->frame_box->SetSizeHints(this);

     this->frame_box->Fit(this);



     this->text_ctrl_panel->SetSize(this->text_ctrl_panel->GetClientSize());

     this->close_panel->SetSize(this->close_panel->GetClientSize());


     this->text_ctrl_panel->Update();

     this->textctrl->Update();




     this->SetSize(this->GetClientSize());

     this->PostSizeEvent();

     this->Centre(wxBOTH);

     this->Update();
}


void Project_Descriptions_Printer::Print_Descriptions(){

     this->Des_Reader->Read_Descriptor_File();

     std::string git_repo_location;

    if(this->Des_Reader->Get_Repo_Directory_Location() != ""){

       git_repo_location =  this->Des_Reader->Get_Repo_Directory_Location();

       git_repo_location.push_back('\n');
    }


    std::cout << "\n WAREHOUSE LOCATION:";

    std::string warehouse_location;

    if(this->Des_Reader->Get_Warehouse_Location() != ""){

       warehouse_location =  this->Des_Reader->Get_Warehouse_Location();

       warehouse_location.push_back('\n');

       this->textctrl->AppendText(wxString(warehouse_location));
    }

    std::cout << "\n STANDART RECORD:";

    std::string standard;

    if(this->Des_Reader->Get_Standard() != ""){

       standard =  this->Des_Reader->Get_Standard();

       standard.push_back('\n');

       this->textctrl->AppendText(wxString(standard));
    }

    std::cout << "\n INCLUDE DIRECTORY RECORD:";

    int include_dir_num = this->Des_Reader->Get_Include_Directory_Number();

     std::vector<std::string> include_dirs;

    if(include_dir_num > 0){

       for(int i=0;i<include_dir_num;i++){

          std::string inc_dir = this->Des_Reader->Get_Include_Directory(i);

          inc_dir.push_back('\n');

          include_dirs.push_back(inc_dir);
       }
    }

    for(int i=0;i<include_dir_num;i++){

        this->textctrl->AppendText(wxString(include_dirs.at(i)));
    }

    std::cout << "\n\n";




    std::cout << "\n SOURCE FILE DIRECTORIES RECORD:";

    int source_dir_num = this->Des_Reader->Get_Source_File_Directory_Number();

    std::vector<std::string> source_dirs;

    if(source_dir_num > 0){

       for(int i=0;i<source_dir_num;i++){

          std::string source_directory = this->Des_Reader->Get_Source_File_Directory(i);

          source_directory.push_back('\n');

          source_dirs.push_back(source_directory);
       }
    }

    for(int i=0;i<source_dir_num;i++){

        this->textctrl->AppendText(wxString(source_dirs.at(i)));
    }


    std::cout << "\n\n";


    std::cout << "\n LIBRARY DIRECTORIES RECORD:";

    int lib_dir_num = this->Des_Reader->Get_Library_Directory_Number();

    std::vector<std::string> library_dirs;

    if(lib_dir_num > 0){

       for(int i=0;i<lib_dir_num;i++){

           std::string library_directory = this->Des_Reader->Get_Library_Directory(i);

           library_directory.push_back('\n');

           library_dirs.push_back(library_directory);           
       }
    }

    for(int i=0;i<lib_dir_num;i++){

        this->textctrl->AppendText(wxString(library_dirs.at(i)));
    }


    std::cout << "\n\n";

    std::cout << "\n LIBRARY-FILES RECORD:";

    int lib_files_num = this->Des_Reader->Get_Library_Files_Number();

    std::vector<std::string> library_files;


    if(lib_files_num > 0){

       for(int i=0;i<lib_files_num;i++){

           std::string library_file = this->Des_Reader->Get_Library_File(i);

           library_file.push_back('\n');

           library_files.push_back(library_file);
       }
    }

    for(int i=0;i<lib_files_num;i++){

        this->textctrl->AppendText(wxString(library_files.at(i)));
    }



    std::cout << "\n\n";

    std::cout << "\n OPTIONS RECORD: ";

    std::string options;

    if(this->Des_Reader->Get_Options() != ""){

       options = this->Des_Reader->Get_Options();

       this->textctrl->AppendText(wxString(options));
    }
}

void Project_Descriptions_Printer::DrawBackground(wxDC& dc, wxWindow *  wnd, const wxRect& rect)
{
     dc.SetBrush(wxColour(220,220,220));

     dc.DrawRectangle(rect.GetX()-5, rect.GetY()-5, rect.GetWidth()+5,rect.GetHeight()+5);
}

void Project_Descriptions_Printer::PaintNow(wxWindow * wnd)
{
     wxClientDC dc(wnd);

     wxSize Rect_Size = wxSize(wnd->GetSize().x+5,wnd->GetSize().y+5);

     wxRect rect(Rect_Size);

     this->DrawBackground(dc,wnd,rect);
}


void Project_Descriptions_Printer::CloseWindow(wxCommandEvent & event){

     if(event.GetId() == ID_CLOSE_DESCRIPTION_WINDOW){

        this->Destroy();
     }
}


void Project_Descriptions_Printer::OnSize(wxSizeEvent & event){

     event.Skip(true);

     this->PaintNow(this);
}


wxTextCtrl * Project_Descriptions_Printer::GetTextControl() const {

     return this->textctrl;
}

int Project_Descriptions_Printer::GetLogNumber(){

     return this->log_num;
}

bool Project_Descriptions_Printer::GetWindowsOpenStatus(){

     return this->window_open_status;
}