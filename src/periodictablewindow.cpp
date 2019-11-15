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
//  Last changes on November 14, 2019 for version 1.6.3
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
  s_MenuItemPageSetup(),
  s_MenuItemPrintPreview(),
  s_MenuItemPrint(),
  s_MenuItemLine(),
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
    // Set up window and the top-level container
    // set background image of window
    set_name("window_seashell");
    Glib::RefPtr<Gtk::CssProvider> windowCssProvider = Gtk::CssProvider::create();
    windowCssProvider->load_from_data(window_css);
    get_style_context()->add_provider(\
        windowCssProvider, GTK_STYLE_PROVIDER_PRIORITY_USER);
    set_title(_(app_title));
    m_FormulaWindow.signal_hide().connect(sigc::mem_fun(*this,\
        &PeriodicTableWindow::on_menu_calc_close));
    // menu "Table"
    m_MenuTable = Gtk::MenuItem(_("Table"));
    s_MenuItemPageSetup.add_pixlabel("16x16/document-page-setup.png", _("Page Setup"), Gtk::Align::ALIGN_START);
    s_MenuItemPageSetup.signal_activate().connect(sigc::mem_fun(*this,\
        &PeriodicTableWindow::on_menu_table_page_setup));
    s_MenuItemPrintPreview.add_pixlabel("16x16/document-print-preview.png", _("Print Preview"), Gtk::Align::ALIGN_START);
    s_MenuItemPrintPreview.signal_activate().connect(sigc::mem_fun(*this,\
        &PeriodicTableWindow::on_menu_table_print_preview));
    s_MenuItemPrint.add_pixlabel("16x16/document-print.png", _("Print..."), Gtk::Align::ALIGN_START);
    s_MenuItemPrint.signal_activate().connect(sigc::mem_fun(*this,\
        &PeriodicTableWindow::on_menu_table_print));
    s_MenuItemQuit.add_pixlabel("16x16/application-exit.png", _("Exit"), Gtk::Align::ALIGN_START);
    s_MenuItemQuit.signal_activate().connect(sigc::mem_fun(*this,\
        &PeriodicTableWindow::on_menu_table_quit));
    s_MenuTable.append(s_MenuItemPageSetup);
    s_MenuTable.append(s_MenuItemPrintPreview);
    s_MenuTable.append(s_MenuItemPrint);
    s_MenuTable.append(s_MenuItemLine);
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
    s_MenuItemAbout.add_pixlabel("16x16/help-about.png", _("About"), Gtk::Align::ALIGN_START);
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
                case 3:
                {
                    auto element = elements[i];
                    std::stringstream text;
                    // use momentan valid locale
                    text.imbue(std::locale(""));
                    int element_ordinal = i + 1;
                    double mass;
                    stringstream massStream(element[4]);
                    massStream >> mass; 
                    text << "<span ";
                    if (elements_radioactive.count(element_ordinal))
                        text << "foreground=\"green\"";
                    else
                        text << "foreground=\"black\"";
                    text << "size=\"small\" weight=\"bold\">";
                    text << element_ordinal << " </span>";
                    // second line
                    text << "<span rise=\"-14000\" ";
                    if ((elements_gaseous.count(element_ordinal))\
                        || (elements_liquid.count(element_ordinal))) {
                        if (elements_gaseous.count(element_ordinal))
                            text << "foreground=\"red\"";
                        else
                            text << "foreground=\"blue\"";
                    }
//                    else
//                        text << "foreground=\"black\"";
                    text << "size=\"10800\" weight=\"bold\">";
                    text << element[2] << "</span>" << std::endl;
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
                    // buttons can expand horizontally and vertically
                    //element_button->set_hexpand(Gtk::EXPAND);
                    //element_button->set_vexpand(Gtk::EXPAND);
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
                    Gtk::Label* label = Gtk::manage(new Gtk::Label(element[0]));
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
                case 2: {
                    // write number of group
                    stringstream s;
                    s << "<span weight=\"bold\" foreground=\"black\">" << group.second << "</span>";
                    Gtk::Label* g_l = Gtk::manage(new Gtk::Label(Glib::ustring()));
                    g_l->set_markup(s.str());
                    Gtk::Box *g_b = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL));
                    g_b->set_size_request(48,12);
                    g_b->pack_end(*g_l, false, false, 4);
                    m_Grid.attach(*g_b, g, p, 1, 1); // column g, row p
                    g++;
                    break;
                }
                case 1: {
                    if (group.second > 0) {
                        // write number of period
                        stringstream s;
                        s << "<span weight=\"bold\" foreground=\"black\">" << group.second << "</span>";
                        Gtk::Label* p_l = Gtk::manage(new Gtk::Label());
                        p_l->set_markup(s.str());
                        Gtk::Box *p_b = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL));
                        p_b->set_size_request(8,48);
                        p_b->pack_end(*p_l, false, false, 4);
                        m_Grid.attach(*p_b, g, p, 1, 1);
                    }
                    g++;
                    break;
                }
                case 0: {
                    // setup text for title
                    std::stringstream title_text;
                    title_text << "<span stretch=\"expanded\" weight=\"bold\" size=\"18000\" ";
                    title_text << "foreground=\"black\">";
                    title_text << _("—  Periodic Table of the Elements  —");
                    title_text << "</span>";
                    // empty space for title
                    Gtk::Label* title = Gtk::manage(new Gtk::Label());
                    //title->set_size_request(480, 32);
                    title->set_justify(Gtk::Justification::JUSTIFY_CENTER);
                    title->set_markup(title_text.str());
                    m_Grid.attach(*title, 1, p, 18, 1);
                    break;
                }
                case -1: {
                    g += 16;
                    break;
                }
                case -2: {
                    // space for legend in room above transition metals
                    // from block 3 to 12, period 1 to period 3
                    m_Space = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL));
                    m_Space->set_size_request(480, 144);
                    //m_Space->set_border_width(4);
                    m_Space->set_name("legend");
                    Glib::RefPtr<Gtk::CssProvider> legendCssProvider = Gtk::CssProvider::create();
                    std::string image_url = _("legend-EN-480x140.svg");
                    stringstream legend;
                    legend << "#legend {background-image: url(\"" << image_url \
                        << "\"); background-size: cover; }";
                    std::string legend_css = legend.str();
                    legendCssProvider->load_from_data(legend_css);
                    m_Space->get_style_context()->add_provider(\
                        legendCssProvider, GTK_STYLE_PROVIDER_PRIORITY_USER);
                    m_Grid.attach(*m_Space, g, p-1, 10, 3); // column g, row p
                    g += 10;
                    break;
           }
                case -3: {
                    // give room above transition metals
                    g += 10;
                    break;
                }
                case -4: {
                    // space for lanthanides and actinides
                    Gtk::Label* space = Gtk::manage(new Gtk::Label(Glib::ustring()));
                    space->set_size_request(48, 48);
                    m_Grid.attach(*space, g, p, 1, 1); // column g, row p
                    g++;
                    i += 15;
                    break;
                }
                case -5: {
                    // empty space before extra lanthanides resp. actinides period
                    Gtk::Label* space = Gtk::manage(new Gtk::Label(Glib::ustring()));
                    space->set_size_request(48, 12);
                    m_Grid.attach(*space, g, p, 1, 1); // column g, row p
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
    m_Grid.set_column_homogeneous(false);
    m_Grid.set_row_homogeneous(false);
    m_TableWindow.set_min_content_width(616);
    m_TableWindow.set_min_content_height(616);
    m_TableWindow.add(m_Grid);
    m_TableWindow.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    m_VBox.pack_start(m_TableWindow);

    m_Dialog.set_transient_for(*this);
    m_Dialog.set_logo(Gdk::Pixbuf::create_from_xpm_data(about));
    m_Dialog.set_program_name(_(app_title));
    m_Dialog.set_version(_("Version 1.6.3"));
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
    list_authors.push_back(_("Dmitri Ivanovich Mendeleev, Saint Petersburg / Russia, 6 March 1869"));
    list_authors.push_back(_("IUPAC, International Union of Pure and Applied Chemistry"));
    list_authors.push_back(_("Erich Küster, Krefeld / Germany"));
    m_Dialog.set_authors(list_authors);

    m_Dialog.signal_response().connect(sigc::mem_fun(*this,\
        &PeriodicTableWindow::on_about_dialog_response));
    // no background color
    m_OffscreenWindow.set_app_paintable(true);
    m_OffscreenWindow.set_decorated(false);
    m_OffscreenWindow.signal_damage_event().connect(sigc::mem_fun(*this,
        &PeriodicTableWindow::on_offscreen_window_damage_event));

    add(m_VBox);
    show_all_children();
    present();
    move(64,96);
}

PeriodicTableWindow::~PeriodicTableWindow() {
}

bool PeriodicTableWindow::on_button_query_tooltip(int, int, bool, const Glib::RefPtr<Gtk::Tooltip>&) {
    //we already have a custom window ready, just return true to show it:
    return true;
}

bool PeriodicTableWindow::on_offscreen_window_damage_event(GdkEventExpose *event) {
    if (is_first_pass) {
        m_refTablePixbuf = m_OffscreenWindow.get_pixbuf()->copy();
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

void PeriodicTableWindow::on_printoperation_status_changed()
{
    Glib::ustring status_msg;

    if (m_refPrintFormOperation->is_finished())
    {
        status_msg = "Print job completed.";
    }
    else
    {
        //You could also use get_status().
        status_msg = m_refPrintFormOperation->get_status_string();
    }
//    no status bar in the moment
//    m_ContextId = m_Statusbar.push(status_msg, m_ContextId);
	std::cout << status_msg << std::endl;
}

void PeriodicTableWindow::on_printoperation_done(Gtk::PrintOperationResult result)
{
    //Printing is "done" when the print data is spooled.
    if (result == Gtk::PRINT_OPERATION_RESULT_ERROR)
    {
        Gtk::MessageDialog err_dialog(*this, "Error printing form", false,
            Gtk::MESSAGE_ERROR, Gtk::BUTTONS_OK, true);
        err_dialog.run();
    }
    else if (result == Gtk::PRINT_OPERATION_RESULT_APPLY)
    {
        //Update PrintSettings with the ones used in this PrintOperation:
        m_refSettings = m_refPrintFormOperation->get_print_settings();
    }

    if (!m_refPrintFormOperation->is_finished())
    {
        //We will connect to the status-changed signal to track status
        //and update a status bar. In addition, you can, for example,
        //keep a list of active print operations, or provide a progress dialog.
        m_refPrintFormOperation->signal_status_changed().connect(sigc::mem_fun(*this,
                &PeriodicTableWindow::on_printoperation_status_changed));
    }
}

void PeriodicTableWindow::page_settings_setup() {
    //Create a new PrintOperation with PageSetup and PrintSettings:
    if (!m_refPageSetup) {
        m_refPageSetup = Gtk::PageSetup::create();
        m_refPageSetup->set_orientation(Gtk::PAGE_ORIENTATION_LANDSCAPE);
    }
    if (!m_refSettings) {
        m_refSettings = Gtk::PrintSettings::create();
        // set landscape and 300 dpi in print settings
        m_refSettings->set_orientation(Gtk::PAGE_ORIENTATION_LANDSCAPE);
        m_refSettings->set_resolution(300);
    }
}

void PeriodicTableWindow::print_or_preview(Gtk::PrintOperationAction print_action) {
    page_settings_setup();
    m_refPrintFormOperation = PrintFormOperation::create();
    m_refPrintFormOperation->set_default_page_setup(m_refPageSetup);
    // if using PRINT_OPERATION_ACTION_EXPORT
    m_refPrintFormOperation->set_export_filename("PeriodicTable.pdf");
    // only one page should be printed
    m_refPrintFormOperation->set_n_pages(1);
    // pixel buffer to print
    m_refPrintFormOperation->set_pixbuf(m_refTablePixbuf);
    m_refPrintFormOperation->set_print_settings(m_refSettings);
    m_refPrintFormOperation->set_track_print_status();
    m_refPrintFormOperation->set_use_full_page(true);
    m_refPrintFormOperation->signal_done().connect(sigc::mem_fun(*this,
            &PeriodicTableWindow::on_printoperation_done));
    try {
        // run preview or print
        m_refPrintFormOperation->run(print_action, *this);
    } catch (const Gtk::PrintError& ex) {
        //See documentation for exact Gtk::PrintError error codes.
        std::cerr << "An error occurred while trying to run a print operation:"
                << ex.what() << std::endl;
    }
}

void PeriodicTableWindow::on_menu_table_page_setup() {
    page_settings_setup();
    //Show the page setup dialog, asking it to start with the existing settings:
    auto new_page_setup =
            Gtk::run_page_setup_dialog(*this, m_refPageSetup, m_refSettings);

    //Save the chosen page setup dialog for use when printing, previewing, or
    //showing the page setup dialog again:
    m_refPageSetup = new_page_setup;
}

void PeriodicTableWindow::trigger_table_snapshot() {
    is_first_pass = true;
    m_VBox.remove(m_MenuBar);
    m_VBox.remove(m_TableWindow);
    m_TableWindow.remove();
    m_VBox.pack_start(m_Grid);
    m_parent = m_VBox.get_parent();
    m_VBox.reparent(m_OffscreenWindow);
    m_OffscreenWindow.show();
    // must wait as long as events are pending otherwise program crashes
    while (Gtk::Main::events_pending()) {
        Gtk::Main::iteration(true);
    }
}

// not implemented yet
void PeriodicTableWindow::on_menu_table_print_export() {
    trigger_table_snapshot();
    print_or_preview(Gtk::PRINT_OPERATION_ACTION_EXPORT);
}

void PeriodicTableWindow::on_menu_table_print_preview() {
    trigger_table_snapshot();
    print_or_preview(Gtk::PRINT_OPERATION_ACTION_PREVIEW);
}

void PeriodicTableWindow::on_menu_table_print() {
    trigger_table_snapshot();
    print_or_preview(Gtk::PRINT_OPERATION_ACTION_PRINT_DIALOG);
}
