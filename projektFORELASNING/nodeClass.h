#pragma once
#include <fstream>
#include <vector>
#include <string>
#include <iostream>


using namespace std;



class stationNode		// en disjointed m�ngd (tr�d nod(station))
{

private:
	vector<string> stationTree; // vector which may contain an amount of other stations
	int root;

public:
	stationNode(string stationName);
	

	bool find(string x);		// letar upp om stationens m�ngd inneh�ller en vis station av v�rde x
	void unionStations(int station1Root, int station2Root, vector<stationNode>& stations); //l�gger ihop en annan stationsm�ngd med denna

	int stationTreeSize();	//skriver ut storleken av tr�det
	vector<string> getStationArray(); // returnar arrayen
	int getRoot();
	void setRoot(int root);
	void addtoTree(vector<string> station2Tree);

	void getStationArrayFile(ofstream& file); //skriver ut stationsarrayen till en fil


};



class rail	//en l�nk/railroad mellan tv� stationer med en kostnad
{
private:
	int cost;
	string node1;
	string node2;
public:

	rail(string node1, string node2, int cost);
	rail(int cost);
	rail();
	void setCost(int c);
	void setNodes(string node1, string node2);
	int getCost();

	string getNode1();
	string getNode2();


};


//priotity queue following a minHeap model
class priority_queue
{
private:
	int totalRails;
	vector<rail> pqArray;

public:
	priority_queue(vector<rail>& rails); //konstrukt�r som tar emot en array av l�nkar

	//balance the heap
	void percolateUp(int percolateFrom); //fr�n �versta v�rdet o ner.
	void percolateDown(int percolateFrom); // fr�n senaste tillaggda v�rdet och upp till roten.

	rail pop();							//skriver ut �versta v�rdet i k�n
	void insert(rail& rails, int i);	// l�gger in v�rdena i k�n



};