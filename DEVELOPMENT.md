
# 12-1-2020
## Elia
* Wrote Edge class, implementing unit tests for equality and comparison
* Added Graph class with functions implemented in cpp file
	* Modified class to work with any templated object, with hashmaps rather than vectors for the adjacency list
	* This sacrifices a bit of performance when it comes to accessing, but when it comes to any kind of actual traversal, we do not change the asymptotic runtime.
	* Templating will help if we want to index airports by both their id's and their string names.
	* Fixed issues with templating through cpp files and converted Graph.cpp to Graph.hpp
* Made makefile to compile tests

# 12-2-2020
## Matt
* Re-write tests written for Graph to use catch instead of print statements
* Add GraphTraversal class
	* Abstract class with pure virtual functions to model BFS and DFS traversals
	* Conforms to iterator
* Add BFS
	* Breadth-first-search conforming to GraphTraversal
	* Copy one unit test from Graph tests and re-write to test BFS
* Add DFS
	* Depth-first-search conforming to GraphTraversal
	* Copy BFS unit test and switch to use BFS (will add more tests for both later)

# 12-5-2020
## Matt
* Add new tests for simple tree graph and cyclic graph for BFS & DFS
* Fix BFS
	* Now returns correct first value
	* Also does not repeat values
* Fix DFS
	* Now returns correct first value
	* Also does not repeat values
* Fix DFS Basic Test
	* Realized initial DFS test was using BFS, so replaced to use DFS

# 12-6-2020
## Madhav
* Restructured Makefile substantially
	* Add warnings
	* Improve modularity
	* Add dependencies
* Fixed .gitignore issues
* Set up algorithms file structure
* Created Floyd Warshall functions
	* Shortest distance from each vertex to every vertex
	* Shortest path from each vertex to every vertex
	* Shortest path from any 1 vertex to any other vertex given output from above function
	
# 12-7-2020
## Charles
* Updated Makefile to compile Dijkstra files
* Created Dijkstra test file
* Added and filled out functions for Dijkstra algorithm
	* Shortest distance between two points
	* Shortest path between two points
	* Shortest distance to every other point in the graph from a given point
* Made various bug fixes to Graph.hpp
	* Fixed syntax error in getEdge()
	* Updated getVertices() to include vertices that are only 
	
# 12-8-2020
## Charles
* Added tests to Dijkstra test file
	* Tests to check correctness of distance between points in graphs with and without diverging paths
	* Tests to check correctness of path between points in graphs with and without diverging paths
	* Tests to check correctness of data map in graphs with and without diverging paths
	* Tests to check handling of vertices not in graph
	* Tests to check handling of empty graph
	* Checks print output of Dijkstra functions
* Updated Dijkstra class
	* Added code to prevent visiting vertices without paths to the source
	* Added code to handle empty graph inputs
	* Added code to handle vertex inputs that are not in the graph
	* Added comments for documentation purposes
	* Added helper functions to print outputs of Dijkstra functions
* Fixed infinite loop bugs in Dijkstra functions
* Updated Graph class
	* Fixed bug in getEdge() function
	* Added vertexExists() function

# 12-9-2020
## Madhav
* Fixed Floyd Warshall bug for min path
* Added all tests for Floyd Warshall and verified correctness
* Added Betweenness Centrality

## Elia
* Added Parsing functions to read from airport and route data files
* Bug exists with comma separation, will fix tomorrow

# 12-10-2020
## Elia
* Fixed bug with parsing
* Implemented thorough tests for parsing/mathfunctions
* Passes with flying colors
## Madhav
* Added all tests for Betweenness Centrality and verified correctness
* Add prints for main function (betweenness centrality)
* Add README.md info
## Matt
* Fix issues with traversals of empty graphs
* Add empty graph traversal tests
## Charles
* Updated main.cpp to run Dijkstra's algorithm on a randomly selected vertex in the OpenFlights dataset
* Added descriptions for Dijkstra's algorithm to README.md, and updated the description of Betweenness Centrality to talk about Floyd-Warshall
