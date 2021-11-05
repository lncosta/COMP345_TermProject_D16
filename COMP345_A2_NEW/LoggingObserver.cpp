#include "LoggingObserver.h"
#include "Orders.h"
#include "GameEngine.h"
#include <fstream>
#include <iostream>

class Order;
class OrdersList;
class GameEngine;
class Command;
class CommandProcessor;

// ----------------------------------- Observer class ----------------------------------------

Observer::Observer() {

}

Observer::~Observer() {

}

// ----------------------------------- Subject class ----------------------------------------
Subject::Subject() {
	_observers = new list<Observer*>;
}

Subject::Subject(const Subject& s) {
	_observers = s._observers;
}

Subject::~Subject() {
	delete _observers;
	_observers = nullptr;
}

void Subject::Attach(Observer* obsView) {
	_observers->push_back(obsView);
}

void Subject::Detach(Observer* obsView) {
	_observers->remove(obsView);
}

void Subject::Notify() {
	cout << "called notify?" << endl;
	list<Observer*>::iterator i = _observers->begin();
	for (; i != _observers->end(); ++i) {
		string log = this->stringToLog();
		(*i)->Update(log);
	}
	/*
	//attach orders inside a list if we have orderlist
	OrdersList* tempList = dynamic_cast<OrdersList*>(this);
	if (tempList != NULL) {
		i = _observers->begin();
		for (; i != _observers->end(); ++i) {
			(*tempList->getOrderList().back()).Attach(*i);
		}
	}
	tempList = nullptr;
	*/
}

string Subject::stringToLog() {
	return "unspecified subject log";
}


// ----------------------------------- LogObserver class ----------------------------------------

LogObserver::LogObserver() {
	/* deliberately empty */
}
LogObserver::LogObserver(Subject* s) {
	_subject = s;
	_subject->Attach(this);
	cout << "!!!attaching!!!" << endl;
}
LogObserver::~LogObserver() {
	_subject->Detach(this);
	cout << "!!!detaching!!!" << endl;
}

//**was having issues trying to pass a Subject pointer as a parameter so I decided to call stringToLog inside Notify
void LogObserver::Update(string nextLog) {
	//get the string to log from the subject from "nextLog"

	//then add the string to the log

	ofstream filewriting;
	filewriting.open("gamelog.txt", ios::app);

	if (filewriting) {
		//write to file 
		filewriting << nextLog << endl; //call saveEffect here?

		cout << "Successfully added log to file." << endl;
		cout << endl;
		filewriting.close();
	}
	else {
		cout << "ERROR - File could not be opened!" << endl;
		throw invalid_argument("ERROR - File could not be opened!");
		return;
	}
}

