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
//  File:   ElementPropertyWindow.cpp
//  Created on November 7 2018, 22:31
 */

#include "elementproperty.h"

using namespace std;

ElementProperty::ElementProperty()
: m_VBox(Gtk::ORIENTATION_VERTICAL),
  m_TitleLabel(),
  m_TableWindow(),
  m_Grid(),
  m_Move_HBox(Gtk::Orientation::ORIENTATION_HORIZONTAL),
  m_LeftRight_HBox(Gtk::Orientation::ORIENTATION_HORIZONTAL)
{
    // set background color
    set_name("window_azure");
    Glib::RefPtr<Gtk::CssProvider> windowCssProvider = Gtk::CssProvider::create();
    windowCssProvider->load_from_data(window_css);
    get_style_context()->add_provider(\
        windowCssProvider, GTK_STYLE_PROVIDER_PRIORITY_USER);
    set_title(_("Gtk+: Application - Element Properties"));
    set_border_width(4);
    set_type_hint(Gdk::WindowTypeHint::WINDOW_TYPE_HINT_DIALOG);
    // set position of window
    move(512, 64);
    m_VBox.pack_start(m_TitleLabel, Gtk::PackOptions::PACK_SHRINK);
    m_Grid.set_column_spacing(8);
    // Add the Grid, inside a ScrolledWindow
    m_TableWindow.add(m_Grid);
    // Only show the scrollbars when they are necessary:
    m_TableWindow.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    m_VBox.pack_start(m_TableWindow);
    m_VBox.set_border_width(8);
    m_go_left_Button.signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this,\
        &ElementProperty::on_button_clicked), -1));
    m_go_right_Button.signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this,\
        &ElementProperty::on_button_clicked), 1));
    m_LeftRight_HBox.pack_start(m_go_left_Button, Gtk::PackOptions::PACK_SHRINK);
    m_LeftRight_HBox.pack_start(m_go_right_Button, Gtk::PackOptions::PACK_SHRINK);
    // style
    m_LeftRight_HBox.get_style_context()->add_class("raised");
    m_LeftRight_HBox.get_style_context()->add_class("linked");
    // Buttons
    m_go_left_Button.set_image_from_icon_name("go-previous-symbolic", Gtk::ICON_SIZE_BUTTON, true);
    m_go_right_Button.set_image_from_icon_name("go-next-symbolic", Gtk::ICON_SIZE_BUTTON, true);
    m_Move_HBox.pack_start(m_LeftRight_HBox, Gtk::PackOptions::PACK_EXPAND_PADDING);
    m_VBox.pack_start(m_Move_HBox, Gtk::PackOptions::PACK_SHRINK);
    // build first column with names of properties
    int row = 0;
    for (auto name : property_names) {
        Gtk::Label* left = Gtk::manage(new Gtk::Label(_(name), Gtk::ALIGN_START));
        left->set_hexpand(Gtk::EXPANDER_SEMI_EXPANDED);
        left->set_margin_right(8);
        left->set_margin_right(8);
        left->set_vexpand(Gtk::EXPANDER_COLLAPSED);
        m_Grid.attach(*left, 0, row, 1, 1); // column 0, row row
        row++;
    }
}

ElementProperty::ElementProperty(const ElementProperty& orig) {
}

ElementProperty::~ElementProperty() {
}

#define ELEMENT_NAME_INDEX 3
#define ELEMENT_NAME_ROW 2
void ElementProperty::on_element_clicked(int index) {
    // place to give more information about the specific element
    if (m_ElementIndex >= 0) {
        remove();
        m_Grid.remove_column(1);
    }
    m_ElementIndex = index;
    auto element = elements[index];
    stringstream title;
    title << "<b>" << setw(48) << element[0] << setw(48) << "</b>";
    m_TitleLabel.set_markup(title.str());
    m_TitleLabel.set_margin_bottom(8);
    // Get the name of the current locale
    std::locale current("");
    char decimal = use_facet<numpunct<char> > (current).decimal_point(); 
    auto element_name = std::string(_(element[ELEMENT_NAME_INDEX].data()));
    int row = 0;
    // iterator over vector of strings
    auto value = element.begin();
    bool loop = true;
    while (loop) {
        value++;
        Gtk::Label* right = Gtk::manage(new Gtk::Label());
        right->set_alignment(Gtk::ALIGN_START);
        right->set_hexpand(Gtk::EXPANDER_SEMI_EXPANDED);
        right->set_vexpand(Gtk::EXPANDER_COLLAPSED);
        if (value != element.end()) {
            if (!(*value).empty()) {
                std::string label;
                if (row == ELEMENT_NAME_ROW) {
                    // look for anomalies in element name
                    auto pos = element_name.find('_');
                    label = element_name.substr(0, pos);
                } else {
                    // look for decimal point
                    auto pos = (*value).find('.');
                    if (pos != std::string::npos) {
                        label = (*value).substr(0, pos)
                            + decimal
                            + (*value).substr(pos+1);
                        right->set_label(label);
                    } else {
                        label = std::string(_((*value).data()));
                    }
                }
                right->set_label(label);
            }
        } else {
            stringstream url;
            url << scheme << _("en") << wikipedia << element_name; 
            stringstream wiki;
            wiki << _("see <a href=\"") << url.str() << "\" title=\""
                << url.str() << _("\">Wikipedia</a> article");
            right->set_markup(wiki.str());
            loop = false;            
        }
        m_Grid.attach(*right, 1, row, 1, 1); // column 1, row row
        row++;
    }
    add(m_VBox);
    show_all_children();
    present();
    // now set property window size, works well in hiDPI environment
    // we need 25 lines
    int height = m_TitleLabel.get_height() * 25;
    set_size_request(m_TitleLabel.get_width(), height);
}

void ElementProperty::on_button_clicked(int advance) {
    int index = m_ElementIndex + advance;
    if ((index >= 0) && (index < elements.size())) {
        on_element_clicked(index);
    }
}
