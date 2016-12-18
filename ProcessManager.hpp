#pragma once

#include <list>
#include <random>
#include "Process.hpp"

class ProcessManager {
public:
	ProcessManager();
	std::list< Process >& processes();
	void createProcess(const std::string& name,
		const Undefined& programCode);
	void createProcess(const std::string& name,
		const Undefined& programCode, unsigned int priority);
	Process& getProcess(const std::string& name);
	Process& getRunningProcess();
	void removeTerminatedProcesses();
private:
	Process& getProcess(
		std::function< bool(const Process& process) > unaryPredicate);
	bool isNameUsed(const std::string& name);
	std::random_device::result_type generateSeed();
	std::mt19937 randomNumberGenerator_;
	std::list< Process > processes_;
};

// Jeśli moduł zarządzania pamięcią operacyjną zostanie ubrany w klasę (bardzo
// pewne), jego funkcje (a wtedy już metody) przestaną mieć globalny zakres i
// pojawi się wymóg przekazywania obiektu wyżej wspomnianej klasy do niektórych
// metod klasy ProcessManager jako argument.
//
// Przy założeniu, że klasa IZP = klasa implementująca moduł zarządzania pamięcia operacyjną:
//
// Aby to zniwelować, można by pokusić się o uczynienie metod klasy IZP
// statycznymi, ale nawet lepszym pomysłem byłoby umieścić wśród składowych
// klasy ProcessManager odwołanie (wskaźnik/referencję) do obiektu klasy IZP.
//
// Wtedy należałoby takie odwołanie zapewnić np. przez konstruktor klasy
// ProcessManager przy tworzeniu instancji tej klasy w klasie zespalającej
// wszystkie moduły całego systemu operacyjnego.