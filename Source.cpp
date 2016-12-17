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
			display_harddrive(harddrive);
			break;
		}
		case 3:
		{
			display_harddrive_2(harddrive);
			break;
		}
		case 4:
		{
			create_empty_file(harddrive);
			break;
		}
		default:
			break;
		}
	} while (choice != 0);
	return 0;
}