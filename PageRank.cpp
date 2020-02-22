#include <iostream>
#include "Graph.hpp"

extern const double damping_factor = 0.85; // Adjusts the derived value downward.
extern const unsigned max_iterations = 10;

void PageRank(Graph *graph)
{
    unsigned num_v = graph->VertexesNum();

    double init_rank = 1.0 / num_v;
    double pr_random = (1.0 - damping_factor) / num_v;

    // Declare two vectors store current pr and previous pr perspectively.
    std::vector< double > pagerank;
    pagerank.reserve( num_v + 1u );
    std::vector< double > pre_pagerank;
    pre_pagerank.reserve( num_v + 1u );

    for (unsigned i = 0; i < num_v; i++)
    {
        pagerank[i] = init_rank;
        pre_pagerank[i] = 0.0;
    }

    unsigned iter = 0;
    while (iter++ < max_iterations)
    {
    	// Update the pagerank values in every iteration
        for (unsigned i = 0; i < num_v; i++)
        {
            pre_pagerank[i] = pagerank[i];
            pagerank[i] = 0.0;
            //TODO: temporary test, needs to be removed after testing
            std::cout << i  << " = "<< pre_pagerank[i] << std::endl;
        }

        // Distribute the sum of all dangling nodes(no outer edges) to all nodes.
        double dangling_sum = 0.0;
        for (unsigned i = 0; i < num_v; i++)
            if (graph->OutgoingEdgeCount(i) == 0){
                dangling_sum += pre_pagerank[i];
                std::cout << "dangling " << pre_pagerank[i];}
        double pr_dangling = damping_factor * dangling_sum / num_v;


        // Iterater all the vertexes and calculate its adjacency function l(pi,pj) of all inward links
        // Update its pagerank value by adding pr_eigenvector from its inward links separately
        for (unsigned i = 0; i < num_v; i++)
        {
         signed inward_edges_num = graph->InwardEdgeCount(i);
            // std::cout << inward_edges_num << std::endl;
            for (unsigned edge_num = 0; edge_num < inward_edges_num; edge_num++)
            {
             unsigned inward_edge_index = graph->adjEdges[i].at(edge_num);
                // std::cout << inward_edge_index << std::endl;
                double pr_eigenvector = damping_factor * pre_pagerank[inward_edge_index] / graph->OutgoingEdgeCount(inward_edge_index);
                pagerank[i] += pr_eigenvector;
            }
            pagerank[i] += pr_random + pr_dangling;
        }

        std::cout << "Iteration time: " << iter << std::endl;
    }
}

int main(int argc, char *argv[])
{
	// Make convenient labels for the vertices
	enum { A, B, C, D};
    const unsigned num_vertex = 4;
  
    // writing out the edges in the graph
    std::vector<Edge> input { Edge{A,B}, Edge{A,C}, Edge{B,D}, Edge{C,A}, Edge{C,B}, Edge{C,D}, Edge{D,C}};

	Graph graph(num_vertex, input);

	PageRank(&graph);

    return 0;
}
