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
	array <char, fn> get_filename();
	string get_filename_as_string();
	array <char, tn> get_type();
	string get_type_as_string();
	char get_firstSectorID();
};