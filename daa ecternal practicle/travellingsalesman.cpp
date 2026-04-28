#include <bits/stdc++.h>

using namespace std;

int min_cost = INT_MAX;

void tsp(vector<vector<int>>& graph, vector<bool>& visited, int currPos, int n, int count, int cost) {
    if (count == n && graph[currPos][0] > 0) {
        min_cost = min(min_cost, cost + graph[currPos][0]);
        return;
    }

    for (int i = 0; i < n; i++) {
        if (!visited[i] && graph[currPos][i] > 0) {
            visited[i] = true;
            tsp(graph, visited, i, n, count + 1, cost + graph[currPos][i]);
            visited[i] = false; 
        }
    }
}

int main() {
    int n = 4;
    vector<vector<int>> graph = {
        {0, 10, 15, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0}
    };

    vector<bool> visited(n, false);
    visited[0] = true;

    tsp(graph, visited, 0, n, 1, 0);

    cout << "Minimum Cost: " << min_cost << endl;

    return 0;
}