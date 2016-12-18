#pragma once
#include <iostream>
using std::cin;
using std::cout;
#include "HardDrive.h"
#include <list>
string filename_and_type_as_string(array <char, fn> filename_, array <char, tn> type_)
{
	string file_type_as_string;
	for (auto it = filename_.begin(); it != filename_.end(); it++)
	{
		if (*it != 0)
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

array <char, fn> convert_filename_to_array(string filename_as_string)
{
	//cout << "\nDlugosc nazwy to " << filename_as_string.size();
	array <char, fn> filename;
	if (filename_as_string.size() <= fn)
	{
		size_t i = 0;
		for (; filename_as_string.size() != 0; i++)
		{
			filename[i] = *(filename_as_string.begin()); // wyluskanie wartosci begin
														 //cout << "\ndopisalem " << *(filename_as_string.begin());
			filename_as_string.erase(filename_as_string.begin()); // usuwa pierwszy element
		}
		for (;i<fn; i++)
		{
			filename[i] = 0;//pozostale znaki inicjalizujemy nulem
		}
		return filename;
	}
	else
	{
		for (auto it = filename.begin(); it != filename.end(); it++)
			*it = 0;
		return filename;
	}
}

array <char, tn> convert_type_to_array(string type_as_string)
{
	//cout << "\nDlugosc rozszerzenia to " << type_as_string.size();
	array <char, tn> type;
	if (type_as_string.size() <= tn)
	{
		size_t i = 0;
		for (;type_as_string.size() != 0; i++)
		{
			type[i] = *(type_as_string.begin()); // wyluskanie wartosci begin
												 //cout << "\nDopisalem " << *(type_as_string.begin());
			type_as_string.erase(type_as_string.begin()); // usuwa pierwszy element
		}
		for (;i<tn; i++)
		{
			type[i] = 0;//pozostale znaki inicjalizujemy nulem
		}
		return type;
	}
	else
	{
		for (auto it = type.begin(); it != type.end(); it++)
			*it = 0;
		return type;
	}
}

void display_harddrive(HardDrive &harddrive, bool mode) // 1 czyli z bitvectorem, 0 bez bitvectora
{
	cout << "\nLp.\tDane\t\t\tTryb\tstan";
	for (int i = 0; i < max_sector_number; i++)
	{
		Sector sector = harddrive.get_sector(i);
		array<bool, n> bitvector = sector.get_bitvector();
		array<char, n> data = sector.get_data();
		cout << "\n" << i << "\t";
		int counter = 0;
		if (mode)
		{
			for (auto it = bitvector.begin(); it != bitvector.end(); it++, counter++)
			{
				if (counter == (n / 2))
					cout << " ";
				cout << *it;
			}
			cout << "\n\t";
		}

		counter = 0;
		for (auto it = data.begin(); it != data.end(); it++, counter++)
		{
			if (sector.get_mode() == 0) //tryb indeksowy
			{
				if (counter == (n / 2))
					cout << " ";
				cout << (int)*it;
			}
			else //1 - tryb przechowywania danych
			{
				if (counter == (n / 2))
					cout << " ";
				if (*it == '\n')
					cout << ";";
				else
					cout << *it;
			}
		}
		cout << "\t" << sector.get_mode() << "\t" << sector.is_free();
	}
}

void display_file_list(std::list <FCB> &file_list)
{
	if (file_list.begin() == file_list.end())
	{
		cout << "\nList of files is empty!";
	}
	else
	{
		cout << "\nList of files:\t1st index sector";
		for (auto it = file_list.begin(); it != file_list.end(); it++)
		{
			cout << "\n" << it->get_filename_as_string() << "." << it->get_type_as_string() << "\t\t" << (int)(it->get_firstSectorID());
		}
	}
}
//ta metoda nie bedzie dostepna dla usera w ostatecznej wersji
void create_empty_file(HardDrive &harddrive)
{
	string filename_as_string;
	cout << "\nType a filename: "; //tylko filename
	cin >> filename_as_string;
	auto filename = convert_filename_to_array(filename_as_string); // auto to array <char, fn>
	
	if (*filename.begin() != 0)
	{
		string type_as_string;
		cout << "\nType an extension: "; //tylko rozszerzenei
		cin >> type_as_string;
		auto type = convert_type_to_array(type_as_string);

		if (*type.begin() != 0)
		{
			auto result = harddrive.create_empty_file(filename, type);
			if (result == 1)
				cout << "\nPlik utworzony";
			else if (result == 2)
				cout << "\nBrak miejsca na dysku by utworzyc nowy plik.";
			else if (result == 0)
				cout << "\nFile already exists.";
		}
		else
			cout << "\nRozszerzenie pliku jest za dlugie";
	}
	else
		cout << "\nNazwa pliku jest za dluga ";
}
/*
void append_string_to_file(HardDrive &harddrive)
{
	string filename_as_string;
	cout << "\nType a filename: "; //tylko filename
	cin >> filename_as_string;
	auto filename = convert_filename_to_array(filename_as_string); // auto to array <char, fn>

	if (*filename.begin() != 0)
	{
		string type_as_string;
		cout << "\nType an extension: "; //tylko rozszerzenie
		cin >> type_as_string;
		auto type = convert_type_to_array(type_as_string);

		if (*type.begin() != 0)
		{
			if (harddrive.file_exist(filename, type))
			{
				string good;
				cout << "\nWrite your text: ";
				cin.ignore();
				std::getline(cin, good);
				harddrive.append_string_to_file(filename, type, good);
			}
			else
				cout << "No such file";
		}
		else
			cout << "\nTo long extension.";
	}
	else
		cout << "\nTo long filename";
	
}
*/
void delete_file(HardDrive &harddrive)
{
	string filename_as_string;
	cout << "\nType a filename: "; //tylko filename
	cin >> filename_as_string;
	auto filename = convert_filename_to_array(filename_as_string); // auto to array <char, fn>

	string type_as_string;
	cout << "\nType an extension: "; //tylko rozszerzenei
	cin >> type_as_string;
	auto type = convert_type_to_array(type_as_string);
	
	auto result = harddrive.delete_file(filename, type);
	if (result == 1)
		cout << "\nFile deleted properly";
	else if (result == 0)
		cout << "\nNo such file.";
}

void load_file_from_Windows_and_save_on_harddrive(HardDrive &harddrive)
{
	string filename_as_string;
	cout << "\nType a filename: "; //tylko filename
	cin >> filename_as_string;
	auto filename = convert_filename_to_array(filename_as_string); // auto to array <char, fn>

	if (*filename.begin() != 0)
	{
		string type_as_string;
		cout << "\nType an extension: "; //tylko rozszerzenie
		cin >> type_as_string;
		auto type = convert_type_to_array(type_as_string);

		if (*type.begin() != 0)
		{
			//zamiana array filename_ i type_ na string
			string myfile = filename_and_type_as_string(filename, type);

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

				auto result_create = harddrive.create_empty_file(filename, type);
				if (result_create == 1)
				{
					auto result = harddrive.append_string_to_file(filename, type, good);

					if (result == 1)
						cout << "\nFile saved properly";
					else if (result == 0)
						cout << "\nNo such file.";
					else if (result == 2)
						cout << "\nNot enough space.";
				}
				else if (result_create == 0)
				{
					cout << "\nFile already exists.";
				}
				else if (result_create == 2)
					cout << "\nNot enough space.";
			}
			else
				cout << "\nNo such file.";
		}
		else
			cout << "\nTo long extension.";
	}
	else
		cout << "\nTo long filename";
}

void create_this_string_file_system(HardDrive &harddrive, string filename_as_string, string type_as_string, string good)
{
	auto filename = convert_filename_to_array(filename_as_string); // auto to array <char, fn>

	if (*filename.begin() != 0)
	{
		auto type = convert_type_to_array(type_as_string);

		if (*type.begin() != 0)
		{
			auto result_create = harddrive.create_empty_file(filename, type);
			if (result_create == 1)
			{
				auto result = harddrive.append_string_to_file(filename, type, good);

				if (result == 1)
					cout << "\nFile saved properly";
				else if (result == 0)
					cout << "\nNo such file.";
				else if (result == 2)
					cout << "\nNot enough space.";
			}
			else if (result_create == 0)
			{
				cout << "\nFile already exists.";
			}
			else if (result_create == 2)
				cout << "\nNot enough space.";
		}
		else
			cout << "\nTo long extension.";
	}
	else
		cout << "\nTo long filename";
}

void read_file(HardDrive &harddrive)
{
	string filename_as_string;
	cout << "\nType a filename: "; //tylko filename
	cin >> filename_as_string;
	auto filename = convert_filename_to_array(filename_as_string); // auto to array <char, fn>

	if (*filename.begin() != 0)
	{
		string type_as_string;
		cout << "\nType an extension: "; //tylko rozszerzenie
		cin >> type_as_string;
		auto type = convert_type_to_array(type_as_string);

		if (*type.begin() != 0)
		{
			string result;
			if (harddrive.read_file(filename, type, result) == true)
			{}//tak wiem ze i tak i tak sie wyswietli
			cout << "\nPoczatek pliku\n";
			cout << result;
			cout << "\nKoniec pliku";
		}
		else
			cout << "\nTo long extension.";
	}
	else
		cout << "\nTo long filename";
}