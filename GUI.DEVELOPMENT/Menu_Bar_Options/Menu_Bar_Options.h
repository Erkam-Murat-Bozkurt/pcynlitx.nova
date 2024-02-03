
#ifndef MENU_BAR_OPTIONS_H
#define MENU_BAR_OPTIONS_H

#include <wx/wx.h>
#include <wx/frame.h>
#include <wx/menu.h>
#include <wx/menuitem.h>
#include <wx/string.h>
#include <wx\font.h>
#include <wx\fontdata.h>
#include <wx\fontdlg.h>
#include <wx\menuitem.h>

#include "Event_ID_Numbers.h"

class Menu_Bar_Options
{
public:
  Menu_Bar_Options();
  virtual ~Menu_Bar_Options();
  wxMenuBar * Get_MenuBar();
private:
  wxMenu  * Construction_Menu;
  wxMenu  * Help_Menu;;
  wxMenu  * File_Menu;
  wxMenu  * Project_Management;
  wxMenu  * Library_Description_Menu;
  wxMenu  * Edit_Menu;
  wxMenuBar * Menu_Bar;
};

#endif /* MENU_BAR_OPTIONS_H */
