#ifndef CPS2004Q1_EDGE_H
#define CPS2004Q1_EDGE_H


#include <iostream>
#include <vector>
#include "Vertex.h"
#include "Graph.h"

template<typename T>
class Edge {
public:
    Vertex<T> src, dest;

    Edge<T>(Vertex<T> src, Vertex<T> dest) {
        this->src = Vertex<T>(src);
        this->dest = Vertex<T>(dest);
    }

    Edge<T>() = default;
};


#endif //CPS2004Q1_EDGE_H
