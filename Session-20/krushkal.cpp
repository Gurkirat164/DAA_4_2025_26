class Solution {
  public:
  
    vector<int> parent, rankv;
    
    int find(int x) {
        if (parent[x] == x) return x;
        return parent[x] = find(parent[x]);  
    }
    
    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        
        if (a == b) return;
        
        if (rankv[a] < rankv[b])
            parent[a] = b;
        else if (rankv[a] > rankv[b])
            parent[b] = a;
        else {
            parent[b] = a;
            rankv[a]++;
        }
    }
  
    int kruskalsMST(int V, vector<vector<int>> &edges) {
        
        parent.resize(V);
        rankv.assign(V, 0);
        
        for (int i = 0; i < V; i++)
            parent[i] = i;
        
        sort(edges.begin(), edges.end(), [](auto &a, auto &b) {
            return a[2] < b[2];
        });
        
        int mstSum = 0;
        int edgesUsed = 0;
        
        for (auto &e : edges) {
            int u = e[0];
            int v = e[1];
            int w = e[2];
            
            if (find(u) != find(v)) {
                unite(u, v);
                mstSum += w;
                edgesUsed++;
                
                if (edgesUsed == V - 1)
                    break;
            }
        }
        
        return mstSum;
    }
};