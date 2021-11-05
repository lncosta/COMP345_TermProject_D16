#pragma once
#include <list>
using namespace std;

// ----------------------------------- Observer class ----------------------------------------

class Observer {
public:
	~Observer();
	virtual void Update() = 0;
protected:
	Observer();
};

// ----------------------------------- Subject class ----------------------------------------

class Subject {
public:
	virtual void Attach(Observer* observerView);
	virtual void Detach(Observer* observerView);
	virtual void Notify();

	Subject();
	~Subject();
private:
	list<Observer*>* _observers;
};

// ----------------------------------- ILoggable class ----------------------------------------


class ILoggable : Subject {
	virtual void stringToLog() = 0;
};
//Order, OrderList, Game Engine, Command, CommandProcessor must inherit this

// ----------------------------------- LogObserver class ----------------------------------------

class LogObserver : Observer {
	virtual void Update(); //Notify() will call Update()
};