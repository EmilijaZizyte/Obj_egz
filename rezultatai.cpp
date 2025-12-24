#include "rezultatai.h"
#include "bibliotekos.h"

using namespace std;
std::wstring normalizuoti_lietuviskus_zodzius(const std::wstring& zodis, const std::locale& loc) {
    std::wstring rezultatas;
    for (wchar_t wc : zodis) {
        if (!iswpunct(wc) && !iswdigit(wc)) {
            wc = std::use_facet<std::ctype<wchar_t>>(loc).tolower(wc);
            rezultatas += wc;
        }
    }
    return rezultatas;
}

std::string pakeistas_zodis(const std::string& zodis) {
    std::locale loc("lt_LT.UTF-8");
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::wstring w_zodis = converter.from_bytes(zodis);
    std::wstring w_naujas = normalizuoti_lietuviskus_zodzius(w_zodis, loc);
    return converter.to_bytes(w_naujas);
}

// Spausdina zodzius ir ju pasikartojimu kieki (>1)
void spausdinimas_zodziu_kiekis(const map<string, int>& zodziu_kiekis) {
    ofstream failas("kiekis.txt");
    if (!failas.is_open()) {
        cout << "Nepavyko atidaryti failo 'kiekis.txt'!" << endl;
        return;
    }

    failas << left << setw(20) << "Zodis" << setw(10) << "Kiekis" << endl;
    failas << string(30, '-') << endl;

    for (map<string, int>::const_iterator it = zodziu_kiekis.begin(); it != zodziu_kiekis.end(); ++it) {
        if (it->second > 1) {
            failas << left << setw(20) << it->first << setw(10) << it->second << endl;
        }
    }

    cout << "Rezultatai issaugoti faile 'kiekis.txt'" << endl;
}

// Spausdina cross-reference lentele
void spausdinimas_zodziu_eil(const map<string, pair<int, set<int>>>& zodziu_eil) {
    ofstream failas("eil.txt");
    if (!failas.is_open()) {
        cout << "Nepavyko atidaryti failo 'eil.txt'!" << endl;
        return;
    }

    failas << left << setw(20) << "Zodis" << "Eilutes" << endl;
    failas << string(40, '-') << endl;

    for (map<string, pair<int, set<int>>>::const_iterator it = zodziu_eil.begin(); it != zodziu_eil.end(); ++it) {
        const string& zodis = it->first;
        const pair<int, set<int>>& duomenys = it->second;

        if (duomenys.first > 1) {
            failas << left << setw(20) << zodis << "{";
            bool pirmas = true;
            for (set<int>::const_iterator sit = duomenys.second.begin(); sit != duomenys.second.end(); ++sit) {
                if (!pirmas) failas << ", ";
                failas << *sit;
                pirmas = false;
            }
            failas << "}" << endl;
        }
    }

    cout << "Rezultatai issaugoti faile 'eil.txt'" << endl;
}


void tvarkyti_url(const set<string>& url_set) {
    string pasirinkimas;
    cout << "Pasirinkite kur rodyti URL (1 - terminalas, 2 - failas): ";

    while (true) {
        cin >> pasirinkimas;
        if (pasirinkimas == "1" || pasirinkimas == "2") break;
        cout << "Netinkama ivestis. Bandykite dar karta: ";
    }

    ostream* out_stream = &cout;
    ofstream failas;

    if (pasirinkimas == "2") {
        failas.open("url_info.txt");
        if (!failas.is_open()) {
            cout << "Nepavyko sukurti 'url_info.txt'" << endl;
            return;
        }
        out_stream = &failas;
    }

    *out_stream << "Rasti URL adresai:" << endl;
    *out_stream << string(25, '-') << endl;
    for (const auto& url : url_set) {
        *out_stream << url << endl;
    }

    if (pasirinkimas == "2") {
        cout << "Rezultatai issaugoti faile 'url_info.txt'" << endl;
        failas.close();
    }
}


// Pagrindin? analiz?s funkcija
void failo_tvarkymas() {
    string failo_pavadinimas;
    ifstream failas;

    map<string, int> zodziu_kiekis;
    map<string, pair<int, set<int>>> zodziu_eil;
    set<string> url_set;
    int eil_nr = 0;

    std::regex url_regex(R"((https?:\/\/)?(www\.)?[a-zA-Z0-9-]+\.[a-zA-Z]{2,}(/[^\s]*)?)");

    cout << "Iveskite failo pavadinima: ";
    getline(cin, failo_pavadinimas);

    while (!failas.is_open()) {
        failas.open(failo_pavadinimas);
        if (!failas.is_open()) {
            cout << "Failas nerastas. Bandykite dar karta: ";
            getline(cin, failo_pavadinimas);
        }
    }

    cout << "Failas sekmingai atidarytas!" << endl;

    string eilute;
    while (getline(failas, eilute)) {
        eil_nr++;
        std::stringstream ss(eilute);
        string zodis;
        while (ss >> zodis) {
            if (std::regex_search(zodis, url_regex)) {

                // Atmetam inicialus + pavarde:
                if (zodis.size() >= 4 &&
                    isupper((unsigned char)zodis[0]) &&
                    zodis[1] == '.' &&
                    isupper((unsigned char)zodis[2])) {
                    continue;
                }

                // Atmetam pseudo-domenus su "//", jei neprasideda "http"
                if (zodis.find("//") != string::npos &&
                    zodis.find("http") != 0) {
                    continue;
                }

                // Atmetam per trumpus pseudodomenus, pvz. m.brum
                if (zodis.find("http") != 0 && zodis.find("www.") != 0) {
                    size_t dot = zodis.find('.');
                    if (dot != string::npos && dot <= 1) {
                        continue;
                    }
                }

                // Atmetam klaidingus formatus, pvz. paleolitas.//A.Girininkas
                if (zodis.find(".//") != string::npos) {
                    continue;
                }

                // Pasalinam galine skyryba
                while (!zodis.empty() && ispunct((unsigned char)zodis.back())) {
                    zodis.pop_back();
                }

                // Idedam i URL rinkini
                url_set.insert(zodis);
            }
            else {
                string tvarkytas = pakeistas_zodis(zodis);
                if (!tvarkytas.empty()) {

                    // Patikriname, ar zodyje yra bent viena raide
                    bool turi_raidziu = false;
                    for (char c : tvarkytas) {
                        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
                            turi_raidziu = true;
                            break;
                        }
                    }
                    if (!turi_raidziu) continue;  // jei raidziu nera, praleidziame

                    // Atnaujiname zodziu skaiciu ir eilutes
                    zodziu_kiekis[tvarkytas]++;
                    zodziu_eil[tvarkytas].first++;
                    zodziu_eil[tvarkytas].second.insert(eil_nr);
                }
            }
        }
    }

    failas.close();

    spausdinimas_zodziu_kiekis(zodziu_kiekis);
    spausdinimas_zodziu_eil(zodziu_eil);

    if (!url_set.empty()) {
        tvarkyti_url(url_set);
    }
    else {
        cout << "URL adresu nerasta." << endl;
    }

}
