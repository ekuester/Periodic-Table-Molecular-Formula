SUBDIRS = src po 16x16

ACLOCAL_AMFLAGS = -I m4

bin_SCRIPTS = periodictable.sh

LATERAL_FILES = COMMENTAREN COMMENTAIRES COMMENTI COMMENTS KOMMENTARE LICENSE README.md

lateraldir = $(pkgdatadir)
lateral_DATA = $(LATERAL_FILES)

EXTRA_DIST = 16x16 package autogen.sh GTKPeriodicTable.sh periodictable.pdf\
 $(LATERAL_FILES)

CLEANFILES =

# desktop files
desktopdir = $(datadir)/applications
desktop_DATA = periodictable.desktop

# convenience command for doing Makefile variable substitutions in non-Makefile
# files (scripts, service files, etc.)
do_subst = sed -e 's|@abs_top_srcdir[@]|$(abs_top_srcdir)|g' \
	-e 's|@abs_top_builddir[@]|$(abs_top_builddir)|g' \
	-e 's|@localedir[@]|$(localedir)|g' \
	-e 's|@bindir[@]|$(bindir)|g' \
	-e 's|@libexecdir[@]|$(libexecdir)|g' \
	-e 's|@pkglibdir[@]|$(pkglibdir)|g' \
	-e 's|@pkgdatadir[@]|$(pkgdatadir)|g' \
	-e 's|@have_libnotify[@]|$(HAVE_LIBNOTIFY)|g' \
	-e 's|@have_libsoup[@]|$(HAVE_LIBSOUP)|g' \
	-e 's|@have_cheese[@]|$(HAVE_CHEESE)|g'

periodictable.sh: periodictable.sh.in
	$(AM_V_GEN) $(do_subst) $< > $@
	chmod +x $@

CLEANFILES += periodictable.sh
EXTRA_DIST += periodictable.sh.in

# application icon 256x256
appicondir=$(datadir)/pixmaps
appicon_DATA=periodictable.svg

EXTRA_DIST += periodictable.svg

