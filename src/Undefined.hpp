#pragma once

// Pomocnicza klasa tymczasowa dla obiektów, dla których niesprecyzowana jest
// jeszcze dok³adna postaæ klas, które reprezentuj¹. Dla przyk³adu:
// Wiem, ¿e w PCB znaleŸæ musz¹ siê sk³adowe, reprezentuj¹ce rejestry procesu.
// Jednak na chwilê obecn¹ (2016-11-01, 12:35) nieznana jest mi postaæ klasy,
// implementuj¹cej funkcjonalnoœæ rejestru. Zamiast tworzyæ tymczasow¹, w³asn¹
// klasê Register, powy¿szym sk³adowym nadam po prostu tymczasowo typ Undefined.
//
// W ten sposób uniknê niepotrzebnego zaœmiecania repozytorium wiêksz¹ liczb¹
// tymczasowych plików, w przypadku gdyby wiêcej sk³adowych mia³o podzieliæ los
// obiektu klasy implementuj¹cej funkcjonalnoœæ rejestru.
class Undefined {};