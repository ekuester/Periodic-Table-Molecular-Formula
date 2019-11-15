/*
//  Part of GTKPeriodicTable - Periodic Table of the Elements
//  Copyright (C) 2018  Erich Küster
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <https://www.gnu.org/licenses/>.
//
//  File:   periodictablewindow.h
//  Created on September 27, 2018, 18:36
 */

#ifndef GTKMM_PERIODICTABLEWINDOW_H
#define GTKMM_PERIODICTABLEWINDOW_H

#include <cstdlib>
#include <ctime>
#include <fstream>
#include <glibmm/i18n.h>
#include <gtkmm.h>
#include <iomanip>
#include <iostream>
#include <limits>
#include <locale>
#include <set>
#include <sstream>
#include <string>
#include <vector>
#include "elementproperty.h"
#include "elementschema.h"
#include "formulaparser.h"
#include "molecularformula.h"
#include "printformoperation.h"

class ElementProperty;
class ElementSchema;
class FormulaParser;
class MolecularFormula;

using namespace std;

class PeriodicTableWindow : public Gtk::Window {
public:

    PeriodicTableWindow(const Glib::RefPtr<Gtk::Application>& app);
    PeriodicTableWindow(const PeriodicTableWindow& orig);
    virtual ~PeriodicTableWindow();

protected:
    //Methods:
    void print_or_preview(Gtk::PrintOperationAction print_action);

    //Signal handlers:
    void on_about_dialog_response(int response_id);
    bool on_button_query_tooltip(int x, int y, bool keyboard_tooltip, const Glib::RefPtr<Gtk::Tooltip>& tooltip);
    bool on_offscreen_window_damage_event(GdkEventExpose *event);
    void trigger_table_snapshot();
    void on_menu_table_page_setup();
    void on_menu_table_print_export();
    void on_menu_table_print_preview();
    void on_menu_table_print();
    void on_menu_table_quit();
    void on_menu_calc_open();
    void on_menu_calc_close();
    void on_menu_help_about();

    void page_settings_setup();
    void on_printoperation_status_changed();
    void on_printoperation_done(Gtk::PrintOperationResult result);

   //Printing-related objects
    Glib::RefPtr<Gdk::Pixbuf> m_refTablePixbuf;
    Glib::RefPtr<Gtk::PageSetup> m_refPageSetup;
    Glib::RefPtr<Gtk::PrintSettings> m_refSettings;
    Glib::RefPtr<PrintFormOperation> m_refPrintFormOperation;

    // Containers
    Gtk::OffscreenWindow m_OffscreenWindow;
    Gtk::Container *m_parent;
    //Child widgets:
    Gtk::Box m_VBox;
    Gtk::Box m_HBox;
    Gtk::Box *m_Space;
    Gtk::MenuBar m_MenuBar;
    Gtk::MenuItem m_MenuTable;
    Gtk::MenuItem s_MenuItemPageSetup;
    Gtk::MenuItem s_MenuItemPrintPreview;
    Gtk::MenuItem s_MenuItemPrint;
    Gtk::SeparatorMenuItem s_MenuItemLine;
    Gtk::MenuItem s_MenuItemQuit;
    Gtk::Menu s_MenuTable;
    Gtk::MenuItem m_MenuCalc;
    Gtk::Menu s_MenuCalc;
    Gtk::MenuItem s_MenuItemOpen;    
    Gtk::MenuItem s_MenuItemClose;    
    Gtk::MenuItem m_MenuHelp;
    Gtk::Menu s_MenuHelp;
    Gtk::MenuItem s_MenuItemAbout;
    Gtk::ScrolledWindow m_TableWindow;
    Gtk::Grid m_Grid;

    std::string window_css = "\
@define-color karry rgb(255, 221, 193);\
@define-color paleazure rgb(193, 227, 255);\
#window_seashell {\
   border-radius: 4px;\
   color: black;\
   background-color: seashell;\
}\
#legend {\
   background-image: url(\"legend-EN-480x140.svg\");\
   background-size: cover;\
}";

    std::string button_css = "\
#element_yellow {\
   border-radius: 4px;\
   color: black;\
   background-color: palegoldenrod;\
   background-image: none;\
}\
#element_salmon {\
   border-radius: 4px;\
   color: black;\
   background-image: image(salmon);\
}\
#element_coral {\
   border-radius: 4px;\
   color: black;\
   background-image: image(coral);\
}\
#element_sandybrown {\
   border-radius: 4px;\
   color: black;\
   background-image: image(sandybrown);\
}\
#element_sandybrown_white {\
   border-radius: 4px;\
   color: black;\
   background: repeating-linear-gradient(\
     60deg,\
     sandybrown,\
     sandybrown 5px,\
     white 5px,\
     white 10px);\
}\
@define-color middlebrown rgb(219, 147, 86);\
#element_middlebrown {\
   border-radius: 4px;\
   color: black;\
   background-image: image(@middlebrown);\
}\
#element_middlebrown_white {\
   border-radius: 4px;\
   color: black;\
   background: repeating-linear-gradient(\
     60deg,\
     @middlebrown,\
     @middlebrown 5px,\
     white 5px,\
     white 10px);\
}\
#element_green {\
   border-radius: 4px;\
   color: black;\
   background-image: image(lightgreen);\
}\
#element_blue {\
   border-radius: 4px;\
   color: black;\
   background-image: image(lightblue);\
}\
#element_blue_white {\
   border-radius: 4px;\
   color: black;\
   background: repeating-linear-gradient(\
     60deg,\
     lightblue,\
     lightblue 5px,\
     white 5px,\
     white 10px);\
}\
#element_cyan {\
   border-radius: 4px;\
   color: black;\
   background-image: image(cyan);\
}\
#element_violet {\
   border-radius: 4px;\
   color: black;\
   background-image: image(lavender);\
}\
@define-color paleazure rgb(193, 227, 255);\
#element_azure {\
   border-radius: 4px;\
   color: black;\
   background-image: image(@paleazure);\
}\
#element_azure_white {\
   border-radius: 4px;\
   color: black;\
   background: repeating-linear-gradient(\
     60deg,\
     @paleazure,\
     @paleazure 5px,\
     white 5px,\
     white 10px);\
}\
#element_yellow:hover,\
#element_salmon:hover,\
#element_coral:hover,\
#element_sandybrown:hover,\
#element_sandybrown_white:hover,\
#element_middlebrown:hover,\
#element_middlebrown_white:hover,\
#element_green:hover,\
#element_blue:hover,\
#element_blue_white:hover,\
#element_cyan:hover,\
#element_violet:hover,\
#element_azure:hover,\
#element_azure_white:hover {\
   background-image: image(firebrick);\
   color: white;\
}\
#element_yellow:active,\
#element_salmon:active,\
#element_coral:active,\
#element_sandybrown:active,\
#element_sandybrown_white:active,\
#element_middlebrown:active,\
#element_middlebrown_white:active,\
#element_green:active,\
#element_blue:active,\
#element_blue_white:active,\
#element_cyan:active,\
#element_violet:active,\
#element_azure:active,\
#element_azure_white:active {\
  background-image: image(orange);\
  color: white;\
}";
    Glib::RefPtr<Gtk::CssProvider> m_LabelCssProvider;
    std::string label_css = "\
label {\
  border-radius: 4px;\
  background-color: firebrick;\
  color: white;\
}";

    Gtk::AboutDialog m_Dialog;
    // child windows
    MolecularFormula m_FormulaWindow;
    ElementProperty m_PropertyWindow;

private:
    bool is_first_pass = false;
    std::set< int > elements_radioactive = {
        43, 61,
        83, 84, 85, 86, 87, 88,
        89, 90, 91, 92, 93, 94,
        95, 96, 97, 98, 99,100,
       101,102,103,104,105,106,
       107,108,109,110,111,112,
       113,114,115,116,117,118
    };
    std::set< int > elements_gaseous = {
        1, 2, 7, 8, 9, 10, 17, 18, 36, 54, 86, 118
    };
    std::set< int > elements_liquid = {
        35, 80
    };
    std::vector< std::string > button_colors = {
        "element_green",
        "element_coral",
        "element_salmon",
        "element_yellow",
        "element_violet",
        "element_blue",
        "element_sandybrown",
        "element_middlebrown",
        "element_azure",
        "element_cyan",
        "element_blue_white",
        "element_azure_white",
        "element_sandybrown_white",
        "element_middlebrown_white",
    };
    std::vector< std::vector< std::pair<int,int> > > table_blueprint = {
        {{ 1,0},{ 0,0}},
        {{ 1,0},{ 2,1},{-1,0},{2,18}},
        {{ 1,1},{ 3,0},{ 2,2},{-3,0},{2,13},{2,14},{2,15},{2,16},{2,17},{ 3,4}},
        {{ 1,2},{ 3,1},{ 3,2},{-2,0},{ 3,9},{ 3,0},{ 3,0},{ 3,0},{ 3,3},{ 3,4}},
        {{ 1,3},{ 3,1},{ 3,2},{-3,0},{ 3,8},{ 3,9},{ 3,0},{ 3,0},{ 3,3},{ 3,4}},
        {{ 1,4},{ 3,1},{ 3,2},{ 3,5},{ 3,5},{ 3,5},{ 3,5},{ 3,5},{ 3,5},{ 3,5},
         { 3,5},{ 3,5},{ 3,5},{ 3,8},{ 3,9},{ 3,9},{ 3,0},{ 3,3},{ 3,4}},
        {{ 1,5},{ 3,1},{ 3,2},{ 3,5},{ 3,5},{ 3,5},{ 3,5},{3,10},{ 3,5},{ 3,5},
         { 3,5},{ 3,5},{ 3,5},{ 3,8},{ 3,8},{ 3,9},{ 3,9},{ 3,3},{ 3,4}},
        {{ 1,6},{ 3,1},{ 3,2},{-4,0},{ 3,5},{ 3,5},{ 3,5},{ 3,5},{ 3,5},{ 3,5},
         { 3,5},{ 3,5},{ 3,5},{ 3,8},{ 3,8},{ 3,8},{ 3,9},{ 3,3},{ 3,4}},
        {{ 1,7},{ 3,1},{ 3,2},{-4,0},{3,10},{3,10},{3,10},{3,10},{3,10},{3,10},
         {3,10},{3,10},{3,10},{3,11},{3,11},{3,11},{3,11},{3,11},{3,11}},
        {{ 1,0},{-5,0}},
        {{ 1,0},{-6,0},{ 3,5},{ 3,6},{ 3,6},{ 3,6},{3,12},{ 3,6},{ 3,6},
         { 3,6},{ 3,6},{ 3,6},{ 3,6},{ 3,6},{ 3,6},{ 3,6},{ 3,6}},
        {{ 1,0},{-7,0},{ 3,5},{ 3,7},{ 3,7},{ 3,7},{3,13},{3,13},{3,13},
         {3,13},{3,13},{3,13},{3,13},{3,13},{3,13},{3,13},{3,13}}
    };
};

#endif // GTKMM_PERIODICTABLEWINDOW_H
