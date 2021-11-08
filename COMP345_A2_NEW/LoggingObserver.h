
#pragma once
#include <list>
#include <string>
using namespace std;

// ----------------------------------- ILoggable class ----------------------------------------

class ILoggable {
public:
	virtual string stringToLog() = 0; //creates and returns a string to be output to the log file

};

// ----------------------------------- Observer class ----------------------------------------

class Observer {
public:
	~Observer();
	virtual void Update(string log) = 0;
protected:
	Observer();
};

// ----------------------------------- Subject class ----------------------------------------

class Subject : public ILoggable {
public:
	Subject();
	Subject(const Subject& s);
	virtual ~Subject();

	virtual void Attach(Observer* observerView);
	virtual void Detach(Observer* observerView);
	virtual void Notify();

	virtual string stringToLog();
protected:
	list<Observer*>* _observers;
};

// ----------------------------------- LogObserver class ----------------------------------------


class LogObserver : public Observer {
protected:
	Subject* _subject;
public:
	LogObserver();
	LogObserver(Subject* subject);
	~LogObserver();

	//Notify() will call Update()
	virtual void Update(string log); //takes illogable as parameter?
};
