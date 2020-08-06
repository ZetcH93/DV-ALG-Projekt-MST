#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <chrono>
#include "nodeClass.h"

using namespace std;

void ReadValuesFromFile(const string& filepath, vector<rail>& rails, vector<stationNode>& stations)	 //read in values from filepath
{
	ifstream file(filepath);

	string node1;
	string node2;
	string cost;
	string input;



	int counter = 0; //reglererar hur indatan skickas ut till variablerna.
	int railCounter = 0;	// fungerar som index, beh�vs f�r att ge de olika v�rderna fr�n textfil till samma l�nk


	while (getline(file, input, '\n'))
	{
		if (input.size() == 0)	// n�r det blir ett /n s� g�r input �ver till l�nkarna fr�n stationerna
		{
			counter++;
		}
		if (counter == 0)		// assign the stations, prior to \n has been found.
		{
			stations.push_back(input);
		}

		for (int i = 0; i < input.size(); i++)	// assigns the railroad links after the \n in the txtfile has been found
		{

			if (input[i] == '\t')
			{
				counter++;			// om input �r en "tab" s� hoppa till n�sta data i l�nken
			}

			else if (input[i] != '\t' && counter == 1)
			{
				node1 += input[i];		// node1 i getlinen

			}

			else if (input[i] != '\t' && counter == 2)
			{
				node2 += input[i];		// node2 i getlinen

			}

			else if (input[i] != '\t' && counter == 3)
			{
				while (i < input.size())
				{
					cost += input[i];		// cost i getlinen
					i++;
				}


			}
			else
				break;
		}

		if (counter > 0 && input.size() > 0)	// matar inindatan in i l�nk vektorn
		{
			rails.push_back(stoi(cost));
			rails[railCounter].setNodes(node1, node2);
			railCounter++;

			node1 = "";
			node2 = "";
			cost = "";
			counter = 1;
		}

	}
}







void WriteValuesToFile(vector<rail>& mstRail, vector<stationNode>& stations)
{
	ofstream file("Awnser.txt");
	char tab = '\t';

	for (unsigned int i = 0; i < (stations.size()); i++)	// skriver ut stationerna som anv�ndes i MST
		if (stations.at(i).stationTreeSize() > 1)
			stations[i].getStationArrayFile(file);


	for (unsigned int i = 0; i < (mstRail.size()); i++) // skriver ut mst l�nkarna
	{
		file << (mstRail[i].getNode1() + tab + mstRail[i].getNode2() + tab + to_string(mstRail[i].getCost()) + "\n");
	}
}


//kruskal algorithm
vector<rail> kruskal(vector<rail>& railroads, vector<stationNode>& stations)
{
	int stationSize = stations.size();
	priority_queue pq{ railroads };
	vector<rail> mst;

	while (mst.size() != stationSize - 1)
	{	
		int station1 = NULL;
		int station2 = NULL;
		rail rail = pq.pop(); 

		for (int i = 0; i < stations.size(); i++)
		{
			if (stations[i].find(rail.getNode1()))
				station1 = i;
			if (stations[i].find(rail.getNode2()))
				station2 = i;
			if ((station1 != NULL) && (station2 != NULL))
				break;
		}
		if (station1 != station2)
		{
			mst.push_back(rail);
			stations[station1].unionStations(station1, station2, stations);
		}
	}
	return mst;
}


int main(long int argc, char** argv)
{
	auto start = std::chrono::steady_clock::now();
	vector<rail> rails;		// vektorarray som inneh�ller "edges/l�nkar"
	vector<stationNode> stations;	// en vektor som inneh�ller stationsNoder som fungerar som disjunta m�ngder
	vector<rail> mstRail;	// en vektor som inneh�ller de l�nkar som finns i minimal spanning tree (ett cykliskt viktat tr�d utan riktning)

	ReadValuesFromFile(argv[1], rails, stations); //l�ser in vertices och l�nkarna fr�n en textfil

	mstRail = kruskal(rails, stations);	// bygger en mst baserat p� de l�nkar och vertices fr�n textfil

	WriteValuesToFile(mstRail, stations);	// l�ser ut datan fr�n mst samt de aktuella stationer som �r kvar till en textfil.

	auto end = chrono::steady_clock::now();
	chrono::duration<double> elapsed_seconds = end - start;
	cout << "Sorting took: " << elapsed_seconds.count() << " seconds" << std::endl;

}

