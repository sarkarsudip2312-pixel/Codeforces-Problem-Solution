#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int n;
        cin >> n;

        vector<vector<int>> g(n + 1);

        for (int i = 0; i < n - 1; ++i) {
            int u, v;
            cin >> u >> v;

            g[u].push_back(v);
            g[v].push_back(u);
        }


        vector<int> parent(n + 1, 0);
        vector<int> order;
        order.reserve(n);

        parent[1] = -1;
        order.push_back(1);

        for (int i = 0; i < (int)order.size(); ++i) {
            int u = order[i];

            for (int v : g[u]) {
                if (v == parent[u])
                    continue;

                parent[v] = u;
                order.push_back(v);
            }
        }


        vector<char> down(n + 1, false);

        for (int i = n - 1; i >= 0; --i) {
            int u = order[i];


            if (parent[u] == -1)
                continue;

            if ((int)g[u].size() % 2 == 1)
                continue;

            bool hasLosingChild = false;

            for (int v : g[u]) {
                if (parent[v] == u) {
                    if (down[v]) {
                        hasLosingChild = true;
                        break;
                    }
                }
            }

            if (!hasLosingChild)
                down[u] = true;
        }

        vector<char> up(n + 1, false);


        for (int u : order) {


            int total = 0;

            if (parent[u] != -1) {
                total += up[u];
            }

            for (int v : g[u]) {
                if (parent[v] == u) {
                    total += down[v];
                }
            }


            for (int v : g[u]) {
                if (parent[v] != u)
                    continue;


                int excludingV = total - (int)down[v];


                if ((int)g[u].size() % 2 == 0 &&
                    excludingV == 0) {
                    up[v] = true;
                }
            }
        }


        vector<int> answer;

        for (int r = 1; r <= n; ++r) {

            if ((int)g[r].size() % 2 == 1)
                continue;

            int incoming = 0;


            if (parent[r] != -1) {
                incoming += up[r];
            }


            for (int v : g[r]) {
                if (parent[v] == r) {
                    incoming += down[v];
                }
            }

            if (incoming == 0) {
                answer.push_back(r);
            }
        }

        if (answer.empty()) {
            cout << "Alice\n";
        } else {
            cout << "Bob\n";

            cout << answer.size() << '\n';

            for (int v : answer) {
                cout << v << ' ';
            }

            cout << '\n';
        }
    }

    return 0;
}