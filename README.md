# Monopoly

A simple command line Monopoly game!

# Features list
- Play with up to 7 friends
- Intuitive commands
- Inspired by the classic Monopoly game you know and love
- Free and open source
- Cross-platform
- Full colorblind support coming soon!

# Installation
Just download the latest release for your operating system and run the executable!


# Development

## Tema 0

- [X] Nume proiect (poate fi schimbat ulterior)
- [X] Scurtă descriere a temei alese, ce v-ați propus să implementați

## Tema 1

#### Cerințe
- [X] definirea a minim **3-4 clase** folosind compunere cu clasele definite de voi
- [X] constructori de inițializare
- [X] pentru o aceeași (singură) clasă: constructor de copiere, `operator=` de copiere, destructor
<!-- - [ ] pentru o altă clasă: constructor de mutare, `operator=` de mutare, destructor -->
<!-- - [ ] pentru o altă clasă: toate cele 5 funcții membru speciale -->
- [X] `operator<<` pentru toate clasele pentru afișare 
- [X] cât mai multe `const` (unde este cazul)
- [X] implementarea a minim 3 funcții membru publice pentru funcționalități specifice temei alese, dintre care cel puțin 1-2 funcții mai complexe
  - nu doar citiri/afișări sau adăugat/șters elemente într-un/dintr-un vector
- [X] scenariu de utilizare a claselor definite:
  - crearea de obiecte și apelarea tuturor funcțiilor membru publice în main
  - vor fi adăugate în fișierul `tastatura.txt` DOAR exemple de date de intrare de la tastatură (dacă există); dacă aveți nevoie de date din fișiere, creați alte fișiere separat
- [X] tag de `git`: de exemplu `v0.1`
- [X] serviciu de integrare continuă (CI); exemplu: GitHub Actions

### Tema 2

#### Cerințe
- [X] separarea codului din clase în `.h` (sau `.hpp`) și `.cpp`
- [X] moșteniri:
  - minim o clasă de bază și **3 clase derivate**
  - ierarhia trebuie să fie cu bază proprie, nu derivată dintr-o clasă predefinită
  - [X] clasă cu atribut de tip pointer la o clasă de bază cu derivate
  - [X] funcții virtuale (pure) apelate prin pointeri de bază din clasa care conține atributul de tip pointer de bază
    - minim o funcție virtuală va fi **specifică temei** (e.g. nu simple citiri/afișări)
    - constructori virtuali (clone): sunt necesari, dar nu se consideră funcții specifice temei
  - [X] apelarea constructorului din clasa de bază din constructori din derivate
  - [X] smart pointers (recomandat, opțional)
  - [X] `dynamic_cast`/`std::dynamic_pointer_cast` pentru downcast cu sens
- [X] suprascris cc/op= pentru copieri/atribuiri corecte, copy and swap
- [X] excepții
  - [X] ierarhie proprie cu baza `std::exception` sau derivată din `std::exception`; minim **3** clase pentru erori specifice
  - [X] utilizare cu sens: de exemplu, `throw` în constructor (sau funcție care întoarce un obiect), `try`/`catch` în `main`
- [X] funcții și atribute `static`
- [X] STL
- [X] cât mai multe `const`
- [X] la sfârșit: commit separat cu adăugarea unei noi clase derivate fără a modifica restul codului, **pe lângă cele 3 derivate deja adăugate**
  - noua derivată nu poate fi una existentă care a fost ștearsă și adăugată din nou
- [X] tag de `git`: de exemplu `v0.2`

## Tema 3

#### Cerințe
- [X] 2 șabloane de proiectare (design patterns)
- [X] o clasă șablon cu sens; minim **2 instanțieri**
  - [X] preferabil și o funcție șablon (template) cu sens; minim 2 instanțieri
<!-- - [ ] o specializare pe funcție/clasă șablon -->
- [X] tag de `git`: de exemplu `v0.3` sau `v1.0`

## Resurse
https://github.com/nlohmann/json

https://github.com/ikalnytskyi/termcolor

https://github.com/tapio/rlutil