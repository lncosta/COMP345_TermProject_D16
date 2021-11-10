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
	virtual string stringToLog() = 0; 
};

// ----------------------------------- Observer class ----------------------------------------

class Observer {
public:
	virtual ~Observer();
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
	Subject& operator=(const Subject& sub);
	friend ostream& operator<<(ostream& output, const Subject& order);

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
	LogObserver(const LogObserver& logobs);
	virtual ~LogObserver();
	
	LogObserver& operator=(const LogObserver& logobs);
	friend ostream& operator<<(ostream& output, const LogObserver& order);

	//Notify() will call Update()
	virtual void Update(string log); 
};
