#pragma once
#include <iostream>
using std::cout;
#include <fstream>
#include <string>
using std::string;
#include <list>
#include <array>
using std::array;
#include "filesystemcommon.h"
#include "FCB.h"
#include "Sector.h"

class HardDrive
{
private:
	std::list <FCB> Catalog{};
	array <Sector, max_sector_number> harddrive;
	char find_empty_sector() // sektor tn2 oznacza brak wolnego sektoru
	{
		char sector_ID = 0;
		for (auto it = harddrive.begin(); it != harddrive.end(); it++, sector_ID++)
		{
			if (it->is_free())
			{
				return sector_ID;
			}
		}
		return sector_ID;
	}
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
	void append_to_string_from_deep_index(char firstSectorID, string &result)
	{
		if (harddrive[firstSectorID].get_mode() == 0) // jesli sektor jest sektorem indeksowym
		{
			auto copy_of_bitvector = harddrive[firstSectorID].get_bitvector();
			auto copy_of_indexes = harddrive[firstSectorID].get_data();

			auto it = copy_of_bitvector.begin();
			auto it2 = copy_of_indexes.begin();
			for (; it != copy_of_bitvector.end() && *it == 0; it++, it2++) // dopoki koniec wektora lub char jest zajety
			{
				if (harddrive[*it2].get_mode() == 0) // jesli zagniezdzony indeks jest sektorem indeksowym
				{
					append_to_string_from_deep_index(*it2, result);
				}
				else // jesli zagniezdzony indeks jest sektorem danych
				{
					result.append(harddrive[*it2].get_data_as_string());
				}
			}
		}
		else
		{
			string message = "Sektor nie jest sektorem indeksowym. Blad nieznany.";
			cout << message;
		}
	}
	string filename_and_type_as_string(array <char, fn> filename_, array <char, tn> type_)
	{
		string file_type_as_string;
		for (auto it = filename_.begin(); it != filename_.end(); it++)
		{
			if(*it != 0)
				file_type_as_string.push_back(*it);
		}
		file_type_as_string.push_back('.');
		for (auto it = type_.begin(); it != type_.end(); it++)
		{
			if (*it != 0)
				file_type_as_string.push_back(*it);
		}
		//cout << "\nfile_type_as_string: " << file_type_as_string;
		return file_type_as_string;
	}
	char find_deep_index_sector_ID(char ID)//zwraca ID najgleszego sektora indeksowego zaczynajac od pewnego ID
	{
		if (harddrive[ID].get_mode() == 0) // jesli jest to sektor indeksowy
		{
			if (!(harddrive[ID].get_last_bitvector())) // jestli element jest zajety
			{
				return (find_deep_index_sector_ID(harddrive[ID].get_last_data()));//wywolujemy metode szukajaca glebiej - sama siebie
			}
			else
			{
				return ID; // jestli nie ma kolejnych sektorow indeksowych zwracamy nasze id jako ze jestesmy ostatni
			}
		}
		else
		{
			char errorchar = -1;
			return errorchar;
		}
	}
	void delete_deep_index_sector_ID(char ID)//zwraca ID najgleszego sektora indeksowego zaczynajac od pewnego ID
	{
		if (harddrive[ID].get_mode() == 0) // jesli jest to sektor indeksowy
		{
			harddrive[ID].set_free(1);
			if (!(harddrive[ID].get_last_bitvector())) // jestli element jest zajety
			{
				delete_deep_index_sector_ID(harddrive[ID].get_last_data());//wywolujemy metode szukajaca glebiej - sama siebie
			}
		}
	}
	bool add_data_sector_to_file(array <char, fn> filename_, array <char, tn> type_, Sector sector) // nazwa, rozszerzenie i sektor danych do dopisania
	{
		cout << "\n\nWeszlismy do add_data_sector_to_file";
		if (file_exist(filename_, type_))
		{
			auto it = Catalog.begin();
			for (; it != Catalog.end() && it->get_filename() != filename_ && it->get_type() != type_; it++) // szukamy danego pliku
			{
			}

			if (it->get_filename() == filename_ && it->get_type() == type_)
			{
				auto index_sector_ID = it->get_firstSectorID();
				auto free_sector_id = find_empty_sector();//znajdujemy wolny sektor i zapamietujemy jego indeks
				//cout << "\nWolny jest sektor " << (int)free_sector_id;
				if (free_sector_id < max_sector_number)
				{
					harddrive[free_sector_id] = sector;//nadpisujemy wolny sektor przez nasz sektor
					cout << "\nNadpisalismy sektor " << (int)free_sector_id;
					index_sector_ID = find_deep_index_sector_ID(index_sector_ID); // znajdujemy najglebszy sektor indeksowy
					if (harddrive[index_sector_ID].add_one_data(free_sector_id))//dodajemy indeks do sektora indeksowego
					{
						cout << "\ndodajemy indeks do sektora indeksowego";
						return 1; // udalo sie
					}
					else // jesli mozemy dodac juz tylko ostatni element
					{//sektor indeksowy sie skonczyl. rezerwujemy nowy i bedziemy przypisywac kolejne indeksy do nowego
						cout << "\nSektor indeksowy sie skonczyl";
						auto free_sector_id = find_empty_sector();//znajdujemy wolny sektor i zapamietujemy jego indeks
						if (free_sector_id < max_sector_number)
						{
							Sector new_index_sector;
							new_index_sector.set_mode(0); // 0 - przechowuje indeksy
							new_index_sector.set_free(0); // ustawiamy na zajety
							if (harddrive[index_sector_ID].add_last_data(free_sector_id))//dodajemy ostatni indeks do sektora indeksowego
							{
								index_sector_ID = free_sector_id; // nadpisujemy firstSectorID by juz sie do niego nie odnosic bo jest zajety
								return 1;
							}
							else
							{
								cout << "\nBlad nieznany\nten sektor jest zajety a nie powinen byc";
								return 0;
							}
						}
						else
						{
							cout << "\nBrak miejsca na dysku. Skonczyly sie sektory";
							return 0;
						}
					}
				}
				else
				{
					cout << "\nBrak miejsca na dysku. Skonczyly sie wolne sektory";
					return 0;
				}
			}
			else
			{
				cout << "\nNieznany blad z plikiem";
				return 0;
			}
		}
		else
		{
			return 0; // plik nie istnieje
		}
	}

public:
	bool file_exist(array <char, fn> filename_, array <char, tn> type_) // 1 - plik istnieje, 0 - plik nieistnieje
	{
		for (auto it = Catalog.begin(); it != Catalog.end(); it++)
		{
			if (it->get_filename() == filename_ && it->get_type() == type_)
			{
				//cout << "\nfile_exist mowi, ze plik istnieje";
				return 1;
			}
		}
		return 0;
	}
	char create_empty_file(array <char, fn> filename_, array <char, tn> type_) // 2 - brak miejsca, 1 - ok, 0 - plik juz istnieje
	{
		if (file_exist(filename_, type_))
		{
			return 0; // taki plik juz istnieje
		}

		//rezerwujemy sektor indeksowy
		auto index_sector_ID = find_empty_sector();
		if (index_sector_ID < max_sector_number)
		{
			Sector index_sector; //tworzymy pusty sector
			index_sector.set_mode(0); // Sektor przechowuje indeksy innych sektorow
			index_sector.set_free(0);
			harddrive[index_sector_ID] = index_sector;
			FCB new_fcb{ filename_, type_, index_sector_ID };
			Catalog.push_back(new_fcb);
			return 1; // operacja zakonczona pomyslnie
		}
		else
		{
			return 2; // brak miejsca na dysku
		}
	}
	bool load_file_from_Windows_and_save_on_harddrive(array <char, fn> filename_, array <char, tn> type_) // 1 - operacja zakonczona powodzeniem
	{
		//zamiana array filename_ i type_ na string
		string myfile = filename_and_type_as_string(filename_, type_);

		//wczytujemy plik z systemu windows
		string good;
		std::ifstream infile; infile.open(myfile);
		if (infile.is_open())
		{
			while (infile.good())
			{
				char character;//string line;
				character = infile.get();//getline(infile, line);//jak to zamienic na get?
				//cout << "\nWczytalem znak " << character;
				good.push_back(character);//good.append(line);
			}
			infile.close();
			//cout << "\nCaly plik:\n"; cout << good;

			create_empty_file(filename_, type_);
			bool is_ok = true;
			while (!(good.empty()))
			{
				//cout << "\nzamiana string na sektory";//zamiana string na sektory
				array <bool, n> bitvector = create_empty_bitvector(); //1 - blok wolny, 0 - blok zajety
				array <char, n> data = create_empty_data_array();
				for (int i = 0; i < n && !(good.empty()); i++)
				{
					bitvector[i] = 0; // oznaczamy char jako uzywany
					data[i] = *(good.begin()); // wyluskanie wartosci begin
					//cout << "\ndata " << i << ": " << data[i];
					good.erase(good.begin()); // usuwa pierwszy element
				}
				Sector sector;
				sector.save_data(bitvector, data, 1); // 1 - przechowuje dane
				//
				//auto temp = sector.get_data_as_string();
				//cout << "\ntemp: " << temp;
				//
				if (add_data_sector_to_file(filename_, type_, sector))//dodajmy sektor do pliku
				{
					cout << "\nUdalo sie poprawnie dopisac sektor";
				}
				else
				{
					cout << "\nNie udalo sie dopisac sektoru";
					is_ok = false;
					delete_file(filename_, type_);
					break; // wyjsc z petli for
				}
			}
			if (is_ok)
				return 1;
			else
				return 0;
		}
		else
		{
			cout << "\nPlik nie zostal otwarty";
			return 0;
		}
	}
	string read_file(array <char, fn> filename_, array <char, tn> type_)//zwraca caly plik jako string
	{
		if (file_exist(filename_, type_))
		{
			string file;
			for (auto it = Catalog.begin(); it != Catalog.end(); it++)
			{
				if (it->get_filename() == filename_ && it->get_type() == type_)
				{
					char firstSectorID = it->get_firstSectorID(); // SectorID odczytane z katalogu
					append_to_string_from_deep_index(firstSectorID, file);
				}
				else
				{
					string message = "Niby plik istnieje ale jednak nie ma zgodnosci???";
					return message;
				}
			}
			return file;
		}
		else
		{
			string message = "No such file.";
			return message;
		}
	}
	bool delete_file(array <char, fn> filename_, array <char, tn> type_) // 1 zakonczone powodzeniem
	{
		if (file_exist(filename_, type_))
		{
			//cout << "\nTaki plik istnieje";
			for (auto it = Catalog.begin(); it != Catalog.end(); it++)
			{
				if (it->get_filename() == filename_ && it->get_type() == type_)
				{
					//cout << "\nNa pewno taki plik istnieje, bo jestesmy az tu";
					delete_deep_index_sector_ID(it->get_firstSectorID());
					Catalog.erase(it);//trzeba usunac wpis katalogowy od tego pliku
					return 1;
				}//else nie robilby nic
			}
			return 0;
		}
		else
		{
			return 0;
		}
	}
	/*
	bool append_string_to_file(array <char, fn> filename_, array <char, tn> type_, string good)
	{
		//create_empty_file(filename_, type_);
		while (!(good.empty()))
		{
			//zamiana string na sektory
			array <bool, n> bitvector = create_empty_bitvector(); //1 - blok wolny, 0 - blok zajety
			array <char, n> data = create_empty_data_array();
			for (int i = 0; i < n && !(good.empty()); i++)
			{
				bitvector[i] = 0; // oznaczamy char jako uzywany
				data[i] = *(good.begin()); // wyluskanie wartosci begin
				good.erase(good.begin()); // usuwa pierwszy element
			}
			Sector sector;
			sector.save_data(bitvector, data, 1); // 1 - przechowuje dane
			if (add_data_sector_to_file(filename_, type_, sector))//dodajmy sektor do pliku
			{
			}
			else
			{
				cout << "\nBrak miejsca na dysku";
				//delete_file(filename_, type_);
				break; // wyjsc z petli for
			}
		}
		if (good.empty())
			return 1;
		else
			return 0;
	}
	//metoda dopisywania danych do pliku tylko jak bedzie czas
	*/
	std::list <FCB> get_file_list()
	{
		return Catalog;
	}
	Sector get_sector(char number)
	{
		return harddrive[number];
	}
};