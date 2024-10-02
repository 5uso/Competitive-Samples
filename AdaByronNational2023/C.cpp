#include <bits/stdc++.h>
using namespace std;

static int n;
static int counts[25];
static vector<int> wapos;

static inline bool query(int a, int b) {
    cout << "? " << a << " " << b << endl;
    string s; cin >> s;
    return s == "WA";
}

static inline bool chaos() {
    wapos.clear();
    memset(counts, 0x00, sizeof(counts));

    queue<pair<pair<int, int>, int>> q;
    q.push({{1, n}, 0});

    while(!q.empty()) {
        pair<pair<int, int>, int> p = q.front(); q.pop();
        int a = p.first.first, b = p.first.second, level = p.second;
        
        if(a == b) {
            if(query(a, b)) {
                wapos.push_back(a);
                counts[level]++;
                if(counts[level] >= 4) return true;
            }
            continue;
        }

        int mid = (a + b) / 2;
        if(query(a, mid)) {
            q.push({{a, mid}, level + 1});
            counts[level]++;
            if(counts[level] >= 4) return true;
        }
        if(query(mid + 1, b)) {
            q.push({{mid + 1, b}, level + 1});
            counts[level]++;
            if(counts[level] >= 4) return true;
        }
    }

    return false;
}

int main() {
    cin >> n;
    while(n) {
        if(!query(1, n)) {
            cout << "Veredicto: AC" << endl;
            cin >> n;
            continue;
        }

        if(chaos()) {
            cout << "Veredicto: WA" << endl;
            cin >> n;
            continue;
        }

        sort(wapos.begin(), wapos.end());

        if(wapos.size() == 3) cout << "Veredicto: WA en " << wapos[0] << " " << wapos[1] << " " << wapos[2] << endl;
        if(wapos.size() == 2) cout << "Veredicto: WA en " << wapos[0] << " " << wapos[1] << endl;
        if(wapos.size() == 1) cout << "Veredicto: WA en " << wapos[0] << endl;

        cin >> n;
    }
    
    return 0;
}