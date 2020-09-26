/*
//  Part of gtkPeriodicTable - Periodic Table of the Elements
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
//  File:   elementschema.h
//  Created on October1, 2018, 19:28
 */

#ifndef ELEMENTSCHEMA_H
#define ELEMENTSCHEMA_H

#include <glibmm/i18n.h>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include "formulaparser.h"

using namespace std;

class FormulaParser;

// official <https://iupac.org/what-we-do/periodic-table-of-elements/>
// latin <https://la.wikipedia.org/wiki/Systema_periodicum>
static std::vector< std::vector<Glib::ustring> > elements = {
{"Hydrogenium", "1", "H", N_("Hydrogen"), "1.00794(4)", "#FFFFFF", "1s1 ", "2.2", "37", "", "120", "1312", "-73", "-1, 1", N_("gas"), N_("diatomic"), "14", "20", "0.0000899", N_("nonmetal"), "1766"},
{"Helium", "2", "He", N_("Helium"), "4.002602(2)", "#D9FFFF", "1s2 ", "", "32", "", "140", "2372", "0", "", N_("gas"), N_("monatomic"), "", "4", "0.0001785", N_("noble gas"), "1868"},
{"Lithium", "3", "Li", N_("Lithium"), "6.941(2)", "#CC80FF", "[He] 2s1 ", "0.98", "134", "76 (+1)", "182", "520", "-60", "1", N_("solid"), N_("metallic"), "454", "1603", "0.534", N_("alkali metal"), "1817"},
{"Beryllium", "4", "Be", N_("Beryllium"), "9.0121831(5)", "#C2FF00", "[He] 2s2 ", "1.57", "90", "45 (+2)", "153 a", "900", "0", "2", N_("solid"), N_("metallic"), "1560", "3243", "1.845", N_("alkaline earth metal"), "1798"},
{"Borium", "5", "B", N_("Boron"), "10.811(7)", "#FFB5B5", "[He] 2s2 2p1 ", "2.04", "82", "27 (+3)", "192 a", "801", "-27", "1, 2, 3", N_("solid"), N_("covalent network"), "2348", "4203", "2.37", N_("metalloid"), "1807"},
{"Carbonium", "6", "C", N_("Carbon"), "12.0107(8)", "#909090", "[He] 2s2 2p2 ", "2.55", "77", "16 (+4)", "170", "1087", "-154", "-4, -3, -2, -1, 1, 2, 3, 4", N_("solid"), N_("covalent network"), "(3823)", "3915 subl.", "2.26", N_("nonmetal"), N_("ancient")},
{"Nitrogenium", "7", "N", N_("Nitrogen"), "14.0067(2)", "#3050F8", "[He] 2s2 2p3 ", "3.04", "75", "146 (-3)", "155", "1402", "-7", "-3, -2, -1, 1, 2, 3, 4, 5", N_("gas"), N_("diatomic"), "63", "77", "0.001251", N_("nonmetal"), "1772"},
{"Oxygenium", "8", "O", N_("Oxygen"), "15.9994(3)", "#FF0D0D", "[He] 2s2 2p4 ", "3.44", "73", "140 (-2)", "152", "1314", "-141", "-2, -1, 1, 2", N_("gas"), N_("diatomic"), "55", "90", "0.001429", N_("nonmetal"), "1774"},
{"Fluorinum", "9", "F", N_("Fluorine"), "18.998403163(6)", "#90E050", "[He] 2s2 2p5 ", "3.98", "71", "133 (-1)", "147", "1681", "-328", "-1", N_("gas"), N_("monatomic"), "54", "85", "0.001696", N_("halogen"), "1670"},
{"Neon", "10", "Ne", N_("Neon"), "20.1797(6)", "#B3E3F5", "[He] 2s2 2p6 ", "", "69", "", "154", "2081", "0", "", N_("gas"), N_("monatomic"), "25", "27", "0.0008999", N_("noble gas"), "1898"},
{"Natrium", "11", "Na", N_("Sodium"), "22.98976928(2)", "#AB5CF2", "[Ne] 3s1 ", "0.93", "154", "102 (+1)", "227", "496", "-53", "-1, 1", N_("solid"), N_("metallic"), "371", "1156", "0.968", N_("alkali metal"), "1807"},
{"Magnesium", "12", "Mg", N_("Magnesium"), "24.3050(6)", "#8AFF00", "[Ne] 3s2 ", "1.31", "130", "72 (+2)", "173", "738", "0", "1, 2", N_("solid"), N_("metallic"), "923", "1363", "1.738", N_("alkaline earth metal"), "1808"},
{"Aluminium", "13", "Al", N_("Aluminum"), "26.9815384(3)", "#BFA6A6", "[Ne] 3s2 3p1 ", "1.61", "118", "53.5 (+3)", "184 a", "578", "-43", "1, 3", N_("solid"), N_("metallic"), "933", "2743", "2.7", N_("metal"), N_("ancient")},
{"Silicium", "14", "Si", N_("Silicon"), "28.0855(3)", "#F0C8A0", "[Ne] 3s2 3p2 ", "1.9", "111", "40 (+4)", "210", "787", "-134", "-4, -3, -2, -1, 1, 2, 3, 4", N_("solid"), N_("metallic"), "1687", "3538", "2.329", N_("metalloid"), "1854"},
{"Phosphorus", "15", "P", N_("Phosphorus"), "30.973761998(5)", "#FF8000", "[Ne] 3s2 3p3 ", "2.19", "106", "44 (+3)", "180", "1012", "-72", "-3, -2, -1, 1, 2, 3, 4, 5", N_("solid"), N_("covalent network"), "317", "554", "1.823", N_("nonmetal"), "1669"},
{"Sulphur", "16", "S", N_("Sulfur"), "32.065(5)", "#FFFF30", "[Ne] 3s2 3p4 ", "2.58", "102", "184 (-2)", "180", "1000", "-200", "-2, -1, 1, 2, 3, 4, 5, 6", N_("solid"), N_("covalent network"), "388", "718", "2.07 (alpha)", N_("nonmetal"), N_("ancient")},
{"Chlorinum", "17", "Cl", N_("Chlorine"), "35.453(2)", "#1FF01F", "[Ne] 3s2 3p5 ", "3.16", "99", "181 (-1)", "175", "1251", "-349", "-1, 1, 2, 3, 4, 5, 6, 7", N_("gas"), N_("covalent network"), "172", "239", "0.003214", N_("halogen"), "1774"},
{"Argon", "18", "Ar", N_("Argon"), "39.948(1)", "#80D1E3", "[Ne] 3s2 3p6 ", "", "97", "", "188", "1521", "0", "", N_("gas"), N_("monatomic"), "84", "87", "0.001784", N_("noble gas"), "1894"},
{"Kalium", "19", "K", N_("Potassium"), "39.0983(1)", "#8F40D4", "[Ar] 4s1 ", "0.82", "196", "138 (+1)", "275", "419", "-48", "1", N_("solid"), N_("metallic"), "337", "1032", "0.862", N_("alkali metal"), "1807"},
{"Calcium", "20", "Ca", N_("Calcium"), "40.078(4)", "#3DFF00", "[Ar] 4s2 ", "1", "174", "100 (+2)", "231 a", "590", "-2", "2", N_("solid"), N_("metallic"), "1115", "1757", "1.55", N_("alkaline earth metal"), N_("ancient")},
{"Scandium", "21", "Sc", N_("Scandium"), "44.955 908(5)", "#E6E6E6", "[Ar] 3d1 4s2 ", "1.36", "144", "74.5 (+3)", "211 a", "633", "-18", "1, 2, 3", N_("solid"), N_("metallic"), "1814", "3109", "2.985", N_("transition metal"), "1876"},
{"Titanium", "22", "Ti", N_("Titanium"), "47.867(1)", "#BFC2C7", "[Ar] 3d2 4s2 ", "1.54", "136", "86 (+2)", "", "659", "-8", "-1, 2, 3, 4", N_("solid"), N_("metallic"), "1941", "3560", "4.506", N_("transition metal"), "1791"},
{"Vanadium", "23", "V", N_("Vanadium"), "50.9415(1)", "#A6A6AB", "[Ar] 3d3 4s2 ", "1.63", "125", "79 (+2)", "", "651", "-51", "-1, 2, 3, 4", N_("solid"), N_("metallic"), "2183", "3680", "6.0", N_("transition metal"), "1803"},
{"Chromium", "24", "Cr", N_("Chromium"), "51.9961(6)", "#8A99C7", "[Ar] 3d5 4s1 ", "1.66", "127", "80 (+2*)", "", "653", "-64", "-2, -1, 1, 2, 3, 4, 5, 6", N_("solid"), N_("metallic"), "2180", "2944", "7.19", N_("transition metal"), N_("ancient")},
{"Manganum", "25", "Mn", N_("Manganese"), "54.938043(2)", "#9C7AC7", "[Ar] 3d5 4s2 ", "1.55", "139", "67 (+2)", "", "717", "0", "-3, -2, -1, 1, 2, 3, 4, 5, 6, 7", N_("solid"), N_("metallic"), "1519", "2334", "7.21", N_("transition metal"), "1774"},
{"Ferrum", "26", "Fe", N_("Iron"), "55.845(2)", "#E06633", "[Ar] 3d6 4s2 ", "1.83", "125", "78 (+2*)", "", "763", "-16", "-2, -1, 1, 2, 3, 4, 5, 6", N_("solid"), N_("metallic"), "1811", "3134", "7.874", N_("transition metal"), N_("ancient")},
{"Cobaltum", "27", "Co", N_("Cobalt"), "58.933194(3)", "#F090A0", "[Ar] 3d7 4s2 ", "1.88", "126", "74.5 (+2*)", "", "760", "-64", "-1, 1, 2, 3, 4, 5", N_("solid"), N_("metallic"), "1768", "3200", "8.9", N_("transition metal"), N_("ancient")},
{"Niccelium", "28", "Ni", N_("Nickel"), "58.6934(4)", "#50D050", "[Ar] 3d8 4s2 ", "1.91", "121", "69 (+2)", "163", "737", "-112", "-1, 1, 2, 3, 4", N_("solid"), N_("metallic"), "1728", "3003", "8.908", N_("transition metal"), "1751"},
{"Cuprum", "29", "Cu", N_("Copper"), "63.546(3)", "#C88033", "[Ar] 3d10 4s1 ", "1.9", "138", "77 (+1)", "140", "746", "-118", "1, 2, 3, 4", N_("solid"), N_("metallic"), "1358", "2835", "8.96", N_("transition metal"), N_("ancient")},
{"Zincum", "30", "Zn", N_("Zinc"), "65.38(2)", "#7D80B0", "[Ar] 3d10 4s2 ", "1.65", "131", "74 (+2)", "139", "906", "0", "2", N_("solid"), N_("metallic"), "693", "1180", "7.14", N_("transition metal"), "1746"},
{"Gallium", "31", "Ga", N_("Gallium"), "69.723(1)", "#C28F8F", "[Ar] 3d10 4s2 4p1 ", "1.81", "126", "62 (+3)", "187", "579", "-29", "1, 2, 3", N_("solid"), N_("metallic"), "303", "2473", "5.91", N_("metal"), "1875"},
{"Germanium", "32", "Ge", N_("Germanium"), "72.64(1)", "#668F8F", "[Ar] 3d10 4s2 4p2 ", "2.01", "122", "73 (+2)", "", "762", "-119", "-4, 1, 2, 3, 4", N_("solid"), N_("metallic"), "1211", "3106", "5.323", N_("metalloid"), "1886"},
{"Arsenicum", "33", "As", N_("Arsenic"), "74.921595(6)", "#BD80E3", "[Ar] 3d10 4s2 4p3 ", "2.18", "119", "58 (+3)", "185", "947", "-78", "-3, 2, 3, 5", N_("solid"), N_("metallic"), "1090", "887", "5.727", N_("metalloid"), N_("ancient")},
{"Selenium", "34", "Se", N_("Selenium"), "78.971(8)", "#FFA100", "[Ar] 3d10 4s2 4p4 ", "2.55", "116", "198 (-2)", "190", "941", "-195", "-2, 2, 4, 6", N_("solid"), N_("metallic"), "494", "958", "4.81", N_("nonmetal"), "1817"},
{"Brominum", "35", "Br", N_("Bromine"), "79.904(1)", "#A62929", "[Ar] 3d10 4s2 4p5 ", "2.96", "114", "196 (-1)", "185", "1140", "-325", "-1, 1, 3, 4, 5, 7", N_("liquid"), N_("covalent network"), "266", "332", "3.1028", N_("halogen"), "1826"},
{"Krypton", "36", "Kr", N_("Krypton"), "83.798(2)", "#5CB8D1", "[Ar] 3d10 4s2 4p6 ", "", "110", "", "202", "1351", "0", "2", N_("gas"), N_("monatomic"), "116", "120", "0.003749", N_("noble gas"), "1898"},
{"Rubidium", "37", "Rb", N_("Rubidium"), "85.4678(3)", "#702EB0", "[Kr] 5s1 ", "0.82", "211", "152 (+1)", "303 a", "403", "-47", "1", N_("solid"), N_("metallic"), "312", "961", "1.532", N_("alkali metal"), "1861"},
{"Strontium", "38", "Sr", N_("Strontium"), "87.62(1)", "#00FF00", "[Kr] 5s2 ", "0.95", "192", "118 (+2)", "249 a", "550", "-5", "2", N_("solid"), N_("metallic"), "1050", "1650", "2.64", N_("alkaline earth metal"), "1790"},
{"Yttrium", "39", "Y", N_("Yttrium"), "88.90584(1)", "#94FFFF", "[Kr] 4d1 5s2 ", "1.22", "162", "90 (+3)", "", "600", "-30", "1, 2, 3", N_("solid"), N_("metallic"), "1799", "3203", "4.472", N_("transition metal"), "1794"},
{"Zirkonium", "40", "Zr", N_("Zirconium"), "91.224(2)", "#94E0E0", "[Kr] 4d2 5s2 ", "1.33", "148", "72 (+4)", "", "640", "-41", "1, 2, 3, 4", N_("solid"), N_("metallic"), "2128", "4650", "6.52", N_("transition metal"), "1789"},
{"Niobium", "41", "Nb", N_("Niobium"), "92.90637(1)", "#73C2C9", "[Kr] 4d4 5s1 ", "1.6", "137", "72 (+3)", "", "652", "-86", "-1, 2, 3, 4, 5", N_("solid"), N_("metallic"), "2750", "5017", "8.57", N_("transition metal"), "1801"},
{"Molybdenum", "42", "Mo", N_("Molybdenum"), "95.95(1)", "#54B5B5", "[Kr] 4d5 5s1 ", "2.16", "145", "69 (+3)", "", "684", "-72", "-2, -1, 1, 2, 3, 4, 5, 6", N_("solid"), N_("metallic"), "2896", "4912", "10.28", N_("transition metal"), "1778"},
{"Technetium", "43", "Tc", N_("Technetium"), "98.9063", "#3B9E9E", "[Kr] 4d5 5s2 ", "1.9", "156", "64.5 (+4)", "", "702", "-53", "-3, -1, 1, 2, 3, 4, 5, 6, 7", N_("solid"), N_("metallic"), "2430", "4538", "11", N_("transition metal"), "1937"},
{"Ruthenium", "44", "Ru", N_("Ruthenium"), "101.07(2)", "#248F8F", "[Kr] 4d7 5s1 ", "2.2", "126", "68 (+3)", "", "710", "-101", "-2, 1, 2, 3, 4, 5, 6, 7, 8", N_("solid"), N_("metallic"), "2607", "4423", "12.45", N_("transition metal"), "1827"},
{"Rhodium", "45", "Rh", N_("Rhodium"), "102.90549(2)", "#0A7D8C", "[Kr] 4d8 5s1 ", "2.28", "135", "66.5 (+3)", "", "720", "-110", "-1, 1, 2, 3, 4, 5, 6", N_("solid"), N_("metallic"), "2237", "3968", "12.41", N_("transition metal"), "1803"},
{"Palladium", "46", "Pd", N_("Palladium"), "106.42(1)", "#006985", "[Kr] 4d10 ", "2.2", "131", "59 (+1)", "163", "804", "-54", "2, 4", N_("solid"), N_("metallic"), "1828", "3236", "12.023", N_("transition metal"), "1803"},
{"Argentum", "47", "Ag", N_("Silver"), "107.8682(2)", "#C0C0C0", "[Kr] 4d10 5s1 ", "1.93", "153", "115 (+1)", "172", "731", "-126", "1, 2, 3", N_("solid"), N_("metallic"), "1235", "2435", "10.49", N_("transition metal"), N_("ancient")},
{"Cadmium", "48", "Cd", N_("Cadmium"), "112.411(4)", "#FFD98F", "[Kr] 4d10 5s2 ", "1.69", "148", "95 (+2)", "158", "868", "0", "2", N_("solid"), N_("metallic"), "594", "1040", "8.65", N_("transition metal"), "1817"},
{"Indium", "49", "In", N_("Indium"), "114.818(3)", "#A67573", "[Kr] 4d10 5s2 5p1 ", "1.78", "144", "80 (+3)", "193", "558", "-29", "1, 2, 3", N_("solid"), N_("metallic"), "430", "2345", "7.31", N_("metal"), "1863"},
{"Stannum", "50", "Sn", N_("Tin"), "118.710(7)", "#668080", "[Kr] 4d10 5s2 5p2 ", "1.96", "141", "112 (+2)", "217", "709", "-107", "-4, 2, 4", N_("solid"), N_("metallic"), "505", "2875", "7.265 (beta)", N_("metal"), N_("ancient")},
{"Stibium", "51", "Sb", N_("Antimony"), "121.760(1)", "#9E63B5", "[Kr] 4d10 5s2 5p3 ", "2.05", "138", "76 (+3)", "206 a", "834", "-103", "-3, 3, 5", N_("solid"), N_("metallic"), "904", "1908", "6.697", N_("metalloid"), N_("ancient")},
{"Tellurium", "52", "Te", N_("Tellurium"), "127.60(3)", "#D47A00", "[Kr] 4d10 5s2 5p4 ", "2.1", "135", "221 (-2)", "206", "869", "-190", "-2, 2, 4, 5, 6", N_("solid"), N_("metallic"), "723", "1261", "6.24", N_("metalloid"), "1782"},
{"Iodinum", "53", "I", N_("Iodine"), "126.90447(3)", "#940094", "[Kr] 4d10 5s2 5p5 ", "2.66", "133", "220 (-1)", "198", "1008", "-295", "-1, 1, 3, 5, 7", N_("solid"), N_("covalent network"), "387", "457", "4.933", N_("halogen"), "1811"},
{"Xenon", "54", "Xe", N_("Xenon"), "131.293(6)", "#429EB0", "[Kr] 4d10 5s2 5p6 ", "", "130", "48 (+8)", "216", "1170", "0", "2, 4, 6, 8", N_("gas"), N_("monatomic"), "161", "165", "0.005894", N_("noble gas"), "1898"},
{"Caesium", "55", "Cs", N_("Cesium"), "132.90545196(6)", "#57178F", "[Xe] 6s1 ", "0.79", "225", "167 (+1)", "343 a", "376", "-46", "1", N_("solid"), N_("metallic"), "302", "944", "1.93", N_("alkali metal"), "1860"},
{"Barium", "56", "Ba", N_("Barium"), "137.327(7)", "#00C900", "[Xe] 6s2 ", "0.89", "198", "135 (+2)", "268 a", "503", "-14", "2", N_("solid"), N_("metallic"), "1000", "2118", "3.51", N_("alkaline earth metal"), "1808"},
{"Lanthanium", "57", "La", N_("Lanthanum"), "138.90547(7)", "#70D4FF", "[Xe] 5d1 6s2 ", "1.1", "169", "103.2 (+3)", "", "538", "-48", "2, 3", N_("solid"), N_("metallic"), "1193", "3737", "6.162", N_("lanthanoid"), "1839"},
{"Cerium", "58", "Ce", N_("Cerium"), "140.116(1)", "#FFFFC7", "[Xe] 4f1 5d1 6s2 ", "1.12", "", "102 (+3)", "", "534", "-50", "2, 3, 4", N_("solid"), N_("metallic"), "1068", "3716", "6.77", N_("lanthanoid"), "1803"},
{"Praseodymium", "59", "Pr", N_("Praseodymium"), "140.90766(1)", "#D9FFC7", "[Xe] 4f3 6s2 ", "1.13", "", "99 (+3)", "", "527", "-50", "2, 3, 4", N_("solid"), N_("metallic"), "1208", "3403", "6.77", N_("lanthanoid"), "1885"},
{"Neodymium", "60", "Nd", N_("Neodymium"), "144.242(3)", "#C7FFC7", "[Xe] 4f4 6s2 ", "1.14", "", "129 (+2)", "", "533", "-50", "2, 3", N_("solid"), N_("metallic"), "1297", "3347", "7.01", N_("lanthanoid"), "1885"},
{"Promethium", "61", "Pm", N_("Promethium"), "146.9151", "#A3FFC7", "[Xe] 4f5 6s2 ", "1.13", "", "97 (+3)", "", "540", "-50", "3", N_("solid"), N_("metallic"), "1315", "3273", "7.26", N_("lanthanoid"), "1947"},
{"Samarium", "62", "Sm", N_("Samarium"), "150.36(2)", "#8FFFC7", "[Xe] 4f6 6s2 ", "1.17", "", "122 (+2)", "", "545", "-50", "2, 3", N_("solid"), N_("metallic"), "1345", "2173", "7.52", N_("lanthanoid"), "1853"},
{"Europium", "63", "Eu", N_("Europium"), "151.964(1)", "#61FFC7", "[Xe] 4f7 6s2 ", "1.2", "", "117 (+2)", "", "547", "-50", "2, 3", N_("solid"), N_("metallic"), "1099", "1802", "5.264", N_("lanthanoid"), "1901"},
{"Gadolinium", "64", "Gd", N_("Gadolinium"), "157.25(3)", "#45FFC7", "[Xe] 4f7 5d1 6s2 ", "1.2", "", "93.8 (+3)", "", "593", "-50", "1, 2, 3", N_("solid"), N_("metallic"), "1585", "3273", "7.9", N_("lanthanoid"), "1880"},
{"Terbium", "65", "Tb", N_("Terbium"), "158.925354(8)", "#30FFC7", "[Xe] 4f9 6s2 ", "1.2", "", "92.3 (+3)", "", "566", "-50", "1, 3, 4", N_("solid"), N_("metallic"), "1629", "3396", "8.23", N_("lanthanoid"), "1843"},
{"Dysprosium", "66", "Dy", N_("Dysprosium"), "162.500(1)", "#1FFFC7", "[Xe] 4f10 6s2 ", "1.22", "", "107 (+2)", "", "573", "-50", "2, 3", N_("solid"), N_("metallic"), "1680", "2840", "8.54", N_("lanthanoid"), "1886"},
{"Holmium", "67", "Ho", N_("Holmium"), "164.930328(7)", "#00FF9C", "[Xe] 4f11 6s2 ", "1.23", "", "90.1 (+3)", "", "581", "-50", "3", N_("solid"), N_("metallic"), "1734", "2873", "8.795", N_("lanthanoid"), "1878"},
{"Erbium", "68", "Er", N_("Erbium"), "167.259(3)", "#00e675", "[Xe] 4f12 6s2 ", "1.24", "", "89 (+3)", "", "589", "-50", "3", N_("solid"), N_("metallic"), "1802", "3141", "9.066", N_("lanthanoid"), "1842"},
{"Thulium", "69", "Tm", N_("Thulium"), "168.934218(6)", "#00D452", "[Xe] 4f13 6s2 ", "1.25", "", "103 (+2)", "", "597", "-50", "2, 3", N_("solid"), N_("metallic"), "1818", "2223", "9.321", N_("lanthanoid"), "1879"},
{"Ytterbium", "70", "Yb", N_("Ytterbium"), "173.054(5)", "#00BF38", "[Xe] 4f14 6s2 ", "1.1", "", "102 (+2)", "", "603", "-50", "2, 3", N_("solid"), N_("metallic"), "1097", "1469", "6.9", N_("lanthanoid"), "1878"},
{"Lutetium", "71", "Lu", N_("Lutetium"), "174.9668(1)", "#00AB24", "[Xe] 4f14 5d1 6s2 ", "1.27", "160", "86.1 (+3)", "", "524", "-50", "3", N_("solid"), N_("metallic"), "1925", "3675", "9.841", N_("lanthanoid"), "1907"},
{"Hafnium", "72", "Hf", N_("Hafnium"), "178.49(2)", "#4DC2FF", "[Xe] 4f14 5d2 6s2 ", "1.3", "150", "71 (+4)", "", "659", "0", "2, 3, 4", N_("solid"), N_("metallic"), "2506", "4876", "13.31", N_("transition metal"), "1923"},
{"Tantalium", "73", "Ta", N_("Tantalum"), "180.94788(2)", "#4DA6FF", "[Xe] 4f14 5d3 6s2 ", "1.5", "138", "72 (+3)", "", "761", "-31", "-1, 2, 3, 4, 5", N_("solid"), N_("metallic"), "3290", "5731", "16.69", N_("transition metal"), "1802"},
{"Wolframium", "74", "W", N_("Tungsten"), "183.84(1)", "#2194D6", "[Xe] 4f14 5d4 6s2 ", "2.36", "146", "66 (+4)", "", "770", "-79", "-2, -1, 1, 2, 3, 4, 5, 6", N_("solid"), N_("metallic"), "3695", "6203", "19.3", N_("transition metal"), "1783"},
{"Rhenium", "75", "Re", N_("Rhenium"), "186.207(1)", "#267DAB", "[Xe] 4f14 5d5 6s2 ", "1.9", "159", "63 (+4)", "", "760", "-15", "-3, -1, 1, 2, 3, 4, 5, 6, 7", N_("solid"), N_("metallic"), "3459", "5903", "21.02", N_("transition metal"), "1925"},
{"Osmium", "76", "Os", N_("Osmium"), "190.23(3)", "#266696", "[Xe] 4f14 5d6 6s2 ", "2.2", "128", "63 (+4)", "", "840", "-106", "-2, -1, 1, 2, 3, 4, 5, 6, 7, 8", N_("solid"), N_("metallic"), "3306", "5285", "22.59", N_("transition metal"), "1803"},
{"Iridium", "77", "Ir", N_("Iridium"), "192.217(2)", "#175487", "[Xe] 4f14 5d7 6s2 ", "2.2", "137", "68 (+3)", "", "880", "-151", "-3, -1, 1, 2, 3, 4, 5, 6", N_("solid"), N_("metallic"), "2719", "4403", "22.56", N_("transition metal"), "1803"},
{"Platinum", "78", "Pt", N_("Platinum"), "195.084(9)", "#D0D0E0", "[Xe] 4f14 5d9 6s1 ", "2.28", "128", "86 (+2)", "175", "870", "-205", "2, 4, 5, 6", N_("solid"), N_("metallic"), "2041", "4098", "21.45", N_("transition metal"), N_("ancient")},
{"Aurum", "79", "Au", N_("Gold"), "196.966570(4)", "#FFD123", "[Xe] 4f14 5d10 6s1 ", "2.54", "144", "137 (+1)", "166", "890", "-223", "-1, 1, 2, 3, 5", N_("solid"), N_("metallic"), "1337", "3243", "19.3", N_("transition metal"), N_("ancient")},
{"Hydrargyrum", "80", "Hg", N_("Mercury_(element)"), "200.59(2)", "#B8B8D0", "[Xe] 4f14 5d10 6s2 ", "2", "149", "119 (+1)", "155", "1007", "0", "1, 2, 4", N_("liquid"), N_("metallic"), "234", "630", "13.534", N_("transition metal"), N_("ancient")},
{"Thallium", "81", "Tl", N_("Thallium"), "204.3833(2)", "#A6544D", "[Xe] 4f14 5d10 6s2 6p1 ", "1.62", "148", "150 (+1)", "196", "589", "-19", "1, 3", N_("solid"), N_("metallic"), "577", "1746", "11.85", N_("metal"), "1861"},
{"Plumbum", "82", "Pb", N_("Lead"), "207.2(1)", "#575961", "[Xe] 4f14 5d10 6s2 6p2 ", "1.87 (+2)", "147", "119 (+2)", "202", "716", "-35", "-4, 2, 4", N_("solid"), N_("metallic"), "601", "2022", "11.34", N_("metal"), N_("ancient")},
{"Bismuthum", "83", "Bi", N_("Bismuth"), "208.98040(1)", "#9E4FB5", "[Xe] 4f14 5d10 6s2 6p3 ", "2.02", "146", "103 (+3)", "207 a", "703", "-91", "-3, 3, 5", N_("solid"), N_("metallic"), "545", "1837", "9.78", N_("metal"), N_("ancient")},
{"Polonium", "84", "Po", N_("Polonium"), "208.9824", "#AB5C00", "[Xe] 4f14 5d10 6s2 6p4 ", "2", "", "94 (+4)", "197 a", "812", "-183", "-2, 2, 4, 6", N_("solid"), N_("metallic"), "527", "1235", "9.196 (alpha)", N_("metalloid"), "1898"},
{"Astatinum", "85", "At", N_("Astatine"), "209.9871", "#754F45", "[Xe] 4f14 5d10 6s2 6p5 ", "2.2", "", "62 (+7)", "202 a", "920", "-270", "-1, 1, 3, 5", N_("solid"), N_("covalent network"), "575", "610", "6.35", N_("halogen"), "1940"},
{"Radon", "86", "Rn", N_("Radon"), "222.0176", "#428296", "[Xe] 4f14 5d10 6s2 6p6 ", "", "145", "", "220 a", "1037", "", "2", N_("gas"), N_("monatomic"), "202", "211", "0.00973", N_("noble gas"), "1900"},
{"Francium", "87", "Fr", N_("Francium"), "223.0197", "#420066", "[Rn] 7s1 ", "0.7", "", "180 (+1)", "348 a", "380", "", "1", N_("solid"), N_("metallic"), "300", "950", "2.9", N_("alkali metal"), "1939"},
{"Radium", "88", "Ra", N_("Radium"), "226.0254", "#007D00", "[Rn] 7s2 ", "0.9", "", "148 (+2)", "283 a", "509", "", "2", N_("solid"), N_("metallic"), "973", "2010", "5.5", N_("alkaline earth metal"), "1898"},
{"Actinium", "89", "Ac", N_("Actinium"), "227.0278", "#70ABFA", "[Rn] 6d1 7s2 ", "1.1", "", "112 (+3)", "", "499", "", "3", N_("solid"), N_("metallic"), "1500", "3470", "10", N_("actinoid"), "1899"},
{"Thorium", "90", "Th", N_("Thorium"), "232.0377(4)", "#00BAFF", "[Rn] 6d2 7s2 ", "1.3", "", "94 (+4)", "", "587", "", "2, 3, 4", N_("solid"), N_("metallic"), "2023", "5061", "11.7", N_("actinoid"), "1828"},
{"Protactinium", "91", "Pa", N_("Protactinium"), "231.03588(1)", "#00A1FF", "[Rn] 5f2 6d1 7s2 ", "1.5", "", "104 (+3)", "", "568", "", "3, 4, 5", N_("solid"), N_("metallic"), "1841", "4300", "15.37", N_("actinoid"), "1913"},
{"Uranium", "92", "U", N_("Uranium"), "238.02891(3)", "#008FFF", "[Rn] 5f3 6d1 7s2 ", "1.38", "", "102.5 (+3)", "186", "598", "", "3, 4, 5, 6", N_("solid"), N_("metallic"), "1405", "4404", "19.1", N_("actinoid"), "1789"},
{"Neptunium", "93", "Np", N_("Neptunium"), "237.0482", "#0080FF", "[Rn] 5f4 6d1 7s2 ", "1.36", "", "110 (+2)", "", "605", "", "3, 4, 5, 6, 7", N_("solid"), N_("metallic"), "913", "4447", "20.45 (alpha)", N_("actinoid"), "1940"},
{"Plutonium", "94", "Pu", N_("Plutonium"), "244.0642", "#006BFF", "[Rn] 5f6 7s2 ", "1.28", "", "100 (+3)", "", "585", "", "3, 4, 5, 6, 7", N_("solid"), N_("metallic"), "913", "3505", "19.816", N_("actinoid"), "1940"},
{"Americium", "95", "Am", N_("Americium"), "243", "#545CF2", "[Rn] 5f7 7s2 ", "1.3", "", "126 (+2)", "", "578", "", "2, 3, 4, 5, 6", N_("solid"), N_("metallic"), "1449", "2880", "12", N_("actinoid"), "1944"},
{"Curium", "96", "Cm", N_("Curium"), "247", "#785CE3", "[Rn] 5f7 6d1 7s2 ", "1.3", "", "97 (+3)", "", "581", "", "3, 4", N_("solid"), N_("metallic"), "1613", "3383", "13.51", N_("actinoid"), "1944"},
{"Berkelium", "97", "Bk", N_("Berkelium"), "247", "#8A4FE3", "[Rn] 5f9 7s2 ", "1.3", "", "96 (+3)", "", "601", "", "3, 4", N_("solid"), N_("metallic"), "1323", "", "14.78", N_("actinoid"), "1949"},
{"Californium", "98", "Cf", N_("Californium"), "251", "#A136D4", "[Rn] 5f10 7s2 ", "1.3", "", "95 (+3)", "", "608", "", "2, 3, 4", N_("solid"), N_("metallic"), "1173", "1743", "15.1", N_("actinoid"), "1950"},
{"Einsteinium", "99", "Es", N_("Einsteinium"), "252", "#B31FD4", "[Rn] 5f11 7s2 ", "1.3", "", "", "", "619", "", "2, 3", N_("solid"), "", "1133", "1269", "8.84", N_("actinoid"), "1952"},
{"Fermium", "100", "Fm", N_("Fermium"), "257", "#B31FBA", "[Rn] 5f12 7s2 ", "1.3", "", "", "", "627", "", "2, 3", "", "", "1800", "", "9.7", N_("actinoid"), "1952"},
{"Mendelevium", "101", "Md", N_("Mendelevium"), "258", "#B30DA6", "[Rn] 5f13 7s2 ", "1.3", "", "", "", "635", "", "2, 3", "", "", "1100", "", "10.3", N_("actinoid"), "1955"},
{"Nobelium", "102", "No", N_("Nobelium"), "259", "#BD0D87", "[Rn] 5f14 7s2 ", "1.3", "", "", "", "642", "", "2, 3", "", "", "1100", "", "9.9", N_("actinoid"), "1957"},
{"Lawrencium", "103", "Lr", N_("Lawrencium"), "266", "#C70066", "[Rn] 5f14 7s2 7p1 ", "1.3", "", "", "", "", "", "3", "", "", "1900", "", "16", N_("transition metal"), "1961"},
{"Rutherfordium", "104", "Rf", N_("Rutherfordium"), "261.1087", "#CC0059", "[Rn] 5f14 6d2 7s2 ", "", "", "", "", "", "", "4", "", "", "2400", "5800", "23.2", N_("transition metal"), "1969"},
{"Dubnium", "105", "Db", N_("Dubnium"), "262.1138", "#D1004F", "[Rn] 5f14 6d3 7s2 ", "", "", "", "", "", "", "", "", "", "", "", "29.3", N_("transition metal"), "1967"},
{"Seaborgium", "106", "Sg", N_("Seaborgium"), "263.1182", "#D90045", "[Rn] 5f14 6d4 7s2 ", "", "", "", "", "", "", "", "", "", "", "", "35", N_("transition metal"), "1974"},
{"Bohrium", "107", "Bh", N_("Bohrium"), "262.1229", "#E00038", "[Rn] 5f14 6d5 7s2 ", "", "", "", "", "", "", "", "", "", "", "", "37", N_("transition metal"), "1976"},
{"Hassium", "108", "Hs", N_("Hassium"), "270", "#E6002E", "[Rn] 5f14 6d6 7s2 ", "", "", "", "", "", "", "", "", "", "", "", "41", N_("transition metal"), "1984"},
{"Meitnerium", "109", "Mt", N_("Meitnerium"), "268", "#EB0026", "[Rn] 5f14 6d7 7s2 ", "", "", "", "", "", "", "", "", "", "", "", "37", N_("transition metal"), "1982"},
{"Darmstadtium", "110", "Ds", N_("Darmstadtium"), "281", "", "[Rn] 5f14 6d9 7s1 ", "", "", "", "", "", "", "", "", "", "", "", "34.8", N_("transition metal"), "1994"},
{"Roentgenium", "111", "Rg", N_("Roentgenium"), "280", "", "[Rn] 5f14 6d10 7s1 ", "", "", "", "", "", "", "", "", "", "", "", "28.7", N_("transition metal"), "1994"},
{"Copernicium", "112", "Cn", N_("Copernicium"), "277", "", "[Rn] 5f14 6d10 7s2 ", "", "", "", "", "", "", "", "", "", "", "", "", N_("transition metal"), "1996"},
{"Nihonium", "113", "Nh", N_("Nihonium"), "287", "", "[Rn] 5f14 6d10 7s2 7p1 ", "", "", "", "", "", "", "", "", "", "", "", "", N_("post-transition metal"), "2003"},
{"Flerovium", "114", "Fl", N_("Flerovium"), "289", "", "[Rn] 5f14 6d10 7s2 7p2 ", "", "", "", "", "", "", "", "", "", "", "", "", N_("post-transition metal"), "1998"},
{"Moscovium", "115", "Mc", N_("Moscovium"), "288", "", "[Rn] 5f14 6d10 7s2 7p3 ", "", "", "", "", "", "", "", "", "", "", "", "", N_("post-transition metal"), "2003"},
{"Livermorium", "116", "Lv", N_("Livermorium"), "293", "", "[Rn] 5f14 6d10 7s2 7p4 ", "", "", "", "", "", "", "", "", "", "", "", "", N_("post-transition metal"), "2000"},
{"Tennessinum", "117", "Ts", N_("Tennessine"), "292", "", "[Rn] 5f14 6d10 7s2 7p5 ", "", "", "", "", "", "", "", "", "", "", "", "", N_("post-transition metal"), "2010"},
{"Oganesson", "118", "Og", N_("Oganesson"), "294", "", "[Rn] 5f14 6d10 7s2 7p6 ", "", "", "", "", "", "", "", "", "", "", "", "", N_("noble gas"), "2002"}
};

class ElementSchema {
public:
    ElementSchema();
    ElementSchema(const ElementSchema& orig);
    virtual ~ElementSchema();

    double totalMass = 0.0;
/*
    struct element {
        Glib::ustring synonym;
        int ordinal;
        string symbol;
        Glib::ustring name;
        double mass;
    };
 */
    struct FormulaItem {
        string elementSymbol;
        double mass;
        int indexSum;
    };

    std::map<string, FormulaItem> formulaTable;

    std::vector<struct FormulaItem> parseElements(FormulaParser* inputParser);
    string analytics();
    string finalFormula();

private:

};

#endif /* ELEMENTSCHEMA_H */

