ACLOCAL_AMFLAGS = -I m4

installdir = $(datadir)/$(PACKAGE)
install_PROGRAMS = GTKPeriodicTable

GTKPeriodicTable_SOURCES = about.xpm \
elementproperty.h elementproperty.cpp \
elementschema.h elementschema.cpp \
formulaparser.h formulaparser.cpp \
legend_css.template main.cpp \
molecularformula.h molecularformula.cpp \
periodictablewindow.h periodictablewindow.cpp \
printformoperation.h printformoperation.cpp

GTKPeriodicTable_CPPFLAGS = $(GTKMM_CFLAGS) $(CAIRO_CFLAGS) \
-DPROGRAMNAME_LOCALEDIR=\"$(PROGRAMNAME_LOCALEDIR)\" \
-DGETTEXT_PACKAGE=\"${GETTEXT_PACKAGE}\" \
-DNLS=1

GTKPeriodicTable_LDADD = $(GTKMM_LIBS) $(CAIRO_LIBS)

