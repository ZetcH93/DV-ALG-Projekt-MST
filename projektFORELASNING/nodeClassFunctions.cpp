#include "nodeClass.h"


stationNode::stationNode(string stationName)
{
	this->stationTree.push_back(stationName);		//lägger till värde i vektorn när stationen skapas

}



string stationNode::find(string x)	// letar i vektorns array(mängd) om den innehåller station x
{
	string value = "";

	for (unsigned int i = 0; i < stationTree.size(); i++)
	{
		if (stationTree[i] == x)
			value = x;
	}

	return value;
}

void stationNode::unionStations(vector<string> stationpqArray)	//lägger till alla värden från den mindre vektorn till den nya vektorn(mängd)
{
	for (unsigned int i = 0; i < stationpqArray.size(); i++)
	{
		this->stationTree.push_back(stationpqArray.at(i));
	}
}



int stationNode::stationTreeSize() //skriver ut vektorns storlek
{
	return this->stationTree.size();
}

void stationNode::delStation()	// "tar bort" vektorn genom att sätta den till 0
{
	stationTree.resize(0);
}

void stationNode::getStationArrayFile(ofstream& file)	//skriver ut hela mängden för de aktuella stationer i mst
{
	for (unsigned int i = 0; i < stationTree.size(); i++)
	{
		file << stationTree.at(i) << endl;
	}
	file << endl;
}

vector<string> stationNode::getStationArray()	// returnar hela vektorn som finns i detta objektet
{
	return this->stationTree;
}






void rail::setCost(int c)
{
	this->cost = c;
}
void rail::setNodes(string node1, string node2)
{
	this->node1 = node1;
	this->node2 = node2;
}
int rail::getCost()
{
	return this->cost;
}

string rail::getNode1()
{
	return this->node1;
}

string rail::getNode2()
{
	return this->node2;
}

rail::rail(string node1, string node2, int cost)
{
	this->node1 = node1;
	this->node2 = node2;
	this->cost = cost;
}

rail::rail(int x)
{
	this->cost = x;
	this->node1 = "";
	this->node2 = "";
}

rail::rail()
{
	this->node1 = "";
	this->node2 = "";
	this->cost = NULL;
}




priority_queue::priority_queue(vector<rail>& rails)	// pq konstruktor som tar emot en array av edges/länkar
{
	this->totalRails = rails.size();

	for (int i = 0; i < totalRails; i++)
	{
		insert(rails.at(i), i);	// matar in länkarna/rails i en minHeap.
	}

}

rail priority_queue::pop()	
{
	rail returnValue = pqArray[0];	//plockar ut det översta värdet i pqarrayen och lägger denna i returnvalue

	int lastIndex = (pqArray.size()) - 1;

	pqArray[0] = move(pqArray[lastIndex]);	// flyttar värdet som är längst ner i arrayen överst i kön
	pqArray.resize(lastIndex);	// gör kön 1 steg mindre(då ett värde har tagits ut)
	
	if(lastIndex != 0) //om det är fler än ett värde i kön:
		percolateDown(0); //balansera kön (heapen) i storleksordning efter pop

	return returnValue;
}



void priority_queue::insert(rail& rails, int i)
{

	pqArray.push_back(rails); //lägger elementet längst ner i heapen
	percolateUp(i);	// perkulerar upp till värdet 0 dvs, om det nya elementet är mindre än dess parent så byter de plats
}




void priority_queue::percolateDown(int percolateFrom)	//perkulerar neråt, görs efter det att det översta värdet har tagits bort från priority kön, detta då man popar så flyttas det värdet 
{											//som är längst ner i heapen upp till roten(och detta kan vara stort vilket då gör att man dubbelkollar så att de är mindre än dess barn osv osv)
	int min = percolateFrom;
	unsigned int l = 2 * percolateFrom + 1; // left child
	unsigned int r = 2 * percolateFrom + 2; // right child


	if (l < pqArray.size() && pqArray[l].getCost() < pqArray[min].getCost())		// If left child is smaller than root 
		min = l;


	if (r < pqArray.size() && pqArray[r].getCost() < pqArray[min].getCost())		// If right child is smaller than root/left child
		min = r;


	if (pqArray[min].getCost() != pqArray[percolateFrom].getCost()) {		// If min is not root 
		swap(pqArray[percolateFrom], pqArray[min]);

		// balance the rest of the tree through recursion:
		percolateDown(min);
	}
}


void priority_queue::percolateUp(int percolateFrom)
{

	int i = percolateFrom;
	int parent = (i - 1) / 2;

	if (pqArray[parent].getCost() > 0) {
		// if parent is smaller then the percolateFrom child then swap:

		if (pqArray[i].getCost() < pqArray[parent].getCost()) {
			swap(pqArray[i], pqArray[parent]);

			// balance the rest of the tree through recursion:
			percolateUp(parent);
		}
	}
}









