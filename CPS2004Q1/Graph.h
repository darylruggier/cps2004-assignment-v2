#ifndef CPS2004Q1_GRAPH_H
#define CPS2004Q1_GRAPH_H


#include <iostream>
#include <vector>
#include "Vertex.cpp"
#include "Edge.cpp"
using namespace std;

template<typename T>
class Graph {
public:
    vector<vector<Vertex<T> > > adjList; // Adjacency List - will be used to form the Graph
    vector<Edge<T> > edgeList;

    Graph<T>(vector<Edge<T> > edgeList, int n) { // Constructor takes a list of Edges & the number of nodes in the Graph
        this->edgeList = edgeList;
        adjList.resize(n); //Resizing the vector to hold n elements of type vector<Vertex>

        for (auto &edge: edgeList) {
            int i = 0;
            adjList[edge.src.node_id].push_back(edge.dest); // push_back not being recognised ?
            i++;
        }
    }

    Graph<T>() = default;
    ~Graph<T>() = default;
};


#endif //CPS2004Q1_GRAPH_H
