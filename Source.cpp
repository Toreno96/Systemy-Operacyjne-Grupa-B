#include "filesystemUI.h"
using std::cin;
int main()
{
	HardDrive harddrive;
	int choice = 0;
	do
	{
		cout << "\n\n0 - exit"
			<< "\n1 - display_file_list"
			<< "\n2 - display_harddrive"
			<< "\n3 - display_harddrive_2"
			<< "\n4 - create_empty_file"
			<< "\n5 - delete_file"
			<< "\n6 - load_file_from_Windows_and_save_on_harddrive"
			<< "\n7 - create_this_string_file_system"
			<< "\n8 - read_file"
			<< "\nWybierz: ";
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
			create_empty_file(harddrive);
			break;
		}
		case 5:
		{
			delete_file(harddrive);
			break;
		}
		case 6:
		{
			load_file_from_Windows_and_save_on_harddrive(harddrive);
			break;
		}
		case 7:
		{
			string filename = "Pliczek";
			string type = "txt";
			string mystring = "Wynik silnia 5 = 120";
			create_this_string_file_system(harddrive, filename, type, mystring);
			break;
		}
		case 8:
		{
			read_file(harddrive);
			break;
		}
		default:
			break;
		}
	} while (choice != 0);
	return 0;
}