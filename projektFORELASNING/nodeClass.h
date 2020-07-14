#pragma once
#include <fstream>
#include <vector>
#include <string>
#include <iostream>


using namespace std;




class stationNode		// en disjointed mängd (träd nod(station))
{

private:
	vector<string> stationTree; // vector which may contain an amount of other stations

public:
	stationNode(string stationName);

	string find(string x);		// letar upp om stationens mängd innehåller en vis station av värde x
	void unionStations(vector<string> stationArray); //lägger ihop en annan stationsmängd med denna

	int stationTreeSize();	//skriver ut storleken av trädet
	void delStation();  //sätter storleken av trädet till 0
	vector<string> getStationArray(); // returnar arrayen

	void getStationArrayFile(ofstream& file); //skriver ut stationsarrayen till en fil




};

class rail	//en länk/railroad mellan två stationer med en kostnad
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
	priority_queue(vector<rail>& rails); //konstruktör som tar emot en array av länkar

	//balance the heap
	void percolateUp(int percolateFrom); //från översta värdet o ner.
	void percolateDown(int percolateFrom); // från senaste tillaggda värdet och upp till roten.

	rail pop();							//skriver ut översta värdet i kön
	void insert(rail& rails, int i);	// lägger in värdena i kön



};