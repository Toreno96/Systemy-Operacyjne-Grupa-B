#pragma once
#include "filesystemcommon.h"
#include <array>
using std::array;
#include <string>
using std::string;
#include <iostream>
using std::cout;
#include "Sector.h"

array<bool, sn> Sector::create_empty_bitvector()//metoda pomocnicza
	{
		array<bool, sn> bitvector;
		for (auto it = bitvector.begin(); it != bitvector.end(); it++)
		{
			*it = 1;
		}
		return bitvector;
	}
array<char, sn> Sector::create_empty_data_array()//metoda pomocnicza
	{
		array<char, sn> data_array;
		for (auto it = data_array.begin(); it != data_array.end(); it++)
		{
			*it = 0;
		}
		return data_array;
	}

void Sector::save_data(array <bool, sn> bitvector_, array <char, sn> data_, bool mode_)
	{
		bitvector = bitvector_; data = data_; bool mode = mode_; free = 0;
		//cout << "\nSprawdzmy jak wyglada data: ";
		//for (auto it = data.begin(); it != data.end(); it++)
		//cout << *it;
	}
array <bool, sn> Sector::get_bitvector() { return bitvector; }
array <char, sn> Sector::get_data() { return data; }
bool Sector::add_one_data(char one_data) // 1 - zakonczone pomyslnie
	{
		if (mode == 0)//jesli sektor przechowuje indeksy plikow
		{//podzial wynika z tego ze na koncu sektora indeksowego musi byc indeks kolejnego sektora indeksowego
		 //cout << "\nMetoda add_one_data dla sektora indeksowego";
			auto it = bitvector.begin();//iterator bitvectora
			int i = 0;
			for (; (it + 1) != bitvector.end() && (*it != 1); it++, i++) // szukamy wolnego bool czyli char w array data
			{
			}
			//cout << "\nWolny char to " << i;
			if ((it + 1) != bitvector.end() && *it == 1) // jesli znalezlismy wolny element i nie jest on ostatni
			{
				*it = 0; // oznaczamy char jako zajety
				data[i] = one_data;
				//cout << "\nPrzypisalismy " << (int)one_data << " do chara " << i;
				return 1;
			}
			else if ((it + 1) == bitvector.end()) // jesli wszystko az do przedostatniego jest zajete
			{
				return 0;
			}
			else
			{
				cout << "\nNieznany blad w metodzie bool add_one_data(char one_data)"; // To sie nie powinno zdarzyc
				return 0;
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
				cout << "\nNieznany blad"; // To sie nie ma prawa zdarzyc
			}
		}
		else
		{
			cout << "\nBieznany blad. Tryb pliku nierozpoznany"; // To sie nie ma prawa zdarzyc
			return 0;
		}
	}
bool Sector::add_last_data(char one_data) // 1 - zakonczone pomyslnie
	{//umozliwia dodanie swiadomie ostatniego elementu w przypadku sektora indeksowego
		if (bitvector[sn - 1] == 1)//jesli ostatni element jest wolny
		{
			bitvector[sn - 1] = 0; //ustawiamy char na zajety
			data[sn - 1] = one_data;
			return 1;
		}
		else
		{
			return 0;
		}

	}
void Sector::set_mode(bool mode_)
	{
		mode = mode_;
	}
void Sector::set_free(bool free_)
	{
		free = free_;
	}
string Sector::get_data_as_string()
	{
		string result;
		auto it = bitvector.begin();
		auto it2 = data.begin();//auto it2 = 0;
		for (;it != bitvector.end(); it++, it2++)
		{
			if (*it == 0)
			{
				result.push_back(*it2);
			}
		}
		//cout << "\nZaraz zwroce result";
		return result;
	}
bool Sector::get_mode() { return mode; }
bool Sector::is_free() // 1 - wolny, 0 - zajety
	{
		return free;
	}
bool Sector::get_last_bitvector()
	{
		return bitvector[sn - 1];
	}
char Sector::get_last_data() // zwraca ostatni element niezaleznie czy jest uzywany czy jest smieciami
	{
		return data[sn - 1];
	}
