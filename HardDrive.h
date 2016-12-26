#pragma once
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

class HardDrive
{
private:
	std::list <FCB> Catalog{};
	array <Sector, max_sector_number> harddrive;
	char find_empty_sector();
	array<bool, sn> create_empty_bitvector();
	array<char, sn> create_empty_data_array();
	void append_to_string_from_deep_index(char firstSectorID, string &file_content);

	char find_deep_index_sector_ID(char ID);
	void delete_deep_sector_ID(char ID);
	int add_data_sector_to_file(array <char, fn> filename_, array <char, tn> type_, Sector sector);
	bool file_exist(array <char, fn> filename_, array <char, tn> type_);
	
public:
	int create_empty_file(array <char, fn> filename_, array <char, tn> type_);
	bool read_file(array <char, fn> filename_, array <char, tn> type_, string &file_content);
	bool delete_file(array <char, fn> filename_, array <char, tn> type_);
	int append_string_to_file(array <char, fn> filename_, array <char, tn> type_, string file_content);
	std::list <FCB> get_file_list();
	Sector get_sector(char number);
};