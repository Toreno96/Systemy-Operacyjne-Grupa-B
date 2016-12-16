#pragma once
#include "filesystemcommon.h"
#include <array>
using std::array;
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