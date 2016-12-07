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
const unsigned int max_sector_number = 32;
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
	array <bool, 16> bitvector; //1 - blok wolny, 0 - blok zajety
	array <char, 16> data; // liczba 0 oznacza, że mimo wszystko to nie jest żadna informacja. znak ma sens <=> znak>0
	bool mode; // 0 - przechowuje indeksy innych sektorow, 1 - przechowuje dane
	bool free; // 1 wolny, 0 - zajety
			   //metody pomocnicze
	array<bool, 16> create_empty_bitvector()//metoda pomocnicza
	{
		array<bool, 16> bitvector;
		for (auto it = bitvector.begin(); it != bitvector.end(); it++)
		{
			*it = 1;
		}
		return bitvector;
	}
	array<char, 16> create_empty_data_array()//metoda pomocnicza
	{
		array<char, 16> data_array;
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
	bool save_data(array <bool, 16> bitvector, array <char, 16> data, bool mode_) // 1 – operacja zakonczona pomyslnie
	{
		bitvector = bitvector; data = data; bool mode = mode_; free = 0; return 1;
	}
	array <bool, 16> get_bitvector() { return bitvector; }
	array <char, 16> get_data() { return data; }
	//rozszerzyc o tworzony nowy sektor indeksowy jesli chcemy zajac ostatni indeks
	bool add_one_data(char one_data) // 1 jesli zakonczone pomyslnie
	{
		auto it = bitvector.begin();//iterator pierwotny
		auto it2 = bitvector.begin();//iterator ktory zatrzyma sie szybciej
		it2++;
		//dzieki temu it bedzie wskazywac na ostatni element a it2 na koniec bitvectora
		int i = 0;
		for (; it2 != bitvector.end() && *it != 1; it++, it2++, i++) // szukamy wolnego bool czyli char w array data
		{
		}
		if (it2 != bitvector.end() && *it == 1) // jesli it nie wczesniej niz ostatnim elemencie i *it jest wolny
		{
			data[i] = one_data;
			return 1;
		}
		if (it2 == bitvector.end() && *it == 1) // jesli it stoi na ostatnim elemencie i *it jest wolny
		{
			array <bool, 16> bitvector = create_empty_bitvector(); //1 - blok wolny, 0 - blok zajety
			array <char, 16> data = create_empty_data_array();
			Sector sector;
			sector.save_data(bitvector, data, 0); // tryb przechowywania indeksow
												  // trzeba znalezc wolny sektor ktory mozemy do tego celu zarezerwowac
												  // chyba z poziomu twardego dysku
												  //bitvector[16-1] =  //przypisujemy do tego charu indeks tego noego wolnego sektoru
			return 1;
		}


	}
	bool set_mode(bool mode_)
	{
		mode = mode_;
		return 1; // zakonczone pomyslnie
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
	array<bool, 16> create_empty_bitvector()//metoda pomocnicza
	{
		array<bool, 16> bitvector;
		for (auto it = bitvector.begin(); it != bitvector.end(); it++)
		{
			*it = 1;
		}
		return bitvector;
	}
	array<char, 16> create_empty_data_array()//metoda pomocnicza
	{
		array<char, 16> data_array;
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
		{
			string message = "Sektor nie jest sektorem indekswym. Blad nieznany.";
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
	//zrobione
	bool create_empty_file(array <char, 8> filename_, array <char, 3> type_) // 1 – operacja zakonczona pomyslnie, 0 - cos poszlo nie tak
	{
		if (file_exist(filename_, type_))
		{
			return 0; // taki plik juz istnieje
		}

		//rezerwujemy sektor na baze sektorow z danymi
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
			return 0; // brak miejsca na dysku
		}
	}
	// potem skonczyc to
	bool load_file_from_Windows_and_save_on_harddrive(array <char, 8> filename_, array <char, 3> type_) // 1 - operacja zakonczona powodzeniem
	{
		//zamiana array filename_ i type_ na string
		string filename_string = array_type_as_string(filename_, type_);

		//wczytujemy plik z systemu windows
		string line;
		string good;
		std::ifstream infile; infile.open(filename_string);
		while (infile.good())
		{
			getline(infile, line);//jak to zamienic na get?
			good.append(line);
		}
		infile.close();

		while (!(good.empty()))
		{
			//zamiana string na sektory
			array <bool, 16> bitvector = create_empty_bitvector(); //1 - blok wolny, 0 - blok zajety
			array <char, 16> data = create_empty_data_array();
			for (int i = 0; i < 16 && !(good.empty()); i++)
			{
				bitvector[i] = 0; // oznaczamy char jako uzywany
				data[i] = *(good.begin()); // wyluskanie wartosci begin
				good.erase(good.begin()); // usuwa pierwszy element
			}
			Sector sector;
			sector.save_data(bitvector, data, 1);
			add_data_sector_to_file(filename_, type_, sector);// nadpisujemy prawdziwy sektor naszym sektorem
															  //trzeba te x tablic jakos zapisac na harddrive
															  //nowo zajete indeksy
		}

	}
	//napisane
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
	//napisane
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
				auto firstSectorID = it->get_firstSectorID();
				auto free_sector_id = find_empty_sector();//znajdujemy wolny sektor i zapamietujemy jego indeks
				harddrive[free_sector_id] = sector;//nadpisujemy wolny sektor przez nasz sektor
				harddrive[firstSectorID].add_one_data(free_sector_id);//dodajemy indeks do sektora indeksowego
				return 1; // zakonczone poprawnie
			}
		}
		else
		{
			return 0; // plik nie istnieje
		}
	}
	bool delete_file(array <char, 8> filename_, array <char, 3> type_) {}
	//zrobione
	std::list <FCB> get_file_list()
	{
		return Catalog;
	}

};