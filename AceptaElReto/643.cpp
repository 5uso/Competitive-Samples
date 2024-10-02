#include <bits/stdc++.h>
using namespace std;

static int trash[200000];
static char type[200000];

static inline char fits(int k, int n, int size) {
    long long size2 = size * 2;
    int e = 0, r = 0, i, count = 0;

    for(i = 0; i < n; i++) {
        if(type[i]) {
            e += trash[i];
            if(e > size2) {
                e = trash[i];
                if(e > size2) return 0;
                r = 0;
                if(++count >= k) return 0;
            }
        } else {
            r += trash[i];
            if(r > size) {
                r = trash[i];
                if(r > size) return 0;
                e = 0;
                if(++count >= k) return 0;
            }
        }
    }

    return 1;
}

static inline int search(int k, int n, int start, int end) {
    int mid, solution;

    while(start <= end) {
        mid = (start + end) / 2;
        //cout << "Try " << mid << " (" << start << "," << end << ")? ";
        if(fits(k, n, mid)) {
            solution = mid;
            end = mid - 1;
            //cout << "yea\n";
        } else {
            start = mid + 1;
            //cout << "nah\n";
        } 
    }

    return solution;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int k, n, i, max, r, e; cin >> k >> n;
    while(k) {
        max = 0, r = 0, e = 0;
        for(i = 0; i < n; i++) {
            cin >> trash[i];
            cin >> type[i];
            type[i] = type[i] == 'E';
            if(type[i]) {
                e += trash[i];
                max = trash[i] / 2 > max ? trash[i] / 2 : max;
            } else {
                r += trash[i];
                max = trash[i] > max ? trash[i] : max;
            }
        }

        r = e / 2 + 1 > r ? e / 2 + 1 : r;
        cout << search(k, n, max, r) << "\n";
        cin >> k >> n;
    }

    return 0;
}
