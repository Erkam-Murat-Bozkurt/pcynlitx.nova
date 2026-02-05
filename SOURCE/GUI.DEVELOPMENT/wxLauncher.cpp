
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


#include <wx/wx.h>
#include <wx/aui/framemanager.h>
#include <wx/aui/aui.h>
#include <wx/aui/auibar.h>
#include <wx/aui/auibook.h>
#include <wx/aui/dockart.h>
#include <wx/dnd.h>
#include <wx/icon.h>
#include <wx/font.h>
#include <wx/splitter.h>
#include <wx/treectrl.h>
#include <wx/dirctrl.h>
#include <wx/dir.h>
#include <wx/splitter.h>
#include <wx/listbook.h>
#include <wx/listctrl.h>
#include <wx/string.h>
#include <wx/msgdlg.h>
#include <wx/display.h>
#include "MainFrame.h"
#include "Intro_Page_Loader.h"
#include "Event_ID_Numbers.h"
#include "Resource_Loader.hpp"


class wxLauncher : public wxApp
{
public:
  virtual bool OnInit();
  virtual ~wxLauncher();
  MainFrame * Frame;
  wxIcon Frame_Icon;
  wxBitmap * Frame_Bitmap;
  Resource_Loader Rsc_Loader;
};

DECLARE_APP(wxLauncher)

IMPLEMENT_APP(wxLauncher)

wxLauncher::~wxLauncher(){

    if(this->HasPendingEvents()){

       this->DeletePendingEvents();
    }

    delete this->Frame_Bitmap;
}


bool wxLauncher::OnInit(){

     this->SetExitOnFrameDelete(true);

     wxInitAllImageHandlers();

     wxImage::AddHandler(new wxPNGHandler);


     wxColour theme_colour(62,180,137);


     this->Frame = new MainFrame(theme_colour);

     if(this->Frame)
     {
         this->Frame_Bitmap = this->Rsc_Loader.CreateBitmapFromPngResource(wxString("FRAME_ICON"));

         wxIcon Frame_Icon;

         this->Frame_Icon.CopyFromBitmap(*this->Frame_Bitmap);

         this->Frame->SetIcon(this->Frame_Icon);

         this->SetTopWindow(this->Frame);

         this->Frame->SetLabel(wxT("PCYNLITX IDE AND C++ PROJECT MANAGEMENT SYSTEM"));

         this->Frame->Centre(wxBOTH);

         for(int i=0;i<5;i++){

            wxYield();

            this->Frame->Refresh();
         }

         this->Frame->Show(true);

         this->Frame->Centre(wxBOTH);

         this->Frame->SetSize(this->Frame->FromDIP(wxSize(1000,750)));

         this->Frame->SetMinSize(this->Frame->FromDIP(wxSize(975,750)));


         return true;
     }
     else{

         return false;
     }
}
