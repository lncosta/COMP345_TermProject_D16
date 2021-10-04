#include "Map.h"
#include <iostream>
using namespace std;


// Must be changed to fit new methods
int main() {
	Map g1(5);
	g1.addEdge(0, 1);
	g1.addEdge(1, 2);
	g1.addEdge(2, 3);
	g1.addEdge(3, 0);
	g1.addEdge(2, 4);
	g1.addEdge(4, 2);
	g1.DFS(4);
	g1.isConnected() ? cout << "Yes\n" : cout << "No\n";

	cout << "-------------------" << endl;

	Map g2(4);
	g2.addEdge(0, 1);
	g2.addEdge(1, 2);
	g2.addEdge(2, 3);
	g2.DFS(0); // false 
	g2.isConnected() ? cout << "Yes\n" : cout << "No\n";


	MapLoader loader("C:\\Users\\tomas\\Downloads\\solar.map");
	loader.loadMap();



	return 0;
}