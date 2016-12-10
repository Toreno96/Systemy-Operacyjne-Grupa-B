#pragma once

// Pomocnicza klasa tymczasowa dla obiekt�w, dla kt�rych niesprecyzowana jest
// jeszcze dok�adna posta� klas, kt�re reprezentuj�. Dla przyk�adu:
// Wiem, �e w PCB znale�� musz� si� sk�adowe, reprezentuj�ce rejestry procesu.
// Jednak na chwil� obecn� (2016-11-01, 12:35) nieznana jest mi posta� klasy,
// implementuj�cej funkcjonalno�� rejestru. Zamiast tworzy� tymczasow�, w�asn�
// klas� Register, powy�szym sk�adowym nadam po prostu tymczasowo typ Undefined.
//
// W ten spos�b unikn� niepotrzebnego za�miecania repozytorium wi�ksz� liczb�
// tymczasowych plik�w, w przypadku gdyby wi�cej sk�adowych mia�o podzieli� los
// obiektu klasy implementuj�cej funkcjonalno�� rejestru.
class Undefined {};