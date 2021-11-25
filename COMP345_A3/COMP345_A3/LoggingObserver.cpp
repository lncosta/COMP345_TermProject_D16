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

/*
	Observer Constructor
*/
Observer::Observer() {

}
/*
	Observer Destructor
*/
Observer::~Observer() {

}
/*
	No need for an Observer copy constructor since we cannot instantiate an Observer abstract class.
	I thought I would still have Observer destructor and constructor nevertheless.
*/

// ----------------------------------- Subject class ----------------------------------------
/*
	Subject Constructor
*/
Subject::Subject() {
	_observers = new list<Observer*>;
}
/*
	Subject Copy Constructor
*/
Subject::Subject(const Subject& s) {
	_observers = s._observers;
}
/*
	Subject Destructor
*/
Subject::~Subject() {
	delete _observers;
	_observers = nullptr;
}
/*
	Subject Assignment Operator
*/
Subject& Subject::operator=(const Subject& sub) {
	//empty current list to start the copy
	for (Observer* individualObs : *_observers) {
		delete individualObs;
		individualObs = nullptr;
	}
	(*_observers).clear();

	list<Observer*> newObservers = (*sub._observers);
	for (Observer* individualObs : newObservers) {
		this->_observers->push_back(individualObs); //shallow copy because we want to keep a reference of the observers that are attached
	}
	return *this;
}
/*
	Subject Attach function
	Attaches the subject to the observer list
*/
void Subject::Attach(Observer* obsView) {
	_observers->push_back(obsView);
}
/*
	Subject Detach function
	Detaches the subject from the observer list
*/
void Subject::Detach(Observer* obsView) {
	_observers->remove(obsView);
}
/*
	Subject Notify function
	For every observer that the subject is attached to, will call Notify to update each of the observer views.
*/
void Subject::Notify() {
	list<Observer*>::iterator i = _observers->begin();
	for (; i != _observers->end(); ++i) {
		(*i)->Update(this); //if it doesnt go here, it's because it's not attached
	}
}
/*
	Subject stringToLog function
	Returns a dummy string log.
*/
string Subject::stringToLog() {
	return "unspecified subject log";
}
/*
	Subject stream insertion
*/
ostream& operator<<(ostream& output, const Subject& sub) {
	output << "This is a subject." << endl;
	return output;
};

// ----------------------------------- LogObserver class ----------------------------------------

/*
	LogObserver Default Constructor
*/
LogObserver::LogObserver() {
	/* deliberately empty */
}
/*
	LogObserver Overloaded Constructor.
	We usually use this constructor to enable the attachment of a Subject on that observer.
*/
LogObserver::LogObserver(Subject* s) {
	_subject = s;
	_subject->Attach(this);
}
/*
	LogObserver Copy Constructor
*/
LogObserver::LogObserver(const LogObserver& logobs) {
	(*_subject) = (*logobs._subject);
}
/*
	LogObserver Destructor
*/
LogObserver::~LogObserver() {
	_subject->Detach(this);
}
/*
	LogObserver Update function.
	It will append to the gamelog.txt file with any new string log given to it.
*/
void LogObserver::Update(ILoggable* loggable) {
	//get the string to log from the subject from "nextLog"
	string nextLog = loggable->stringToLog();

	//then add the string to the log
	ofstream filewriting;
	filewriting.open("gamelog.txt", ios::app);

	if (filewriting) {
		//write to file 
		filewriting << nextLog << endl;

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
/*
	LogObserver Assignment Operator
*/
LogObserver& LogObserver::operator=(const LogObserver& log) {
	(*_subject) = (*log._subject);
	return *this;
}
/*
	LogObserver stream insertion
*/
ostream& operator<<(ostream& output, const LogObserver& log) {
	output << "This is a LogObserver." << endl;
	return output;
};