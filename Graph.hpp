
#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <array>
#include <algorithm>
#include <iomanip>
#include <cmath>
#include <vector>
#include <functional>
#include <cstdlib>
#include <string>

// data structure to store graph edges
struct Edge 
{
	unsigned int src, dest;
}

// data structure to store pagerank values
std::vector<float> pr_value;

// class to represent a graph object
class Graph
{
public:
	// construct a vector of vectors to represent an adjacency list
	std::vector<std::vector<int>> adjList;

	// Graph Constructor
	Graph(std::vector<Edge> const &edges, int Num)
	{
		adjList.resize(Num);
		// add edges to the directed graph
		for (auto &edge: edges)
		{
			adjList[edge.src].push_back(edge.dest);
		}
	}
	unsigned count_edges(unsigned i) { return adjList[i].size(); }
	unsigned vertex_count() {return vertex_num;}
private:
	
	unsigned int vertex_num;	
}
