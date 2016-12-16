#include "HardDrive.h"

int main()
{
	HardDrive harddrive;
	cout << "Dane\t\t\tTryb\tstan";
	for (int i = 0; i < n; i++)
	{
		Sector sector = harddrive.get_sector(i);
		array<char, n> data = sector.get_data();
		cout << "\n";
		int counter = 0;
		for (auto it = data.begin(); it != data.end(); it++, counter++)
		{
			if (counter == 8)
				cout << " ";
			cout << *it;
		}
		cout << "\t" << sector.get_mode() << "\t" << sector.is_free();
	}
	return 0;
}