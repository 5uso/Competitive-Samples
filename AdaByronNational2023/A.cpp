#include <bits/stdc++.h>
using namespace std;

static int n;
static map<int, vector<int>> locks;
static vector<pair<int, int>> contradicts;

static vector<int> g[20000], gt[20000];
static bool visited[20000];
static int comp[20000];
static bool choice[10000];

vector<int> order;

static inline void add_lock(int lock, int door) {
    for(int d : locks[lock]) 
        if(door != (d ^ 1))
            contradicts.push_back({door, d});
    locks[lock].push_back(door);
}

static inline void dfs1(int v) {
    visited[v] = true;
    for(int u : g[v])
        if(!visited[u]) dfs1(u);
    order.push_back(v);
}

static inline void dfs2(int v, int cl) {
    comp[v] = cl;
    for(int u : gt[v])
        if(comp[u] == -1) dfs2(u, cl);
}

static inline bool check_2sat(int until) {
    int u2 = until * 2;
    order.clear();
    for(int i = 0; i < u2; i++) {
        g[i].clear(); gt[i].clear();
        visited[i] = false;
        comp[i] = -1;
    }

    for(int i = 0; i < contradicts.size(); i++) {
        if(contradicts[i].first >= u2 || contradicts[i].second >= u2) continue;
        int not_a = contradicts[i].first, not_b = contradicts[i].second;
        int a = not_a ^ 1, b = not_b ^ 1;
        g[not_a].push_back(b); g[not_b].push_back(a);
        gt[a].push_back(not_b); gt[b].push_back(not_a);
    }

    for(int i = 0; i < u2; i++)
        if(!visited[i]) dfs1(i);

    for(int i = 0, j = 0; i < u2; i++) {
        int v = order[u2 - i - 1];
        if(comp[v] == -1) dfs2(v, j++);
    }

    memset(choice, 0x00, until * sizeof(bool));
    for(int i = 0; i < u2; i += 2) {
        if(comp[i] == comp[i ^ 1]) return false;
        choice[i >> 1] = comp[i] > comp[i ^ 1];
    }

    return true;
}

static inline int bin_qi_ling() {
    int start = 0, end = n, mid, solution;

    while(start <= end) {
        mid = (start + end) / 2;
        if(check_2sat(mid)) {
            solution = mid;
            start = mid + 1;
        } else end = mid - 1;
    }

    return solution;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int casos, l, a;
    cin >> casos;
    while(casos--) {
        cin >> n;
        for(int i = 0; i < n; i++) {
            cin >> l; while(l--) { cin >> a; add_lock(a, i * 2); }
            cin >> l; while(l--) { cin >> a; add_lock(a, i * 2 + 1); }
        } locks.clear();

        int r = bin_qi_ling();
        check_2sat(r);

        for(int i = 0; i < r; i++) {
            cout << (choice[i] ? 'I' : 'D');
        } cout << "\n";

        contradicts.clear();
    }

    return 0;
}