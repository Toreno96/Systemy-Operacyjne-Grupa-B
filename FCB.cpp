#include "filesystemcommon.h"
#include "FCB.h"
//Podczas tworzenia pliku tworzona jest instancja FCB​

array <char, fn> FCB::get_filename() { return filename; }
string FCB::get_filename_as_string()
{
	string filename_as_string;
	for (auto it = filename.begin(); it != filename.end(); it++)
	{
		if (*it != 0)
			filename_as_string.push_back(*it);
	}
	return filename_as_string;
}
array <char, tn> FCB::get_type() { return type; }
string FCB::get_type_as_string()
	{
		string type_as_string;
		for (auto it = type.begin(); it != type.end(); it++)
		{
			if (*it != 0)
				type_as_string.push_back(*it);
		}
		return type_as_string;
	}
char FCB::get_firstSectorID() { return firstSectorID; }