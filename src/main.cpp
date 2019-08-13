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
	Vertex* vertices;
	unsigned int size;
	Graph (unsigned int sizeArg)
	: size(sizeArg)
	{
		vertices = new Vertex[sizeArg];
	}
	~Graph()
	{
		delete[] vertices;
	}
	void TurnAllOff()
	{
		for(unsigned int i = 0; i < size; ++i) vertices[i].state = false;
	}
	void TurnOnRecursively(unsigned int current, unsigned int arg1, unsigned int arg2)
	{
		unsigned int temp = 0;
		if(vertices[current].state) return;
		vertices[current].state = true;
		for(unsigned int i = 0; i < vertices[current].edges.size(); ++i)
		{
			temp = vertices[current].edges[i];
			if(temp==arg1 || temp==arg2) continue;
			TurnOnRecursively(temp, arg1, arg2);
		}
	}
	bool AreAllOn(unsigned int arg1, unsigned int arg2)
	{
		for(unsigned int i = 0; i < size; ++i) 
		{
			if(!vertices[i].state) return false;
		}
		return true;
	}
	void AddEdge(unsigned int arg1, unsigned int arg2)
	{
		vertices[arg1].edges.push_back(arg2);			//if index1 is connected to index2:
		vertices[arg2].edges.push_back(arg1);			//pushback them to each others vector
	}
	bool IsBridge(unsigned int arg1, unsigned int arg2)
	{
		TurnAllOff();
		vertices[arg1].state = true;
		vertices[arg2].state = true;
		if(arg1!=0 && arg2!=0) TurnOnRecursively(0, arg1, arg2);//recursively turning neighbours on
		else if(arg1!=1 && arg2!=1) TurnOnRecursively(1, arg1, arg2);
		else TurnOnRecursively(2, arg1, arg2);
		if(AreAllOn(arg1, arg2)) return false;
		else return true;
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
		for(unsigned int j = 0; j < graph.vertices[ind].edges.size(); ++j)//for its every neighbour
		{	
			unsigned int nei = graph.vertices[ind].edges[j];	//ind-nei is checked for being a bridge
			if(ind >= nei) continue;
			if(!graph.IsBridge(ind, nei)) continue;		//if all are turned on the graph is connected
			std::cout << ind << " " << nei << std::endl;//if not, ind-nei is a bridge
		}
	return 0;	
}