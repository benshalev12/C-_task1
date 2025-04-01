# Graph Algorithms Project

This project implements core graph algorithms in C++ without using the STL. It includes a console-based interface to interact with a graph, and unit tests using the Doctest framework.

---

## 📁 Project Structure

```
.
├── algorithms.cpp      # Implementation of graph algorithms
├── algorithms.hpp      # Declarations of graph algorithms
├── graph.cpp           # Graph class implementation
├── graph.hpp           # Graph class definition
├── queue.hpp           # Custom queue class (no STL)
├── main.cpp            # CLI menu for interacting with graphs
├── test_doctest.cpp    # Unit tests using Doctest
├── doctest.h           # Doctest header
├── Makefile            # Compilation script
```

---

## 🛠️ Build Instructions

Ensure you have a C++ compiler installed. To compile the project:

```bash
make
```

This will create the `main` executable.

---

## ▶️ Run Instructions

To start the interactive graph menu:

```bash
./main
```

You will be prompted to enter the number of vertices and select operations from a menu.

---

## 🧪 Run Tests

To compile and run the tests:

```bash
g++ test_doctest.cpp graph.cpp algorithms.cpp -o tests
./tests
```

---

## 🧹 Memory Check with Valgrind

Make sure Valgrind is installed:

```bash
sudo apt install valgrind
```

To check your program for memory leaks:

```bash
valgrind --leak-check=full ./main
```

Or for the tests:

```bash
valgrind --leak-check=full ./tests
```

You should see `All heap blocks were freed -- no leaks are possible` if everything is clean.

---

## ✅ Features

- Add and remove edges (undirected graph)
- Graph traversal using BFS and DFS
- Dijkstra’s algorithm for shortest paths (non-negative weights only)
- Prim’s algorithm for Minimum Spanning Tree
- Kruskal’s algorithm for Minimum Spanning Tree using Union-Find
- Manual data structures (queue, union-find) instead of STL
- Input validation and informative error messages

---

## 👤 Author

Developed by **Ben Shalev**  
Code includes self-implemented graph logic and test coverage.

---

## 📄 License

Educational and open-source use permitted.