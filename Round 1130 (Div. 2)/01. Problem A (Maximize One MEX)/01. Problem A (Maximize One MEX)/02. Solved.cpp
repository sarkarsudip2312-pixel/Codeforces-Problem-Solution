#include <bits/stdc++.h>
using namespace std;

int kthLargestValue(const vector<int>& a, int k) {
    int n = a.size();

    vector<int> f(n);
    vector<bool> present(n + 1, false);

    int mex = 0;

    for (int i = 0; i < n; i++) {
        present[a[i]] = true;

        while (mex <= n && present[mex]) {
            mex++;
        }

        f[i] = mex;
    }

    sort(f.begin(), f.end());

    // k-th largest = index n-k in ascending order
    return f[n - k];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        int n, k;
        cin >> n >> k;

        vector<int> a(n);
        for (int &x : a) {
            cin >> x;
        }

        // Value without performing any operation
        int original = kthLargestValue(a, k);

        int best = original;
        int bestI = -1, bestJ = -1;

        // Try every possible swap
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {

                swap(a[i], a[j]);

                int current = kthLargestValue(a, k);

                if (current > best) {
                    best = current;
                    bestI = i;
                    bestJ = j;
                }

                swap(a[i], a[j]);
            }
        }

        // If no swap improves the answer
        if (bestI == -1) {
            cout << -1 << '\n';
        } else {
            // Convert 0-based indices to 1-based
            cout << bestI + 1 << ' ' << bestJ + 1 << '\n';
        }
    }

    return 0;
}