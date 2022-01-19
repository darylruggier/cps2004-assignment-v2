#ifndef CPS2004Q1_VERTEX_H
#define CPS2004Q1_VERTEX_H
#include <vector>

template<typename T>
class Vertex {
public:
    int node_id{};
    T data;

    Vertex<T>(int node_id, T data) {
        this->node_id = node_id;
        this->data = data;
    }

    Vertex<T>() = default;
};

#endif //CPS2004Q1_VERTEX_H
