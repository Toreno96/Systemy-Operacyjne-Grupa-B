#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <array>
#include <vector>
using std::string;
using std::array;
using std::cout;
const unsigned int max_sector_number = 32;//max liczba sektorow na dysku
const unsigned int n = 16; //max liczba znakow w jednym sektorze
//Podczas tworzenia pliku tworzona jest instancja FCB​

class FCB // blok kontrolny pliku
{
private:
	array <char, 8> filename;
	array <char, 3> type; // rozszerzenie np. txt​
	char firstSectorID;

public:
	FCB(array <char, 8> filename_, array <char, 3> type_, char firstSectorID_) : filename(filename_), type(type_), firstSectorID(firstSectorID_) {}
	array <char, 8> get_filename() { return filename; }
	array <char, 3> get_type() { return type; }
	char get_firstSectorID() { return firstSectorID; }
};

class Sector
{
private:
	array <bool, n> bitvector; //1 - blok wolny, 0 - blok zajety
	array <char, n> data; // nie wiem czy trzymac sie tej zasady //liczba 0 oznacza, że mimo wszystko to nie jest żadna informacja. znak ma sens <=> znak>0
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
			*it = 0; // zerujemy wszystkie bloki
		}
		mode = 1; // tryb nie ma znaczenia, gdy state i tak jest wolny;
		free = 1; // oznaczamy sektor jako wolny
	}
	bool save_data(array <bool, n> bitvector, array <char, n> data, bool mode_) // 1 – operacja zakonczona pomyslnie
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
			for (; (it+1) != bitvector.end() && (*it != 1); it++, i++) // szukamy wolnego bool czyli char w array data
			{
			}
			if ((it+1) != bitvector.end() && *it == 1) // jesli znalezlismy wolny element
			{
				data[i] = one_data;
				return 1;
			}
			else if ((it+1) == bitvector.end()) // jesli wszystko az do przedostatniego jest zajete
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
			//result.append( data[it2] ); // tu nie appenduje
			result.push_back(*it2);
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

class HardDrive
{
private:
	std::list <FCB> Catalog{};
	array <Sector, max_sector_number> harddrive;
	char find_empty_sector() // sektor 32 oznacza brak wolnego sektoru
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
	// napisane
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
	string array_type_as_string(array <char, 8> filename_, array <char, 3> type_)
	{
		string file_type_as_string;
		for (auto it = filename_.begin(); it != filename_.end(); it++)
		{
			file_type_as_string.push_back(*it);
		}
		return file_type_as_string;
	}

public:
	//zrobione
	bool file_exist(array <char, 8> filename_, array <char, 3> type_) // 1 - plik istnieje, 0 - plik nieistnieje
	{
		for (auto it = Catalog.begin(); it != Catalog.end(); it++)
		{
			if (it->get_filename() == filename_ && it->get_type() == type_)
			{
				return 1;
			}
		}
		return 0;
	}
	//ta metoda jest niepotrzebna
	bool create_empty_file(array <char, 8> filename_, array <char, 3> type_) // 1 – operacja zakonczona pomyslnie, 0 - cos poszlo nie tak
	{
		if (file_exist(filename_, type_))
		{
			return 0; // taki plik juz istnieje
		}

		//rezerwujemy sektor indeksowy
		auto index_sector_ID = find_empty_sector();
		if (index_sector_ID < max_sector_number)
		{
			Sector index_sector{}; //tworzymy pusty sector
			index_sector.set_mode(0); // Sektor przechowuje indeksy innych sektorow
			harddrive[index_sector_ID] = index_sector;
			FCB new_fcb{ filename_, type_, index_sector_ID };
			Catalog.push_back(new_fcb);
			return 1; // operacja zakonczona pomyslnie
		}
		else
		{
			cout << "\nBrak miejsca na dysku by utworzyc nowy plik.";
			return 0; // brak miejsca na dysku
		}
	}
	//zrobione
	bool load_file_from_Windows_and_save_on_harddrive(array <char, 8> filename_, array <char, 3> type_) // 1 - operacja zakonczona powodzeniem
	{
		//zamiana array filename_ i type_ na string
		string filename_string = array_type_as_string(filename_, type_);

		//wczytujemy plik z systemu windows
		char character;//string line;
		string good;
		std::ifstream infile; infile.open(filename_string);
		while (infile.good())
		{
			character = infile.get();//getline(infile, line);//jak to zamienic na get?
			good.push_back(character);//good.append(line);
		}
		infile.close();

		create_empty_file(filename_, type_);

		while ( !(good.empty()) )
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
			add_data_sector_to_file(filename_, type_, sector);//dodajmy sektor do pliku
		}

	}
	//zrobione
	string read_file(array <char, 8> filename_, array <char, 3> type_)//zwraca caly plik jako string
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
	//zrobione
	char find_deep_index_sector_ID(char ID)//zwraca ID najgleszego sektora indeksowego zaczynajac od pewnego ID
	{
		if (harddrive[ID].get_mode() == 0) // jesli jest to sektor indeksowy
		{
			if (!(harddrive[ID].get_last_bitvector())) // jestli element jest zajety
			{
				return (find_deep_index_sector_ID(harddrive[ID].get_last_data()) );//wywolujemy metode szukajaca glebiej - sama siebie
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
	//zrobic
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
	//zrobione
	bool add_data_sector_to_file(array <char, 8> filename_, array <char, 3> type_, Sector sector) // nazwa, rozszerzenie i sektor danych do dopisania
	{
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
				if (free_sector_id < max_sector_number)
				{
					harddrive[free_sector_id] = sector;//nadpisujemy wolny sektor przez nasz sektor
					index_sector_ID = find_deep_index_sector_ID(index_sector_ID); // znajdujemy najglebszy sektor indeksowy
					if (harddrive[index_sector_ID].add_one_data(free_sector_id))//dodajemy indeks do sektora indeksowego
					{
						return 1; // udalo sie
					}
					else // jesli mozemy dodac juz tylko ostatni element
					{//sektor indeksowy sie skonczyl. rezerwujemy nowy i bedziemy przypisywac kolejne indeksy do nowego
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
							cout << "\nBrak miejsca na dysku";
							return 0;
						}
					}
				}
				else
				{
					cout << "\nBrak miejsca na dysku";
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
	//to napisac
	bool delete_file(array <char, 8> filename_, array <char, 3> type_) // 1 zakonczone powodzeniem
	{
		if (file_exist(filename_, type_))
		{
			for (auto it = Catalog.begin(); it != Catalog.end(); it++)
			{
				if (it->get_filename() == filename_ && it->get_type() == type_)
				{
					delete_deep_index_sector_ID(it->get_firstSectorID);
					//trzeba usunac wpis katalogowy od tego pliku
				}
				else
				{
					cout << "Niby plik istnieje ale jednak nie ma zgodnosci???";
					return 0;
				}
			}
			return 1;//?
		}
		else
		{
			cout << "No such file.";
			return 0;
		}
	}
	//metoda tworzaca plik o zadanym stringu
	//metoda dopisywania danych do pliku tylko jak bedzie czas
	//zrobione
	std::list <FCB> get_file_list()
	{
		return Catalog;
	}

};