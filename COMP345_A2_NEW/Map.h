#ifndef _MAP_H_
#define _MAP_H_
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

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

class Player;
class Territory; // Declaring these 2 classes so that the later classes can access them

struct Continent {
	int id;
	string name;
	int armyValue;
	vector<Territory*> subGraph;
	vector<int> subGraphIndex;
	// friend class
	friend class MapLoader; // so MapLoader can store data in subGraph's vectors
	friend class Map;

	vector<Territory*> getSubGraph(void);
	~Continent(void);

};

// Territory Class, acts as the nodes for the Map class
class Territory {
private:
	//Data members:
	int territoryID;
	string name;
	Player* owner;
	vector<Territory*> adjTerritories; // works as edges
	int armiesPlaced;

	int continentID; // should be changed to Continent object
	Continent* cont; //Must keep track of Continent it belongs to. 

public:
	//Constructors:
	Territory(int tID, int cID);
	Territory(int tID, int cID, string name);
	Territory(const Territory& other);

	//Destructors:
	~Territory(void);
	string getTerritoryName(void);
	int getContinentID(void);
	int getTerritoryID(void);
	int getArmiesPlaced(void);
	void setArmiesPlaced(int newNum);
	vector<Territory*> getAdjTerritories(void);
	void addAdj(Territory* o);
	void setOwner(Player* o);
	Player* getOwner(void); 

	//Stream Insertions:
	friend ostream& operator << (ostream& out, const Territory& p);
	friend istream& operator >> (istream& in, Territory& p);
};

// Map Class, represents the actual game map being played
class Map {
private:
	// Data members
	vector<Continent*> continentVector;
	vector<Territory*> territoryVector;
	bool valid = true;

public:
	bool* wasVisited; // a boolean vector keeps track if a node/territory was visited
	int numTerritories;
	vector<int>* neighbors; // a vector points to border index collected when loading the map

	// friend class
	friend class MapLoader; // so MapLoader can store data in Map's vectors
	// constructors 
	Map(void);
	~Map(void);

	//Destructors:
	Map(const Map& toCopy);

	//Stream insertion:
	friend ostream& operator << (ostream& out, const Map& p);

	void addContinent(Continent* theContinent);
	Territory* getTerritory(int territoryID);
	vector<Territory*> getTerritoyVector(void);

	vector<Continent*> getContinentVector(void);

	//methods related to validate()
	void DFS(int s);
	void DFS_helper(int s, bool* wasVisited);
	void DFS1(int s, int bond, vector<Territory*> trr);
	void DFS_helper1(int s, bool* wasVisited, vector<Territory*> trr);
	bool validate(bool a, bool b, bool c);
	bool validateWrapper(void);
	// Must check the following 3 functions	
	bool validate(void);
	bool isConnected(void);// Test to the see if the map is a connected graph	
	bool continentSubgraphs(Map* map); // Test to see that continents are connected subgraphs	
	bool countryToContinentRelation(void); // Test to see that each country belongs to only one continent

	bool getValidity();
};

// Map Loader Class, used to create a map object from a given file
class MapLoader {
private:
	string fileName;
	Map loadedMap;
public:
	MapLoader();
	~MapLoader();
	Map* getMap(void);

	Map* loadMap(string MapFile);

	//Stream insertion:
	friend ostream& operator << (ostream& out, const MapLoader& p);

};
#endif // !_MAP_H_


