#pragma once
#include "filesystemcommon.h"
#include <array>
using std::array;
#include <string>
using std::string;
#include <iostream>
using std::cout;
class Sector
{
private:
	array <bool, n> bitvector; //1 - blok wolny, 0 - blok zajety
	array <char, n> data; // nie wiem czy trzymac sie tej zasady //liczba 0 oznacza, �e mimo wszystko to nie jest �adna informacja. znak ma sens <=> znak>0
	bool mode; // 0 - przechowuje indeksy innych sektorow, 1 - przechowuje dane
	bool free; // 1 wolny, 0 - zajety
			   //metody pomocnicze
	array<bool, n> create_empty_bitvector()//metoda pomocnicza
	{
		array<bool, n> bitvector;
		for (auto it = bitvector.begin(); it != bitvector.end(); it++)
		{
			*it = 1;
		}
		return bitvector;
	}
	array<char, n> create_empty_data_array()//metoda pomocnicza
	{
		array<char, n> data_array;
		for (auto it = data_array.begin(); it != data_array.end(); it++)
		{
			*it = 0;
		}
		return data_array;
	}

public:
	Sector() // konstruktor
	{
		for (auto it = bitvector.begin(); it != bitvector.end(); it++)
		{
			*it = 1; // wszystkie bloki oznaczamy jako wolne
		}

		for (auto it = data.begin(); it != data.end(); it++)
		{
			*it = 35; // wypelniamy wszystkie bloki znakiem #
		}
		mode = 1; // tryb nie ma znaczenia, gdy state i tak jest wolny;
		free = 1; // oznaczamy sektor jako wolny
	}
	bool save_data(array <bool, n> bitvector, array <char, n> data, bool mode_) // 1 � operacja�zakonczona�pomyslnie
	{
		bitvector = bitvector; data = data; bool mode = mode_; free = 0; return 1;
	}
	array <bool, n> get_bitvector() { return bitvector; }
	array <char, n> get_data() { return data; }
	bool add_one_data(char one_data) // 1 jesli zakonczone pomyslnie
	{
		if (mode == 0)//jesli sektor przechowuje indeksy plikow
		{//podzial wynika z tego ze na koncu sektora indeksowego musi byc indeks kolejnego sektora indeksowego
			auto it = bitvector.begin();//iterator bitvectora
			int i = 0;
			for (; (it + 1) != bitvector.end() && (*it != 1); it++, i++) // szukamy wolnego bool czyli char w array data
			{
			}
			if ((it + 1) != bitvector.end() && *it == 1) // jesli znalezlismy wolny element
			{
				data[i] = one_data;
				return 1;
			}
			else if ((it + 1) == bitvector.end()) // jesli wszystko az do przedostatniego jest zajete
			{
				return 0;
			}
			else
			{
				return 0;
				cout << "\nNieznany blad";
			}
		}
		else if (mode == 1)// jesli sektor przechowuje dane
		{
			auto it = bitvector.begin();//iterator bitvectora
			int i = 0;
			for (; it != bitvector.end() && (*it != 1); it++, i++) // szukamy wolnego bool czyli char w array data
			{
			}
			if (it != bitvector.end() && *it == 1) // jesli znalezlismy wolny element
			{
				data[i] = one_data;
				return 1;
			}
			else if (it == bitvector.end()) // jesli wszystko jest zajete
			{
				return 0;
			}
			else
			{
				return 0;
				cout << "\nNieznany blad";
			}
		}
		else
		{
			cout << "\nBieznany blad. Tryb pliku nierozpoznany";
		}
	}
	bool add_last_data(char one_data) // 1 operacja zakonczona pomyslnie
	{//umozliwia dodanie swiadomie ostatniego elementu w przypadku sektora indeksowego
		if (bitvector[n - 1] == 1)//jesli ostatni element jest wolny
		{
			data[n - 1] = one_data;
			return 1;
		}
		else
		{
			return 0;
		}

	}
	void set_mode(bool mode_)
	{
		mode = mode_;
	}
	void set_free(bool free_)
	{
		free = free_;
	}
	string get_data_as_string()
	{
		string result;
		auto it = bitvector.begin();
		auto it2 = data.begin();//auto it2 = 0;
		for (; *it == 0; it++, it2++)
		{
			result.push_back(*it2);
			cout << "\nDodaje " << *it2;
		}
		return result;
	}
	bool get_mode() { return mode; }
	bool is_free() // 1 - wolny, 0 - zajety
	{
		return free;
	}
	bool get_last_bitvector()
	{
		return bitvector[n - 1];
	}
	char get_last_data() // zwraca ostatni element niezaleznie czy jest uzywany czy jest smieciami
	{
		return data[n - 1];
	}
};