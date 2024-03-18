//
// pch.cpp
//

#include "pch.h"
#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

class Graph {
private:
    int V;  
    vector<vector<int>> adj;  //список сум≥жностей
public:
    Graph(int v) {
        V = v;
        adj.resize(V);
    }

    // дод. ребро
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // к-ть вершин
    int countVertices() {
        return V;
    }

    // к-ть ребер
    int countEdges() {
        int count = 0;
        for (int i = 0; i < V; i++) {
            count += adj[i].size();
        }
        return count / 2;
    }

    // сум≥жн≥ з будь-€кою вершиною вершини
    int countAdjacentVertices(int u) {
        return adj[u].size();
    }

    // пошук висоти (ураховуючи п≥ддерва)
    int maxHeight() {
        int max_height = 0;
        for (int i = 0; i < V; i++) {
            vector<bool> visited(V, false);
            int height = 0;
            dfs(i, 0, &height, visited);
            if (height > max_height) {
                max_height = height;
            }
        }
        return max_height;
    }

    // допом≥жна ф. пошук углиб
    void dfs(int v, int depth, int* max_depth, vector<bool>& visited) {
        visited[v] = true;
        if (depth > *max_depth) {
            *max_depth = depth;
        }
        for (int u : adj[v]) {
            if (!visited[u]) {
                dfs(u, depth + 1, max_depth, visited);
            }
        }
    }

    // к-ть листк≥в
    int countLeaves() {
        int count = 0;
        for (int i = 0; i < V; i++) {
            if (adj[i].size() == 1) {
                count++;
            }
        }
        return count;
    }

    // алгоритм ƒейкстри
    void dijkstra(int source, vector<int>& distances) {
        distances.assign(V, INT_MAX);
        distances[source] = 0;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({ 0, source });

        while (!pq.empty()) {
            int u = pq.top().second;
            int dist_u = pq.top().first;
            pq.pop();

            if (dist_u > distances[u]) {
                continue;
            }

            for (int v : adj[u]) {
                int dist_v = 1; // assume edge weight is 1
                if (distances[u] + dist_v < distances[v]) {
                    distances[v] = distances[u] + dist_v;
                    pq.push({ distances[v], v });
                }
            }
        }
    }
};

int test() {
    Graph g(6);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 4);
    g.addEdge(3, 5);
    g.addEdge(4, 5);

    cout << "Number of vertices: " << g.countVertices() << endl;
    cout << "Number of edges: " << g.countEdges() << endl;
    cout << "Number of leaves: " << g.countLeaves() << endl << endl;

    cout << "Number of adjacent vertices for vertex 0: " << g.countAdjacentVertices(0) << endl;
    cout << "Max height of the graph: " << g.maxHeight() << endl;

    vector<int> distances;
    int source = 0; // choose the source vertex
    g.dijkstra(source, distances);

    cout << "Shortest distances from vertex " << source << ":" << endl;
    for (int i = 0; i < g.countVertices(); i++) {
        cout << i << ": " << distances[i] << endl;
    }

    return 0;
}

//////////////////////////// “≈—“”¬јЌЌя //////////////////////////////////////

class GraphTest : public ::testing::Test {
protected:
    Graph g{5};

    void SetUp() override {
        g.addEdge(0, 1);
        g.addEdge(0, 2);
        g.addEdge(1, 3);
        g.addEdge(1, 4);
    }
};

TEST_F(GraphTest, CountVertices) {
    EXPECT_EQ(g.countVertices(), 5);
}

TEST_F(GraphTest, CountEdges) {
    EXPECT_EQ(g.countEdges(), 4);
}

TEST_F(GraphTest, CountAdjacentVertices) {
    EXPECT_EQ(g.countAdjacentVertices(1), 3);
}

TEST_F(GraphTest, MaxHeight) {
    EXPECT_EQ(g.maxHeight(), 3);
}

TEST_F(GraphTest, CountLeaves) {
    EXPECT_EQ(g.countLeaves(), 3);
}

TEST_F(GraphTest, Dijkstra) {
    vector<int> distances;
    g.dijkstra(0, distances);
    EXPECT_EQ(distances, vector<int>({ 0, 1, 1, 2, 2 }));
}
