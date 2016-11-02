#include <iostream>
#include <string>
#include <list>
#include <array>
using std::string;

class FCB // blok kontrolny pliku
{
private:
	char user_code;
	std::array <char, 8> filename{};
	char typ [3]; // rozszerzenie np txt
	char* indeks1;
	char* indeks2;
	char* indeks3;
	char* indeks4;
	char* indeks5;

public:
	FCB(std::array <char, 8> filename_, char atrybut_) : filename(filename_)
	{}
};

class Sektor
{
private:
	std::array <bool, 16> bitvector{}; //1 - blok wolny, 0 - blok zajety
	std::array <char, 16> data{};

public:
	Sektor() // konstruktor
	{
		for (auto it = bitvector.begin(); it != bitvector.end(); it++)
		{
			*it = 1; //oznaczanie wszystkich pol sektora jako wolne
		}
	}

	void zapisz_plik() {}
	bool czy_mozna wpisac plik() {}

};

class Dysk
{
private:
	std::array <char, 16> cashe{};
	std::list <FCB> Katalog{};
	Sektor dysk [16];
	void zajmij_byte()
	{}
	void zwolnij_byte() {}
	char wyslij_do_cashe() {}
	char zapisz_z_cashe() {}

public:
	Dysk() // konstruktor
	{
		for(int i=0; i<32; i++)
		cashe[i] = 0;
	}

	void utworz_plik(std::array <char, 8> filename_, std::array <char, 3> typ, unsigned char user_code) {}
	void usun_plik(std::array <char, 8> filename_, std::array <char, 3> typ, unsigned char user_code) {}
	void otworz_plik(std::array <char, 8> filename_, std::array <char, 3> typ, unsigned char user_code) {}
	void edytuj_plik(std::array <char, 8> filename_, std::array <char, 3> typ, unsigned char user_code) {}
	void wyswietl_liste_plików() {}
	dostepnosc_sektora() {}
	szukaj wolnego sektora() {}
	szukaj sektora po nazwie.
	
};