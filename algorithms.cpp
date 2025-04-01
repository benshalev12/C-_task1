//benshalev12@gmail.com

#include "algorithms.hpp"
#include "queue.hpp"
#include <climits>
#include <cstdlib>
#include <iostream>

namespace graph {

// Breadth-First Search (BFS)
Graph* Algorithms::bfs(const Graph& g, int start) {
    int size = g.getNumVertices();
    Graph* tree = new Graph(size);
    int* visited = new int[size];
    for (int i = 0; i < size; ++i) visited[i] = 0;

    SimpleQueue q(size);
    q.enqueue(start);
    visited[start] = 1;

    Neighbor** adj = g.getAdjList();

    while (!q.isEmpty()) {
        int current = q.dequeue();
        Neighbor* neighbor = adj[current];
        while (neighbor) {
            int next = neighbor->vertex;
            int weight = neighbor->weight;
            if (!visited[next]) {
                visited[next] = 1;
                tree->addEdge(current, next, weight);
                q.enqueue(next);
            }
            neighbor = neighbor->next;
        }
    }

    delete[] visited;
    return tree;
}

// Depth-First Search (DFS)
Graph* Algorithms::dfs(const Graph& g, int start) {
    int size = g.getNumVertices();
    Graph* tree = new Graph(size);
    int* visited = new int[size];
    for (int i = 0; i < size; ++i) visited[i] = 0;

    struct Frame {
        int v;
        int parent;
    };

    Frame* stack = new Frame[size];
    int top = 0;
    stack[top++] = {start, -1};

    Neighbor** adj = g.getAdjList();

    while (top > 0) {
        Frame frame = stack[--top];
        int v = frame.v;
        int parent = frame.parent;

        if (!visited[v]) {
            visited[v] = 1;
            if (parent != -1) {
                Neighbor* n = adj[v];
                while (n) {
                    if (n->vertex == parent) {
                        tree->addEdge(parent, v, n->weight);
                        break;
                    }
                    n = n->next;
                }
            }

            Neighbor* neighbor = adj[v];
            while (neighbor) {
                if (!visited[neighbor->vertex]) {
                    stack[top++] = {neighbor->vertex, v};
                }
                neighbor = neighbor->next;
            }
        }
    }

    delete[] visited;
    delete[] stack;
    return tree;
}

// Dijkstra's Algorithm: Shortest paths from a source
Graph* Algorithms::dijkstra(const Graph& g, int start) {
    Neighbor** adj = g.getAdjList();
    for (int i = 0; i < g.getNumVertices(); ++i) {
        Neighbor* n = adj[i];
        while (n) {
            if (n->weight < 0) {
                std::cout << "Error: Dijkstra cannot compute negative edge weights.\n";
                return nullptr;
            }
            n = n->next;
        }
    }

    int size = g.getNumVertices();
    Graph* tree = new Graph(size);
    int* dist = new int[size];
    int* parent = new int[size];
    bool* visited = new bool[size];

    for (int i = 0; i < size; ++i) {
        dist[i] = INT_MAX;
        parent[i] = -1;
        visited[i] = false;
    }

    dist[start] = 0;

    for (int i = 0; i < size; ++i) {
        int u = -1;
        for (int j = 0; j < size; ++j) {
            if (!visited[j] && (u == -1 || dist[j] < dist[u])) {
                u = j;
            }
        }

        if (dist[u] == INT_MAX)
            break;

        visited[u] = true;

        Neighbor* neighbor = g.getAdjList()[u];
        while (neighbor) {
            int v = neighbor->vertex;
            int w = neighbor->weight;
            if (w >= 0 && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                parent[v] = u;
            }
            neighbor = neighbor->next;
        }
    }

    for (int i = 0; i < size; ++i) {
        if (parent[i] != -1) {
            Neighbor* n = g.getAdjList()[i];
            while (n) {
                if (n->vertex == parent[i]) {
                    tree->addEdge(i, parent[i], n->weight);
                    break;
                }
                n = n->next;
            }
        }
    }

    delete[] dist;
    delete[] parent;
    delete[] visited;
    return tree;
}

// Prim's Algorithm: Minimum Spanning Tree (MST)
Graph* Algorithms::prim(const Graph& g) {
    

    int size = g.getNumVertices();
    Graph* tree = new Graph(size);
    int* key = new int[size];
    int* parent = new int[size];
    bool* inMST = new bool[size];

    for (int i = 0; i < size; ++i) {
        key[i] = INT_MAX;
        parent[i] = -1;
        inMST[i] = false;
    }

    key[0] = 0;

    for (int count = 0; count < size; ++count) {
        int u = -1;
        for (int v = 0; v < size; ++v) {
            if (!inMST[v] && (u == -1 || key[v] < key[u])) {
                u = v;
            }
        }

        inMST[u] = true;

        Neighbor* neighbor = g.getAdjList()[u];
        while (neighbor) {
            int v = neighbor->vertex;
            int weight = neighbor->weight;
            if (!inMST[v] && weight < key[v]) {
                key[v] = weight;
                parent[v] = u;
            }
            neighbor = neighbor->next;
        }
    }

    for (int i = 1; i < size; ++i) {
        if (parent[i] != -1) {
            Neighbor* n = g.getAdjList()[i];
            while (n) {
                if (n->vertex == parent[i]) {
                    tree->addEdge(i, parent[i], n->weight);
                    break;
                }
                n = n->next;
            }
        }
    }

    delete[] key;
    delete[] parent;
    delete[] inMST;
    return tree;
}

// Kruskal's Algorithm: Minimum Spanning Tree (MST)
Graph* Algorithms::kruskal(const Graph& g) {
    int size = g.getNumVertices();
    Graph* tree = new Graph(size);
    int* parent = new int[size];
    for (int i = 0; i < size; ++i) parent[i] = i;

    struct Edge {
        int u, v, w;
    };

    Edge* edges = new Edge[size * size]; // oversize
    int edgeCount = 0;

    Neighbor** adj = g.getAdjList();
    for (int u = 0; u < size; ++u) {
        Neighbor* neighbor = adj[u];
        while (neighbor) {
            int v = neighbor->vertex;
            int w = neighbor->weight;
            if (u < v) {
                edges[edgeCount++] = {u, v, w};
            }
            neighbor = neighbor->next;
        }
    }

    for (int i = 0; i < edgeCount - 1; ++i) {
        int minIdx = i;
        for (int j = i + 1; j < edgeCount; ++j) {
            if (edges[j].w < edges[minIdx].w)
                minIdx = j;
        }
        if (minIdx != i) {
            Edge temp = edges[i];
            edges[i] = edges[minIdx];
            edges[minIdx] = temp;
        }
    }

    auto find = [&](int u) {
        while (u != parent[u]) u = parent[u];
        return u;
    };

    auto unite = [&](int u, int v) {
        parent[find(v)] = find(u);
    };

    for (int i = 0; i < edgeCount; ++i) {
        int u = edges[i].u;
        int v = edges[i].v;
        int w = edges[i].w;

        if (find(u) != find(v)) {
            tree->addEdge(u, v, w);
            unite(u, v);
        }
    }

    delete[] parent;
    delete[] edges;
    return tree;
}

} // namespace graph