

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

#ifndef WXDIRTRAVERSER_EXECUTER_H
#define WXDIRTRAVERSER_EXECUTER_H

#include <wx/dir.h>

class wxDirTraverser_executer : public wxDirTraverser
{
public:
  wxDirTraverser_executer(wxArrayString & index) : Folder_Index (index) {}

  virtual ~wxDirTraverser_executer(){

      Folder_Index.Clear();
  };

  virtual wxDirTraverseResult OnFile(const wxString & filename){

      Folder_Index.Add(filename);

      return wxDIR_CONTINUE;
  }
  virtual wxDirTraverseResult OnDir(const wxString & dirname){

    Folder_Index.Add(dirname);

    return wxDIR_CONTINUE;
  }
  virtual wxDirTraverseResult OnOpenError(const wxString &openerrorname){

    Folder_Index.Add(openerrorname);

    return wxDIR_IGNORE;
  }
private:
  wxArrayString & Folder_Index;
};

#endif /* WXDIRTRAVERSER_EXECUTER_H */
