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
#include "HardDrive.h"

	char HardDrive::find_empty_sector() // sektor 32 oznacza brak wolnego sektoru
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
	array<bool, sn> HardDrive::create_empty_bitvector()//metoda pomocnicza
	{
		array<bool, sn> bitvector;
		for (auto it = bitvector.begin(); it != bitvector.end(); it++)
		{
			*it = 1;
		}
		return bitvector;
	}
	array<char, sn> HardDrive::create_empty_data_array()//metoda pomocnicza
	{
		array<char, sn> data_array;
		for (auto it = data_array.begin(); it != data_array.end(); it++)
		{
			*it = 0;
		}
		return data_array;
	}
	void HardDrive::append_to_string_from_deep_index(char firstSectorID, string &file_content)
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
					append_to_string_from_deep_index(*it2, file_content);
				}
				else // jesli zagniezdzony indeks jest sektorem danych
				{
					file_content.append(harddrive[*it2].get_data_as_string());
					//cout << "\nAktualny file_content:\n";
					//cout << file_content;
					//cout << "\nKoniec";
				}
			}
		}
		else
		{
			//string message = "Sektor nie jest sektorem indeksowym. Blad nieznany.";
			//cout << message;
		}
	}

	char HardDrive::find_deep_index_sector_ID(char ID)//zwraca ID najgleszego sektora indeksowego zaczynajac od pewnego ID
	{
		if (harddrive[ID].get_mode() == 0) // jesli jest to sektor indeksowy
		{
			if (!(harddrive[ID].get_last_bitvector())) // jestli element jest zajety
			{
				return (find_deep_index_sector_ID(harddrive[ID].get_last_data()));//wywolujemy metode szukajaca glebiej - sama siebie
			}
			else
			{
				//cout << "\nNajglebszy sektor indeksowy to " << (int)ID;
				return ID; // jestli nie ma kolejnych sektorow indeksowych zwracamy nasze id jako ze jestesmy ostatni
			}
		}
		else
		{
			char errorchar = -1;
			return errorchar;
		}
	}
	void HardDrive::delete_deep_sector_ID(char ID)//czysci wszystkie sektory zaczynajac od zadanego
	{
		//cout << "\nMamy usunac sektor " << (int)ID;
		Sector clear_sector;
		if (harddrive[ID].get_mode() == 0) // jesli jest to sektor indeksowy
		{//trzeba zwolnic wszystkie sektory z danymi
			auto bitvector = harddrive[ID].get_bitvector();
			auto data = harddrive[ID].get_data();
			for (char i = 0; i < (sn - 1); i++)//iterujemy po wszystkich elementach bitvectora
			{
				if (bitvector[i] == 0)//jesli element jest zajety
				{
					harddrive[data[i]] = clear_sector;
					bitvector[i] = 1;
					data[i] = 0;
				}
			}

			if (harddrive[ID].get_last_bitvector() == 0) // jestli element jest zajety
			{
				delete_deep_sector_ID(harddrive[ID].get_last_data());//wywolujemy metode szukajaca glebiej - sama siebie
			}
		}
		harddrive[ID] = clear_sector; // tworzymy pusty sektor i nadpisujemy ten stary
	}
	int HardDrive::add_data_sector_to_file(array <char, fn> filename_, array <char, tn> type_, Sector sector) // nazwa, rozszerzenie i sektor danych do dopisania, zwraca kod bledu
	{
		if (file_exist(filename_, type_))
		{
			auto it = Catalog.begin();
			for (; it != Catalog.end(); it++) // szukamy danego pliku
			{
				if (it->get_filename() == filename_ && it->get_type() == type_)
					break;
			}

			if (it->get_filename() == filename_ && it->get_type() == type_)
			{
				auto index_sector_ID = it->get_firstSectorID();
				auto free_sector_id = find_empty_sector();//znajdujemy wolny sektor i zapamietujemy jego indeks
														  //cout << "\nWolny jest sektor " << (int)free_sector_id;
				if (free_sector_id < max_sector_number)
				{
					harddrive[free_sector_id] = sector;//nadpisujemy wolny sektor przez nasz sektor z danymi
													   //cout << "\nNadpisalismy sektor " << (int)free_sector_id;
					index_sector_ID = find_deep_index_sector_ID(index_sector_ID); // znajdujemy najglebszy sektor indeksowy
																				  //cout << "\n\nAktualny index_sector_ID: " << (int)index_sector_ID;
					if (harddrive[index_sector_ID].add_one_data(free_sector_id))//dodajemy indeks do sektora indeksowego
					{
						//cout << "\ndodajemy indeks do sektora indeksowego " << index_sector_ID;
						return 1; // udalo sie
					}
					else // jesli mozemy dodac juz tylko ostatni element
					{//sektor indeksowy sie skonczyl. rezerwujemy nowy i bedziemy przypisywac kolejne indeksy do nowego
					 //cout << "\nSektor indeksowy sie skonczyl";
						auto next_index_sector_ID = find_empty_sector();//znajdujemy wolny sektor i zapamietujemy jego indeks
																		//cout << "\nKolejny wolny sektor indeksowy to " << (int)next_index_sector_ID;
						if (next_index_sector_ID < max_sector_number)
						{
							harddrive[next_index_sector_ID].set_mode(0); // 0 - przechowuje indeksy
							harddrive[next_index_sector_ID].set_free(0);// ustawiamy na zajety
							auto cos = harddrive[next_index_sector_ID].add_one_data(free_sector_id);//dodajemy sektor z danymi do nowego sektora indeksowego 

																									//Sector next_index_sector;
																									//next_index_sector.set_mode(0); // 0 - przechowuje indeksy
																									//next_index_sector.set_free(0); // ustawiamy na zajety
							if (harddrive[index_sector_ID].add_last_data(next_index_sector_ID))//dodajemy ostatni indeks do wczesniejszego sektora indeksowego
							{
								return 1;
							}
							else
							{
								//cout << "\nBlad nieznany\nten sektor jest zajety a nie powinen byc";//to sie nei zdarzy
								return 0;
							}
						}
						else
						{
							//cout << "\nNot enough space.";
							//zeby nie bylo "wycieku pamieci" czyscimy ten ostatni sektor z danymi
							Sector clear_sector;
							harddrive[free_sector_id] = clear_sector;
							return 2;
						}
					}
				}
				else
				{
					//cout << "\nNot enough space.";
					return 2;
				}
			}
			else
			{
				//cout << "\nNieznany blad z plikiem";
				return 0;
			}
		}
		else
		{
			return 0; // plik nie istnieje
		}
	}
	bool HardDrive::file_exist(array <char, fn> filename_, array <char, tn> type_) // 1 - plik istnieje, 0 - plik nie istnieje
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

	int HardDrive::create_empty_file(array <char, fn> filename_, array <char, tn> type_) // 2 - brak miejsca, 1 - ok, 0 - plik juz istnieje
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
	
	bool HardDrive::read_file(array <char, fn> filename_, array <char, tn> type_, string &file_content)//1 - przypisanie sie powiodlo, 0 - przypisano komunikat bledu
	{
		if (file_exist(filename_, type_))
		{
			file_content;
			for (auto it = Catalog.begin(); it != Catalog.end(); it++)
			{
				if (it->get_filename() == filename_ && it->get_type() == type_)
				{
					char firstSectorID = it->get_firstSectorID(); // SectorID odczytane z katalogu
					append_to_string_from_deep_index(firstSectorID, file_content);
					//cout << "\nOstateczny file_content:\n";
					//cout << file_content;
					//cout << "\nKoniec file_content";
				}
			}
			return 1;
		}
		else
		{
			file_content = "No such file.";
			return 0;
		}
	}
	bool HardDrive::delete_file(array <char, fn> filename_, array <char, tn> type_) // 1 zakonczone powodzeniem
	{
		if (file_exist(filename_, type_))
		{
			//cout << "\nTaki plik istnieje";
			for (auto it = Catalog.begin(); it != Catalog.end(); it++)
			{
				if (it->get_filename() == filename_ && it->get_type() == type_)
				{
					//cout << "\nNa pewno taki plik istnieje, bo jestesmy az tu";
					delete_deep_sector_ID(it->get_firstSectorID());
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
	int HardDrive::append_string_to_file(array <char, fn> filename_, array <char, tn> type_, string file_content)
	{
		while (!(file_content.empty()))
		{
			//cout << "\nzamiana string na sektory";//zamiana string na sektory
			array <bool, sn> bitvector = create_empty_bitvector(); //1 - blok wolny, 0 - blok zajety
			array <char, sn> data = create_empty_data_array();
			for (int i = 0; i < sn && !(file_content.empty()); i++)
			{
				bitvector[i] = 0; // oznaczamy char jako uzywany
				data[i] = *(file_content.begin()); // wyluskanie wartosci begin
												   //cout << "\ndata " << i << ": " << data[i];
				file_content.erase(file_content.begin()); // usuwa pierwszy element
			}
			Sector sector;
			sector.save_data(bitvector, data, 1); // 1 - przechowuje dane
												  //
												  //auto temp = sector.get_data_as_string();
												  //cout << "\ntemp: " << temp;
			auto result = add_data_sector_to_file(filename_, type_, sector);
			if (result == 1)//dodajmy sektor do pliku
			{
				//cout << "\nUdalo sie poprawnie dopisac sektor";
			}
			else if (result == 0)
			{
				//cout << "\nNo such file.";
				return result;
			}
			else if (result == 2)
			{
				//cout << "\nNot enough space.";
				return result;
			}
		}
		return 1;
	}
	std::list <FCB> HardDrive::get_file_list()
	{
		return Catalog;
	}
	Sector HardDrive::get_sector(char number)
	{
		return harddrive[number];
	}