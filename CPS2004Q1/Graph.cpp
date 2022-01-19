#include "Graph.h"
using namespace std;

template<typename T>
// Perform DFS on the graph and set the departure time of all vertices of the graph
void DFS(Graph<T> const &graph, int v, vector<bool> &discovered, vector<int> &departure, int &time) {
    // mark the current node as discovered
    discovered[v] = true;

    // do for every edge (v, u)
    for (Vertex<T> u: graph.adjList[v]) {
        // if u is not yet discovered
        if (!discovered[u.node_id]) {
            DFS(graph, u.node_id, discovered, departure, time);
        }
    }

    // ready to backtrack
    // set departure time of vertex v
    departure[v] = time++;
}

template<typename T>
// Returns true if given directed graph is DAG
bool isDAG(Graph<T> graph, int n) {
    // keep track of whether a vertex is discovered or not
    vector<bool> discovered(n);

    // keep track of the departure time of a vertex in DFS
    vector<int> departure(n);

    int time = 0;

    // Perform DFS traversal from all undiscovered vertices to visit all connected components of a graph
    for (int i = 0; i < n; i++) {
        if (!discovered[i]) {
            DFS(graph, i, discovered, departure, time);
        }
    }

    // check if the given directed graph is DAG or not
    for (int u = 0; u < n; u++) {
        // check if (u, v) forms a back-edge.
        for (Vertex<T> v: graph.adjList[u]) {
            // If the departure time of vertex v is greater than equal to the departure time of u, they form a back edge.
            // Note that departure[u] will be equal to departure[v] only if u = v, i.e., vertex contains an edge to itself
            if (departure[u] <= departure[v.node_id]) {
                return false;
            }
        }
    }
    // no back edges
    return true;
}


template<typename T>
void removeNode(Graph<T> const &graph, Vertex<T> v) {
    for (int i = 0; i < graph.adjList[v.node_id].size(); i++) {
        if (graph.adjList[v.node_id][i] == v.data) {
            graph.adjList.erase(graph.adjList[v.node_id].begin() + i);
        }
    }
}

template<typename T>
vector<Edge<T>> getEdges(Graph<T> const &graph, int n) { // node_id --> {source node, dest node} (e.g. 0 --> {1, 3}, or 1 --> {"hello", "world"})
    for (Edge<T> edge : graph.edgeList) {
        cout << edge.src.node_id << " --> {" << edge.src.data << ", " << edge.dest.data << "}\n";
    }
    return graph.edgeList;
}

