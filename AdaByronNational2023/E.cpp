#include <bits/stdc++.h>
using namespace std;

static vector<long long> costs;

static long long tree[300001 * 4];

int n;

static inline long long seg_min(int a, int b) {
    a += n + 1; b += n + 1; long long s = 0x7F7F7F7F7F7F7F7F;
    while(a <= b) { 
        if(a & 1) s = min(s, tree[a++]);
        if(!(b & 1)) s = min(s, tree[b--]);
        a /= 2; b /= 2;
    }
    return s;
}

static inline void seg_set(int k, long long x) {
    k += n + 1; tree[k] = x;
    for(k /= 2; k >= 1; k /= 2) tree[k] = min(tree[2*k], tree[2*k+1]);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int m, a; cin >> m;
    while(m) {
        costs.clear(); long long prev = 0;
        n = m * 2; memset(tree, 0x7F, (n + 1) * sizeof(int) * 2);
        for(int i = 0; i < m; i++) {
            cin >> a; prev += a;
            costs.push_back(prev);
        } prev = 0;
        for(int i = 0; i < m; i++) {
            cin >> a; prev -= a;
            costs[i] += prev;
            seg_set(i, costs[i]);
        } prev = 0;
        for(int i = 0; i < m; i++) {
            costs.push_back(costs.back() + (costs[i] - prev));
            prev = costs[i];
            seg_set(i + m, costs.back());
        }

        vector<int> can;
        for(int i = 0; i < m; i++)
            if(seg_min(i, i + m - 1) >= costs[i - 1] * (i > 0))
                can.push_back(i + 1);

        bool first = true; int combo = 0, start;
        for(int i = 0; i < can.size(); i++) {
            if(i < can.size() - 1 && can[i + 1] == can[i] + 1) {
                if(!combo) start = can[i];
                combo++;
            } else {
                if(!first) cout << ",";
                if(combo) {
                    cout << start << "-" << can[i];
                    combo = 0;
                } else {
                    cout << can[i];
                }
                first = false;
            }
        }
        
        if(!can.size()) cout << "NO HAY VIAJE";
        
        cout << "\n";

        cin >> m;
    }

    return 0;
}