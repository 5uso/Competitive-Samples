#include <bits/stdc++.h>
using namespace std;

static char cards_len = 0;
static int cards[15];

static char selected_len = 0;
static int selected[15];

static inline int cost(int * c, int len) {
    if(len == 1) return *c;
    priority_queue<int, vector<int>, greater<int>> q;
    int r = 0;
    for(int i = 0; i < len; i++) q.push(c[i]);
    while(q.size() > 1) {
        int a = q.top(); q.pop();
        a += q.top(); q.pop();
        r += a;
        q.push(a);
    }
    return r;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int m, n, a, j, maxi;
    cin >> m >> n;
    while(m) {
        cards_len = 0;
        for(int i = 0; i < n; i++) {
            cin >> a;
            cards[cards_len++] = a;
        }

        sort(&cards[0], &cards[cards_len]);

        maxi = 0;
        for(int i = 1; i < (1 << n); i++) {
            selected_len = 0;
            int damage = 0;
            for(a = i, j = 0; a; a >>= 1, j++)
                if(a & 1) {
                    damage += cards[j];
                    selected[selected_len++] = cards[j];
                }
            if(damage > maxi && damage <= m && cost(&selected[0], selected_len) <= m) maxi = damage;
        }

        cout << maxi << "\n";
        cin >> m >> n;
    }

    return 0;
}
