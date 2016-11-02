#include <iostream>
#include <string>
#include <list>
#include <array>
using std::string;

//Podczas tworzenia pliku tworzona jest instancja FCB​

class FCB // blok kontrolny pliku
{
private:
	std::array <char, 8> filename;
	std::array <char, 3> type; // rozszerzenie np. txt​
	std::array <int, 5> sectorID; // wartosc ujemna – nieprzypisany sektor do pliku​

public:
	FCB(std::array <char, 8> filename_, std::array <char, 3> type_, std::array <int, 5> sectorID_) : filename(filename_), type(type_), sectorID(sectorID_) {}
	std::array <int, 5> read_sectors () {}
};

class Sector
{
private:
	std::array <bool, 16> bitvector; //1 - blok wolny, 0 - blok zajety
	std::array <char, 16> data;

public:
	bool save_data (std::array <char, 16> data_) {} // 1 – operacja zakonczona pomyslnie
	std::array <char, 16> read_data() {}
	std::array <bool, 16> get_bitvector() {}
};

class HardDrive
{
private:
	std::list <FCB> Catalog{};
	Sector harddrive [16];
	unsigned int find_empty_sector() {}

public:
	bool create_file (std::array <char, 8> filename_, std::array <char, 3> type_) {} // 1 – operacja zakonczona pomyslnie
	bool delete_file (std::array <char, 8> filename_, std::array <char, 3> type_) {}
	FCB read_file (std::array <char, 8> filename_, std::array <char, 3> type_) {}
	bool add_to_file (std::array <char, 8> filename_, std::array <char, 3> type_, std::array <char, 16> data_) {}

	std::array <char, 16> read_sector (unsigned int sectorID) {}
	std::list <FCB> get_file_list () {}
};