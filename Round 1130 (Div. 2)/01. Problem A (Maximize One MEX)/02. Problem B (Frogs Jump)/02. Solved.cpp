#include <bits/stdc++.h>
using namespace std;

int maxPairs(const string& s) {
    int n = s.size();
    int pairs = 0;

    for (int i = 0; i + 1 < n; ) {
        if (s[i] == 'f' && s[i + 1] == 'f') {
            pairs++;
            i += 2; 
        } else {
            i++;
        }
    }

    return pairs;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;

        string top, bottom;
        cin >> top >> bottom;

        
        int T = count(top.begin(), top.end(), 'f');
        int B = count(bottom.begin(), bottom.end(), 'f');

        
        int mxT = maxPairs(top);
        int mxB = maxPairs(bottom);

        int answer = INT_MAX;

        
        for (int x = 0; x <= mxT; x++) {
            for (int y = 0; y <= mxB; y++) {

                int remainingTop = T - 2 * x;
                int remainingBottom = B - 2 * y;

                
                int removed = abs(remainingTop - remainingBottom);

                answer = min(answer, removed);
            }
        }

        cout << answer << '\n';
    }

    return 0;
}