
#include <iostream>
#include <vector>

// data structure to store graph edges
struct Edge 
{
	unsigned src, dest;
};

// class to represent a graph object
class Graph
{
public:
	// construct a vector of vectors to represent each edge index and its outhoing edges
	std::vector<std::vector<int>> adjEdges;

	// Graph Constructor
	Graph(unsigned Num, std::vector<Edge> &input): vertex_num(Num), edges(input)
	{
		adjEdges.resize(Num);
		// add edges to the directed graph
		for (auto &edge: edges)
		{
			adjEdges[edge.src].push_back(edge.dest);
		}
	}

	unsigned OutgoingEdgeCount(unsigned i) { return adjEdges[i].size(); }
	unsigned VertexesNum() {return vertex_num;}

private:
	unsigned int vertex_num;	
	std::vector<Edge> const &edges;
};
