// Graph Implementation basis: https://www.geeksforgeeks.org/connectivity-in-a-directed-graph/
#include "Map.h"
#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <iomanip>
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
// Temporary Classes

// Player Class for Territory Ownership
Player::Player(void) {
	name = "Default";
	playerID = 0;
}
Player::Player(const Player& other) {
	name = other.name;
	playerID = other.playerID;
}
Player::~Player(void) {

}

// Task Specific Classes

// Constructor for the Territory Class
Territory::Territory(int tID, int cID) {
	Player* nullPlayer = new Player();
	owner = nullPlayer;
	name = "Default";
	continentID = cID;
	territoryID = tID;
	vector<Territory*> adjTerritories;
	armiesPlaced = 0;
}
Territory::Territory(int tID, int cID, string o)
{
	Player* nullPlayer = new Player();
	owner = nullPlayer;
	continentID = cID;
	territoryID = tID;
	name = o;
	vector<Territory*> adjTerritories;
	armiesPlaced = 0;
}
Territory::Territory(const Territory& other) : adjTerritories(other.adjTerritories.size()) {
	continentID = other.continentID;
	territoryID = other.territoryID;
	name = other.name;
	armiesPlaced = other.armiesPlaced;
	owner = other.owner;

	adjTerritories = other.adjTerritories;
}
Territory::~Territory(void) {
	for (auto p : adjTerritories) {
		delete p;
	}
	adjTerritories.clear();
}
int Territory::getContinentID(void) {
	return continentID;
}
int Territory::getTerritoryID(void) {
	return territoryID;
}
vector<Territory*> Territory::getAdjTerritories(void) {
	return adjTerritories;
}

void Territory::addAdj(Territory* o)
{
	adjTerritories.push_back(o);
}

void Territory::setOwner(Player* o)
{
	owner = o;
}

string Territory::getTerritoryName() {
	return name;
}

// Overloading the '==' operator for comparision between Territory objects
bool Territory::operator==(const Territory& other) {
	return territoryID == other.territoryID;
}


// Constructor for the Map Class.
Map::Map(void) {

	numTerritories = 0;


}
// Destructor for the Map Class
Map:: ~Map() {

}
// Copy constructor
Map::Map(const Map& toCopy) {
	numTerritories = toCopy.numTerritories;
}


void Map::addContinent(Continent* theContinent)
{
	continentVector.push_back(theContinent);
}

vector<Territory*> Map::getTerritoyVector(void) {
	return territoryVector;
}
// Given a territory ID, will return the associate Territory Object
Territory* Map::getTerritory(int territoryToFind) {
	vector<Territory*> currentTerritoryVector = this->getTerritoyVector();
	Territory* theTerritory = 0;
	for (auto t : currentTerritoryVector) {
		if (t->getTerritoryID() == territoryToFind)
			theTerritory = t;
	}
	return theTerritory;
}

void Map::printMap(void) {
	cout << "----- Printing The Map Contents Below ------" << endl;
	for (auto p : territoryVector) {
		cout << left << setw(4) << p->getTerritoryID() << left << " " << setw(5) << p->getTerritoryName() << left << " connects to";
		for (auto q : p->getAdjTerritories()) {
			 cout << left << " [" << q->getTerritoryID() << " " << q->getTerritoryName() << setw(2) << "]" << left;
		}
		cout << endl;
	}
}




// Constructor for the Maploader class
MapLoader::MapLoader()
{
	cout << "MapLoader created" << endl;
}

MapLoader::MapLoader(string MapFile)
{
}

MapLoader::~MapLoader()
{
}

Map* MapLoader::getMap(void)
{
	return &loadedMap;
}

//Solution from: https://stackoverflow.com/questions/236129/how-do-i-iterate-over-the-words-of-a-string
template <typename Out>
void split(const std::string& s, char delim, Out result) {
	std::istringstream iss(s);
	std::string item;
	while (std::getline(iss, item, delim)) {
		*result++ = item;
	}
}


std::vector<std::string> split(const std::string& s, char delim) {
	std::vector<std::string> elems;
	split(s, delim, back_inserter(elems));
	return elems;
}

Map* MapLoader::loadMap(string MapFile)
{
	ifstream input;
	bool readingContinents = false;
	bool readingTerritories = false;
	bool readingBorders = false;
	Map* created = new Map();
	vector<string> contents;
	bool validFile1 = false, validFile2 = false, validFile3 = false;
	Continent* conti = new Continent();
	int contCreated = 0;
	int territoryCreated = 0;



	input.open(MapFile);
	if (input) {
		string current;
		cout << "----------------------------------------" << endl;
		//Check if file exists but is empty:
		if (input.peek() == std::ifstream::traits_type::eof()) {
			cout << "ERROR - File is empty!" << endl;
			throw invalid_argument("Received Empty File.");
			return created;
		}
		else {

			while (input.peek() != EOF && getline(input, current))
			{
				if (current == "[continents]") {
					cout << current << endl;
					getline(input, current);
					readingContinents = true;
					readingTerritories = false;
					readingBorders = false;
					validFile1 = true;
				}
				else if (current == "[countries]") {
					cout << current << endl;
					getline(input, current);
					readingContinents = false;
					readingTerritories = true;
					readingBorders = false;
					validFile2 = true;
				}
				else if (current == "[borders]") {
					cout << current << endl;
					getline(input, current);
					readingContinents = false;
					readingTerritories = false;
					readingBorders = true;
					validFile3 = true;
				}

				if (readingContinents) { //Reads and adds continent objects. 
				//	cout << "current " << current << endl;
					contCreated++;
					contents = split(current, ' ');
					if (contents.size() > 0) {
						conti->name = contents[0];
						conti->id = contCreated;
						conti->armyValue = stoi(contents[1]);
						Continent* ret = new Continent();
						ret->name = conti->name;
						ret->id = conti->id;
						ret->armyValue = conti->armyValue;
						created->addContinent(ret);
					}


				}
				else if (readingTerritories) {
					contents = split(current, ' ');
					territoryCreated++;
					if (contents.size() > 0) {
						conti->id = stoi(contents[0]);
						conti->name = contents[1];
						int contID = stoi(contents[2]);
						Territory* ret = new Territory(conti->id, contID, conti->name);
						created->territoryVector.push_back(ret);
						cout << *ret;



						for (Continent* cont : created->continentVector) {
							if (cont->id == contID) {
								cont->subGraphIndex.push_back(ret->getTerritoryID());
								cont->subGraph.push_back(ret);


							}
						}


					}

					created->wasVisited = new bool[territoryCreated - 1];
					created->numTerritories = territoryCreated - 1; // initialize numTerritories here
					created->neighbors = new vector<int>[territoryCreated - 1]; // initialize neighbors here
				}
				else if (readingBorders) {
					cout << current << endl;
					contents = split(current, ' ');
					if (contents.size() > 0) {
						vector<int> edges;

						for (string p : contents) {
							edges.push_back(stoi(p));   // 1 2 3

						}

						Territory* t = created->territoryVector[edges[0] - 1]; // 1
						int k = edges[0] - 1;

						for (int i = 1; i < edges.size(); i++) { // add 2 and 3 to 1's territories
							Territory* o = created->territoryVector[edges[i] - 1];
							t->addAdj(o);
							created->neighbors[(k)].push_back(edges[i] - 1);
						}


					}
				}
				else {
					cout << current << endl;
					readingContinents = false;
					readingTerritories = false;
					readingBorders = false;
				}


			}
			if (validFile1 && validFile2 && validFile3) {
				cout << "EOF" << endl;
				//Printing territories that belong to the first continent:
				cout << "here is" << endl;
				vector<Territory*> temp = created->continentVector[0]->subGraph;
				for (Territory* p : temp) {
					cout << *p;
				}

				// printing all the continents' names in the map 
				//for (Continent* con : created->continentVector) {
				//	cout << con->name << endl;
				//}



				// validate() method here
				cout << "check the connectivity" << endl;
				created->isConnected() ? cout << "Yes\n" : cout << "No\n";
				//created->continentSubgraphs(created)? cout << "Yes\n" : cout << "No\n";

				loadedMap = *created;
				return created;
			}
			else {
				cout << "ERROR - File is of incorrect format! Keywords were not found. Please check that the file meets the Map parameters." << endl;
				throw invalid_argument("ERROR - File is of incorrect format! Keywords were not found.");
				return nullptr;
			}

		}


	}
	else {
		cout << "ERROR - File could not be opened!" << endl;
		throw invalid_argument("ERROR - File could not be opened!");
		return nullptr;
	}


	//Map Creation:
	// ADD HERE
	loadedMap = *created;
	return created;

	return created;
}

ostream& operator<<(ostream& out, const Territory& p)
{
	out << p.name << " " << p.territoryID << " " << p.continentID << endl;
	return out;
}

ostream& operator<<(ostream& out, const Map& p)
{
	out << "Territories that belong to the Map: " << endl;
	for (Territory* a : p.territoryVector) {
		out << *a;
	}
	out << "Continents that belong to the Map: " << endl;
	for (Continent* a : p.continentVector) {
		out << a->name << " " << a->id << " " << a->armyValue << endl;
	}
	return out;
}




// Functions for Map Validation

// Checks that the given Map object is a connected graph
bool Map::isConnected() {

	for (int i = 0; i < numTerritories; i++) {
		DFS(i); // fill in the boolean values in wasVisited vector
		for (int j = 0; j < numTerritories; j++) {
			if (!wasVisited[j])    // check if there is any false value in the above array, which means the graph is not connected
			{
				int index = i;
				cout << "TerritoryId " << (index + 1) << " cannot reach to all the other territories: ";  // print which continentID is not inner connected
				cout << "The map is not connected" << endl;
				return false;
			}
		}
	}
	delete wasVisited;
	cout << "The map is a connected graph." << endl;
	return true;
}

void Map::DFS(int s) {

	//starting with all nodes as not visited
	for (int i = 0; i < numTerritories; i++) {
		wasVisited[i] = false;
	}
	// Let the helper do the DFS recursively
	DFS_helper(s, wasVisited);

}

void Map::DFS_helper(int s, bool* visitedOrNot) {
	// mark the current node as visited
	visitedOrNot[s] = true;

	// Go through the neighbors vector	

	for (int i : neighbors[s]) {
		// if the neighbor is not visited, go visit that neighbor; if visited, iterate to the next neighbor
		if (!visitedOrNot[i]) {
			int index = i;
			int index2 = s;
		//	cout << "Going to visit " << (index + 1) << " from " << (index2 + 1) << endl;
			DFS_helper(i, visitedOrNot);
		}
	}

}

bool Map::continentSubgraphs(Map* map) {

	cout << "-------- Checking Subgraph Connectivity -------- " << endl;

	vector<Territory*> trr = map->territoryVector;

	for (Continent* con : map->continentVector) {
		int bond = con->subGraph.size();
		wasVisited = new bool[bond];
		for (int i = 0; i < bond; i++) {

			DFS1(i, bond, trr); // fill in the boolean values in wasVisited vector
			for (int j = 0; j < bond; j++) {
				if (!wasVisited[j])    // check if there is any false value in the above array, which means the graph is not connected
				{
					cout << "The continent " << con->name << " is not a connected graph." << endl;  // print which continentID is not inner connected
					return false;

				}
			}
		}
	}

	delete wasVisited;
	cout << "All the continents are connected subgraphs" << endl;
	return true;



}

void Map::DFS1(int s, int bond, vector<Territory*> trr) {

	//starting with all nodes as not visited
	for (int i = 0; i < bond; i++) {
		wasVisited[i] = false;
	}
	// Let the helper do the DFS recursively
	DFS_helper1(s, wasVisited, trr);

}

void Map::DFS_helper1(int s, bool* visitedOrNot, vector<Territory*> trr) {

	int tID = trr[s]->getTerritoryID();
	int cID = trr[s]->getContinentID();
	vector<int> localNeighbors = neighbors[s]; // [1] connects to [21] [3] => localNeighbors[0] is (21-1) 

	// mark the current node as visited
	visitedOrNot[s] = true;

	// Go through the neighbors vector	
	for (int i = 0; i < neighbors[s].size(); i++)
	{
		int tID2 = localNeighbors[i];
		int cID2 = trr[tID2]->getContinentID();

		if ((cID2 == cID) && (!visitedOrNot[tID2]))
		{
			int index = s;
			//cout << "Going to visit " << tID2+1 << " from " << (index + 1) << endl;
			DFS_helper1(tID2, visitedOrNot, trr);

		}

	}

}


// process subGraphIndex
// 1 8 21 6 7 5 2 3 4 ==> 1 7 5 2 3 4 ==> in memory is 
// make a new vector with the value within 

/*
bool Map::continentSubgraphs(Map* map) {

	int numOfContinents = map->continentVector.size();
	Continent* con = map->continentVector[0];
	// 1 2 3 4 5 6 7
	int startID = con->subGraphIndex[0]; // 1  : will be line 0 in neighbors
	int endID = con->subGraphIndex[con->subGraphIndex.size() -1]; // 7  : will be line 6 in neighbors
	vector<vector <int> > processedNeighbors;
	for (int i = startID-1; i <= endID-1; i++) { // 0 , 6
		vector<int> temp;
		for (int j : neighbors[i]) {
			if (j >= startID-1 & j <= endID-1)
				temp.push_back(j);
		}
		processedNeighbors.push_back(temp);

	}
	cout << "hereeeee" << endl;
	for (vector<int> k : processedNeighbors) {
		for (int i : k)
			cout << i << " ";
		cout << " " << endl;
	}

	cout << "!!!!" << endl;

		for (int k : neighbors[0]) { // 0 7 20 5 6 4 1 2 3
			cout << k << " ";

		}
		cout << " " << endl;


	/*
	// process the subGraphIndex
	for (int i = 0; i < numOfContinents; i++) {
	}
	for (Continent* con : map->continentVector) {
		for (int i = 0; i < con->subGraphIndex.size(); i++) {
			DFS1(i); // fill in the boolean values in wasVisited vector
			for (int j = 0; j < con->subGraphIndex.size(); j++) {
				if (!wasVisited[j])    // check if there is any false value in the above array, which means the graph is not connected
				{
					int index = i;
					cout << "stops at Continent " << (index + 1);  // print which continentID is not inner connected
					return false;
				}
			}
		}
	}

	return true;

}
*/


// Will traverse through countryList, checking that each entry has a valid value for continentID
bool Map::countryToContinentRelation() {
	cout << "----- Checking Territory to Continent Relation --------" << endl;
	for (Territory* currentTerritory : territoryVector) {
		if (currentTerritory->getContinentID() == NULL) {
			cout << "Territory " << currentTerritory->getTerritoryName() << " does not have a valid continent." << endl;
			return false;	// Returns false after finding an invalid continentID
		}
	}
	cout << "Each Territory belongs to One Continent" << endl;
	return true;
}
// Checks isConnected, continentSubgraphs and countryToContinentRelation. Returns True when all are True.
bool Map::validate() {
	if (this->isConnected() == true && this->continentSubgraphs(this) == true && this->countryToContinentRelation() == true) {
		cout << "This is a valid map" << endl;
		return true;
	}
	cout << "This is not a valid map" << endl;
	return false;
}



//bool Map::continentSubgraphs(Map* map) {
//
//	vector<Continent*> continentsOfMap = map->continentVector;
//	for (Continent* a : continentsOfMap) {
//		vector<Territory*> territoriesOfContinent = a->subGraph;
//		vector<Territory> tocCopyAdj;
//		vector<vector<Territory>> vectorOfAdjs;
//
//
//		// Problem in copying vectors is likely here
//		// Must make the vectors carry the same values but be independent
//		for (Territory* p : territoriesOfContinent) {
//			vector<Territory*> adj = p->getAdjTerritories();
//			for (Territory* p : adj) {
//				Territory copiedTerritory = *p;
//				tocCopyAdj.push_back(copiedTerritory);
//			}
//			vectorOfAdjs.push_back(tocCopyAdj);
//			tocCopyAdj.clear();
//		}
//		
//		Continent currentCont = *a;
//		int currentContID = currentCont.id;
//		cout << "Current ContID: " << currentContID << endl;
//
//		// Removing from territory's adjlist the countries that dont belong to the current country
//		for (vector<Territory> p : vectorOfAdjs) {
//			for (Territory q : p) {
//				if (q.getContinentID() != currentContID) {
//					p.erase(remove(p.begin(), p.end(), q), p.end());
//				}
//			}
//		}
//
//		// Testing that copy is deep
//		cout << "--------------------" << endl;
//		cout << "original copy" << endl;
//		for (Territory* p : territoriesOfContinent) {
//			vector<Territory*> thisTAdj = p->getAdjTerritories();
//			for (Territory* q : thisTAdj) {
//				cout << p->getTerritoryID() << " adjacent to " << q->getTerritoryID() << " from continent " << q->getContinentID() << endl;
//			}
//		}
//		cout << "Copy" << endl;
//		for (auto p : vectorOfAdjs) {
//			cout << "new territory" << endl;
//			for (Territory q : p) {
//				cout << q.getTerritoryID() << endl;
//			}
//		}
//
//
//	}
//	return true;
//}
