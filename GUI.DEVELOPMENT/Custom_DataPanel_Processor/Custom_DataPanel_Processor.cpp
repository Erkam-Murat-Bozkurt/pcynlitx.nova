
#include "Custom_DataPanel_Processor.hpp"

Custom_DataPanel_Processor::Custom_DataPanel_Processor(wxFrame * frame, wxString DataType, 

     wxString Title, wxString Column_Text,

     bool file_selection, bool text_enter_status){


     this->DataPanel_Pointer = new Custom_DataPanel(frame,wxSize(700,400));

     this->DataPanel_Pointer->File_Slection_Status(file_selection);

     this->DataPanel_Pointer->Receive_Text_Enter_Status(text_enter_status);

     this->DataPanel_Pointer->Receive_Data_Type(DataType);

     this->DataPanel_Pointer->SetTitle(Title);

     this->DataPanel_Pointer->AppendTextColumn(Column_Text);

     this->DataPanel_Pointer->Show();

     this->DataPanel_Pointer->GetDataViewListCtrl()->Show();
}


Custom_DataPanel_Processor::~Custom_DataPanel_Processor(){


}


void Custom_DataPanel_Processor::Receive_Descriptor_File_Path(wxString DesPATH){

     this->DataPanel_Pointer->Receive_Descriptor_File_Path(DesPATH);
}