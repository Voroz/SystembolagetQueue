#pragma once
#include <iostream>
#include <queue>
#include <vector>
#include <functional>
#include <string>
#include <fstream>
#include "Person.h"
#include "Register.h"

const int STARTTIME = 39600;
const int nrOfRegisters = 2;

class SimulationSystem
{
public:
	SimulationSystem() {
		loadPersonFile("system.txt", _queue);
		for (int i = 0; i < nrOfRegisters; i++) {
			_registers.push_back(new Register(_currentTime));
		}
		_currentTime = STARTTIME;
	}

	Register* findEarliestFreeRegister() {
		Register* earliestFreeReg = _registers[0];
		for (auto* reg : _registers) {
			if (reg->readyTime() < earliestFreeReg->readyTime()) {
				earliestFreeReg = reg;
			}
		}
		return earliestFreeReg;
	}

	void serveNextPerson() {
		Register* reg = findEarliestFreeRegister();
		reg->queuePerson(_queue.top());
		if (_queue.top().name == "Ragnar") {

			int seconds = reg->readyTime();
			int hours = reg->readyTime() / (60 * 60);
			seconds -= hours * (60 * 60);
			int minutes = seconds / 60;
			seconds -= minutes * 60;

			std::cout << hours << ":" << minutes << ":" << seconds << "   " << reg->readyTime() << std::endl;
		}
		_queue.pop();
	}

	bool loadPersonFile(std::string filename, std::priority_queue<Person, std::vector<Person>, std::greater<Person>>& queue) {
		std::ifstream file;
		file.open(filename);

		if (!file.is_open()) {
			std::cout << "Failed to load file " << filename << std::endl;
			return false;
		}

		while (!file.eof()) {
			Person person;
			file >> person.name;
			file >> person.arrivalTime;
			file >> person.serveTime;
			queue.push(person);
		}
		file.close();
		return true;
	}

	void run() {

		while (_queue.size() > 0) {
			Register* earliestFreeRegister = findEarliestFreeRegister();
			if (earliestFreeRegister->readyTime() > _queue.top().arrivalTime) {
				_currentTime = earliestFreeRegister->readyTime();

				for (auto reg : _registers) {
					reg->update();
				}
			}
			else {
				_currentTime = _queue.top().arrivalTime;
			}
			serveNextPerson();
		}
	}

private:
	std::priority_queue<Person, std::vector<Person>, std::greater<Person>> _queue;
	std::vector<Register*> _registers;
	int _currentTime;
};

