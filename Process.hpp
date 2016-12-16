﻿#pragma once

#include <functional>
#include <string>
#include "Registers.h"
#include "Undefined.hpp"

class Process {
public:
	static const unsigned int minPriority;
	static const unsigned int maxPriority;
	enum class State { New, Ready, Running, Waiting, Terminated };
	Process(const std::string& name, unsigned int priority,
		Undefined& pageTable);
	std::string getName() const;
	unsigned int getOriginalPriority() const;
	unsigned int getCurrentPriority() const;
	State getState() const;
	Undefined& pageTable();
	Registers getRegistersBackup() const;
	int getInstructionCounter() const;
	int getCurrentPriorityDuration() const;
	void restoreOriginalPriority();
	void increasePriority();
	void decreasePriority();
	// Zamiast poni¿szego, powrót do koncepcji osobnych metod do ustawiania
	// ka¿dego stanu i wykonania "ewentualnych dodatkowych, zwi¹zanych z tym
	// operacji"?
	void setState(const State& state);
	void setRegistersBackup(const Registers& registers);
	void setInstructionCounter(int instructionCounter);
	void increaseCurrentPriorityDuration();
private:
	void setPriority(unsigned int priority);
	void resetCurrentPriorityDuration();
	// Nazwa procesu jest jednoczeœnie jego identyfikatorem, gdy¿ jest ona
	// unikatowa, ze wzglêdu na istnienie tylko jednej grupy procesów w naszym
	// systemie
	std::string name_;
	unsigned int originalPriority_, currentPriority_;
	State state_;
	std::reference_wrapper< Undefined > pageTable_;
	Registers registersBackup_;
	int instructionCounter_,
		currentPriorityDuration_;
	// Poza tym - sk³adowe potrzebne do komunikacji, ale wygl¹du tych ju¿
	// kompletnie nie znam. Potrzebujê info od Jakuba.
};