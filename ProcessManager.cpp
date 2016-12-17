#include <algorithm>
#include <stdexcept>
#include "ProcessManager.hpp"
// Za³¹czenie modu³u zarz¹dzania pamiêci¹ operacyjn¹ TO-DO

ProcessManager::ProcessManager() :
	randomNumberGenerator_(std::mt19937(generateSeed())) {}
std::list< Process >& ProcessManager::processes() {
	return processes_;
}
void ProcessManager::createProcess(const std::string& name,
	const Undefined& programCode) {
	std::uniform_int_distribution< unsigned int > distribution(
		Process::minPriority, Process::maxPriority);
	unsigned int randomPriority = distribution(randomNumberGenerator_);
	createProcess(name, programCode, randomPriority);
}
void ProcessManager::createProcess(const std::string& name,
	const Undefined& programCode, unsigned int priority) {
	if (isNameUsed(name))
		throw std::invalid_argument("Process' name has to be unique");
	// W przysz³oœci pojawi siê inicjalizacja obiektem zwróconym przez tê funkcjê
	// modu³u zarz¹dzania pamiêci¹ operacyjn¹, która odpowiedzialna jest za
	// przeniesienie kodu programu z pamiêci dyskowej do pamiêci RAM. TO-DO
	Undefined pageTable;
	processes_.push_back(Process(name, priority, pageTable));
}
bool ProcessManager::isNameUsed(const std::string& name) {
	return std::any_of(processes_.begin(), processes_.end(),
		[name](const Process& process) {
		return process.getName() == name;
	});
}
void ProcessManager::removeTerminatedProcesses() {
	auto isTerminated = [](const Process& process) {
		return process.getState() == Process::State::Terminated; };
	processes_.erase(std::remove_if(processes_.begin(), processes_.end(),
		isTerminated), processes_.end());
}
std::random_device::result_type ProcessManager::generateSeed() {
	std::random_device randomDevice;
	return randomDevice();
}
