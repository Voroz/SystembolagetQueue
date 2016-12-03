#pragma once
#include "Person.h"
#include <deque>

class Register
{
public:
	Register(int& currentTime) :
		_currentTime(currentTime){

	}

	void queuePerson(Person person) {
		_queue.push_back(person);
	}

	int readyTime() {
		int willBeReadyAt = _currentTime;
		for (auto person : _queue) {
			willBeReadyAt += person.serveTime;
		}
		return willBeReadyAt;
	}

	void update() {
		while (_queue.size() >  0 && _currentTime >= _queue.front().arrivalTime + _queue.front().serveTime) {
			_queue.pop_front();
		}
	}

private:
	int& _currentTime;
	std::deque<Person, std::vector<Person>> _queue;
};

