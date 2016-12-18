#pragma once
#include<iostream>
#include"Process.hpp"
#include<deque>
class Lock
{
protected:
	int value = 1;			 // wartosc zamka, ujemne wartosci oznaczaja ile procesow czeka pod zamkiem
	std::deque <std::reference_wrapper<Process>> waiting_process_list; //lista procesow czekajacych pod zamkiem
	std::deque <std::string> blocking_IDs_list; //lista ID procesow czekajacych pod zamkiem, uzywana do weryfikacji procesu, ktory zajal zamek
public:
	int GetValue(); // ilosc procesow pod zamkiem
	std::string GetProcessName(); //wypisuje id procesu pierwszego do zwolnienia
	void Show_List_of_Processes(); // wyswietlenie calej listy procesow pod zamkiem
	void lock(Process &process);   // metoda ryglujaca
	void unlock(Process &process); // metoda otwierajaca zamek, otworzy jesli ID procesu zgadza sie z ID procesu, ktory zamknal zamek
};
