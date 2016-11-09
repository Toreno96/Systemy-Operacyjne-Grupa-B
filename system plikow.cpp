#include <iostream>
#include <string>
#include <list>
#include <array>
using std::string;
using std::array;

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
	array <char, 16> data;
	bool mode; // tryb 0 - przechowuje indeksy innych sektorow, 1 - przechowuje dane

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
		mode = 0; // tryb nie ma znaczenia, gdy w bitvector i tak jest wolne
	}
	bool save_data(array <bool, 16> bitvector_, array <char, 16> data_, bool mode_)
	{ bitvector = bitvector_; data = data_; bool mode = mode_; return 1; } // 1 – operacja zakonczona pomyslnie
	array <bool, 16> get_bitvector() { return bitvector; }
	array <char, 16> get_data() { return data; }
	bool get_mode() { return mode; }
};

class HardDrive
{
private:
	std::list <FCB> Catalog{};
	Sector harddrive [32];
	unsigned int find_empty_sector() {}

public:
	bool create_file (array <char, 8> filename_, array <char, 3> type_) {} // 1 – operacja zakonczona pomyslnie
	bool delete_file (array <char, 8> filename_, array <char, 3> type_) {}
	FCB read_file (array <char, 8> filename_, array <char, 3> type_) {}
	bool add_to_file (array <char, 8> filename_, array <char, 3> type_, array <char, 16> data_) {}

	array <char, 16> read_sector (unsigned int sectorID) {}
	std::list <FCB> get_file_list () {}
};