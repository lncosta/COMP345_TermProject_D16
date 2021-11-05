#include "Orders.h"
#include <iostream>
#include <fstream>
using namespace std;

void orderdriver() {
	/*
	Driver that creates orders of every kind, places them in an OrdersList object, and
demonstrates that the above features are available.
	*/

	ofstream filewriting;

	filewriting.open("gamelog.txt");

	if (filewriting) {
		//emptying file here
		cout << "Emptying gamelog.txt for this game..." << endl;
		cout << endl;
		filewriting.open("gamelog.txt", std::ofstream::out | std::ofstream::trunc);
		filewriting.close();

	}
	else {
		cout << "ERROR - File could not be opened!" << endl;
		throw invalid_argument("ERROR - File could not be opened!");
		return;
	}
	
	

	AdvanceOrder a1(3);
	cout << a1;
	cout << endl;
	a1.execute(); //invalid because odd

	AdvanceOrder a2(6);
	//LogObserver obs3(&a2);
	a1 = a2;
	cout << a1;
	cout << endl;
	a1.execute(); //valid because even

	
	OrdersList* list = new OrdersList();

	

	list->addOrder(new BlockadeOrder(8));
	list->addOrder(new AdvanceOrder(66));
	list->addOrder(new NegotiateOrder(2));
	list->addOrder(new BombOrder(54));
	list->addOrder(new AirliftOrder(6));
	list->addOrder(new DeployOrder(34));

	cout << "Size of list1: " << list->getOrderList().size() << endl; //6

	Order* d4 = new BlockadeOrder(66);
	Order* d5 = new AdvanceOrder(74);
	Order* d6 = new NegotiateOrder(22);
	Order* d7 = new BombOrder(76);
	Order* d8 = new AirliftOrder(12);
	Order* d9 = new DeployOrder(24);

	
	AdvanceOrder* a3 = new AdvanceOrder(666);
	LogObserver* obs3 = new LogObserver(a3); 
	a3->execute(); //LOG WORKS

	OrdersList * list3 = new OrdersList();
	LogObserver* obs2 = new LogObserver(list3);
	
	list3->addOrder(d4);
	list3->addOrder(d5);
	list3->addOrder(d6);
	list3->addOrder(d7);
	list3->addOrder(d8);
	list3->addOrder(d9);
	
	cout << *list3;
	cout << "Size of list3: " << list3->getOrderList().size() << endl; //6
	cout << endl;
	/*
	OrdersList list2(list);
	cout << endl;
	cout << list2;
	cout << endl;

	list2 = list3;

	cout << endl;
	cout << list2;
	cout << "Size of list2: " << list2.getOrderList().size() << endl; //6
	cout << endl;

	list.move(2, 5); //valid
	list.move(0, 1); //valid
	list.move(3, 6); //invalid because out of bounds
*/
	
	cout << endl;
	//ogObserver* obs = new LogObserver(d7); //DOESNT WORK

	for (int i = 0; i < list3->getOrderList().size(); i++) {
		(*list->getOrderList().at(i)).execute(); //execute() calls validate()
	}
	cout << endl;
/*
	
	list.remove(1); //valid
	list.remove(3); //valid
	list.remove(5); //invalid because out of bounds
	cout << endl;
	cout << list;

	cout << endl;
	cout << "Size of list1: " << list.getOrderList().size() << endl;
	cout << endl;
	cout << endl;

	*/


	//delete obs;
	//obs = nullptr;
	delete obs2;
	obs2 = nullptr;
	delete obs3;
	obs3 = nullptr;

	delete list;
	list = nullptr;
	delete list3;
	list3 = nullptr;
	delete a3;
	a3 = nullptr;
	
	//next place Notify() everywhere where needed, then call those methods

	
}

int main() {
	orderdriver();

	return 0;
}