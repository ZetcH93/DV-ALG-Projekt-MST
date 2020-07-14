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
	int railCounter = 0;	// fungerar som index, behövs för att ge de olika värderna från textfil till samma länk


	while (getline(file, input, '\n'))
	{
		if (input.size() == 0)	// när det blir ett /n så går input över till länkarna från stationerna
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
				counter++;			// om input är en "tab" så hoppa till nästa data i länken
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

		if (counter > 0 && input.size() > 0)	// matar inindatan in i länk vektorn
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

	for (unsigned int i = 0; i < (stations.size()); i++)	// skriver ut stationerna som användes i MST
		if (stations.at(i).stationTreeSize() > 1)
			stations[i].getStationArrayFile(file);


	for (unsigned int i = 0; i < (mstRail.size()); i++) // skriver ut mst länkarna
	{
		file << (mstRail[i].getNode1() + tab + mstRail[i].getNode2() + tab + to_string(mstRail[i].getCost()) + "\n");
	}
}


//kruskal algorithm
vector<rail> kruskal(vector<rail>& railroads, vector<stationNode>& stations)
{
	priority_queue pq{ railroads };		//skapar en prioritets kö och matar in länkarna/edges
	vector<rail> mst;	// en tom mst som kommer fyllas med de mest optimala länkarna för givna stationer
	int stationAmount = (stations.size() - 1);



	while (mst.size() != stationAmount)	//kör tills dess att mst trädet har lika många noder som antalet stationer
	{
		rail railBetweenStations = pq.pop(); //pops out the cheapest value from the minHeap priority queue


		for (unsigned int i = 0; i < stations.size(); i++)		// för varje station...
		{
			if (stations.at(i).find(railBetweenStations.getNode1()) == railBetweenStations.getNode1())	// om stationens vektor innehåller första noden i den ena länken
				if (stations.at(i).find(railBetweenStations.getNode2()) == railBetweenStations.getNode2())	//checks for cycles, genom att kolla om första stationen innehåller båda noderna redan
				{
					break;
				}
				else
				{
					mst.push_back(railBetweenStations);	// lägger till länken i mst trädet

					for (unsigned int x = 0; x < stations.size(); x++)		
					{
						if (stations.at(x).find(railBetweenStations.getNode2()) == railBetweenStations.getNode2()) //looks for the station containing the node2 in the edge/länken
							if (stations.at(i).stationTreeSize() >= stations.at(x).stationTreeSize())	// lägger till den mindre stationsvektorn i den större
							{
								stations.at(i).unionStations(stations.at(x).getStationArray());	// adds together the two station amounts into one
								stations.at(x).delStation();	// sätter den gamla vektorn till 0 (då värdet av dess element nu tillhör den andra stations mängden)

								break;

							}
							else
							{
								stations.at(x).unionStations(stations.at(i).getStationArray()); // adds together the two station amounts into one
								stations.at(i).delStation();	// sätter den gamla vektorn till 0 (då värdet av dess element nu tillhör den andra stations mängden)

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
	vector<rail> rails;		// vektorarray som innehåller "edges/länkar"
	vector<stationNode> stations;	// en vektor som innehåller stationsNoder som fungerar som disjunta mängder
	vector<rail> mstRail;	// en vektor som innehåller de länkar som finns i minimal spanning tree (ett cykliskt viktat träd utan riktning)

	ReadValuesFromFile(argv[1], rails, stations); //läser in vertices och länkarna från en textfil

	mstRail = kruskal(rails, stations);	// bygger en mst baserat på de länkar och vertices från textfil

	WriteValuesToFile(mstRail, stations);	// läser ut datan från mst samt de aktuella stationer som är kvar till en textfil.


}

