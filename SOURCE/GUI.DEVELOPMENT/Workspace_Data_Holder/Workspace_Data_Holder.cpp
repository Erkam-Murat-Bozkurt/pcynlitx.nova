
#include "Workspace_Data_Holder.hpp"

Workspace_Data_Holder::Workspace_Data_Holder()
{

  this->build_type = wxString("");
  this->project_file_receive_status = false;
  this->build_system_construction_status =nullptr;
  bool git_repository_detection_status = false;
}


Workspace_Data_Holder::~Workspace_Data_Holder(){


}


