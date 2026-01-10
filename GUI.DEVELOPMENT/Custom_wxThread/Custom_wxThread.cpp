

/*
 *
 * Copyright ©  2025,  Erkam Murat Bozkurt
 *
 * This file is part of the research project which is carried by Erkam Murat Bozkurt.
 * 
 * This is a free software: you can redistribute it and/or modify it under the terms
 * of the GNU General Public License as published by the Free Software Foundation
 * either version 3 of the License, or any later version.
 * 
 * This software is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.
 *
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 *
 */



#include "Custom_wxThread.hpp"

wxThread::ExitCode  Custom_wxThread::Entry()
{

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
