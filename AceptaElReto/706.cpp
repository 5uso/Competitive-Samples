#include <bits/stdc++.h>
using namespace std;

struct phash {
    size_t operator () (const pair<int,int> &p) const {
        return (p.first << 16) | p.second;  
    }
};

unordered_multiset<pair<int, int>, phash> g[10001];
vector<pair<pair<int, int>, int>> edges;

static inline void dijkstra(int start, vector<int> &dist) {
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> q;
    q.push({0, start}); dist[start] = 0;
    while(not q.empty()) {
        int priority = q.top().first, u = q.top().second; q.pop();
        if(priority != dist[u]) continue;
        for(pair<int,int> p : g[u]) {
            int v = p.first, w = p.second;
            if(dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w; q.push({dist[v], v});
            }
        }
    }
}

static inline void add_edge(int a, int b, int w) {
    g[a].insert({b, w}); g[b].insert({a, w});
    edges.push_back({{a, b}, w});
}

static inline void remove_edge(int a, int b, int w) {
    g[a].erase({b, w}); g[b].erase({a, w});
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    int ni, nc;
    while(cin >> ni >> nc) {
        edges.clear();
        for(int i = 0; i < nc; i++) {
            int a, b, c;
            cin >> a >> b >> c;
            add_edge(a, b, c);
        }

        vector<int> dist1, dist2; dist1.resize(ni +  1, 1e9); dist2.resize(ni + 1, 1e9);
        dijkstra(1, dist1); dijkstra(ni, dist2);
        int optimal = dist1[ni];
        for(auto p : edges) {
            int a = p.first.first, b = p.first.second, c = p.second;
            if((dist1[a] + c + dist2[b] == optimal) || (dist1[b] + c + dist2[a] == optimal)) remove_edge(a, b, c);
        }
        dist1.clear(); dist1.resize(ni +  1, 1e9);
        dijkstra(1, dist1);
        if(dist1[ni] < 1e9) cout << dist1[ni] << "\n";
        else cout << "IMPOSIBLE\n";

        for(int i = 0; i <= ni; i++) g[i].clear();
    }

    return 0;
}
