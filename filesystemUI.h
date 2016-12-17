#pragma once
#include <iostream>
using std::cin;
using std::cout;
#include "HardDrive.h"
#include <list>
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
			if (counter == 8)
				cout << " ";
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

		for (auto it = bitvector.begin(); it != bitvector.end(); it++, counter++)
		{
			if (counter == 8)
				cout << " ";
			cout << *it;
		}
		cout << "\n\t";

		counter = 0;
		for (auto it = data.begin(); it != data.end(); it++, counter++)
		{
			if (counter == 8)
				cout << " ";
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
		for (auto it = file_list.begin(); it != file_list.end(); it++)
		{
			cout << it->get_filename_as_string() << "." << it->get_type_as_string() << std::endl;
		}
	}
}

void create_empty_file(HardDrive &harddrive)
{
	string filename_as_string;
	cout << "\nPodaj nazwe pliku: "; //tylko filename
	cin >> filename_as_string;
	//cout << "\nDlugosc nazwy to " << filename_as_string.size();
	array <char, 8> filename;
	if (filename_as_string.size() <= fn)
	{
		size_t i = 0;
		for (; filename_as_string.size() != 0; i++)
		{
			filename[i] = *(filename_as_string.begin()); // wyluskanie wartosci begin
			//cout << "\ndopisalem " << *(filename_as_string.begin());
			filename_as_string.erase(filename_as_string.begin()); // usuwa pierwszy element
		}
		for(;i<fn; i++)
		{
			filename[i] = 0;//pozostale znaki inicjalizujemy nulem
		}
	}
	else
	{
		cout << "\nNazwa pliku jest za dluga";
		return;
	}

	string type_as_string;
	cout << "\nPodaj rozszerzenie pliku: "; //tylko rozszerzenei
	cin >> type_as_string;
	//cout << "\nDlugosc rozszerzenia to " << type_as_string.size();
	array <char, 3> type;
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
	}
	else
	{
		cout << "\nRozszerzenie pliku jest za dlugie";
		return;
	}

	if (harddrive.create_empty_file(filename, type) == 1)
		cout << "\nPlik utworzony";
	else if (harddrive.create_empty_file(filename, type) == 2)
		cout << "\nBrak miejsca na dysku by utworzyc nowy plik.";
	else if (harddrive.create_empty_file(filename, type) == 0)
		cout << "\nTaki plik juz istnieje";
}

//void delete_file(array <char, 8> filename_, array <char, 3> type_)