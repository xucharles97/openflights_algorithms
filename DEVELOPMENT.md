
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
* Added skeleton for functions in Dijkstra.hpp 
	* Shortest distance between two points
	* Shortest path between two points
	* Shortest distance to every other point in the graph from a given point
* Filled out Dijkstra.hpp function
	* Filled out function for shortest distance to every other point in graph from a given point
