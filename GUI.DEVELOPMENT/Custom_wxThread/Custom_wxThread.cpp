

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

#include "Custom_wxThread.hpp"

wxThread::ExitCode  Custom_wxThread::Entry()
{

  int status  = this->Process_Manager_Ptr->Get_Process_Exit_Status();

  std::unique_lock<std::mutex> lck(this->mtx);

  lck.unlock();


  lck.lock();

  if(!*this->Progress_Bar_Start_status){

      this->cv->wait(lck);

      lck.unlock();
  }
  else{

      lck.unlock();
  }

  return (wxThread::ExitCode)0;     // success
}
