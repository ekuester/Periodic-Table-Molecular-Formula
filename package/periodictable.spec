%define        name Periodic-Table-Molecular-Formula
%define        alias periodictable
%define        version 1.7.0
%define        release 1
Summary:    Periodic Table of the Elements for Chemists
Name:       %{name}
Version:    %{version}
Release:    %{release}
License:    GPLv3+
Group:      Applications/Science
URL:        https://github.com/ekuester/Periodic-Table-Molecular-Formula
Source0:    %{name}-%{version}.tar.gz
BuildRoot:  %{_tmppath}/%{alias}-%{version}-%{release}-root-%(%{__id_u} -n)
Requires:    cairo
Requires:    cairo-gobject
Requires:    gtk3
Requires:    pango
Buildrequires:    cairo-devel
Buildrequires:    gtkmm30-devel
Buildrequires:    pango-devel

%description
PeriodicTable is a free open source Linux program for browsing the
Periodic Table of the elements ( PTE ) combined with information about
elements and calculation of molecular formulas and their molecular weight
(also named molar mass), additionally the amount of the contained
elements in percent is calculated.

%prep
%setup -q

%build
./autogen.sh --prefix=%{_prefix}
make %{?_smp_mflags}

%install
rm -rf $RPM_BUILD_ROOT

make install DESTDIR=$RPM_BUILD_ROOT PREFIX=%{_prefix}

# let's build our own desktop entry, on-the-fly:
echo -e "[Desktop Entry]
Type=Application
Version=1.1
Name=Periodic Table
Name[de]=Periodensystem
Name[fr]=Tableau périodique des éléments
Name[it]=Tavola periodica
Name[nl]=Periodiek Systeem
Comment=Periodic table with molecular weight calculator
Comment[de]=Periodensystem mit Rechner für Summenformeln
Comment[fr]=Tableau périodique avec un calculateur de poids moléculaire
Comment[it]=Tavola periodica con un calcolatore per peso moleculare
Comment[nl]=Periodiek Systeem met een calculator van somformules
Exec=gnome-terminal --geometry=16x5 --hide-menubar --working-directory=/usr/share/gtkperiodictable --command=./GTKPeriodicTable
Icon=periodictable
Categories=Education;Science;Chemistry;Math
StartupNotify=true
Terminal=true" > %{alias}.desktop
                                                                               
desktop-file-install --vendor "" --delete-original \
  --dir $RPM_BUILD_ROOT%{_datadir}/applications \
  --add-category Education \
  --add-category Science \
  --add-category Chemistry \
  --add-category Math \
  %{alias}.desktop

mkdir -p $RPM_BUILD_ROOT%{_datadir}/pixmaps/
install -m 644 periodictable.svg $RPM_BUILD_ROOT%{_datadir}/pixmaps/
desktop-file-validate $RPM_BUILD_ROOT%{_datadir}/applications/%{alias}.desktop

%clean
rm -rfv $RPM_BUILD_ROOT

%files
%defattr(-,root,root,-)
%{_bindir}/%{alias}.sh
%{_datadir}/applications/%{alias}.desktop
%{_datadir}/gtk%{alias}/*
%{_datadir}/locale/*
%{_datadir}/pixmaps/*.svg

%changelog
* Sat Sep 26 2020 Erich Küster <erich.kuester@arcor.de> - 1.7.0-1
- introducing svg template
* Sun Sep 13 2020 Erich Küster <erich.kuester@arcor.de> - 1.6.5-1
- enhanced version, rebuild for Fedora 32
* Sun Jan  5 2020 Erich Küster <erich.kuester@arcor.de> - 1.6.4
- new version
* Mon Dec 23 2019 Erich Küster <erich.kuester@arcor.de> - 1.6.3
- Rebuild for Fedora 31

