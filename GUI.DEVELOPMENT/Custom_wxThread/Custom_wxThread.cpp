
#include "Custom_wxThread.hpp"

wxThread::ExitCode  Custom_wxThread::Entry()
{

  int Proc_ID = this->Process_Manager_Ptr->GetPid();

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

  this->Process_Manager_Ptr->OnTerminate(Proc_ID,status);

  return (wxThread::ExitCode)0;     // success
}
