#include <bits/stdc++.h>

using namespace std;

struct Edge {
    int u, v, w;
};
void bellmanFord(int V, int E, int src, vector<Edge>& edges) {
    vector<int> dist(V, INT_MAX);
    dist[src] = 0;
    for (int i = 1; i <= V - 1; i++) {
        for (int j = 0; j < E; j++) {
            if (dist[edges[j].u] != INT_MAX && dist[edges[j].u] + edges[j].w < dist[edges[j].v]) {
                dist[edges[j].v] = dist[edges[j].u] + edges[j].w;
            }
        }
    }
    for (int i = 0; i < V; i++) {
        if (dist[i] == INT_MAX) cout << i << ": INF" << endl;
        else cout << i << ": " << dist[i] << endl;
    }
}
int main() {
    int V = 5, E = 8;
    vector<Edge> edges = {
        {0, 1, -1}, {0, 2, 4}, {1, 2, 3}, {1, 3, 2},
        {1, 4, 2}, {3, 2, 5}, {3, 1, 1}, {4, 3, -3}
    };
    bellmanFord(V, E, 0, edges);
    return 0;
}