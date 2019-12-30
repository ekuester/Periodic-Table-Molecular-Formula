/* 
 * Part of PeriodicTable - Periodic Table of the Elements
 * File:   molecularformula.h
 * Author: kuestere
 *
 * Created on 27. September 2018, 18:36
 * Last changes on November 9, 2019
 */

#ifndef MOLECULARFORMULA_H
#define MOLECULARFORMULA_H

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
#include "formulaparser.h"
#include "elementschema.h"

using namespace std;

class FormulaParser;
class ElementSchema;

class MolecularFormula : public Gtk::Window {
public:
    MolecularFormula();
    MolecularFormula(const MolecularFormula& orig);
    virtual ~MolecularFormula();

private:

protected:
    std::vector<Glib::ustring> m_StatusMessages = {
        N_("Place holder, no error"),
        N_("No formula entered"),
        N_("Element symbol expected"),
        N_("No valid element symbol (actual not in table)"),
        N_("Too many bond signs"),
        N_("Bond sign misplaced here"),
        N_("Closing ) missing"),
        N_("Closing ] missing"),
        N_("Index 0 not allowed"),
        N_("Molecular weight is too big")
    };
    int errorAlert(int messageNumber);

    //Signal handlers for entries and buttons
    void on_activated();

    //Child widgets:
    Gtk::Box m_VBox;
    Gtk::Grid m_Grid;

    Gtk::Label m_InputLabel;
    Gtk::Entry m_InputEntry;

    Gtk::Label m_FormulaLabel;
    Gtk::Entry m_FormulaEntry;

    Gtk::Label m_WeightLabel;
    Gtk::Entry m_WeightEntry;

    Gtk::ScrolledWindow m_TextWindow;
    Gtk::Frame m_TextFrame;
    Gtk::TextView m_TextView;
    Glib::RefPtr<Gtk::TextBuffer> m_refTextBuffer;

    std::string icon_svg = "\
<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"256\" height=\"256\">\
  <defs>\
    <filter id=\"a\" x=\"-.072\" width=\"1.144\" y=\"-.072\" height=\"1.144\"\
    color-interpolation-filters=\"sRGB\">\
      <feGaussianBlur stdDeviation=\"3.514\" />\
    </filter>\
  </defs>\
  <g transform=\"translate(0 240)\">\
    <rect width=\"240\" height=\"240\" x=\"8.145\" y=\"-232.868\" rx=\"32\"\
    ry=\"32\" fill-opacity=\".937\" fill=\"#2394da\" />\
    <path d=\"M117.139 6.861A15.94 15.94 0 01120 16v88c0 8.864-7.136 16-16 16H16a15.94 15.94 0 01-9.139-2.861A15.95 15.95 0 0020 124h88c8.864 0 16-7.136 16-16V20a15.95 15.95 0 00-6.861-13.139z\"\
    transform=\"matrix(2 0 0 2 .145 -240.868)\" opacity=\".36\"\
    filter=\"url(#a)\" />\
    <path d=\"M68.913-186.312l.117 4.436 54.505 67.83-55.11 65.456-.158 4.122 106.862-.553c1.044-13.203 3.91-26.855 6.367-39.873l-3.473-.867c-3.236 7.29-5.537 15.085-12.445 19.925-7.573 5.306-17.566 4.635-26.337 4.635h-49.2l50.152-60.48-45.22-56.436 26.324-.104c16.876 0 40.882-4.07 47.56 16.18 1.141 3.462 1.933 7.056 2.22 10.69h3.762l-2.894-34.96z\"\
    font-size=\"12\" fill=\"#dccf25\" />\
  </g>\
</svg>\
";
    std::string window_css = "\
#window_seashell {\
   border-radius: 4px;\
   color: black;\
   background-color: seashell;\
}\
#frame_seashell {\
   border-radius: 4px;\
   color: black;\
   background-color: seashell;\
}\
#view_seashell text {\
   border-radius: 0px;\
   color: black;\
   background-color: seashell;\
}";

};

#endif /* MOLECULARFORMULA_H */
