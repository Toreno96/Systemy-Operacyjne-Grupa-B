#pragma once
#include "filesystemcommon.h"
#include <array>
using std::array;
#include <string>
using std::string;
//Podczas tworzenia pliku tworzona jest instancja FCB​

class FCB // blok kontrolny pliku
{
private:
	array <char, fn> filename;
	array <char, tn> type; // rozszerzenie np. txt​
	char firstSectorID;

public:
	FCB(array <char, fn> filename_, array <char, tn> type_, char firstSectorID_) : filename(filename_), type(type_), firstSectorID(firstSectorID_) {}
	array <char, fn> get_filename() { return filename; }
	string get_filename_as_string()
	{
		string filename_as_string;
		for (auto it = filename.begin(); it != filename.end(); it++)
		{
			if(*it !=0)
				filename_as_string.push_back(*it);
		}
		return filename_as_string;
	}
	array <char, tn> get_type() { return type; }
	string get_type_as_string()
	{
		string type_as_string;
		for (auto it = type.begin(); it != type.end(); it++)
		{
			if (*it != 0)
				type_as_string.push_back(*it);
		}
		return type_as_string;
	}
	char get_firstSectorID() { return firstSectorID; }
};