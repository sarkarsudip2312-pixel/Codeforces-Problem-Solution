#include <bits/stdc++.h>
using namespace std;

using ll = long long;


int requiredExtra(const vector<ll>& a, ll k) {
    int n = a.size();

    vector<ll> isolated;


    for (int i = 0; i < n; i++) {
        bool hasNeighbor = false;

        if (i > 0 && a[i] - a[i - 1] <= k)
            hasNeighbor = true;

        if (i + 1 < n && a[i + 1] - a[i] <= k)
            hasNeighbor = true;

        if (!hasNeighbor)
            isolated.push_back(a[i]);
    }

    int extra = 0;

    for (int i = 0; i < (int)isolated.size(); ) {
        if (i + 1 < (int)isolated.size() &&
            isolated[i + 1] - isolated[i] <= 2 * k) {

            extra++;
            i += 2;
        } else {

        
            extra++;
            i++;
        }
    }

    return extra;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int n, x;
        cin >> n >> x;

        vector<ll> a(n);

        for (ll &v : a)
            cin >> v;

        // Binary search for minimum k.
        ll lo = 1;
        ll hi = 1000000000LL;

        while (lo < hi) {
            ll mid = lo + (hi - lo) / 2;

            if (requiredExtra(a, mid) <= x) {
                hi = mid;
            } else {
                lo = mid + 1;
            }
        }

        cout << lo << '\n';
    }

    return 0;
}