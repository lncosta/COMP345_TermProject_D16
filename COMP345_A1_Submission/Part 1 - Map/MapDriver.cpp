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
	Map* created;
	vector<Map*> mapsCreated;


	while (numberOfMaps < 1) {
		cout << "Please enter the number of Map files to be read. Number must be greater than zero." << endl;
		cin >> numberOfMaps;
	}
	for (int i = 0; i < numberOfMaps; i++) {
		cout << "Enter the name of the Map file you would like to read. Do not forget to add the extension." << endl;
		cin >> fileName; 
		try {
			created = load.loadMap(fileName);
			if (created == nullptr)
				continue;
			mapsCreated.push_back(created);
			int sum = 0;
			cout << "The Map #" << i + 1 << " Contains the Following Territories : " << endl;
			for (Territory* p : created->getTerritoyVector()) {
				cout << *p << endl;
				sum++;
			}
			cout << "Territories placed: " << sum << endl;
		}
		catch (const invalid_argument& e) {
			cout << "The map file provided was invalid. " << endl;
		}
		/**/
		cout << "All maps created were: " << endl;
		for (Map* a : mapsCreated) {
			//cout << *a;
			Map temp = *a;
			vector<Territory*> t = (*a).getTerritoyVector();
			//cout << "Adjacent:" << endl; 
			for (Territory* o : t) {
				vector<Territory*> adj = o->getAdjTerritories();
				cout << "Territories adjacent to: " << o->getTerritoryID() << endl;
				for (Territory* p : adj) {
					//cout << *p;
				}
			}



			//cout << (*(temp.wasVisited)).size();
			//bool temp2 = *(temp.wasVisited);


			//vector<int>* temp1 = a->neighbors;
			//int size = temp1->size();




		}

		//Go through mapsCreated and call validate()
		for (auto p : mapsCreated) {
			p->continentSubgraphs(p);
			p->printMap();
			p->countryToContinentRelation();
			p->isConnected();
		}


	}
	system("pause");
	return 0;
}
