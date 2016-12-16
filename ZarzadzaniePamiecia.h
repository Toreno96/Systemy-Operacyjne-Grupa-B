#pragma once

#include<iostream>
#include<string>
#include<vector>
#include <math.h>
#include<deque>
using std::cout;
using std::vector;
using std::endl;
using std::string;
using std::deque;
typedef vector< vector< int > > typ_tablicy_stron;


class ZarzadzaniePamiecia
{
	
public:
	/// GLOBALNE NA POLECENIE  MASTERA
    vector<char>PLIK_WYMIANY;
	vector<char>RAM;
	int RAMKA_DO_USUNIECIA;
	int ilosc_stronic_danego_procesu;
	deque<typ_tablicy_stron>TABLICA_POMOCNICZA;                  //vector< typ_tablicy_stron* >TABLICA_POMOCNICZA;
	vector< typ_tablicy_stron* > wskazniki_na_tablice_stron;
	vector< int >POMOC;
	int ILE_STRONIC_JEST_ZAJETYCH;
	/// GLOBALNE NA POLECENIE  MASTERA
	/////////////////////////////////
	ZarzadzaniePamiecia();
	~ZarzadzaniePamiecia();

	void inicjalizacja_RAMU();
	void inicjalizacja_PLIKU_WYMIANY();
	void zapewnij_wolne_miejsce_w_ramie();// OD TERAZ NIC NIE ZWRACA TYLKO TRZEBA TO WYWOLAC PRZED PRZENIESIENIEM STRONICY DO RAMKI
	void wpisz_do_TABLICY_STRON(typ_tablicy_stron &TABLICA_STRON, int Numer_Strony, int WOLNA_RAMKA_KTORA_BEDZIE_ZAJETA);
	typ_tablicy_stron& Porcjuj_i_wloz(string kodprogramu);
	void przeniesStroniceDoRamu(int Numer_Strony, typ_tablicy_stron &TABLICA_STRON);
	char daj_mi_litere(int adres_logiczny, typ_tablicy_stron &TABLICA_STRON);
	void zwolnij_pamiec();   //typ_tablicy_stron &TABLICA_STRON)
	void fu(typ_tablicy_stron*TABLICA_STRON);
};

