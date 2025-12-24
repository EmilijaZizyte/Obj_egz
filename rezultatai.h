#ifndef TEXT_ANALYSIS_H_INCLUDED
#define TEXT_ANALYSIS_H_INCLUDED

#include "bibliotekos.h"


// Funkcija pasalina skyrybos zenklus, pavercia visas raides i mazasias
std::wstring normalizuoti_lietuviskus_zodzius(const std::wstring& zodis, const std::locale& loc);
std::string geras_zodis(const std::string& zodis);

// Atspausdina zodzius ir ju pasikartojimu kieki (>1)
void spausdinimas_zodziu_kiekis(const map<string, int>& zodziu_kiekis);

// Atspausdina zodzius ir eiluciu numerius (cross-reference)
void spausdinimas_zodziu_eil(
    const map<string, pair<int, set<int>>>& zodziu_eil
);

void tvarkyti_url(const set<string>& url_set);

// Pagrindine teksto analizes funkcija
void failo_tvarkymas();

#endif
