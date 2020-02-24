
#include <iostream>
#include <vector>

// Use structure of Array to store Edge
struct Edge 
{
	std::vector<unsigned> src;
	std::vector<unsigned> dest;
};

// class to represent a graph object
class Graph
{
public:
	// construct a vector of vectors to represent each edge index and its outhoing edges
	std::vector<std::vector<int>> adjEdges;

	// Graph Constructor
	Graph(unsigned Num, Edge &input): vertex_num(Num), edges(input)
	{
		adjEdges.resize(Num);

		// Check if edge number is even 
		if (edges.src.size() != edges.dest.size()) 
		{
			std::cout << "Links are not in pair: losing one source/destination!" << std::endl;
		}
		// add edges to the directed graph
		for (auto i = 0; i < edges.src.size(); i++)
		{
			adjEdges[edges.src[i]].push_back(edges.dest[i]);
		}
	}

	unsigned OutgoingEdgeCount(unsigned i) { return adjEdges[i].size(); }
	unsigned VertexesNum() {return vertex_num;}

private:
	unsigned int vertex_num;	
	Edge const &edges;
};
