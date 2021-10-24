#include "LoggingObserver.h"

// ----------------------------------- Observer class ----------------------------------------

Observer::Observer() {

}

Observer::~Observer() {

}

// ----------------------------------- Subject class ----------------------------------------
Subject::Subject() {
	_observers = new list<Observer*>;
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
	list<Observer*>::iterator i = _observers->begin();
	for (; i != _observers->end(); ++i) {
		(*i)->Update();
	}
}



