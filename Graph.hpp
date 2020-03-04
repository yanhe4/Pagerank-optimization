
#include <iostream>
#include <vector>

namespace CSC586C {

namespace original_graph {
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
	std::vector<std::vector<int> > adjEdges;

	// Graph Constructor
	Graph(unsigned Num, std::vector<original_graph::Edge> &input): vertex_num(Num), edges(input)
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
	std::vector<original_graph::Edge> const &edges;
	// construct a vector to store outgoing edges for each source index
	std::vector<int> outgoing_edges_num;
};
}



namespace optimize_graph {
// data structure to store cold data: edges (pairs of src and dest)
struct ColdEdge 
{
	unsigned int src;
	unsigned int dest;
};

// data structure to store hot data: number of outgoing links each node and its pagerank values 
struct HotData
{
	double pagerank;
	double pre_pagerank;
	int outgoing_edges_num;
};

// class to represent a graph object
class SoA_Graph
{
public:
	// construct a vector of vectors to represent each edge index and its inward edges (hot data)
	std::vector<std::vector<int> > adjEdges;
	// construct a vector to store hot data structure
	std::vector<HotData> nodes;

	// Graph Constructor
	SoA_Graph(unsigned Num, std::vector<optimize_graph::ColdEdge> &input): vertex_num(Num), edges(input)
	{
		adjEdges.resize(Num);
		nodes.resize(Num);
		// add edges to the directed graph
		for (auto &edge: edges)
		{
			adjEdges[edge.dest].push_back(edge.src);
			nodes[edge.src].outgoing_edges_num++;
		}
	}
	unsigned VertexesNum() {return vertex_num;}

private:
	unsigned int vertex_num;	
	// construct a vector to store cold data structure
	std::vector<optimize_graph::ColdEdge> const &edges;
};
}

namespace optimize_algorithm {
// data structure to store cold data: edges (pairs of src and dest)
struct ColdEdge 
{
	unsigned int src;
	unsigned int dest;
};

// data structure to store hot data: number of outgoing links each node and its pagerank values 
struct HotData
{
	double pagerank;
	double pre_pagerank;
};

// class to represent a graph object
class Algorithm_Graph
{
public:
	// construct a vector of vectors to represent each edge index and its inward edges (hot data)
	std::vector<std::vector<int> > adjEdges;
	// construct a vector to store hot data structure
	std::vector<HotData> nodes;

	// Graph Constructor
	Algorithm_Graph(unsigned Num, std::vector<optimize_algorithm::ColdEdge> &input): vertex_num(Num), edges(input)
	{
		adjEdges.resize(Num);
		nodes.resize(Num);
		// add edges to the directed graph
		for (auto &edge: edges)
		{
			adjEdges[edge.src].push_back(edge.dest);
		}
	}
	unsigned VertexesNum() {return vertex_num;}

private:
	unsigned int vertex_num;	
	// construct a vector to store cold data structure
	std::vector<optimize_algorithm::ColdEdge> const &edges;
};
}

}
