class Solution {
public:
    int spanningTree(int V, vector<vector<int>>& edges) {
    
        vector<vector<pair<int,int>>> adj(V);
        for (auto &e : edges) {
            int u = e[0];
            int v = e[1];
            int w = e[2];
            
            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
        }

        priority_queue<pair<int,int>, 
                       vector<pair<int,int>>, 
                       greater<pair<int,int>>> pq;

        vector<bool> visited(V, false);
        int mstSum = 0;
       
        pq.push({0, 0});

        while (!pq.empty()) {
            auto [wt, node] = pq.top();
            pq.pop();
            if (visited[node]) continue;
            visited[node] = true;
            mstSum += wt;
            for (auto &neighbor : adj[node]) {
                int adjNode = neighbor.first;
                int edgeWt = neighbor.second;
                if (!visited[adjNode]) {
                    pq.push({edgeWt, adjNode});
                }
            }
        }

        return mstSum;
    }
};