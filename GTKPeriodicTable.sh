#! /bin/sh -e
./linguas.sh
echo "now compiling gtkPeriodicTable..." 
cd ./src
g++ `pkg-config gtkmm-3.0 --cflags --libs` -c main.cpp elementproperty.cpp elementschema.cpp formulaparser.cpp molecularformula.cpp periodictablewindow.cpp printformoperation.cpp
g++ main.o elementproperty.o elementschema.o formulaparser.o molecularformula.o periodictablewindow.o printformoperation.o -o gtkPeriodicTable `pkg-config gtkmm-3.0 --cflags --libs`
cd ..
./src/gtkPeriodicTable

