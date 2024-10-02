#include <bits/stdc++.h>
using namespace std;

int casos, c, t, n;
static int values[101];
static int costs[101];
static int DP[501][501];

vector<pair<int, int>> g[101];

static inline void add_edge(int a, int b, int w) {
    g[a].push_back({b, w}); g[b].push_back({a, w});
}

static inline void dijkstra() {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
    q.push({0, 0}); costs[0] = 0;
    while(!q.empty()) {
        int priority = q.top().first, u = q.top().second; q.pop();
        if(priority != costs[u]) continue;
        for(auto p : g[u]) {
            int v = p.first, w = p.second;
            if(costs[u] + w < costs[v]) {
                costs[v] = costs[u] + w;
                q.push({costs[v], v});
            }
        }
    }
}

int knapsack(int a) {
    memset(DP, 0x00, sizeof(DP)); int i, w1, w2;
    for(i = 0; i < a; i++) {
        for(w1 = t; w1 >= 0; w1--) {
            for(w2 = t; w2 >= 0; w2--) {
                if(costs[i] <= w1) {
                    DP[w1][w2] = max(DP[w1][w2], DP[w1 - costs[i]][w2] + values[i]);
                }
                if(costs[i] <= w2) {
                    DP[w1][w2] = max(DP[w1][w2], DP[w1][w2 - costs[i]] + values[i]);
                }
            }
        }
    }

    return DP[t][t];
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int a, x, y, z; cin >> casos;
    while(casos--) {
        cin >> a >> c >> t >> n;
        memset(values, 0x00, sizeof(values));
        for(int i = 0; i < a + 1; i++) costs[i] = 1e9;

        for(int i = 0; i < n; i++) {
            cin >> x >> y;
            values[x] = y;
        }
        for(int i = 0; i < c; i++) {
            cin >> x >> y >> z;
            add_edge(x, y, z);
        }

        dijkstra();

        for(int i = 0; i < a + 1; i++) costs[i] *= 2;

        cout << knapsack(a + 1) << "\n";

        for(int i = 0; i < a + 1; i++) g[i].clear();
    }

    return 0;
}