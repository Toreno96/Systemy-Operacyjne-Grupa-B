#pragma once
#include "HardDrive.h"
#include <list>
namespace filesystemUI
{
	string filename_and_type_as_string(array <char, fn> filename_, array <char, tn> type_);

	array <char, fn> convert_filename_to_array(string filename_as_string);

	array <char, tn> convert_type_to_array(string type_as_string);

	void display_harddrive(HardDrive &harddrive, bool mode);

	void display_file_list(std::list <FCB> &file_list);

	void delete_file(HardDrive &harddrive);

	void load_file_from_Windows_and_save_on_harddrive(HardDrive &harddrive);

	void system_create_file_based_on_string(HardDrive &harddrive, string filename_as_string, string type_as_string, string file_content);

	int system_read_file(HardDrive &harddrive, string filename_as_string, string type_as_string, string &file_content);

	void display_file(HardDrive &harddrive);
}