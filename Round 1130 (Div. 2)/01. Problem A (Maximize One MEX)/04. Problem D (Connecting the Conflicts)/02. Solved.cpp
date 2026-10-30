#include <bits/stdc++.h>
using namespace std;

struct Tree {
    int n;

    vector<vector<int>> adj;

    
    vector<array<int, 2>> dp;

    vector<int> parent;
    vector<int> chosen;

    int root;

    Tree(int n = 0) : n(n) {
        adj.resize(n + 1);
        dp.resize(n + 1);
        parent.resize(n + 1);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void dfs(int v, int p) {
        parent[v] = p;

        dp[v][0] = 0;
        dp[v][1] = 1;

        for (int u : adj[v]) {
            if (u == p)
                continue;

            dfs(u, v);

            dp[v][0] += max(dp[u][0], dp[u][1]);
            dp[v][1] += dp[u][0];
        }
    }

    void reconstruct(int v, int p, bool take) {
        bool canTake = take;

        if (take) {
            chosen.push_back(v);

            for (int u : adj[v]) {
                if (u == p)
                    continue;

                
                reconstruct(u, v, false);
            }
        } else {
            for (int u : adj[v]) {
                if (u == p)
                    continue;

                
                if (dp[u][1] > dp[u][0])
                    reconstruct(u, v, true);
                else
                    reconstruct(u, v, false);
            }
        }
    }

    
    int getExcludedVertex() {
        if (n == 1) {
            
            return -1;
        }

        root = 1;

        dfs(root, 0);

        chosen.clear();

        if (dp[root][1] > dp[root][0])
            reconstruct(root, 0, true);
        else
            reconstruct(root, 0, false);

        vector<bool> inSet(n + 1, false);

        for (int v : chosen)
            inSet[v] = true;

        
        for (int v = 1; v <= n; v++) {
            if (!inSet[v])
                return v;
        }

        return -1;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int k;
        cin >> k;

        vector<Tree> trees(k);

        for (int i = 0; i < k; i++) {
            int n;
            cin >> n;

            trees[i] = Tree(n);

            for (int j = 0; j < n - 1; j++) {
                int u, v;
                cin >> u >> v;

                trees[i].addEdge(u, v);
            }
        }

        
        int base = -1;

        for (int i = 0; i < k; i++) {
            if (trees[i].n > 1) {
                base = i;
                break;
            }
        }

        
        if (base == -1) {

            
            for (int i = 1; i < k; i++) {
                cout << 1 << ' ' << 1 << ' '
                     << i + 1 << ' ' << 1 << '\n';
            }

            continue;
        }


        int baseVertex = trees[base].getExcludedVertex();

        
        for (int i = 0; i < k; i++) {
            if (i == base)
                continue;

            int v;

            if (trees[i].n == 1) {
            
                v = 1;
            } else {
                
                v = trees[i].getExcludedVertex();
            }

            cout << base + 1 << ' ' << baseVertex << ' '
                 << i + 1 << ' ' << v << '\n';
        }
    }

    return 0;
}