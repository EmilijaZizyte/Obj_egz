#include "rezultatai.h"


std::wstring mazasis_zodis(const std::wstring& zodis, const std::locale& loc) {
    std::wstring rezultatas;
    for (wchar_t wc : zodis) {
        if (!iswpunct(wc) && !iswdigit(wc)) {
            wc = std::use_facet<std::ctype<wchar_t>>(loc).tolower(wc);
            rezultatas += wc;
        }
    }
    return rezultatas;
}

std::string tvarkingas_zodis(const std::string& zodis) {
    std::locale loc("lt_LT.UTF-8");
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::wstring w_zodis = converter.from_bytes(zodis);
    std::wstring w_naujas = mazasis_zodis(w_zodis, loc);
    return converter.to_bytes(w_naujas);
}

// Spausdina zodzius ir ju pasikartojimu kieki (>1)
void Ifaila_zodziai(const map<string, int>& zodziai) {
    ofstream failas("zodziu_kiekis.txt");
    if (!failas.is_open()) {
        cout << "Nepavyko atidaryti failo 'zodziu_kiekis.txt'!" << endl;
        return;
    }

    failas << left << setw(20) << "Zodis" << setw(10) << "Kiek kartu pasikartojo" << endl;
    failas << string(30, '-') << endl;

    for (map<string, int>::const_iterator it = zodziai.begin(); it != zodziai.end(); ++it) {
        if (it->second > 1) {
            failas << left << setw(20) << it->first << setw(10) << it->second << endl;
        }
    }

    cout << "Rezultatai issaugoti faile 'zodziu_kiekis.txt'" << endl;
}





void failas_eilutems(const map<string, pair<int, set<int>>>& zodziu_eil) {
    ofstream failas("eilutese_pasikatoja.txt");
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

    cout << "Rezultatai issaugoti faile 'eilutese_pasikartoja.txt'" << endl;
}

//URL
void tvarkyti_url(const set<string>& url_pilnas) {
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
    for (const auto& url : url_pilnas) {
        *out_stream << url << endl;
    }

    if (pasirinkimas == "2") {
        cout << "Rezultatai issaugoti faile 'url_info.txt'" << endl;
        failas.close();
    }
}


// Pagrindine analizes funkcija
void pagrindine_analize() {
    string failo_pavadinimas;
    ifstream failas;

    map<string, int> zodziai;
    map<string, pair<int, set<int>>> zodziu_eil;
    set<string> url_pilnas;
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

    cout << "failas analizuojamas" << endl;

    string eilute;
    while (getline(failas, eilute)) {
        eil_nr++;
        std::stringstream ss(eilute);
        string zodis;
        while (ss >> zodis) { //tikrinam ar yra url
            if (std::regex_search(zodis, url_regex)) {

                // Vardu trumpiniai:
                if (zodis.size() >= 4 &&
                    isupper((unsigned char)zodis[0]) &&
                    zodis[1] == '.' &&
                    isupper((unsigned char)zodis[2]))
                {
                    continue;
                }

				// Atmetam jei neprasideda "http" ir turi //, pvz "//vilnius.com"
                if (zodis.find("//") != string::npos &&
                    zodis.find("http") != 0)
                {
                    continue;
                }

				// Atmetam per trumpus pvz. a.lt, b.com
                if (zodis.find("http") != 0 && zodis.find("www.") != 0) {
                    size_t dot = zodis.find('.');
                    if (dot != string::npos && dot <= 1) {
                        continue;
                    }
                }

				//pvz vilnius.lt//.vilnius
                if (zodis.find(".//") != string::npos) {
                    continue;
                }

                // Pasalinam galine skyryba
                while (!zodis.empty() && ispunct((unsigned char)zodis.back())) {
                    zodis.pop_back();
                }
				//pasaliname priekine skyryba pvz skliaustai, arba taskai
                while (!zodis.empty() && (ispunct((unsigned char)zodis.front()))) {
                    zodis.erase(zodis.begin());
                }

                // Idedam i URL rinkini
                url_pilnas.insert(zodis);
            }
			else { //nera url, tvarkom zodi
                string grazus_zodis = tvarkingas_zodis(zodis);
                if (!grazus_zodis.empty()) {

                    // Patikriname, ar zodyje yra bent viena raide
                    bool turi_raidziu = false;
                    for (char c : grazus_zodis) {
                        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
                            turi_raidziu = true;
                            break;
                        }
                    }
                    if (!turi_raidziu) continue;  // jei raidziu nera, praleidziame

                    // Atnaujiname zodziu skaiciu ir eilutes
                    zodziai[grazus_zodis]++;
                    zodziu_eil[grazus_zodis].first++;
                    zodziu_eil[grazus_zodis].second.insert(eil_nr);
                }
            }
        }
    }

    failas.close();

    Ifaila_zodziai(zodziai);
    failas_eilutems(zodziu_eil);

    if (!url_pilnas.empty()) {
        tvarkyti_url(url_pilnas);
    }
    else {
        cout << "URL adresu nerasta." << endl;
    }

}
