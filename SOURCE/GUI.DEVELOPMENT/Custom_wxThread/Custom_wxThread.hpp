
#ifndef CUSTOM_WXTHREAD_HPP
#define CUSTOM_WXTHREAD_HPP

#include <wx\wx.h>
#include <wx\frame.h>
#include <wx\panel.h>
#include <wx\thread.h>
#include <string>
#include <mutex>
#include <condition_variable>
#include "Process_Manager.hpp"
#include "Event_ID_Numbers.h"

class Custom_wxThread : public wxThread
{
public:
    Custom_wxThread(Process_Manager * Pr_Man, bool * status,

      std::condition_variable * cond_vr) : wxThread(wxTHREAD_DETACHED)
    {
      this->Process_Manager_Ptr = Pr_Man;

      this->Progress_Bar_Start_status = status;

      this->cv = cond_vr;
    };

    ~Custom_wxThread(){ };

protected:
    virtual ExitCode Entry();

    Process_Manager * Process_Manager_Ptr;

    bool * Progress_Bar_Start_status;

    std::mutex mtx;

    std::condition_variable * cv;
};

#endif /* CUSTOM_WXTHREAD_HPP */
