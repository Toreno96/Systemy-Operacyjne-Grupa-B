#include "../src/ZarzadzaniePamiecia.h"
#include<iostream>
#include<string>
#include<vector>
#include <math.h>

using std::cout;
using std::vector;
using std::endl;
using std::string;

//vector< typ_tablicy_stron* >TABLICA_POMOCNICZA;


	
// ram @
// plik wymiany #




int main()
{
	string kodprogramu = "123456789abcedfghijklmnoprstABCDEFGHIJK22222222222233333333333333332222222233333333333333333444444444444556677";
	///////////////////////////////
	inicjalizacja_PLIKU_WYMIANY();
	inicjalizacja_RAMU();
	///////////////////////////////

	//cout << "ilosc stronic danego procesu" << ilosc_stronic_danego_procesu << endl;
	typ_tablicy_stron& TABLICA_STRON = Porcjuj_i_wloz(kodprogramu);
	//fu(&TABLICA_STRON);

	/*
	cout << "ilosc stronic danego procesu" << ilosc_stronic_danego_procesu << endl;
	typ_tablicy_stron& TABLICA_STRON2 = Porcjuj_i_wloz(kodprogramu2);
	//fu(&TABLICA_STRON2);
	cout <<"ilosc stronic danego procesu"<< ilosc_stronic_danego_procesu << endl;
	

	for (int i = 0; i < wskazniki_na_tablice_stron.size(); ++i)
	cout<<	wskazniki_na_tablice_stron[i] << endl;
	*/


	/*
	for (int i = 0; i < TABLICA_POMOCNICZA.size(); ++i)
	cout << TABLICA_POMOCNICZA[i] << ' ';
	*/

	

	przeniesStroniceDoRamu(3, TABLICA_STRON);
	przeniesStroniceDoRamu(4, TABLICA_STRON);
	przeniesStroniceDoRamu(5, TABLICA_STRON);

	//WYPISZ_PLIK_WYMIANY();
	WYPISZ_RAM();





	/*
	cout << "przed" << endl;

	cout << "TABLICA_STRON2" << endl;
	for (int i = 0; i < TABLICA_STRON2.size(); ++i)
	{
		for (int j = 0; j < TABLICA_STRON2[i].size(); ++j)
			cout << TABLICA_STRON2[i][j] << ' ';
		cout << " " << endl;
	}


	cout << "TABLICA_STRON" << endl;
	for (int i = 0; i < TABLICA_STRON.size(); ++i)
	{
		for (int j = 0; j < TABLICA_STRON[i].size(); ++j)
			cout << TABLICA_STRON[i][j] << ' ';
		cout << " " << endl;
	}




	zwolnij_pamiec();
	


	cout << "TABLICA_STRON2" << endl;
	for (int i = 0; i < TABLICA_STRON2.size(); ++i)
	{
		for (int j = 0; j < TABLICA_STRON2[i].size(); ++j)
			cout << TABLICA_STRON2[i][j] << ' ';
		cout << " " << endl;
	}


	cout << "TABLICA_STRON" << endl;
	for (int i = 0; i < TABLICA_STRON.size(); ++i)
	{
		for (int j = 0; j < TABLICA_STRON[i].size(); ++j)
			cout << TABLICA_STRON[i][j] << ' ';
		cout << " " << endl;
	}

	/*
	 << "TABLICA_POMOCNICZA" << endl;
	for (int i = 0; i < TABLICA_POMOCNICZA.size(); ++i)
	{
		cout << TABLICA_POMOCNICZA[i] << ' ';
		cout << " " << endl;
	}

	cout << "POMOC" << endl;
	for (int i = 0; i < 17; ++i)
	{
		cout << POMOC[i] << ' ';
		cout << " " << endl;
	}
	
	
	*/



	return 0;
}



/* WEKTOR
for (int i = 0; i < TABLICA_STRON.size(); ++i)
{
//for (int j = 0; j < TABLICA_STRON[i].size(); ++j)
TABLICA_STRON[i][1] = 0;
}

WEKTOR
*/