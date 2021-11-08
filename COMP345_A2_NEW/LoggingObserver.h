#pragma once
#include <list>
#include <string>
using namespace std;

/*COMP 345 Section D - Assignment #2
* Fall 2021
* Due November 12th, 2021
Written by
Yupei Hsu 40139071
Sarah-Noemie Laurin 40150861
Arie Naccache 40099156
Luiza Nogueira Costa 40124771
Tomas Pereira 40128504
*/

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
