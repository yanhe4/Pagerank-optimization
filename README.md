# Pagerank-optimization

# Generate Test Data
  - GenerateTestData.cpp is the file we used to generate test data. We could customize the number of nodes and links( pairs of source node index and destination node index) we want to generate. It will randomly generate the data for us. 
  - We are able to generate the data by inputting the number of vertexed wanted in argc[1], the size of graph links wanted in argc[2] and the output text file name wanted in argc[3].
    * eg: ./a.out 5 6 output.txt
  - The generated  data will be stored in the output.txt file.
	The output format is like:
	number of nodes (n)
	source_index dest_index source_index dest_index ...... source_index dest_index (0 <= index <= n-1)
	eg: 
	5
	3 1 2 4 0 1 2 1 2 3 0 2

# Single-Threaded PageRank Optimization
  - Data Structure: We used Graph.hpp, an indirected graph, to store our indexes and the relationships (links) among them.
  - Algorithm: The original implementation of actual algorithm is in PageRank.cpp, where we calculate the pagerank value of each node in three parts: pagerank[i] = pr_random[i] + pr_dangling[i] + pr_eigenvector[i] according to the basically algorithm from Wikipedia[ https://en.wikipedia.org/wiki/PageRank ] 
    After compiling PageRank.cpp, the algorithm could be run by inputting the input text file name wanted in argc[1] and the time mode(total/graph/pagerank) to be record in argc[2]. Each mode represents the benchmark mode to record the executable time for (total executable time for the whole program/the time to constrcut the graph/the time to run the pagerank algorithm).
    * eg: ./a.out input.txt total
  - Optimizatio: We used methods like SoA(Structure of Array), optimize algorithm, remove branch prediction and pre-sort in this part.
  	Each mainly method of our optimization is stored separately in directories, for example: PageRank_opt_SoA for re-constructing Edge in Graph.hpp from array of structure to structure of arrays, PageRank_opt_algorithm to optimize the pagerank algorithm in PageRank.cpp, Pagerank_opt_presort for presorting the data before instore it. 
  	The files that combined all our valid optimization methods are stored in directory "PageRank_opt_all". The way to compile and run is as same as we introduced before for PageRank.cpp.

  
