using namespace std;
#include "Graph.cpp"

int main() {

    // Setting the Vertices
    Vertex<string> v1(0, "Node 1");
    Vertex<string> v2(1, "Node 2");
    Vertex<string> v3(2, "Node 3");
    Vertex<string> v4(3, "Node 4");
    Vertex<string> v5(4, "Node 5");

    // Creating 4 edges with the previously set Vertices
    Edge<string> e1(v1, v2);
    Edge<string> e2(v2, v3);
    Edge<string> e3(v3, v4);
    Edge<string> e4(v4, v5);


    vector<Edge<string> > edgeList;
    edgeList.push_back(e1);
    edgeList.push_back(e2);
    edgeList.push_back(e3);
    edgeList.push_back(e4);


    int n = 5; // Number of nodes

    // Constructing the graph 
    Graph<string> g(edgeList, n);

    if (!isDAG(g, n)) {
        cout << "Error: The graph is not acyclic." << endl;
        return 0;
    }

    getEdges(g, n);
    //removeNode(g, v1);
    return 0;
}