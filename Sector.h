#pragma once
#include "filesystemcommon.h"
#include <array>
using std::array;
#include <string>
using std::string;
class Sector
{
private:
	array <bool, sn> bitvector; //1 - blok wolny, 0 - blok zajety
	array <char, sn> data; // nie wiem czy trzymac sie tej zasady //liczba 0 oznacza, ¿e mimo wszystko to nie jest ¿adna informacja. znak ma sens <=> znak>0
	bool mode; // 0 - przechowuje indeksy innych sektorow, 1 - przechowuje dane
	bool free; // 1 wolny, 0 - zajety
			   //metody pomocnicze
	array<bool, sn> create_empty_bitvector();//metoda pomocnicza
	array<char, sn> create_empty_data_array();//metoda pomocnicza

public:
	Sector() // konstruktor
	{
		for (auto it = bitvector.begin(); it != bitvector.end(); it++)
		{
			*it = 1; // wszystkie bloki oznaczamy jako wolne
		}

		for (auto it = data.begin(); it != data.end(); it++)
		{
			*it = 0; // wypelniamy wszystkie bloki znakiem 0
		}
		mode = 1; // tryb nie ma znaczenia, gdy state i tak jest wolny;
		free = 1; // oznaczamy sektor jako wolny
	}
	void save_data(array <bool, sn> bitvector_, array <char, sn> data_, bool mode_);
	array <bool, sn> get_bitvector();
	array <char, sn> get_data();
	bool add_one_data(char one_data); // 1 - zakonczone pomyslnie
	bool add_last_data(char one_data); // 1 - zakonczone pomyslnie
	void set_mode(bool mode_);
	void set_free(bool free_);
	string get_data_as_string();
	bool get_mode();
	bool is_free(); // 1 - wolny, 0 - zajety
	bool get_last_bitvector();
	char get_last_data(); // zwraca ostatni element niezaleznie czy jest uzywany czy jest smieciami
};