#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct Info {
    vector<int> wpos;
    vector<int> gaps;
    vector<ll> pref;

    int lastW = 0;

    void build(const string& s) {
        int n = (int)s.size();

        for (int i = 0; i < n; i++) {
            if (s[i] == 'W') {
                wpos.push_back(i + 1);
            }
        }

        if (!wpos.empty()) {
            lastW = wpos.back();
        }

        for (int i = 1; i < (int)wpos.size(); i++) {
            gaps.push_back(wpos[i] - wpos[i - 1]);
        }

        sort(gaps.begin(), gaps.end());

        pref.resize(gaps.size() + 1, 0);

        for (int i = 0; i < (int)gaps.size(); i++) {
            pref[i + 1] = pref[i] + gaps[i];
        }
    }

    ll sumMin(ll L) const {
        int cnt = upper_bound(gaps.begin(), gaps.end(), L)
                  - gaps.begin();

    
        ll result = pref[cnt];

    
        result += 1LL * ((int)gaps.size() - cnt) * L;

        return result;
    }
};


vector<ll> solveReads(
    const string& s,
    const Info& other
) {
    int n = s.size();
    int m = other.wpos.empty()
        ? 0
        : 0;

    
    return {};
}

vector<ll> solveReads(
    const string& s,
    int m,
    const Info& other
) {
    vector<ll> ans;

    
    int prevW = 0;

    for (int i = 1; i <= (int)s.size(); i++) {

        if (s[i - 1] == 'W') {
            prevW = i;
            continue;
        }

    

        int p = prevW;

    
        int d = i - 1 - p;

        if (p > 0) {


            ll answer = m + 1;

            if (other.lastW > 0) {
                answer += max(
                    0LL,
                    (ll)other.lastW + d - m
                );
            }

            ans.push_back(answer);

        } else {


            ll L = d + 1;

            if (other.wpos.empty()) {
                
                ans.push_back(1);
                continue;
            }

            ll unionSize = L + other.sumMin(L);

            ans.push_back(unionSize + 1);
        }
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int n, m;
        cin >> n >> m;

        string s, t;
        cin >> s >> t;

        Info infoS, infoT;

        infoS.build(s);
        infoT.build(t);

        vector<ll> ansS = solveReads(s, m, infoT);

        vector<ll> ansT = solveReads(t, n, infoS);

        for (int i = 0; i < (int)ansS.size(); i++) {
            if (i) cout << ' ';
            cout << ansS[i];
        }
        cout << '\n';

        for (int i = 0; i < (int)ansT.size(); i++) {
            if (i) cout << ' ';
            cout << ansT[i];
        }
        cout << '\n';
    }

    return 0;
}