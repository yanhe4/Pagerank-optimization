#include <iostream>
#include <fstream> // std::ifstream
#include <sstream> // std::stringstream
#include <string> // std::string
#include <cmath>
#include <vector>
#include <chrono> 
#include <ctime>
#include "Graph.hpp"

extern const double damping_factor = 0.85;
extern const unsigned max_iterations = 100;
extern const double tolerance = 1e-8;

// Read Input from file with format:
// N
// src_index dest_index ... src_index dest_index (pairs of source and destination links)
std::vector<Edge> ReadInputFromTextFile(const char* input_file, unsigned& num_vertices)
{
    std::vector<Edge> input;
    std::string input_line, str;
    std::ifstream myfile (input_file);
    if (myfile.is_open())
    {
        while (getline(myfile,input_line))
        {
           if (input_line.size() < std::to_string(UINT_MAX).size())
           {
                // Record the number of vertexes
               num_vertices = std::stoi(input_line);
               // std::cout << input_line << std::endl;
           } 
           else
           {
                std::stringstream temp_line(input_line);
                unsigned source = 0;
                unsigned destination = 0;
                unsigned count = 0;
                while (getline(temp_line, str, ' '))
                {
                    ++count;
                    unsigned temp_value = std::stoi(str);
                    if (count == 1)
                    {
                        source = temp_value;
                    }
                    else if (count == 2)
                    {
                        count = 0;
                        destination = temp_value;
                        // Writing out the edges into the graph
                        // Example: std::vector<Edge> input{ Edge{1,0}, Edge{4,2}, Edge{2,5}, Edge{1,3}};
                        if (source == destination) break; 
                        input.push_back(Edge{source, destination});  
                        // std::cout << source << std::endl;
                        // std::cout << destination << std::endl;
                    }
                }
           }
        }
        myfile.close();
    }
    return input;
}

bool ToleranceCheck(const unsigned& num_v, std::vector<double> pagerank, std::vector<double> pre_pagerank)
{
    // Sum up the pagerank
    double pr_sum = 0.0;
    for (unsigned i = 0; i < num_v; i++) 
    {
        pr_sum += pagerank[i];
    }
    // Calculate the cur_toleranceor
    pr_sum = 1.0 / pr_sum;
    double cur_tolerance = 0.0;
    for (unsigned i = 0; i < num_v; i++)
    {
        pagerank[i] *= pr_sum;
        // norm 1
        cur_tolerance += std::fabs(pagerank[i] - pre_pagerank[i]);
    }

    std::cout << "Current toleranceor: " << cur_tolerance << std::endl;
     std::cout << std::endl;
    if (cur_tolerance < tolerance)
    {
        return true;
    }
    return false;
}

void PageRank(Graph *graph)
{
    const unsigned num_v = graph->VertexesNum();
    double init_rank = double(1.0 / num_v);
    std::vector<double> pagerank(num_v);
    std::vector<double> pre_pagerank(num_v);
    double pr_random = (1.0 - damping_factor) / num_v;
    
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
            std::cout << i+1 << " = "<< pre_pagerank[i] << std::endl;
        }

        // Distribute the pr_sum of all dangling nodes(no outer edges) to all nodes.
        double dangling_pr_sum = 0.0;
        for (unsigned i = 0; i < num_v; i++)
        {
            if (graph->OutgoingEdgeCount(i) == 0)
            {
                dangling_pr_sum += pre_pagerank[i];
            }
        }
        double pr_dangling = damping_factor * dangling_pr_sum / num_v;

        // Iterater all the vertexes and calculate its adjacency function l(pi,pj) of all inward links
        // Update its pagerank value by adding pr_eigenvector from its inward links separately
        for (unsigned i = 0; i < num_v; i++)
        {
            unsigned inward_edges_num = graph->InwardEdgeCount(i);
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

        // finish when cur_toleranceor is smaller than tolerance we set
        if(ToleranceCheck(num_v,pagerank,pre_pagerank)) break;
    }
}

int main(int argc, char *argv[])
{
    if(argc == 2)
    {
        unsigned num_vertices = 0;

        std::vector<Edge> input = ReadInputFromTextFile(argv[1], num_vertices);
        
        auto start = std::chrono::system_clock::now();

        Graph graph(num_vertices, input);

        PageRank(&graph);

        auto end = std::chrono::system_clock::now();

        std::chrono::duration<double> elapsed_seconds = end - start;
        std::time_t end_time = std::chrono::system_clock::to_time_t(end);
        std::cout << "Finished computation at " << std::ctime(&end_time)
              << "Totle time used: " << elapsed_seconds.count() << "s\n";
    }
    else
    {
        std::cout << "Invalid Input: " << std::endl;
        std::cout << "Please input the input text file name wanted in argc[1]" << std::endl;
    }

    return 0;
}
