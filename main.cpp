//benshalev12@gmail.com

#include "graph.hpp"
#include "algorithms.hpp"
#include <iostream>

using namespace std;
using namespace graph;

// Main function: Menu-driven interface for graph operations
int main() {
    int vertices;
// Input number of vertices for the graph
    cout << "Enter number of vertices: ";
    cin >> vertices;

    Graph g(vertices);

// Loop for menu selection until user exits
    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Add Edge\n";
        cout << "2. Remove Edge\n";
        cout << "3. Print Graph\n";
        cout << "4. BFS\n";
        cout << "5. DFS\n";
        cout << "6. Dijkstra\n";
        cout << "7. Prim\n";
        cout << "8. Kruskal\n";
        cout << "9. Exit\n";
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

// Option 1: Add an edge
        if (choice == 1) {
            int v1, v2, w;
            cout << "Enter vertex 1, vertex 2 and weight: ";
            cin >> v1 >> v2 >> w;
            g.addEdge(v1, v2, w);
// Option 2: Remove an edge
        } else if (choice == 2) {
            int v1, v2;
            cout << "Enter vertex 1 and vertex 2: ";
            cin >> v1 >> v2;
            g.removeEdge(v1, v2);
// Option 3: Print the current graph
        } else if (choice == 3) {
            g.printGraph();
// Option 4: Run BFS from a start vertex
        } else if (choice == 4) {
            int start;
            cout << "Enter start vertex: ";
            cin >> start;
            Graph* tree = Algorithms::bfs(g, start);
            cout << "BFS Tree:\n";
            tree->printGraph();
            delete tree;
// Option 5: Run DFS from a start vertex
        } else if (choice == 5) {
            int start;
            cout << "Enter start vertex: ";
            cin >> start;
            Graph* tree = Algorithms::dfs(g, start);
            cout << "DFS Tree:\n";
            tree->printGraph();
            delete tree;
// Option 6: Run Dijkstra from a start vertex
        } else if (choice == 6) {
            int start;
            cout << "Enter start vertex: ";
            cin >> start;
            Graph* tree = Algorithms::dijkstra(g, start);
            if (tree) {
                cout << "Dijkstra Shortest Path Tree:\n";
                tree->printGraph();
                delete tree;
            }
// Option 7: Run Prim's MST
        } else if (choice == 7) {
            Graph* mst = Algorithms::prim(g);
            if (mst) {
                cout << "Prim MST:\n";
                mst->printGraph();
                delete mst;
            }
// Option 8: Run Kruskal's MST
        } else if (choice == 8) {
            Graph* mst = Algorithms::kruskal(g);
            if (mst) {
                cout << "Kruskal MST:\n";
                mst->printGraph();
                delete mst;
            }
// Option 9: Exit the program
        } else if (choice == 9) {
            break;
        } else {
            cout << "Invalid choice.\n";
        }
    }

    return 0;
}