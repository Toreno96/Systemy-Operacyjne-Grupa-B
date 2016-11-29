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
	FCB(array <char, 8> filename_, array <char, 3> type_, char firstSectorID_) : filename(filename_), type(type_), firstSectorID (firstSectorID_) {}
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
		mode = 0; // tryb nie ma znaczenia, gdy state i tak jest wolny;
		free = 1; // oznaczamy sektor jako wolny
	}
	bool save_data(array <bool, 16> data_bitvector, array <char, 16> data_data, bool mode_) // 1 – operacja zakonczona pomyslnie
	{
		bitvector = data_bitvector; data = data_data; bool mode = mode_; free = 0; return 1;
	}

	array <bool, 16> get_bitvector() { return bitvector; }
	array <char, 16> get_data() { return data; }
	//napisane
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
				if(harddrive[*it2].get_mode() == 0) // jesli zagniezdzony indeks jest sektorem indeksowym
				{
					append_to_string_from_deep_index(*it2, result);
				}
				else // jesli zagniezdzony indeks jest sektorem danych
				{
					result.append( harddrive[*it2].get_data_as_string() );
				}
			}
		}
		{
			string message = "Sektor nie jest sektorem indekswym. Blad nieznany.";
			cout << message;
		}
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
	bool create_empty_file (array <char, 8> filename_, array <char, 3> type_) // 1 – operacja zakonczona pomyslnie, 0 - cos poszlo nie tak
	{
		if (file_exist(filename_, type_))
		{
			return 0; // taki plik juz istnieje
		}

		//rezerwujemy sektor na dane
		auto data_sector_ID = find_empty_sector();
		if (data_sector_ID < max_sector_number)
		{
			array<bool, 16> data_bitvector = create_empty_bitvector();
			array<char, 16> data_data = create_empty_data_array();

			//rezerwujemy sektor na baze sektorow z danymi
			auto index_sector_ID = find_empty_sector();
			if (index_sector_ID < max_sector_number)
			{
				array<bool, 16> index_bitvector = create_empty_bitvector();
				array<char, 16> index_data = create_empty_data_array();
				index_data[0] = data_sector_ID; // pierwszy char sektora indeksowego zawiera indeks sektora z danymi

				harddrive[data_sector_ID].save_data(data_bitvector, data_data, 1); // Sektor przechowuje dane
				harddrive[index_sector_ID].save_data(index_bitvector, index_data, 0); // Sektor przechowuje indeksy innych sektorow
				FCB new_fcb{ filename_, type_, index_sector_ID };
				Catalog.push_back(new_fcb);
				return 1; // operacja zakonczona pomyslnie
			}
			else
			{
				return 0; // brak miejsca na dysku
			}
		}
		else
		{
			return 0; // brak miejsca na dysku
		}
	}
	// potem skonczyc to
	bool load_file_from_Windows(string filename_)
	{ // uwaga. Co sie dzieje z \n itp znakami? czy sie zapisuja?
		string line;
		string good;
		std::ifstream infile; infile.open(filename_);
		while (infile.good())
		{
			getline(infile, line);
			good.append(line);
		}
		infile.close();

		array<bool, 16> bitvector = create_empty_bitvector();
		array<char, 16> data = create_empty_data_array();
		//std::vector <array< char, 16 > > x;
		
		while ( !(good.empty()) )
		{
			for (int i = 0; i < 16 && !(good.empty()); i++)
			{
				bitvector[i] = 0; // oznaczamy char jako uzywany
				data[i] = *(good.begin()); // wyluskanie wartosci begin
				good.erase(good.begin()); // usuwa pierwszy el.
			}
			//tworzymy nowy sektor z tego co mamy
			// nadpisujemy prawdziwy sektor tym naszym cudem :D
			//trzeba te x tablic jakos zapisac na harddrive
			// trzeba dopisac do sektora indeksowego
			//nowo zajete indeksy
		}

	}
	//napisane
	string read_file(array <char, 8> filename_, array <char, 3> type_)
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
		}
		else
		{
			string message = "No such file.";
			return message;
		}
	}
	//najpierw to
	bool add_to_file(array <char, 8> filename_, array <char, 3> type_, string data_string)
	{
		if (file_exist(filename_, type_))
		{
			// trzeba zczytac wszystkie dane, zrobic z tego string, potem append data_string,
			//znow porozdzielac na sektory, sprawdzic ilosc, przypisac, dopisac sektory do sektora indeksowego
		}
		else
		{
			return 0; // plik nie istnieje
		}
	}
	bool delete_file (array <char, 8> filename_, array <char, 3> type_) {}
	//zrobione
	std::list <FCB> get_file_list ()
	{
		return Catalog;
	}
	
};