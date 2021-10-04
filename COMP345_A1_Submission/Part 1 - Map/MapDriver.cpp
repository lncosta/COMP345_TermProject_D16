#include "Map.h"
#include <iostream>
using namespace std;

/*COMP 345 Section D - Assignment #1
* Fall 2021
* Due October 8th, 2021
Written by
Yupei Hsu 40139071
Sarah-Noemie Laurin 40150861
Arie Naccache 40099156
Luiza Nogueira Costa 40124771
Tomas Pereira 40128504
*/
int main() {
	cout << "Welcome to Warzone!" << endl;
	cout << "This driver demonstrates the functionality of the Maps" << endl;
	int numberOfMaps = -1;
	string fileName;
	MapLoader load;
	Map created; 

	
	while (numberOfMaps < 1) {
		cout << "Please enter the number of Map files to be read. Number must be greater than zero." << endl;
		cin >> numberOfMaps;
	}
	for (int i = 0; i < numberOfMaps; i++) {
		cout << "Enter the name of the Map file you would like to read. Do not forget to add the extension." << endl;
		cin >> fileName; 
		
		created = load.loadMap(fileName);
		int sum = 0; 
		for (Territory p : created.getCountryList()) {
			cout << p << endl;
			sum++; 
		}
		cout << "Territories placed: " << sum << endl;
	}
	return 0;
}