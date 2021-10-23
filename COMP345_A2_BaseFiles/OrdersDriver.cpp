#include "Orders.h"
#include <iostream>
#include <fstream>
using namespace std;

void orderdriver() {
	/*
	Driver that creates orders of every kind, places them in an OrdersList object, and
demonstrates that the above features are available.
	*/

	AdvanceOrder a1(3);
	cout << a1;
	cout << endl;
	a1.execute(); //invalid because odd

	AdvanceOrder a2(6);
	a1 = a2;
	cout << a1;
	cout << endl;
	a1.execute(); //valid because even

	
	OrdersList list;

	list.addOrder(new BlockadeOrder(7));
	list.addOrder(new AdvanceOrder(66));
	list.addOrder(new NegotiateOrder(1));
	list.addOrder(new BombOrder(54));
	list.addOrder(new AirliftOrder(9));
	list.addOrder(new DeployOrder(34));

	cout << "Size of list1: " << list.getOrderList().size() << endl; //6

	Order* d4 = new BlockadeOrder(63);
	Order* d5 = new AdvanceOrder(75);
	Order* d6 = new NegotiateOrder(22);
	Order* d7 = new BombOrder(76);
	Order* d8 = new AirliftOrder(12);
	Order* d9 = new DeployOrder(24);

	OrdersList list3;

	list3.addOrder(d4);
	list3.addOrder(d5);
	list3.addOrder(d6);
	list3.addOrder(d7);
	list3.addOrder(d8);
	list3.addOrder(d9);

	cout << list3;
	cout << "Size of list3: " << list3.getOrderList().size() << endl; //6
	cout << endl;

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

	cout << endl;

	for (int i = 0; i < list.getOrderList().size(); i++) {
		(*list.getOrderList().at(i)).execute(); //execute() calls validate()
	}
	cout << endl;

	list.remove(1); //valid
	list.remove(3); //valid
	list.remove(5); //invalid because out of bounds
	cout << endl;
	cout << list;

	cout << endl;
	cout << "Size of list1: " << list.getOrderList().size() << endl;
	cout << endl;
	cout << endl;

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

	d9->stringToLog();
	d8->stringToLog();
	d7->stringToLog();
	d6->stringToLog();
	d5->stringToLog();
	d4->stringToLog();
	list2.stringToLog();
}

int main() {
	orderdriver();

	return 0;
}