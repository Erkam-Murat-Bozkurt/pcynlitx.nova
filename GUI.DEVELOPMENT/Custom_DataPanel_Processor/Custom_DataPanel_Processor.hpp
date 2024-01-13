





#ifndef CUSTOM_DATAPANEL_PROCESSOR_HPP
#define CUSTOM_DATAPANEL_PROCESSOR_HPP

#include <wx\wx.h>
#include <wx\sizer.h>
#include <wx\event.h>
#include <wx\aui\aui.h>
#include <wx\aui\framemanager.h>
#include <wx\sizer.h>
#include <wx\dataview.h>
#include <wx\textdlg.h>
#include <wx\msgdlg.h>
#include "Process_Manager.hpp"
#include "Custom_DataPanel.hpp"

class Custom_DataPanel_Processor
{
public:
    Custom_DataPanel_Processor(wxFrame * frame, wxString DataType, wxString Title, 

     wxString Column_Text, bool file_selection, bool text_enter_status);

    virtual ~Custom_DataPanel_Processor();

    void Receive_Descriptor_File_Path(wxString DesPATH);

protected:
    Custom_DataPanel * DataPanel_Pointer;
    wxString DataType;
};


#endif /* CUSTOM_DATAPANEL_PROCESSOR_HPP */
