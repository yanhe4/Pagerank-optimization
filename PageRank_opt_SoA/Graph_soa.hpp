
#include <iostream>
#include <vector>

// // data structure to store graph edges (AoS)
// struct Edge 
// {
// 	unsigned src, dest;
// };

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
	// Structure of array for hot data
	// construct a vector of vectors to represent each edge index and its inward edges (SoA)
	std::vector<std::vector<int> > adjEdges;

	// Graph Constructor
	Graph(unsigned Num, Edge &input): vertex_num(Num), edges(input)
	{
		adjEdges.resize(Num);
		outgoing_edges_num.resize(Num);

		// add edges to the directed graph
		if (edges.src.size() != edges.dest.size()) 
		{
			std::cout << "Links are not in pair: losing one source/destination!" << std::endl;
		}
		for (auto i = 0; i < edges.src.size(); i++)
		{
			adjEdges[edges.dest[i]].push_back(edges.src[i]);
			outgoing_edges_num[edges.src[i]]++;
		}
	}

	unsigned InwardEdgeCount(unsigned i) { return adjEdges[i].size();}
	unsigned OutgoingEdgeCount(unsigned i) { return outgoing_edges_num[i]; }
	unsigned VertexesNum() {return vertex_num;}

private:
	unsigned int vertex_num;	

	// Structure of arrays for cold data (SoA)
	// construct a vector to store outgoing edges for each source index
	std::vector<int> outgoing_edges_num;  
	Edge edges;
	// std::vector<Edge> const &edges; // (AoS)
	
};
