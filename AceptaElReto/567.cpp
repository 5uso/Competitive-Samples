#include <bits/stdc++.h>
using namespace std;

typedef struct info {
    int val, comp;
} info;

static int s, n, m, a, b, c, comp;

static set<pair<int, int>> gottem;
static vector<pair<int, int>> g[4001];
static info perf[4001];

static char visited[4001];
#define SOLVED 27
#define PRECOMP 11

static inline void propagate(int u, int val) {
    perf[u] = { .val = val, .comp = 0 };
    visited[u] = SOLVED;
    for(auto p : g[u])
        if(visited[p.first] != SOLVED) propagate(p.first, p.second - val);
}

static inline void compute(int u, int val, char sign) {
    perf[u] = { .val = val, .comp = comp * sign };
    visited[u] = PRECOMP;
    for(auto p : g[u]) {
        if(!visited[p.first]) compute(p.first, val + p.second * sign, -sign);
        else if(visited[p.first] == PRECOMP && perf[p.first].comp == perf[u].comp) propagate(comp, (val + p.second * sign + perf[p.first].val) / 2);
    }
}

static inline void add_edge(int u, int v, int w) {
    g[u].push_back({v, w}); g[v].push_back({u, w});
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    cin >> s >> n >> m;
    while(s) {
        memset(visited, 0x00, (s + 1) * sizeof(char));
        for(int i = 0; i < n; i++) {
            cin >> a;
            if(a == 1) {
                cin >> a >> b;
                gottem.insert({a, b});
            } else {
                cin >> a >> b >> c;
                add_edge(a, b, c);
            }
        }

        for(auto p : gottem)
            if(visited[p.first] != SOLVED) propagate(p.first, p.second);
        gottem.clear();

        for(comp = 1; comp <= s; comp++) {
            if(visited[comp]) continue;
            compute(comp, 0, 1);
        }

        for(int i = 1; i <= s; i++) g[i].clear();

        for(int i = 0; i < m; i++) {
            cin >> a;
            if(a == 1) {
                cin >> a;
                if(perf[a].comp) cout << "CUIDADO\n";
                else cout << perf[a].val << "\n";
            } else {
                cin >> a >> b;
                if(perf[a].comp != -perf[b].comp) cout << "CUIDADO\n";
                else if(!perf[a].comp) cout << perf[a].val + perf[b].val << "\n";
                else cout << abs(perf[a].val - perf[b].val) << "\n";
            }
        }
        cout << "---\n";
        cin >> s >> n >> m;
    }

    return 0;
}
