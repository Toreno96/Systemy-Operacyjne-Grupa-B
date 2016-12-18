#ifndef ZarzadzaniePamiecia_h
#define ZarzadzaniePamiecia_h
/////////////////////////////////

#include<iostream>
#include<string>
#include<vector>
#include <deque>
#include <math.h>

using std::cout;
using std::vector;
using std::deque;
using std::endl;
using std::string;

typedef vector< vector< int > > typ_tablicy_stron;

/// GLOBALNE NA POLECENIE  MASTERA
extern vector<char>PLIK_WYMIANY;
extern vector<char>RAM;
//extern char*PLIK_WYMIANY;
//extern char*RAM;
extern int RAMKA_DO_USUNIECIA;
extern int ilosc_stronic_danego_procesu;
extern deque<typ_tablicy_stron>TABLICA_POMOCNICZA; //vector< typ_tablicy_stron* >TABLICA_POMOCNICZA;
extern vector< typ_tablicy_stron* > wskazniki_na_tablice_stron;
extern vector< int > POMOC;
extern int ILE_STRONIC_JEST_ZAJETYCH;
/// GLOBALNE NA POLECENIE  MASTERA
/////////////////////////////////

void inicjalizacja_RAMU();
void inicjalizacja_PLIKU_WYMIANY();
void zapewnij_wolne_miejsce_w_ramie();
void wpisz_do_TABLICY_STRON(typ_tablicy_stron &TABLICA_STRON, int Numer_Strony, int WOLNA_RAMKA_KTORA_BEDZIE_ZAJETA);
typ_tablicy_stron& Porcjuj_i_wloz(string kodprogramu);
void przeniesStroniceDoRamu(int Numer_Strony, typ_tablicy_stron &TABLICA_STRON);
char daj_mi_litere(int adres_logiczny, typ_tablicy_stron &TABLICA_STRON);
void zwolnij_pamiec();   //typ_tablicy_stron &TABLICA_STRON)
void fu(typ_tablicy_stron*TABLICA_STRON);
void WYPISZ_RAM();
void WYPISZ_PLIK_WYMIANY();
#endif