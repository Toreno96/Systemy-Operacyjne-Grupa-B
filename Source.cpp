#include "filesystemUI.h"
using std::cin;
using namespace filesystemUI;
int main()
{
	HardDrive harddrive;
	int choice = 0;
	do
	{
		cout << "\n\nSpaces in filename or extension are not allowed."
			<< "\n0 - exit"
			<< "\n1 - display_file_list"
			<< "\n2 - display_harddrive"
			<< "\n3 - display_harddrive_2"
			<< "\n4 - delete_file"
			<< "\n5 - load_file_from_Windows_and_save_on_harddrive"
			<< "\n6 - create_file_based_on_string_system"
			<< "\n7 - display_file"
			<< "\n8 - add_to_file"
			<< "\nYour choice: ";
		cin >> choice;

		switch (choice)
		{
		case 0:
			{
				break;
			}
		case 1:
		{
			display_file_list(harddrive.get_file_list());
			break;
		}
		case 2:
		{
			display_harddrive(harddrive, 0);
			break;
		}
		case 3:
		{
			display_harddrive(harddrive, 1);
			break;
		}
		case 4:
		{
			delete_file(harddrive);
			break;
		}
		case 5:
		{
			load_file_from_Windows_and_save_on_harddrive(harddrive);
			break;
		}
		case 6:
		{
			string filename = "Pliczek";
			string type = "txt";
			string mystring = "Wynik silnia 5 = 120";
			system_create_file_based_on_string(harddrive, filename, type, mystring);
			break;
		}
		case 7:
		{
			display_file(harddrive);
			break;
		}
		case 8:
		{
			string filename_as_string;
			cout << "\nType a filename: "; //tylko filename
			cin >> filename_as_string;
			auto filename = convert_filename_to_array(filename_as_string);

			string type_as_string;
			cout << "\nType an extension: "; //tylko rozszerzenie
			cin >> type_as_string;
			auto type = convert_type_to_array(type_as_string);

			cout << "\nPodaj tekst: ";
			string file_content;
			cin.ignore();
			std::getline(cin, file_content);
			auto jakiswynik = harddrive.append_string_to_file(filename, type, file_content);
			cout << "\nJuz!";
		}
		default:
			break;
		}
	} while (choice > 0 && choice <=8);
	return 0;
}