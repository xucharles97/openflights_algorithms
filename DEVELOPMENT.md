
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
