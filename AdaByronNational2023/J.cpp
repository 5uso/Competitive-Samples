#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int n, m, d1, h1, m1, d2, h2, m2; char nope;
    cin >> n >> m;
    while(n || m) {
        vector<pair<int, int>> v;
        for(int i = 0; i < n; i++) {
            cin >> d1 >> h1 >> nope >> m1 >> d2 >> h2 >> nope >> m2;
            int t1 = d1 * (24*60) + h1 * 60 + m1;
            int t2 = d2 * (24*60) + h2 * 60 + m2;
            v.push_back({t1, 1});
            v.push_back({t2, -1});
        }

        sort(v.begin(), v.end());

        int result = n > 0, curr = 0;
        for(int i = 0; i < v.size() - 1; i++) {
            int prev = curr;
            curr += v[i].second;
            if(prev > 0 && curr <= 0) {
                if(v[i + 1].first - v[i].first >= m * 2) result++;
            }
        }

        cout << result << "\n";
        cin >> n >> m;
    }

    return 0;
}