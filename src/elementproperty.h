/*
//  Part of PeriodicTable - Periodic Table of the Elements
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
//  File:   elementproperty.h
//  Created on November 7, 2018, 22:31
 */

#ifndef ELEMENTPROPERTYWINDOW_H
#define ELEMENTPROPERTYWINDOW_H

#include <cstdlib>
#include <ctime>
#include <fstream>
#include <glibmm/i18n.h>
#include <gtkmm.h>
#include <iomanip>
#include <iostream>
#include <limits>
#include <locale>
#include <sstream>
#include <string>
#include "elementschema.h"

class ElementSchema;

class ElementProperty : public Gtk::Window {
public:
    ElementProperty();
    ElementProperty(const ElementProperty& orig);
    virtual ~ElementProperty();

    void on_element_clicked(int index);

protected:
    int m_ElementIndex = -1;
    std::string scheme = "https://";
    std::string wikipedia = ".wikipedia.org/wiki/";
    // Subroutines
    // Signal Handlers
    void on_button_clicked(int advance);
    // Containers
    Gtk::ScrolledWindow m_TableWindow;
    Gtk::Box m_VBox;
    Gtk::Grid m_Grid;
    Gtk::Box m_Move_HBox;
    Gtk::Box m_LeftRight_HBox;
    // Widgets
    Gtk::Button m_go_left_Button;
    Gtk::Button m_go_right_Button;
    Gtk::Label m_TitleLabel;

    std::string window_css = "\
@define-color paleazure rgb(193, 227, 255);\
@define-color serenade rgb(255, 235, 219);\
#window_azure {\
   border-radius: 4px;\
   color: black;\
   background-image: image(@paleazure);\
}";

    std::string start_svg = "\
<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"256\" height=\"256\">\
";
    std::string defs_svg = "\
  <defs>\
    <filter id=\"a\" x=\"-.072\" width=\"1.144\" y=\"-.072\" height=\"1.144\"\
    color-interpolation-filters=\"sRGB\">\
      <feGaussianBlur stdDeviation=\"3.514\" />\
    </filter>\
  </defs>\
";
    std::string rect_svg ="\
  <rect ry=\"32\" rx=\"32\" y=\"7.132\" x=\"8.145\" height=\"240\"\
  width=\"240\" fill=\"#2394da\" fill-opacity=\".939\" />\
";
    std::string transform_svg ="\
  <path transform=\"matrix(2 0 0 2 .145 -.868)\"\
  d=\"M117.139 6.861A15.94 15.94 0 01120 16v88c0 8.864-7.136 16-16 16H16a15.94 15.94 0 01-9.139-2.861A15.95 15.95 0 0020 124h88c8.864 0 16-7.136 16-16V20a15.95 15.95 0 00-6.861-13.139z\"\
  opacity=\".36\" filter=\"url(#a)\" />\
  <text style=\"line-height:1.25;-inkscape-font-specification:'Noto Sans, sans-serif'\"\
";
    std::string middle_svg = "\
  x=\"36.0\" y=\"172.0\" transform=\"scale(.99918 1.00082)\"\
  font-weight=\"700\" font-size=\"110.204\" font-family=\"Noto Sans\"\
  letter-spacing=\"0\" word-spacing=\"0\" fill=\"#dccf25\"\
  stroke-width=\"2.952\">\
    <tspan x=\"36.0\" y=\"172.0\" font-size=\"125.947\"\
    fill=\"#ffffac\">\
";
    std::string end_svg = "\
</tspan>\
  </text>\
</svg>\
";

private:
    std::vector<const char*> property_names = {
//        N_("Synonym"),
        N_("Ordinal"),
        N_("Symbol"),
        N_("Name"),
        N_("Mass"),
        N_("cpkHexColor"),
        N_("Electronic Configuration"),
        N_("Electronegativity"),
        N_("Atomic Radius [pm]"),
        N_("Ion Radius [pm]"),
        N_("van der Waals Radius [pm]"),
        N_("Ionization Energy"),
        N_("Electronaffinity"),
        N_("Oxidation States"),
        N_("State @RT"),
        N_("Bonding Type"),
        N_("Melting Point [K]"),
        N_("Boiling Point [K]"),
        N_("Density [g/m\u2113]"),
        N_("Group, Block"),
        N_("Year of Discovery"),
        N_("Further Information")
    };

    struct element {
        Glib::ustring synonym;
        int ordinal;
        std::string symbol;
        Glib::ustring name;
        double mass;
    };
};

#endif /* ELEMENTPROPERTYWINDOW_H */
