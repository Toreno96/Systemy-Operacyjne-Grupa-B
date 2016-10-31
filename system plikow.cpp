#include <iostream>
#include <string>
#include <list>
using std::string;

class FCB // blok kontrolny pliku
{
public:
	FCB(char filename_ [8], char atrybut_): filename(filename_), atrybut(atrybut_)// <- blad przy inicjalizacji
	{}
private:
	char user_code;
	char filename [8];
	char typ [3]; // rozszerzenie
	char atrybut; // tylko do odczytu, do modyfikacji
	char* indeks1;
	char* indeks2;
	char* indeks3;
	char* indeks4;
	char* indeks5;
};

class system_plikow
{
private:
	char pamiec_cashe[32];
	char bit_vector [128]; //32*32=1024 a kazde reprezentuje 1 bit czyli dzielone/8 = 128
	//1 - sektor wolny, 0 - sektor zajety
	std::list <FCB> Katalog{};
	char dysk_twardy[32][32];

public:
	system_plikow()
	{
		for(int i=0; i<32; i++)
		pamiec_cashe[i] = 0;
	}
};