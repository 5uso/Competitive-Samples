#include <bits/stdc++.h>
using namespace std;

typedef struct subset {int parent, rank; long long points;} subset;

static subset s[200001];

static inline int find(int i) {
    while(i != s[i].parent) i = s[i].parent;
    return i;
}

static inline void unionn(int xroot, int yroot) {
    if(s[xroot].rank < s[yroot].rank) {
        s[xroot].parent = yroot;
        s[xroot].points -= s[yroot].points;
    }
    else if(s[xroot].rank > s[yroot].rank) {
        s[yroot].parent = xroot;
        s[yroot].points -= s[xroot].points;
    }
    else {
        s[yroot].parent = xroot; s[xroot].rank++;
        s[yroot].points -= s[xroot].points;
    }
}

static inline long long get_points(int lmaoi) {
    long long sum = 0;
    while(lmaoi != s[lmaoi].parent) {
        sum += s[lmaoi].points;
        lmaoi = s[lmaoi].parent;
    }
    return sum + s[lmaoi].points;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int casos, n, m, a, b, repr, repra, reprb; cin >> casos; char act;
    while(casos--) {
        cin >> n >> m;

        for(int i = 1; i <= n ; i++) {
            s[i].parent = i;
            s[i].rank = 0;
            s[i].points = 0;
        }

        while(m--) {
            cin >> act;
            switch (act) {
                case 'S':
                    cin >> a >> b;
                    repr = find(a);
                    s[repr].points += b;
                    break;
                case 'U':
                    cin >> a >> b;
                    repra = find(a), reprb = find(b);
                    if(repra != reprb) unionn(repra, reprb);
                    break;
                case 'P':
                    cin >> a;
                    cout << get_points(a) << "\n";
                    break;
            }
        }
        cout << "---\n";
    }

    return 0;
}