#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
#include <ostream>
#include <sstream>
#include <map>
#include <set>
#include <cctype>
#include <regex>
#include <algorithm>
#include <locale>
#include <codecvt>
#include <cwctype>



using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::setw;
using std::left;
using std::ifstream;
using std::ofstream;
using std::ostream;
using std::map;
using std::set;
using std::pair;
using std::vector;
using std::regex;


// Funkcijos pasalina skyrybos zenklus, pavercia visas raides i mazasias
//Liedzia normalizuoti lietuviskus zodzius ir grazina normalizuota zodi
std::wstring mazasis_zodis(const std::wstring& zodis, const std::locale& loc);
std::string tvarkingas_zodis(const std::string& zodis);

// Atspausdina zodzius ir ju pasikartojimu kieki 
void Ifaila_zodziai(const map<string, int>& zodziu_kiekis);

// Atspausdina zodzius ir eilutes, kuriose jie pasikartoja, ju nr 
void failas_eilutems(const map<string, pair<int, set<int>>>& zodziu_eil);

// Tvarko ir spausdina URL adresus
void tvarkyti_url(const set<string>& url_set);

// Pagrindine teksto analizes funkcija
void pagrindine_analize();


