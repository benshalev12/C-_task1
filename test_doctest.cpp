//benshalev12@gmail.com
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "graph.hpp"
#include "algorithms.hpp"

using namespace graph;

// Tests: add, remove, and validate basic edges
TEST_CASE("Graph Basic Operations") {
    Graph g(4);

    SUBCASE("Add and remove valid edges") {
        CHECK(g.addEdge(0, 1, 5));
        CHECK(g.addEdge(1, 2, 3));
        CHECK(g.hasEdge(0, 1));
        CHECK(g.getWeight(0, 1) == 5);
        CHECK(g.removeEdge(0, 1));
        CHECK_FALSE(g.hasEdge(0, 1));
    }

    SUBCASE("Reject edge to self") {
        CHECK_FALSE(g.addEdge(2, 2, 10));
    }

    SUBCASE("Remove non-existent edge") {
        CHECK_FALSE(g.removeEdge(3, 0));
    }

    SUBCASE("Overwrite edge") {
        CHECK(g.addEdge(1, 3, 4));
        CHECK(g.addEdge(1, 3, 9));
        CHECK(g.getWeight(1, 3) == 9);
    }
}

// Tests: BFS tree construction
TEST_CASE("BFS Tree Structure") {
    Graph g(5);
    g.addEdge(0, 1, 1);
    g.addEdge(0, 2, 1);
    g.addEdge(1, 3, 1);
    g.addEdge(2, 4, 1);

    Graph* bfsTree = Algorithms::bfs(g, 0);
    REQUIRE(bfsTree != nullptr);
    REQUIRE(bfsTree->getNumVertices() == 5);

    CHECK(bfsTree->hasEdge(0, 1));
    CHECK(bfsTree->hasEdge(0, 2));
    CHECK(bfsTree->hasEdge(1, 3));
    CHECK(bfsTree->hasEdge(2, 4));

    CHECK_FALSE(bfsTree->hasEdge(3, 4));
    CHECK_FALSE(bfsTree->hasEdge(1, 2));

    delete bfsTree;
}

// Tests: DFS tree construction
TEST_CASE("DFS Tree Structure") {
    Graph g(5);
    g.addEdge(0, 1, 1);
    g.addEdge(0, 2, 1);
    g.addEdge(1, 3, 1);
    g.addEdge(2, 4, 1);

    Graph* dfsTree = Algorithms::dfs(g, 0);
    REQUIRE(dfsTree != nullptr);
    REQUIRE(dfsTree->getNumVertices() == 5);

    bool validRoot = dfsTree->hasEdge(0, 1) || dfsTree->hasEdge(0, 2);
    CHECK(validRoot);
    CHECK_FALSE(dfsTree->hasEdge(1, 2));

    delete dfsTree;
}

// Tests: Dijkstra algorithm for shortest path tree
TEST_CASE("Dijkstra Shortest Path Tree") {
    Graph g(4);
    g.addEdge(0, 1, 1);
    g.addEdge(1, 2, 2);
    g.addEdge(2, 3, 3);

    SUBCASE("Valid weights") {
        Graph* spTree = Algorithms::dijkstra(g, 0);
        REQUIRE(spTree != nullptr);
        CHECK(spTree->hasEdge(0, 1));
        CHECK(spTree->hasEdge(1, 2));
        CHECK(spTree->hasEdge(2, 3));
        delete spTree;
    }

    SUBCASE("With negative weight") {
        g.addEdge(0, 3, -4);
        Graph* spTree = Algorithms::dijkstra(g, 0);
        CHECK(spTree == nullptr);  // should fail
    }
}

// Tests: Prim's algorithm for MST
TEST_CASE("Prim MST Structure") {
    Graph g(5);
    g.addEdge(0, 1, 2);
    g.addEdge(0, 2, 3);
    g.addEdge(1, 3, 1);
    g.addEdge(3, 4, 4);
    g.addEdge(2, 4, 5);
    g.addEdge(1, 2, -2);  // allowed in Prim

    Graph* mst = Algorithms::prim(g);
    REQUIRE(mst != nullptr);
    CHECK(mst->getNumVertices() == 5);
    CHECK(mst->hasEdge(1, 2));
    delete mst;
}

// Tests: Kruskal's algorithm for MST
TEST_CASE("Kruskal MST Structure") {
    Graph g(5);
    g.addEdge(0, 1, 10);
    g.addEdge(1, 2, 1);
    g.addEdge(2, 3, 2);
    g.addEdge(3, 4, 3);
    g.addEdge(0, 4, 0);

    Graph* mst = Algorithms::kruskal(g);
    REQUIRE(mst != nullptr);
    CHECK(mst->hasEdge(0, 4));
    CHECK(mst->hasEdge(1, 2));
    CHECK(mst->hasEdge(2, 3));
    bool validLastEdge = mst->hasEdge(3, 4) || mst->hasEdge(0, 1);
    CHECK(validLastEdge); // last edge might vary
    delete mst;
}