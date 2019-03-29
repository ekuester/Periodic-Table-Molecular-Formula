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
//  along with this program. If not, see <https://www.gnu.org/licenses/>.
//
//  File:   periodictablewindow.cpp
//
//  Created by Erich Kuester, Krefeld, Germany
//    Copyright © 2014 - 2019 Erich Kuester.
//          All rights reserved.
//  Last changes on March 22, 2019
 */

#include "periodictablewindow.h"
#include "about.xpm"

const char* app_title \
= N_("Gtk+: Chemistry Application - Periodic Table · Element Properties · Molecular Weight");

PeriodicTableWindow::PeriodicTableWindow(const Glib::RefPtr<Gtk::Application>& app)
:
//m_Overlay(),
  m_VBox(Gtk::ORIENTATION_VERTICAL, 3),
  m_HBox(Gtk::ORIENTATION_HORIZONTAL),
  m_MenuBar(),
  s_MenuTable(),
  //s_MenuItemLine(),
  s_MenuItemSnapshot(),
  s_MenuItemQuit(),
  s_MenuCalc(),
  s_MenuItemOpen(),
  s_MenuItemClose(),
  s_MenuItemAbout(),
  m_TableWindow(),
  m_Grid(),
  m_Dialog(),
  m_FormulaWindow(),
  m_OffscreenWindow(),
  m_PropertyWindow()
{
    //Set up window and the top-level container:
    set_title(_(app_title));
    set_default_size(1072, 596);
    m_FormulaWindow.signal_hide().connect(sigc::mem_fun(*this,\
        &PeriodicTableWindow::on_menu_calc_close));
    // menu "Table"
    m_MenuTable = Gtk::MenuItem(_("Table"));
    s_MenuItemSnapshot.add_pixlabel("16x16/camera-snapshot.png", _("Snapshot"), Gtk::Align::ALIGN_START);
    s_MenuItemSnapshot.signal_activate().connect(sigc::mem_fun(*this,\
        &PeriodicTableWindow::on_menu_table_snapshot));
    s_MenuItemQuit.add_pixlabel("16x16/application-exit.png", _("Exit"), Gtk::Align::ALIGN_START);
    s_MenuItemQuit.signal_activate().connect(sigc::mem_fun(*this,\
        &PeriodicTableWindow::on_menu_table_quit));
    //s_MenuTable.append(s_MenuItemLine);
    s_MenuTable.append(s_MenuItemSnapshot);
    s_MenuTable.append(s_MenuItemQuit);

    m_MenuTable.set_submenu(s_MenuTable);
    // menu "Calc"
    m_MenuCalc = Gtk::MenuItem(_("Calc"));
    m_MenuCalc.set_submenu(s_MenuCalc);
    s_MenuItemOpen.add_pixlabel("16x16/document-open.png", _("Open"), Gtk::Align::ALIGN_START);
    s_MenuItemOpen.signal_activate().connect(sigc::mem_fun(*this,\
        &PeriodicTableWindow::on_menu_calc_open));
    s_MenuItemClose.add_pixlabel("16x16/window-close.png", _("Close"), Gtk::Align::ALIGN_START);
    s_MenuItemClose.set_sensitive(false);
    s_MenuItemClose.signal_activate().connect(sigc::mem_fun(*this,\
        &PeriodicTableWindow::on_menu_calc_close));
    s_MenuCalc.append(s_MenuItemOpen);
    s_MenuCalc.append(s_MenuItemClose);
    // menu "Help"
    m_MenuHelp = Gtk::MenuItem(_("Help"));
    s_MenuItemAbout.add_pixlabel("16x16/help-about.png", _("Info"), Gtk::Align::ALIGN_START);
    s_MenuItemAbout.signal_activate().connect(sigc::mem_fun(*this,\
        &PeriodicTableWindow::on_menu_help_about));
    s_MenuHelp.append(s_MenuItemAbout);
    m_MenuHelp.set_submenu(s_MenuHelp);
    // set menu bar
    m_MenuBar.append(m_MenuTable);
    m_MenuBar.append(m_MenuCalc);
    m_MenuBar.append(m_MenuHelp);
    m_VBox.set_border_width(4);
    m_VBox.pack_start(m_MenuBar, Gtk::PACK_SHRINK);

    Glib::RefPtr<Gtk::CssProvider> m_LabelCssProvider = Gtk::CssProvider::create();
    m_LabelCssProvider->load_from_data(label_css);
    int i = 0;
    int p = 0;
    for (auto period : table_blueprint) {
        int g = 0;
        for (auto group : period) {
            switch (group.first) {
                case 1:
                {
                    auto element = elements[i];
                    std::stringstream text;
                    // use momentan valid locale
                    text.imbue(std::locale(""));
                    int element_ordinal = i + 1;//element[0];
                    double mass;
                    stringstream massStream(element[3]);
                    massStream >> mass; 
                    text << "<span ";
                    if (elements_radioactive.count(element_ordinal))
                        text << "foreground=\"green\"";
                    text << "size=\"small\" weight=\"bold\">";
                    text << element_ordinal << " </span>";
                    // second line
                    text << "<span rise=\"-14000\" ";
                    if (elements_gaseous.count(element_ordinal))
                        text << "foreground=\"red\"";
                    if (elements_liquid.count(element_ordinal))
                        text << "foreground=\"blue\"";
                    text << "size=\"10800\" weight=\"bold\">";
                    text << element[1] << "</span>" << std::endl;
                    // third line
                    text << "<span size=\"small\">";
                    text << std::setprecision(3) << std::fixed << mass;
                    text << "</span>";
                    //Tooltip Window:
                    Gtk::Window* tooltip_window = new Gtk::Window(Gtk::WINDOW_POPUP);
                    tooltip_window->set_default_size(144, 24);
                    //Label:
                    Gtk::Label* element_label = Gtk::manage(new Gtk::Label());
                    element_label->set_justify(Gtk::Justification::JUSTIFY_CENTER);
                    element_label->set_markup(text.str());
                    //Button:
                    Gtk::Button* element_button = Gtk::manage(new Gtk::Button());
                    element_button->set_size_request(48, 48);
                    std::string button_name = button_colors[group.second];
                    element_button->set_name(button_name);
                    Glib::RefPtr<Gtk::CssProvider> buttonCssProvider = Gtk::CssProvider::create();
                    buttonCssProvider->load_from_data(button_css);
                    element_button->get_style_context()->add_provider(\
                        buttonCssProvider, GTK_STYLE_PROVIDER_PRIORITY_USER);
                    element_button->add(*element_label);
                    // set_tooltip_window(), like set_tooltip_text()
                    // will call set_has_tooltip() for us.
                    element_button->set_tooltip_window(*tooltip_window);
                    //Button's custom tooltip window:
                    Gtk::Label* label = Gtk::manage(new Gtk::Label(element[2]));
                    label->get_style_context()->add_provider(\
                        m_LabelCssProvider, GTK_STYLE_PROVIDER_PRIORITY_USER);
                    label->show();
                    tooltip_window->add(*label);
                    element_button->signal_query_tooltip().connect(sigc::mem_fun(*this,\
                        &PeriodicTableWindow::on_button_query_tooltip));
                    element_button->signal_clicked().connect(\
                        sigc::bind<int>(sigc::mem_fun(&m_PropertyWindow,\
                            &ElementProperty::on_element_clicked), i));
                    m_Grid.attach(*element_button, g, p, 1, 1); // column g, row p
                    g++;
                    i++;
                    break;
                }
                case 0: {
                    // setup text for title
                    std::stringstream title_text;
                    title_text << "<span stretch=\"semiexpanded\" weight=\"bold\" size=\"18000\">";
                    title_text << _("··· Periodic Table of the Elements ···");
                    title_text << "</span>";
                    // empty space for title
                    Gtk::Label* title = Gtk::manage(new Gtk::Label());
                    title->set_size_request(864, 32);
                    title->set_justify(Gtk::Justification::JUSTIFY_CENTER);
                    title->set_markup(title_text.str());
                    m_Grid.attach(*title, g, p, 18, 1); // column g, row p
                    g++;
                    break;
                }
                case -1: {
                    g += 16;
                    break;
                }
                case -2: {
                    // space for legend in room above transition metals
                    // from block 3 to 12, period 1 to period 3
                    Gtk::Box *space = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL));
                    space->set_size_request(480, 144);
                    space->set_border_width(4);
                    Gtk::Image *image = Gtk::manage(new Gtk::Image(_("legend-EN-456x144.svg")));
                    space->pack_start(*image, Gtk::PackOptions::PACK_EXPAND_WIDGET);
                    m_Grid.attach(*space, g, p-1, 10, 3); // column g, row p
                    g += 10;
                    break;
                }
                case -3: {
                    // give room above transition metals
                    g += 10;
                    break;
                }
                case -4: {
                    // space for lanthanoides and actinoids
                    Gtk::Label* space = Gtk::manage(new Gtk::Label(Glib::ustring()));
                    space->set_size_request(48, 48);
                    m_Grid.attach(*space, g, p, 1, 1); // column g, row p
                    g++;
                    i += 15;
                    break;
                }
                case -5: {
                    // empty space before extra lanthanoids resp. actinoids period
                    Gtk::Label* space = Gtk::manage(new Gtk::Label(Glib::ustring()));
                    space->set_size_request(48, 12);
                    m_Grid.attach(*space, g, p, 1, 1); // column g, row p
                    g++;
                    break;
                }
                case -6: {
                    g += 2;
                    i -= 62;
                    break;
                }
                case -7: {
                    g += 2;
                    i += 17;
                    break;
                }
                default:
                    break;
            }
        }
        p++;
    }
    m_Grid.set_column_homogeneous(true);
    m_TableWindow.add(m_Grid);
    m_VBox.pack_start(m_TableWindow);

    m_Dialog.set_transient_for(*this);
    m_Dialog.set_logo(Gdk::Pixbuf::create_from_xpm_data(about));
    m_Dialog.set_program_name(_(app_title));
    m_Dialog.set_version(_("Version 1.5.2"));
    m_Dialog.set_copyright(_("Copyright © 2018 Erich Küster. All rights reserved."));
    m_Dialog.set_comments(_("Periodic Table and Molecular Formula for Chemists"));
    std::ifstream licenseFile("LICENSE");
    std::stringstream licenseStream;
    licenseStream << licenseFile.rdbuf();
    m_Dialog.set_license(licenseStream.str());
    std::ifstream commentsFile(_("COMMENTS"));
    std::stringstream commentsStream;
    commentsStream << commentsFile.rdbuf();
    m_Dialog.set_comments(commentsStream.str());

    m_Dialog.set_website("http://www.gtkmm.org");
    m_Dialog.set_website_label(_("gtkmm Website - C++ Interfaces for GTK+ and GNOME"));

    std::vector<Glib::ustring> list_authors;
    list_authors.push_back(_("Dmitri Ivanovich Mendeleev, Saint Petersburg/Russia, 6 March 1869"));
    list_authors.push_back(_("IUPAC, International Union of Pure and Applied Chemistry"));
    list_authors.push_back(_("Erich Küster, Krefeld/Germany"));
    m_Dialog.set_authors(list_authors);

    m_Dialog.signal_response().connect(sigc::mem_fun(*this,\
        &PeriodicTableWindow::on_about_dialog_response));
    
    m_OffscreenWindow.signal_damage_event().connect(sigc::mem_fun(*this,
        &PeriodicTableWindow::on_offscreen_window_damage_event));

    add(m_VBox);
    show_all_children();
}

PeriodicTableWindow::~PeriodicTableWindow() {
}

bool PeriodicTableWindow::on_button_query_tooltip(int, int, bool, const Glib::RefPtr<Gtk::Tooltip>&) {
    //we already have a custom window ready, just return true to show it:
    return true;
}

bool PeriodicTableWindow::on_offscreen_window_damage_event(GdkEventExpose *event) {   
    if (is_first_pass) {
        Glib::RefPtr<Gdk::Pixbuf> osw_pixbuf = m_OffscreenWindow.get_pixbuf()->copy();
        osw_pixbuf->save(_("PeriodicTable.png"), "png");
       // allow only one pass, otherwise an empty OffscreenWindow is stored
        is_first_pass = false;
        m_VBox.reparent(*m_parent);
        m_VBox.remove(m_Grid);
        m_TableWindow.add(m_Grid);
        m_VBox.pack_start(m_MenuBar, Gtk::PACK_SHRINK);
        m_VBox.pack_start(m_TableWindow);
    }
    return true;
}

void PeriodicTableWindow::on_menu_table_snapshot() {
    is_first_pass = true;
    m_VBox.remove(m_MenuBar);
    m_VBox.remove(m_TableWindow);
    m_TableWindow.remove();
    m_VBox.pack_start(m_Grid);
    m_parent = m_VBox.get_parent();
    m_VBox.reparent(m_OffscreenWindow);
    m_OffscreenWindow.show();
}

void PeriodicTableWindow::on_menu_table_quit() {
    hide();
}

void PeriodicTableWindow::on_menu_calc_open() {
    s_MenuItemClose.set_sensitive(true);
    s_MenuItemOpen.set_sensitive(false);
    m_FormulaWindow.present();
}

void PeriodicTableWindow::on_menu_calc_close() {
    s_MenuItemClose.set_sensitive(false);
    s_MenuItemOpen.set_sensitive(true);
    m_FormulaWindow.hide();
}

void PeriodicTableWindow::on_menu_help_about() {
    m_Dialog.show();
    //bring it to the front, in case it was already shown:
    m_Dialog.present();
}

void PeriodicTableWindow::on_about_dialog_response(int response_id) {
    switch (response_id) {
        case Gtk::RESPONSE_CLOSE:
        case Gtk::RESPONSE_CANCEL:
        case Gtk::RESPONSE_DELETE_EVENT:
            m_Dialog.hide();
            break;
        default:
            std::cout << _("Unexpected response!") << std::endl;
            break;
    }
}
