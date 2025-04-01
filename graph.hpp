//benshalev12@gmail.com

#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>

namespace graph {
struct Neighbor {
    int vertex;
    int weight;
    Neighbor* next;
};

class Graph {
private:
    int numVertices;
    Neighbor** adjList;

public:
    Graph(int vertices);
    ~Graph();
    bool hasEdge(int v1, int v2) const;
    int getWeight(int v1, int v2) const;
    bool addEdge(int v1, int v2, int weight);
    bool removeEdge(int v1, int v2);
    void printGraph() const;
    int getNumVertices() const;
    Neighbor** getAdjList() const;
};
}
#endif // GRAPH_HPP
