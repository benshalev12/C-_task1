//benshalev12@gmail.com

#include "graph.hpp"
#include <cstdlib>
#include <iostream>
namespace graph {
    // Constructor: Initializes the graph with a specified number of vertices.
Graph::Graph(int vertices) : numVertices(vertices) {
    adjList = new Neighbor*[numVertices];
    for (int i = 0; i < numVertices; ++i) {
        adjList[i] = nullptr;
    }
}
// Destructor: Frees the dynamically allocated memory for the adjacency list.
Graph::~Graph() {
    for (int i = 0; i < numVertices; ++i) {
        Neighbor* current = adjList[i];
               // Traverse the adjacency list for the vertex.
        while (current) {
            Neighbor* temp = current;
            current = current->next;
            delete temp;
        }
    }
    delete[] adjList;
}

// Checks if there is an edge between two vertices.
bool Graph::hasEdge(int v1, int v2) const {
    Neighbor* current = adjList[v1];
        // Traverse the adjacency list for the vertex.
    while (current) {
        if (current->vertex == v2)
            return true;
        current = current->next;
    }
    return false;
}

// Returns the weight of the edge between two vertices, or -1 if the edge doesn't exist.
int Graph::getWeight(int v1, int v2) const {
    Neighbor* current = adjList[v1];
       // Traverse the adjacency list for the vertex.
    while (current) {
        if (current->vertex == v2)
            return current->weight;
        current = current->next;
    }
    return -1; // If edge does not exist
}

// Adds an undirected edge between two vertices with the specified weight.
bool Graph::addEdge(int v1, int v2, int weight) {
        // Validate that vertices are within range and not equal to each other.
    if (v1 < 0 || v2 < 0 || v1 >= numVertices || v2 >= numVertices) {
        std::cout << "Invalid vertices.\n";
        return false;
    }
    if (v1 == v2) {
        std::cout << "Cannot add edge to the same vertex.\n";
        return false;
    }

    // Check if the edge already exists
    Neighbor* check = adjList[v1];
    bool exists = false;
    while (check) {
        if (check->vertex == v2) {
            exists = true;
            break;
        }
        check = check->next;
    }
        // If it exists, remove the existing edge to update weight
    if (exists) {
        removeEdge(v1, v2);
    }

    // Add the new edge in both directions
    Neighbor* n1 = new Neighbor{v2, weight, adjList[v1]};
    adjList[v1] = n1;

    Neighbor* n2 = new Neighbor{v1, weight, adjList[v2]};
    adjList[v2] = n2;

    return true;
}

bool Graph::removeEdge(int v1, int v2) {
    if (v1 < 0 || v2 < 0 || v1 >= numVertices || v2 >= numVertices || v1 == v2) {
        std::cout << "Invalid vertices or same vertex.\n";
        return false;
    }

    bool found = false;

    Neighbor** curr = &adjList[v1];
    while (*curr) {
        if ((*curr)->vertex == v2) {
            Neighbor* temp = *curr;
            *curr = (*curr)->next;
            delete temp;
            found = true;
            break;
        }
        curr = &((*curr)->next);
    }

    curr = &adjList[v2];
    while (*curr) {
        if ((*curr)->vertex == v1) {
            Neighbor* temp = *curr;
            *curr = (*curr)->next;
            delete temp;
            found = true;
            break;
        }
        curr = &((*curr)->next);
    }

    if (!found) {
        std::cout << "Edge does not exist.\n";
        return false;
    }

    return true;
}

void Graph::printGraph() const {
    for (int i = 0; i < numVertices; ++i) {
        std::cout << "Vertex " << i << ": ";
        Neighbor* current = adjList[i];
        while (current) {
            std::cout << "(" << current->vertex << ", weight: " << current->weight << ") ";
            current = current->next;
        }
        std::cout << std::endl;
    }
}

int Graph::getNumVertices() const {
    return numVertices;
}

Neighbor** Graph::getAdjList() const {
    return adjList;
}
}