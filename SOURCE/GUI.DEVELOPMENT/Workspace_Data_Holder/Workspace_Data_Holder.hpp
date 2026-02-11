

#ifndef WORKSPACE_DATA_HOLDER_HPP
#define WORKSPACE_DATA_HOLDER_HPP

#include <wx/wx.h>
#include <wx/treectrl.h>
#include <wx/panel.h>
#include <wx/splitter.h>
#include <wx/sizer.h>
#include <wx/dir.h>
#include <wx/icon.h>
#include <wx/dialog.h>
#include <wx/window.h>
#include <cstdlib>
#include <wx/artprov.h>
#include <wx/msgout.h>
#include <wx/dataview.h>
#include <string>


class Workspace_Data_Holder
{
public:
  Workspace_Data_Holder();
  virtual ~Workspace_Data_Holder();
  wxString build_type;
  bool project_file_receive_status;
  bool * build_system_construction_status;
  bool git_repository_detection_status;
};

#endif /* WORKSPACE_DATA_HOLDER_HPP */
