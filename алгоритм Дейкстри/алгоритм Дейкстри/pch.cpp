//
// pch.cpp
//

#include "pch.h"
#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

class Graph {
private:
    int n;
    vector<vector<int>> adj; 

public:
    Graph(int n) {
        this->n = n;
        adj.resize(n);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void removeEdge(int u, int v) {
        adj[u].erase(remove(adj[u].begin(), adj[u].end(), v), adj[u].end());
        adj[v].erase(remove(adj[v].begin(), adj[v].end(), u), adj[v].end());
    }

    void addVertex() {
        n++;
        adj.resize(n);
    }

    void removeVertex(int v) {
        for (int u : adj[v]) {
            removeEdge(u, v);
        }
        adj.erase(adj.begin() + v);
        n--;
    }

    int numVertices() {
        return n;
    }

    int numEdges() {
        int count = 0;
        for (int u = 0; u < n; u++) {
            count += adj[u].size();
        }
        return count / 2;
    }

    bool hasEdge(int u, int v) {
        for (int i = 0; i < adj[u].size(); i++) {
            if (adj[u][i] == v) {
                return true;
            }
        }
        return false;
    }

    bool isTree() {
        vector<bool> visited(n, false);
        queue<int> q;
        int num_components = 0;
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                num_components++;
                q.push(i);
                visited[i] = true;
                while (!q.empty()) {
                    int u = q.front();
                    q.pop();
                    for (int v : adj[u]) {
                        if (visited[v] && v != u) {
                            return false;
                        }
                        visited[v] = true;
                        q.push(v);
                    }
                }
            }
        }
        return num_components == 1 && count(visited.begin(), visited.end(), true) == n;
    }


    bool hasCycle() {
        vector<int> parent(n, -1);
        vector<bool> visited(n, false);
        for (int u = 0; u < n; u++) {
            if (!visited[u]) {
                stack<int> s;
                s.push(u);
                visited[u] = true;
                while (!s.empty()) {
                    int v = s.top();
                    s.pop();
                    for (int w : adj[v]) {
                        if (!visited[w]) {
                            visited[w] = true;
                            parent[w] = v;
                            s.push(w);
                        }
                        else if (w != parent[v]) {
                            return true;
                        }
                    }
                }
            }
        }
        return false;
    }

    int edgeWeight(int u, int v) {
        for (int w : adj[u]) {
            if (w == v) {
                return 1;
            }
        }
        return 0;
    }

    vector<int> dijkstra(int s) {
        vector<int> dist(n, INT_MAX);
        dist[s] = 0;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({ 0, s });
        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();
            for (int v : adj[u]) {
                int w = edgeWeight(u, v);
                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    pq.push({ dist[v], v });
                }
            }
        }
        return dist;
    }

    void dfs(int u, vector<bool>& visited) {
        visited[u] = true;
        cout << u << " ";
        for (int v : adj[u]) {
            if (!visited[v]) {
                dfs(v, visited);
            }
        }
    }

    void dfs(int s) {
        vector<bool> visited(n, false);
        dfs(s, visited);
    }

    void bfs(int s) {
        vector<bool> visited(n, false);
        queue<int> q;
        q.push(s);
        visited[s] = true;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            cout << u << " ";
            for (int v : adj[u]) {
                if (!visited[v]) {
                    visited[v] = true;
                    q.push(v);
                }
            }
        }
    }

    Graph subgraph(vector<int>& vertices) {
        Graph sub(vertices.size());
        map<int, int> index;
        for (int i = 0; i < vertices.size(); i++) {
            index[vertices[i]] = i;
        }
        for (int u : vertices) {
            for (int v : adj[u]) {
                if (index.count(v)) {
                    sub.addEdge(index[u], index[v]);
                }
            }
        }
        return sub;
    }

};

int test() {
    Graph g(6);
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    g.addEdge(3, 4);
    g.addEdge(4, 0);

    cout << "Graph has " << g.numVertices() << " vertices and " << g.numEdges() << " edges." << endl;

    if (g.isTree()) {
        cout << "Graph is a tree." << endl;
    }
    else {
        cout << "Graph is not a tree." << endl;
    }

    if (g.hasCycle()) {
        cout << "Graph has at least one cycle." << endl;
    }
    else {
        cout << "Graph does not have any cycles." << endl << endl;
    }

    vector<int> dist = g.dijkstra(0);
    cout << "Shortest distances from vertex 0:" << endl;
    for (int i = 0; i < dist.size(); i++) {
        cout << i << ": " << dist[i] << endl;
    }
    cout << endl;

    cout << "DFS starting from vertex 0: ";
    g.dfs(0);
    cout << endl;

    cout << "BFS starting from vertex 0: ";
    g.bfs(0);
    cout << endl;

    vector<int> subvertices = { 0, 2, 3 };
    Graph sub = g.subgraph(subvertices);
    cout << "Subgraph of vertices {0, 2, 3}: " << sub.numVertices() << " vertices and " << sub.numEdges() << " edges." << endl;

    return 0;
}



TEST(GraphTest, AddEdgeTest) {
    Graph g(5);
    g.addEdge(0, 1);
    EXPECT_EQ(g.numEdges(), 1);
}

TEST(GraphTest, RemoveEdgeTest) {
    Graph g(5);
    g.addEdge(0, 1);
    g.removeEdge(0, 1);
    EXPECT_EQ(g.numEdges(), 0);
}

TEST(GraphTest, AddVertexTest) {
    Graph g(5);
    g.addVertex();
    EXPECT_EQ(g.numVertices(), 6);
}

TEST(GraphTest, RemoveVertexTest) {
    Graph g(5);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.removeVertex(1);
    EXPECT_EQ(g.numVertices(), 4);
    EXPECT_EQ(g.numEdges(), 1);
}

TEST(GraphTest, NumVerticesTest) {
    Graph g(5);
    EXPECT_EQ(g.numVertices(), 5);
}

TEST(GraphTest, NumEdgesTest) {
    Graph g(5);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    EXPECT_EQ(g.numEdges(), 2);
}

TEST(GraphTest, IsTreeTest) {
    Graph g(5);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(2, 3);
    g.addEdge(2, 4);
    EXPECT_FALSE(g.isTree());
    g.removeEdge(2, 3);
    g.removeEdge(2, 4);
    EXPECT_FALSE(g.isTree());
}

TEST(GraphTest, HasCycleTest) {
    Graph g(5);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(2, 3);
    g.addEdge(3, 4);
    EXPECT_FALSE(g.hasCycle());
    g.addEdge(4, 1);
    EXPECT_TRUE(g.hasCycle());
}

TEST(GraphTest, EdgeWeightTest) {
    Graph g(5);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(2, 3);
    EXPECT_EQ(g.edgeWeight(0, 1), 1);
    EXPECT_EQ(g.edgeWeight(0, 3), 0);
}

TEST(GraphTest, DijkstraTest) {
    Graph g(5);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 4);
    g.addEdge(3, 4);
    vector<int> dist = g.dijkstra(0);
    EXPECT_EQ(dist[0], 0);
    EXPECT_EQ(dist[1], 1);
    EXPECT_EQ(dist[2], 1);
    EXPECT_EQ(dist[3], 2);
    EXPECT_EQ(dist[4], 2);
}

TEST(GraphTest, DFSTest) {
    Graph g(5);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(2, 3);
    g.addEdge(3, 4);
    testing::internal::CaptureStdout();
    g.dfs(0);
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "0 1 2 3 4 ");
}


TEST(GraphTest, BFSTest) {
    Graph g(5);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 4);
    stringstream out;

    streambuf* coutBuf = cout.rdbuf();
    cout.rdbuf(out.rdbuf());

    g.bfs(0);
    cout.rdbuf(coutBuf);

    EXPECT_EQ("0 1 2 3 4 ", out.str());
}

TEST(GraphTest, SubgraphTest) {
    Graph G(5);
    G.addEdge(0, 1);
    G.addEdge(0, 2);
    G.addEdge(1, 2);
    G.addEdge(2, 3);

    vector<int> vertices = { 0, 2, 3 };
    Graph sub = G.subgraph(vertices);

    EXPECT_EQ(sub.numVertices(), 3);
    EXPECT_EQ(sub.numEdges(), 4);
    EXPECT_TRUE(sub.hasEdge(0, 1));
    EXPECT_TRUE(sub.hasEdge(1, 2));
    EXPECT_FALSE(sub.hasEdge(0, 2));
    EXPECT_FALSE(sub.hasEdge(0, 3));
}
