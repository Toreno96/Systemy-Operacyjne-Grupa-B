#pragma once
#include <iostream>
using std::cin;
using std::cout;
#include "HardDrive.h"
#include <list>
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

void display_harddrive(HardDrive &harddrive)
{
	cout << "\tDane\t\t\tTryb\tstan";
	for (int i = 0; i < n; i++)
	{
		Sector sector = harddrive.get_sector(i);
		array<char, n> data = sector.get_data();
		cout << "\n" << i << "\t";
		int counter = 0;
		for (auto it = data.begin(); it != data.end(); it++, counter++)
		{
			if (counter == (n / 2))
				cout << " ";
			if (*it == '\n')
				cout << ";";
			else
				cout << *it;
		}
		cout << "\t" << sector.get_mode() << "\t" << sector.is_free();
	}
}

void display_harddrive_2(HardDrive &harddrive)
{
	cout << "\tDane\t\t\tTryb\tstan";
	for (int i = 0; i < n; i++)
	{
		Sector sector = harddrive.get_sector(i);
		array<char, n> data = sector.get_data();
		array<bool, n> bitvector = sector.get_bitvector();
		cout << "\n" << i << "\t";
		int counter = 0;

		for (auto it = data.begin(); it != data.end(); it++, counter++)
		{
			if (counter == (n / 2))
				cout << " ";
			if (*it == '\n')
				cout << ";";
			else
				cout << *it;
		}
		cout << "\n\t";

		counter = 0;
		for (auto it = data.begin(); it != data.end(); it++, counter++)
		{
			if (counter == (n / 2))
				cout << " ";
			if (*it == '\n')
				cout << ";";
			else
				cout << *it;
		}
		cout << "\t" << sector.get_mode() << "\t" << sector.is_free();
	}
}

void display_file_list(std::list <FCB> &file_list)
{
	if (file_list.begin() == file_list.end())
	{
		cout << "\nLista plikow jest pusta";
	}
	else
	{
		cout << "\nLista plików:";
		for (auto it = file_list.begin(); it != file_list.end(); it++)
		{
			cout << "\n" << it->get_filename_as_string() << "." << it->get_type_as_string();
		}
	}
}

void create_empty_file(HardDrive &harddrive)
{
	string filename_as_string;
	cout << "\nPodaj nazwe pliku: "; //tylko filename
	cin >> filename_as_string;
	auto filename = convert_filename_to_array(filename_as_string); // auto to array <char, fn>
	
	if (*filename.begin() != 0)
	{
		string type_as_string;
		cout << "\nPodaj rozszerzenie pliku: "; //tylko rozszerzenei
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
				cout << "\nTaki plik juz istnieje";
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
	cout << "\nPodaj nazwe pliku: "; //tylko filename
	cin >> filename_as_string;
	auto filename = convert_filename_to_array(filename_as_string); // auto to array <char, fn>

	if (*filename.begin() != 0)
	{
		string type_as_string;
		cout << "\nPodaj rozszerzenie pliku: "; //tylko rozszerzenie
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
			cout << "\nTo long type";
	}
	else
		cout << "\nTo long filename";
	
}
*/
void delete_file(HardDrive &harddrive)
{
	string filename_as_string;
	cout << "\nPodaj nazwe pliku: "; //tylko filename
	cin >> filename_as_string;
	auto filename = convert_filename_to_array(filename_as_string); // auto to array <char, fn>

	string type_as_string;
	cout << "\nPodaj rozszerzenie pliku: "; //tylko rozszerzenei
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
	cout << "\nPodaj nazwe pliku: "; //tylko filename
	cin >> filename_as_string;
	auto filename = convert_filename_to_array(filename_as_string); // auto to array <char, fn>

	if (*filename.begin() != 0)
	{
		string type_as_string;
		cout << "\nPodaj rozszerzenie pliku: "; //tylko rozszerzenei
		cin >> type_as_string;
		auto type = convert_type_to_array(type_as_string);

		if (*type.begin() != 0)
		{
			auto result = harddrive.load_file_from_Windows_and_save_on_harddrive(filename, type);
			if (result == 1)
				cout << "\nFile saved properly";
			else
				cout << "\nBrak miejsca na dysku";
		}
		else
			cout << "\nRozszerzenie pliku jest za dlugie";
	}
	else
		cout << "\nNazwa pliku jest za dluga ";
}