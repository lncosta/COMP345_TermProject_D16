#include "Orders.h"
#include <iostream>

using namespace std; //make sure to add the "only compile this once" keyword

int main() {
	/*
	Driver that creates orders of every kind, places them in an OrdersList object, and
demonstrates that the above features are available. 
	*/
	Order o1(7);
	cout << o1;
	DeployOrder d1(3);
	cout << d1;
	d1.execute(); //invalid because odd
	
	d1.setId(6); 
	cout << d1;
	d1.execute(); //valid because even

	DeployOrder d2(4);
	d1 = d2;
	cout << d1;

	OrdersList list;

	list.addOrder(new Order(o1));
	Order o2(66);
	Order o3(54);
	list.addOrder(new Order(o2));
	Order* d3 = new DeployOrder(34); //doesnt display the deploy order description
	list.addOrder(d3);
	list.addOrder(new Order(o3));
	
	OrdersList list2(list);
	list2 = list;
	//cout << list;
	list.move(0, 5);
	cout << list;

	list.remove(1);
	//cout << list;
	//cout << list2;
	return 0;
}