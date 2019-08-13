#include <iostream>
#include <vector>
#include <string>
#include <sstream>

struct Vertex
{
	bool state;
	std::vector<unsigned int> edges;
	Vertex(): state(false) {}
};
struct Graph
{
	Vertex* tab;
	unsigned int size;
	Graph (unsigned int sizeArg)
	: size(sizeArg)
	{
		tab = new Vertex[sizeArg];
	}
	~Graph()
	{
		delete[] tab;
	}
	void TurnAllOff()
	{
		for(unsigned int i = 0; i < size; ++i) tab[i].state = false;
	}
	void TurnOnRecursively(unsigned int current, unsigned int arg1, unsigned int arg2)
	{
		unsigned int temp = 0;
		if(tab[current].state) return;
		tab[current].state = true;
		for(unsigned int i = 0; i < tab[current].edges.size(); ++i)
		{
			temp = tab[current].edges[i];
			if(temp==arg1 || temp==arg2) continue;
			TurnOnRecursively(temp, arg1, arg2);
		}
	}
	bool AreAllOn(unsigned int arg1, unsigned int arg2)
	{
		for(unsigned int i = 0; i < size; ++i) 
		{
			if(i==arg1 || i==arg2) continue;
			if(!tab[i].state) return false;
		}
		return true;
	}
	void AddEdge(unsigned int arg1, unsigned int arg2)
	{
		tab[arg1].edges.push_back(arg2);			//if index1 is connected to index2:
		tab[arg2].edges.push_back(arg1);			//pushback them to each others vector
	}
};

int main() 
{
	unsigned int graphSize, index1, index2;
	std::string input;
	std::getline(std::cin, input);
	graphSize = atoi(input.c_str());
	if(graphSize < 4) return 0;							//No bridges if there are less than 4 vertices 
	Graph graph(graphSize);
	while(std::getline(std::cin, input))
	{
		std::stringstream ss(input);
		ss >> index1 >> index2;
		graph.AddEdge(index1, index2);
	}
	for(unsigned int ind = 0; ind < graphSize; ++ind)	//for each vertex
		for(unsigned int j = 0; j < graph.tab[ind].edges.size(); ++j)//for its every neighbour
		{	
			unsigned int nei = graph.tab[ind].edges[j];	//ind-nei is checked for being a bridge
			if(nei <= ind) continue;
			graph.TurnAllOff();							//turning all vertices off
			if(ind!=0 && nei!=0) graph.TurnOnRecursively(0, ind, nei);//recursively turning neighbours on
			else if(ind!=1 && nei!=1) graph.TurnOnRecursively(1, ind, nei);
			else graph.TurnOnRecursively(2, ind, nei);
			if(graph.AreAllOn(ind, nei)) continue;		//if all are turned on the graph is connected
			std::cout << ind << " " << nei << std::endl;//if not, ind-nei is a bridge
		}
	return 0;	
}