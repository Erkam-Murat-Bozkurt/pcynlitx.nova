
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
#include <wx\gauge.h>
#include <mutex>
#include <chrono>
#include <condition_variable>
#include <thread>
#include <wx/dataview.h>
#include "Custom_wxPanel.h"
#include "Custom_Tree_View_Panel.h"
#include "Custom_wxDataViewTreeCtrl.hpp"
#include "Custom_Notebook.h"
#include "Event_ID_Numbers.h"
#include "Custom_DockArt.h"
#include "Intro_Page_Loader.h"
#include "Custom_DataPanel.hpp"
#include "Custom_TabArt.h"
#include "Process_Manager.hpp"
#include "Custom_wxThread.hpp"
#include "Custom_ProcessOutput.hpp"
#include "ToolBar_Initializer.h"
#include "Project_File_Selection_Dialog.h"
#include "Custom_Multi_DataPanel.hpp"
#include "Descriptor_File_Reader.hpp"
#include "Project_Descriptions_Printer.hpp"
#include "Custom_Message_Dialog.hpp"
#include "Help_Page_Constructor.hpp"
#include "Project_File_Selection_Window.hpp"
#include "Custom_Progress_Dialog.hpp"
#include "Dependency_Tree_Printer.hpp"
#include "Custom_System_Interface.h"
#include "Cpp_FileOperations.h"


class MainFrame : public wxFrame
{
public:
  MainFrame(wxColour theme_clr);
  virtual ~MainFrame();
  void OnPaint(wxPaintEvent & event);
  void DrawBackground(wxDC& dc, wxWindow *  wnd, const wxRect& _rect);
  void PaintNow(wxWindow * wnd);
  void Open_Intro_Page(wxCommandEvent & event);
  void Show_Help_Menu(wxCommandEvent & event);
  void Select_Project_File(wxCommandEvent&);
  void Show_Project_File(wxCommandEvent&);
  void DirectoryOpen(wxCommandEvent & event);
  void Open_PopUp_Menu(wxCommandEvent & event);
  wxAuiPaneInfo Central_Pane_Info;
private:
  void OpenSettings(wxCommandEvent & event);
  void Open_Empty_Project_File(wxCommandEvent & event);
  void Enter_Header_File_Location(wxCommandEvent & event);
  void Enter_Source_File_Location(wxCommandEvent & event);
  void Enter_Library_Location(wxCommandEvent & event);
  void Enter_Git_Repo_Location(wxCommandEvent & event);
  void Enter_Main_File_Name(wxCommandEvent & event);
  void Enter_Library_Name(wxCommandEvent & event);
  void Enter_Warehouse_Location(wxCommandEvent & event);
  void Enter_Exe_File_Name(wxCommandEvent & event);
  void Enter_Standard(wxCommandEvent & event);
  void Enter_Options(wxCommandEvent & event);
  void Clear_Style(wxCommandEvent & event);
  void Reload_Default_Style(wxCommandEvent & event);
  void Set_Caret_Line_Visible(wxCommandEvent & event);
  void Set_Caret_Line_InVisible(wxCommandEvent & event);
  void Use_Block_Caret(wxCommandEvent & event);
  void Use_Default_Caret(wxCommandEvent & event);
  void Undo_Changes(wxCommandEvent & event);
  void Redo_Changes(wxCommandEvent & event);
  void Clear_Text(wxCommandEvent & event);
  void Load_Default_Cursor(wxCommandEvent & event);
  void Change_Cursor_Type(wxCommandEvent & event);
  void New_File(wxCommandEvent & event);
  void Use_Bold_Styling(wxCommandEvent & event);
  void Save_File_As(wxCommandEvent & event);
  void File_Save(wxCommandEvent & event);
  void Start_Build_System_Construction(wxCommandEvent & event);
  void Single_File_Script_Construction(wxCommandEvent & event);
  void Start_Construction_Process(wxString label, wxString dir_open, wxString start_text);
  void Descriptor_File_Selection_Check();
  void Close_Directory_Pane(wxAuiManagerEvent & event);
  void OpenTerminal(wxCommandEvent & event);
  void Increase_Font_Size(wxCommandEvent & event);
  void Decrease_Font_Size(wxCommandEvent & event);
  void Change_Font(wxCommandEvent & event);
  void Open_File(wxCommandEvent & event);
  void PrintDescriptions(wxCommandEvent & event);
  void Select_File(wxString & file_path, wxString Title);
  void Determine_Executable_File_Script_Construction_Point(wxString FileName);
  void Custom_DataPanel_Constructor(wxString Dtyp, wxString Title, wxString text, bool sel, bool status);
  void Exit(wxCommandEvent & event);
  void Single_File_Script_Construction_Executer(wxString FilePath, wxString FileName, char strategy);
  void Advance_Single_File_Script_Construction(wxCommandEvent & event);
  void OpenFile(wxCommandEvent & event);
  void Determine_Source_File_Dependencies(wxCommandEvent & event);
  void Run_Source_File_Dependency_Determination_Process(wxString FilePATH);
  void Construct_CMAKE_Build_System(wxCommandEvent & event);
  void Construct_CMAKE_Target(wxCommandEvent & event);
  void Print_File_Dependency_Output();
  void Print_File_Dependency_to_tree_control();
  void Run_Project_Script_On_Terminal(wxCommandEvent & event);
  bool Control_Build_Script_Existance();
  bool Control_Project_File_Syntax();
  void Print_Project_File_Syntax_Error();
  void Descriptor_File_Validity_Control(wxString & message);
  void Print_Lack_of_Description_Message(wxString er_message);
  void Print_Invalid_Descriptor_File_Message(wxString er_message);
  bool Child_Process_End_Status;
  bool Child_Process_Started_to_Execution;
  Custom_System_Interface SysInt;
  std::thread fork_process;
  std::thread read_process_output;
  std::thread * print_file_dependency;
  std::thread * print_to_tree_ctrl;
  std::thread * project_file_selector;
  Custom_DataPanel * data_panel_ptr;
  Custom_Multi_DataPanel * Multi_DataPanel;
  bool is_custom_panel_constructed;
  bool Memory_Delete_Condition;
  bool is_project_file_selected;
  Process_Manager * Process_Ptr;
  Custom_wxThread * Thread_Ptr;
  wxStaticBitmap * background_figure;
  wxString Descriptor_File_Path;
  wxString Warehouse_Location;
  wxString Construction_Point;
  wxString DataType;
  std::string Executable_File_Script_Construction_Point;
  wxString Exe_File_Name;
  wxString Directory_Open_Point;
  wxString Build_Script_Path;
  wxAuiDockArt * Dock_Art_Pointer;
  wxAuiManager Interface_Manager;
  Project_Descriptions_Printer * Descriptions_Printer;
  Project_File_Selection_Dialog * Selection_Dialog;
  Descriptor_File_Reader * Des_Reader;
  Custom_Tree_View_Panel * Dir_List_Manager;
  wxDataViewTreeCtrl * tree_control;
  ToolBar_Initializer * ToolBar_Widget;
  Custom_wxPanel * Custom_Main_Panel;
  Custom_Notebook * Book_Manager;
  Intro_Page_Loader * Intro_Page_Pointer;
  Custom_ProcessOutput * Process_Output;
  Custom_DataPanel * DataPanel_Pointer;
  Dependency_Tree_Printer * depPrinter;
  Dependency_Tree_Printer * dep_process_printer;
  Custom_Progress_Dialog * Progress_Dialog;
  wxBoxSizer * setting_frame_box;
  wxBoxSizer * setting_panel_box;
  wxFrame * Settting_Frame;
  Custom_Multi_DataPanel * Mt_Panel;
  bool is_build_system_constructed;
  bool is_descriptor_file_open;
  wxFont * Default_Font;
  int Process_Event_Counter;
  bool Progress_Bar_Start_status;
  wxDir    * dir_control;
  wxBitmap * exclamation_mark_bmp;
  wxBitmap * logo_bmp;
  std::condition_variable cv_fork;
  bool invalid_descriptor_file_status;
  bool lack_of_description_status;
  bool is_pipe_ready;
  int process_end_counter;
  int Toolbar_ID;
  bool is_bold_style_selected;
  std::mutex mtx;
  char opr_sis;
  DECLARE_EVENT_TABLE()
};

#endif /* MAINFRAME_H */
