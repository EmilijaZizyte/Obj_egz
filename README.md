# Teksto analizės programa 

## Aprašymas

Ši C++ programa skirta teksto failo analizei. Ji nuskaito vartotojo pasirinktą tekstinį failą ir:

- Suskaičiuoja žodžių pasikartojimo skaičių
- Nustato, kuriose eilutėse žodžiai pasikartoja
- Aptinka ir surenka URL adresus
- Rezultatus išsaugo tekstiniuose failuose arba, pagal pasirinkimą, išveda į terminalą
---

## Funkcionalumas

###  Žodžių apdorojimas
- Žodžiai paverčiami mažosiomis raidėmis
- Pašalinami skaičiai ir skyrybos ženklai
- Skaičiuojami tik žodžiai, turintys bent vieną raidę
- Ignoruojami simbolių rinkiniai be raidžių

---

### Žodžių pasikartojimo skaičiavimas
- Skaičiuojama, kiek kartų kiekvienas žodis pasikartoja
- Į rezultatų failą įrašomi tik tie žodžiai, kurie pasikartojo daugiau nei vieną kartą
- Rezultatai išsaugomi faile: „zodziu_kiekis.txt“

---

###  Žodžių pasikartojimas eilutėse
- Nustatoma, kuriose teksto eilutėse pasirodo kiekvienas žodis
- Įrašomi tik tie žodžiai, kurie pasikartojo daugiau nei vieną kartą
- Rezultatai išsaugomi faile:  „eilutese_pasikartoja.txt“

---

###  URL adresų atpažinimas
Programa aptinka šių tipų URL adresus:
- `https://vilnius.com`
- `http://www.vilnius.lt`
- `www.vilnius.lt`

Filtravimas:
- Atmetami per trumpi URL (pvz. `a.lt`)
- Atmetami neteisingi URL (pvz. `//vilnius.com`)
- Pašalinami skyrybos ženklai URL pradžioje ir pabaigoje
- Ignoruojami vardų trumpiniai (pvz. `V.ilnius`)

Vartotojas gali pasirinkti:
- rodyti URL terminale
- išsaugoti URL faile
- URL išsaugomi faile:  „url_info.txt“

---

## Programos veikimas

1. Vartotojas įveda analizuojamo failo pavadinimą
2. Programa nuskaito failą eilutė po eilutės
3. Kiekvienas žodis tikrinamas:
   - ar tai URL adresas
   - ar paprastas žodis
4. Atliekama analizė ir sugeneruojami rezultatų failai
5. Jei rasta URL – vartotojas pasirenka, kur juos rodyti


##  Sukuriami failai

- „zodziu_kiekis.txt“ – žodžių pasikartojimų skaičius
- „eilutese_pasikartoja.txt“ – eilutės, kuriose žodžiai pasikartoja
- „url_info.txt“ – rasti URL adresai

## Kaip sukompiliuoti ir paleisti programą

1. Iš šios github repozitorijos, atsisiųskite CMakeFiles.txt, run.bat failus ir src ir include aplankus.

2. Susikurkite darbinį aplankalą, kuriame norėsite vykdyti programą. Į šį aplanką įdėkite visus parsisiųstus failus iš github.

3.Atidarykite komandų eilutę (cmd) ir eikite į projekto katalogą, kuriame yra CMakeLists.txt. 
- Pavyzdžiui:
- cd C:\Users\computer\Desktop\CmakeTest2

4.Sugeneruokite build failus su CMake komanda:
- cmake .\CMakeLists.txt

5.Skompiliuokite projektą:
- cmake --build 

6.Pereikite į katalogą, kuriame sukurtas vykdomasis failas:
- cd C:\Users\computer\Desktop\cmake\build\Debug

5.Paleiskite programą:
- analizuojam_straipsnius.exe

Vaizdinis pavyzdys:

<img width="1366" height="857" alt="image" src="https://github.com/user-attachments/assets/bebee388-15f2-4716-849e-2347a0e17a01" />

