
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
	// construct a vector of vectors to represent each edge index and its inward edges
	std::vector<std::vector<int>> adjEdges;

	// Graph Constructor
	Graph(unsigned Num, std::vector<Edge> &input): vertex_num(Num), edges(input)
	{
		adjEdges.resize(Num);
		outgoing_edges_num.resize(Num);
		// add edges to the directed graph
		for (auto &edge: edges)
		{
			adjEdges[edge.dest].push_back(edge.src);
			outgoing_edges_num[edge.src]++;
		}
	}

	unsigned InwardEdgeCount(unsigned i) { return adjEdges[i].size();}
	unsigned OutgoingEdgeCount(unsigned i) { return outgoing_edges_num[i]; }
	unsigned VertexesNum() {return vertex_num;}

private:
	unsigned int vertex_num;	
	std::vector<Edge> const &edges;
	// construct a vector to store outgoing edges for each source index
	std::vector<int> outgoing_edges_num;
};
