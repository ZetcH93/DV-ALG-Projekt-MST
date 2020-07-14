#include <fstream>
#include <vector>
#include <string>
#include <iostream>
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







void WriteValuesToFile(vector<rail>& mstRail, vector<stationNode>& stations)  //write the mst to "mstRail.txt"
{
	ofstream file("Awnser.txt");
	string tab = "	";

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
	priority_queue pq{ railroads };		//skapar en prioritets k� och matar in l�nkarna/edges
	vector<rail> mst;	// en tom mst som kommer fyllas med de mest optimala l�nkarna f�r givna stationer
	int stationAmount = (stations.size() - 1);



	while (mst.size() != stationAmount)	//k�r tills dess att mst tr�det har lika m�nga noder som antalet stationer
	{
		rail railBetweenStations = pq.pop(); //pops out the cheapest value from the minHeap priority queue


		for (unsigned int i = 0; i < stations.size(); i++)		// f�r varje station...
		{
			if (stations.at(i).find(railBetweenStations.getNode1()) == railBetweenStations.getNode1())	// om stationens vektor inneh�ller f�rsta noden i den ena l�nken
				if (stations.at(i).find(railBetweenStations.getNode2()) == railBetweenStations.getNode2())	//checks for cycles, genom att kolla om f�rsta stationen inneh�ller b�da noderna redan
				{
					break;
				}
				else
				{
					mst.push_back(railBetweenStations);	// l�gger till l�nken i mst tr�det

					for (unsigned int x = 0; x < stations.size(); x++)		
					{
						if (stations.at(x).find(railBetweenStations.getNode2()) == railBetweenStations.getNode2()) //looks for the station containing the node2 in the edge/l�nken
							if (stations.at(i).stationTreeSize() >= stations.at(x).stationTreeSize())	// l�gger till den mindre stationsvektorn i den st�rre
							{
								stations.at(i).unionStations(stations.at(x).getStationArray());	// adds together the two station amounts into one
								stations.at(x).delStation();	// s�tter den gamla vektorn till 0 (d� v�rdet av dess element nu tillh�r den andra stations m�ngden)

								break;

							}
							else
							{
								stations.at(x).unionStations(stations.at(i).getStationArray()); // adds together the two station amounts into one
								stations.at(i).delStation();	// s�tter den gamla vektorn till 0 (d� v�rdet av dess element nu tillh�r den andra stations m�ngden)

								break;

							}
					}

					break;
				}
		}

	}
	return mst;
}


int main(long int argc, char** argv)
{
	vector<rail> rails;		// vektorarray som inneh�ller "edges/l�nkar"
	vector<stationNode> stations;	// en vektor som inneh�ller stationsNoder som fungerar som disjunta m�ngder
	vector<rail> mstRail;	// en vektor som inneh�ller de l�nkar som finns i minimal spanning tree (ett cykliskt viktat tr�d utan riktning)

	ReadValuesFromFile(argv[1], rails, stations); //l�ser in vertices och l�nkarna fr�n en textfil

	mstRail = kruskal(rails, stations);	// bygger en mst baserat p� de l�nkar och vertices fr�n textfil

	WriteValuesToFile(mstRail, stations);	// l�ser ut datan fr�n mst samt de aktuella stationer som �r kvar till en textfil.


}

