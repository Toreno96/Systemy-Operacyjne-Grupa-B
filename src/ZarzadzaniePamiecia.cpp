#include <algorithm>
#include"ZarzadzaniePamiecia.h"
#include<iostream>
#include<string>
#include<vector>
#include <math.h>

using std::cout;
using std::vector;
using std::endl;
using std::string;

/// GLOBALNE NA POLECENIE  MASTERA
vector<char>PLIK_WYMIANY(2048);
vector<char>RAM(256);
//char*PLIK_WYMIANY = new char[2048];
//char*RAM = new char[256];
int RAMKA_DO_USUNIECIA = 0;
int ilosc_stronic_danego_procesu = 0;
deque<typ_tablicy_stron>TABLICA_POMOCNICZA;  //vector< typ_tablicy_stron* >TABLICA_POMOCNICZA;
vector< typ_tablicy_stron* > wskazniki_na_tablice_stron;
vector< int >POMOC(16);
int ILE_STRONIC_JEST_ZAJETYCH = 0;
/// GLOBALNE NA POLECENIE  MASTERA
/////////////////////////////////

void inicjalizacja_RAMU()
{
	for (int i = 0; i < 256; i++)
		RAM[i] = '@';
}
void inicjalizacja_PLIKU_WYMIANY()
{
	for (int i = 0; i < 2048; i++)
		PLIK_WYMIANY[i] = '#';
}
void zapewnij_wolne_miejsce_w_ramie()     //wywo³uj to zawsze przed przeniesieniem stronicy do ramki
{
	int czyjestmiejsce = 1;

	for (int i = 0; i < 17; i++)  //bo tyle ramek w ramie + ramka 0 czyli 16
	{
		if (RAM[16 * i] == '@')
		{
			czyjestmiejsce = 1;
			break;
		}

		if (i == 16)
		{
			zwolnij_pamiec();
			//czyjestmiejsce = 0;
		}
	}
}
void wpisz_do_TABLICY_STRON(typ_tablicy_stron &TABLICA_STRON, int Numer_Strony, int WOLNA_RAMKA_KTORA_BEDZIE_ZAJETA)
{
	auto& wiersz_tablicy_stron =
			*( find_if( TABLICA_STRON.begin(), TABLICA_STRON.end(),
					[ Numer_Strony ]( const std::vector< int >& wiersz ) {
						return wiersz[ 0 ] == Numer_Strony;
					} ) );
	wiersz_tablicy_stron[1] = 1;
	wiersz_tablicy_stron[0] = WOLNA_RAMKA_KTORA_BEDZIE_ZAJETA;
}
typ_tablicy_stron& Porcjuj_i_wloz(string kodprogramu)
{
	//////DLA_MOJEGO_MASTERA_DLA_NIEGO_WEKTOR///////
	typ_tablicy_stron TABLICA_STRON;
	const int liczbaWierszy = 16;
	const int liczbaKolumn = 2;
	for (int i = 0; i < liczbaWierszy; ++i)
		TABLICA_STRON.push_back(vector< int >(liczbaKolumn));

	//////////////////INICJALIZACJA TABLIC STRON
	for (std::size_t i = 0; i < TABLICA_STRON.size(); ++i)
	{
		for (std::size_t j = 0; j < TABLICA_STRON[i].size(); ++j)
			TABLICA_STRON[i][j] = 0;
	}
	//////DLA_MOJEGO_MASTERA_DLA_NIEGO_WEKTOR///////

	int length_of_program_size = kodprogramu.length();//fajnie byloby wiedziec ile on stron/ramek zajmie
	ilosc_stronic_danego_procesu = ceil((static_cast<float>(length_of_program_size)) / 16);
	////rzutowanie + zaaaokraglenie w gore
	

																								 //cout << ilosc_stronic_danego_procesu << endl;


 ////////////wpisanie stronic do tablicy stron numeru zajmowanych stronic PRZEZ DANY PROCES
	for (int i = 0; i <ilosc_stronic_danego_procesu; ++i)
	{
		TABLICA_STRON[i][0] = ILE_STRONIC_JEST_ZAJETYCH;
		ILE_STRONIC_JEST_ZAJETYCH++;
	}


	//// WlASCIWA CZESC TEJ FUNKCJI
	for (int i = 0; i<127; i++)  /////bo 2048/16 -1 =128-1
	{
		int przerwij = 0;
		if (PLIK_WYMIANY[16 * i] == '#')
		{
			for (std::size_t j = 0; j < kodprogramu.size(); j++)
				PLIK_WYMIANY[16 * i + j] = kodprogramu[j];
			przerwij = 1;
		}
		if (przerwij == 1)
			break;
	}

	TABLICA_POMOCNICZA.push_back(TABLICA_STRON);
	typ_tablicy_stron& referencja_na_tablice_stron = TABLICA_POMOCNICZA.back();
	fu(&referencja_na_tablice_stron);
	return referencja_na_tablice_stron;
}
void  przeniesStroniceDoRamu(int Numer_Strony, typ_tablicy_stron &TABLICA_STRON)
{
	int a = Numer_Strony * 16;
	int b = a + 15;

	for (int i = 0; i < 17; i++)  //bo tyle ramek w ramie + ramka 0 czyli 16
	{
		int przerwij = 0;
		if (RAM[16 * i] == '@')
		{
			int WOLNA_RAMKA_KTORA_BEDZIE_ZAJETA = i;
			wpisz_do_TABLICY_STRON(TABLICA_STRON, Numer_Strony, WOLNA_RAMKA_KTORA_BEDZIE_ZAJETA);   ///WLACZENIE FUNKCJI KTORA ZAPISUJE TO W TABLICY STRON

			POMOC[i] = Numer_Strony;  ///WPISANIE DO TABLICY NUMERU RAMKI


			for (int j = 0; j < 16; j++)
			{
				RAM[16 * i + j] = PLIK_WYMIANY[a];
				a++;
				///ustal_porzadek_ramek  ///CHYBA NIE MUSZE ///bo musze znac kolejnosc wchodzenia tych stron do RAMU!!
				if (a == b + 1)
					break;
			}
			przerwij = 1;
		}
		if (przerwij == 1)
			break;
	}
}
char daj_mi_litere(int adres_logiczny, typ_tablicy_stron &TABLICA_STRON)
{
	char odczytany_znak;
	int numer_strony;
	int numer_ramki;
	int przesuniecie = adres_logiczny % 16;

	/*if (adres_logiczny > 255)
		std::cout << adres_logiczny << '\n' << adres_logiczny / 16 << '\n';*/
	numer_strony = adres_logiczny / 16;
	/*std::cout << numer_strony << '\n';*/

	auto& wiersz_tablicy_stron =
			*( find_if( TABLICA_STRON.begin(), TABLICA_STRON.end(),
					[ numer_strony ]( const std::vector< int >& wiersz ) {
						return wiersz[ 0 ] == numer_strony;
					} ) );
	if( wiersz_tablicy_stron[ 1 ] == 0 ) {
		zapewnij_wolne_miejsce_w_ramie();
		przeniesStroniceDoRamu(numer_strony, TABLICA_STRON);
	}
	numer_ramki = wiersz_tablicy_stron[0];
	odczytany_znak = RAM[numer_ramki * 16 + przesuniecie];

/*
	//SPRAWDZAM CZY DANA STRONA JEST W RAMIE /// A TU JEST W RAMIE
	if (TABLICA_STRON[numer_strony][1] == 1)
	{
		numer_ramki = TABLICA_STRON[numer_strony][0];
		//jesli mam numer ramki to moge odczytac z ramu!
		odczytany_znak = RAM[numer_ramki * 16 + przesuniecie];
	}

	//SPRAWDZAM CZY DANA STRONA JEST W RAMIE   ///TU  JEJ NIE MA
	if (TABLICA_STRON[numer_strony][1] == 0)  //nie ma jej, a wiec naleza˜oby ja przniesc do ramu
	{
		zapewnij_wolne_miejsce_w_ramie();
		przeniesStroniceDoRamu(numer_strony, TABLICA_STRON);

		numer_ramki = TABLICA_STRON[numer_strony][0];
		odczytany_znak = RAM[numer_ramki * 16 + przesuniecie];
	}
*/

	return odczytany_znak;
}
void zwolnij_pamiec()//typ_tablicy_stron &TABLICA_STRON
{
	int a;
	int b;
	switch (RAMKA_DO_USUNIECIA)
	{
	case 0:
		a = 0;
		b = 15;
		break;
	case 1:
		a = 16;
		b = 31;
		break;
	case 2:
		a = 32;
		b = 47;
		break;
	case 3:
		a = 48;
		b = 63;
		break;
	case 4:
		a = 64;
		b = 79;
		break;
	case 5:
		a = 80;
		b = 95;
		break;
	case 6:
		a = 96;
		b = 111;
		break;
	case 7:
		a = 112;
		b = 127;
		break;
	case 8:
		a = 128;
		b = 143;
		break;
	case 9:
		a = 144;
		b = 159;
		break;
	case 10:
		a = 160;
		b = 175;
		break;
	case 11:
		a = 176;
		b = 191;
		break;
	case 12:
		a = 192;
		b = 207;
		break;
	case 13:
		a = 208;
		b = 223;
		break;
	case 14:
		a = 224;
		b = 239;
		break;
	case 15:
		a = 240;
		b = 255;
		break;
	}
	///odczytuje to co jest pod indeksem RAMKA_DO_USUNIECIA Z wektora POMOC
	int yy;
	yy = POMOC[RAMKA_DO_USUNIECIA]; //yy to stronica ktora zostanie usunieta
	typ_tablicy_stron &tablica_stron = *(wskazniki_na_tablice_stron[yy]);


	for (int i = a; i <= b; i++)
	{
		RAM[i] = '@';
	}

	// teraz czas na czyszczenie tablic stron
	tablica_stron[RAMKA_DO_USUNIECIA][1] = 0;
	tablica_stron[RAMKA_DO_USUNIECIA][0] = 0;

	/// i dopiero tera moge sobie inkrementowac
	RAMKA_DO_USUNIECIA++;
	/// easy
	if (RAMKA_DO_USUNIECIA == 15)
		RAMKA_DO_USUNIECIA = 0;
}
void fu(typ_tablicy_stron*TABLICA_STRON)
{
	for (int i = 0; i<ilosc_stronic_danego_procesu; i++)
		wskazniki_na_tablice_stron.push_back(TABLICA_STRON);
}


/////////FUNKCJE WYPISUJACE///////
void WYPISZ_PLIK_WYMIANY()
{
	int hehe = 0;
	for (int i = 0; i <2048; i++)       /// tutaj tylko 1200 poniewaz 2048 nie wypisuje ....
	{
		if (i%1200==1184)
		{
			cout << endl;
			cout << "Prosze nacisnij enter raz jeszcze..." << endl;
			std::cin.get();
		}

		if (i % 16== 0)
		{
			cout << "\n\n";
			cout << "      STRONICA '" << hehe<< "'" << endl;
			hehe++;
		}

		if (PLIK_WYMIANY[i] == '\n')
			cout << '^';
		else
			cout << PLIK_WYMIANY[i];
	}
	std::cout << '\n';
}
void WYPISZ_RAM()
{
	int yyy = 0;
	for (int i = 0; i < 256; i++)
	{
		if (i % 16 == 0)
		{
			cout << "\n\n";
			cout << "     RAMKA '"<<yyy<<"'"<< endl;
			yyy++;
		}
		if (RAM[i] == '\n')
			cout << '^';
		else
			cout << RAM[i];
	}
	std::cout << '\n';
}