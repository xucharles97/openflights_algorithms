# Openflights Algorithms

## Disclaimer
This was created as a final project the CS 225 data structures class at UIUC. This repository was copied from the original private repo on Github Enterprise with full permission from all the professor and other group members on January 5th, 2021.

## Objective

Dijkstra's Algorithm: Find the shortest path and distance from a source vertex to every other vertex in the graph. In the context of our dataset, this represents the shortest flight path from a starting airport to every other airport in the dataset

Betweenness Centrality: Uses the Floyd-Warshall algorithm to find the Vertex which is most commonly on the shortest path from all other Vertices to all other Vertices. In the context of our dataset (airports and routes), this can be inferred as the airport which is most likely to be part of the shortest route between 2 other airports. 

To run this (which may take a long time!), see the "Main" section below. 

## Dataset

Both the airports and routes information can be found in the `datasets` folder under the names `airports.txt` and `routes.txt`, respectively.
Source: [Openflights](https://openflights.org/data.html)

## Main

1. `make main` to compile and link
2. `./main [number of airports]` to run Dijkstra's algorithm and Betweenness Centrality. The one and only command-line argument is the number of airports to prune to (as the dataset is extremely large). We recommend a value less than 100 to run in about a minute. Dijkstra's algorithm will find the shortest path from a randomly selected Vertex (airport) to every other Vertex in the dataset, as well as specifically outputting the shortest distance and full path to other two other randomly selected vertices. Betweenness Centrality will find the most central Vertex (airport) in the dataset

## Tests

1. `make test` to compile and link
2. `./test` to run all tests

## Final Presentation Link
https://drive.google.com/file/d/1OE9TqFLyuu-xlEKIwuo-SgtVm1ts3BfS/view?usp=sharing
