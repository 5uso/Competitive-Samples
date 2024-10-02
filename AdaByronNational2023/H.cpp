#include <bits/stdc++.h>
using namespace std;

typedef int compt;
struct point {
    compt x, y;
    bool operator<(point const o) const {return make_pair(x, y) < make_pair(o.x, o.y);}
    bool operator==(point const o) const {return y==o.y&&x==o.x;}
    bool operator!=(point const o) const {return y!=o.y||x!=o.x;}
};
compt cross(point o, point a, point b) {
    return (a.x - o.x)*(b.y - o.y) - (a.y - o.y)*(b.x - o.x);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int casos, n, a; cin >> casos;
    while(casos--) {
        cin >> n;
        vector<point> lmao, lmaos;
        lmao.push_back({x:0, y:0}); lmaos.push_back({x:0, y:0});
        for(int i = 0; i < n; i++) {
            cin >> a; point p = {x: i, y: a};
            while(lmao.size() > 1 && cross(lmao[lmao.size() - 2], lmao.back(), p) > 0) lmao.pop_back();
            while(lmaos.size() > 1 && cross(lmaos[lmaos.size() - 2], lmaos.back(), p) >= 0) lmaos.pop_back();
            lmao.push_back(p); lmaos.push_back(p);
        }

        if(lmao.size() == 2) {
            cout << "1\n";
            continue;
        }

        int result = 0;
        for(int i = 1, k = 1; i < lmaos.size() - 1; i++) {
            int do_it = 1;
            while(lmao[k] != lmaos[i + 1]) {
                k++;
                do_it++;
            }
            result = max(result, do_it);
        }

        cout << result << "\n";
    }

    return 0;
}