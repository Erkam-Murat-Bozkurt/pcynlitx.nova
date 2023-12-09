
#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <wx/wx.h>
#include <wx\frame.h>
#include <wx\panel.h>
#include <wx\thread.h>
#include <wx\aui\framemanager.h>
#include <wx\aui\aui.h>
#include <wx\aui\auibar.h>
#include <wx\aui\auibook.h>
#include <wx\aui\dockart.h>
#include <wx\event.h>
#include <wx\fontdata.h>
#include <wx\fontdlg.h>
#include <wx\filedlg.h>
#include <wx\font.h>
#include <wx\process.h>
#include <wx\utils.h>
#include <wx\dialog.h>
#include <wx\dir.h>
#include <wx\toolbar.h>
#include <wx\richmsgdlg.h>
#include <wx\textdlg.h>
#include <wx/textctrl.h>
#include <wx\colour.h>
#include <wx\string.h>
#include <wx\scrolwin.h>
#include <wx\dcbuffer.h>
#include <wx\display.h>
#include <wx\msgdlg.h>
#include <wx\dataview.h>
#include <wx\listctrl.h>
#include <wx\listbox.h>
#include <wx/gauge.h>
#include <mutex>
#include <condition_variable>
#include "Custom_DataPanel.hpp"
#include "Menu_Bar_Options.h"
#include "Custom_Notebook.h"
#include "Event_ID_Numbers.h"
#include "Custom_DockArt.h"
#include "Intro_Page_Loader.h"
#include "Custom_wxPanel.h"
#include "Custom_TabArt.h"
#include "Process_Manager.hpp"
#include "Custom_wxThread.hpp"
#include "Custom_ProcessOutput.hpp"


class MainFrame : public wxFrame
{
public:
  MainFrame();
  virtual ~MainFrame();
  void OnPaint(wxPaintEvent & event);
  void DrawBackground(wxDC& dc, wxWindow *  wnd, const wxRect& _rect);
  void PaintNow(wxWindow * wnd);
  void Open_Intro_Page(wxCommandEvent & event);
  void Show_Author(wxCommandEvent & event);
  void Select_Project_File(wxCommandEvent&);
  void Show_Project_File(wxCommandEvent&);
  void Show_Progress(wxString Process_Label);
  void DirectoryOpen(wxCommandEvent & event);
  wxAuiPaneInfo Central_Pane_Info;
private:
  void Open_Empty_Project_File(wxCommandEvent & event);
  void Enter_Header_File_Location(wxCommandEvent & event);
  void Enter_Source_File_Location(wxCommandEvent & event);
  void Enter_Library_Location(wxCommandEvent & event);
  void Enter_Git_Repo_Location(wxCommandEvent & event);
  void Enter_Main_File_Name(wxCommandEvent & event);
  void Enter_Header_File(wxCommandEvent & event);
  void Enter_Source_File(wxCommandEvent & event);
  void Enter_Library_Name(wxCommandEvent & event);
  void Enter_Warehouse_Location(wxCommandEvent & event);
  void Enter_Exe_File_Name(wxCommandEvent & event);
  void Enter_Standard(wxCommandEvent & event);
  void Enter_Options(wxCommandEvent & event);
  void Save_File_As(wxCommandEvent & event);
  void Start_Build_System_Construction(wxCommandEvent & event);
  void Process_End(wxProcessEvent & event);
  void Descriptor_File_Selection_Check();
  void Close_Directory_Pane(wxAuiManagerEvent & event);
  Custom_DataPanel * data_panel_ptr;
  bool is_custom_panel_constructed;
  bool Memory_Delete_Condition;
  bool is_project_file_selected;
  Process_Manager * Process_Ptr;
  Custom_wxThread * Thread_Ptr;
  wxString Descriptor_File_Path;
  wxString Construction_Point;
  wxString DataType;
  wxAuiDockArt * Dock_Art_Pointer;
  wxAuiManager Interface_Manager;
  Custom_Tree_View_Panel * Dir_List_Manager;
  Custom_wxTreeCtrl * tree_control;
  Custom_wxPanel * Custom_Main_Panel;
  Custom_Notebook * Book_Manager;
  Menu_Bar_Options * MB_Options;
  Intro_Page_Loader * Intro_Page_Pointer;
  bool is_descriptor_file_open;
  wxFont * Default_Font;
  int Process_Event_Counter;
  bool * Progress_Bar_Start_status;
  std::condition_variable  cv;
  DECLARE_EVENT_TABLE()
};

#endif /* MAINFRAME_H */
