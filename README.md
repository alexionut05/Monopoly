# Monopoly
NU E FINAL!
Apreciez daca imi dati feedback, insa recomandarea mea ar fi sa nu va luati din timp pt asta inca, pt ca mai am niste functionalitati de adaugat in game.cpp, insa iau o pauza in aceasta seara ca de sambata dimineata de cand m-am apucat nu prea m-am odihnit si pierd randament. Maxim in README.md (am lasat comentarii in paranteze + atribuire in josul paginii), CMakeLists.txt si in cmake.yml daca e pt feedback, am aplicat recomandarile. 

De asemenea am inlaturat destructorii si setterii inutili intr-un mare refactor (cu exceptia card.cpp, pentru a indeplini cerinta din tema 1), sper ca e in regula acum. Unii setteri rari i-am lasat; consider ca sunt absolut necesari.

Voi inlatura apelul de sistem din game.cpp inainte de primul release, dar pe moment il pastrez pentru a putea testa fara sa rescriu partea aia.

Multumesc pt feedback in avans si pt intelegerea cu deadline-ul!

Estimare terminare tema 1: 30 aprilie - 2 mai
Estimare terminare tema 2: 3-5 mai
NU E FINAL!

Un joc de Monopoly in comanda de linie.

### Tema 0

- [X] Nume proiect (poate fi schimbat ulterior)
- [X] Scurtă descriere a temei alese, ce v-ați propus să implementați

## Tema 1

#### Cerințe
- [X] definirea a minim **3-4 clase** folosind compunere cu clasele definite de voi
- [X] constructori de inițializare
- [X] pentru o aceeași (singură) clasă: constructor de copiere, `operator=` de copiere, destructor (src/card.cpp)
<!-- - [ ] pentru o altă clasă: constructor de mutare, `operator=` de mutare, destructor -->
<!-- - [ ] pentru o altă clasă: toate cele 5 funcții membru speciale -->
- [X] `operator<<` pentru toate clasele pentru afișare (std::ostream)
- [X] cât mai multe `const` (unde este cazul)
- [X] implementarea a minim 3 funcții membru publice pentru funcționalități specifice temei alese, dintre care cel puțin 1-2 funcții mai complexe
  - nu doar citiri/afișări sau adăugat/șters elemente într-un/dintr-un vector
- [X] scenariu de utilizare a claselor definite:
  - crearea de obiecte și apelarea tuturor funcțiilor membru publice în main
  - vor fi adăugate în fișierul `tastatura.txt` DOAR exemple de date de intrare de la tastatură (dacă există); dacă aveți nevoie de date din fișiere, creați alte fișiere separat
- [ ] tag de `git`: de exemplu `v0.1` (voi face release odata ce termin game.cpp)
- [X] serviciu de integrare continuă (CI); exemplu: GitHub Actions

## Tema 2

#### Cerințe
- [X] separarea codului din clase în `.h` (sau `.hpp`) și `.cpp`
- [ ] moșteniri:
  - minim o clasă de bază și **3 clase derivate**
  - ierarhia trebuie să fie cu bază proprie, nu derivată dintr-o clasă predefinită
  - [X] clasă cu atribut de tip pointer la o clasă de bază cu derivate (src/game.cpp)
  - [ ] funcții virtuale (pure) apelate prin pointeri de bază din clasa care conține atributul de tip pointer de bază
    - minim o funcție virtuală va fi **specifică temei** (e.g. nu simple citiri/afișări)
    - constructori virtuali (clone): sunt necesari, dar nu se consideră funcții specifice temei
  - [X] apelarea constructorului din clasa de bază din constructori din derivate (src/tiles/*.cpp)
  - [X] smart pointers (recomandat, opțional) (src/board.cpp)
  - [X] `dynamic_cast`/`std::dynamic_pointer_cast` pentru downcast cu sens (src/game.cpp)
- [X] suprascris cc/op= pentru copieri/atribuiri corecte, copy and swap (src/card.cpp)
- [ ] excepții
  - [ ] ierarhie proprie cu baza `std::exception` sau derivată din `std::exception`; minim **3** clase pentru erori specifice
  - [ ] utilizare cu sens: de exemplu, `throw` în constructor (sau funcție care întoarce un obiect), `try`/`catch` în `main`
- [ ] funcții și atribute `static` (voi "staticiza" inainte de al doilea release)
- [ ] STL (nu stiu sigur daca se pun ca STL anumite functionalitati, un feedback ar fi apreciat)
- [X] cât mai multe `const`
- [ ] la sfârșit: commit separat cu adăugarea unei noi clase derivate fără a modifica restul codului, **pe lângă cele 3 derivate deja adăugate**
  - noua derivată nu poate fi una existentă care a fost ștearsă și adăugată din nou
- [ ] tag de `git`: de exemplu `v0.2`

## Tema 3

#### Cerințe
- [ ] 2 șabloane de proiectare (design patterns)
- [ ] o clasă șablon cu sens; minim **2 instanțieri**
  - [ ] preferabil și o funcție șablon (template) cu sens; minim 2 instanțieri
<!-- - [ ] o specializare pe funcție/clasă șablon -->
- [ ] tag de `git`: de exemplu `v0.3` sau `v1.0`

## Resurse
https://github.com/nlohmann/json
https://github.com/ikalnytskyi/termcolor