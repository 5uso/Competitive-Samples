#include <bits/stdc++.h>
using namespace std;

static inline void read_int(int * n) {
    char a; *n = 0;
    while((a = getchar_unlocked()) > 47) {
        *n *= 10;
        *n += a - 48;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casos, n, s, p, k, i; read_int(&casos);
    for(; casos > 0; casos--) {
        read_int(&n); read_int(&s); read_int(&p); read_int(&k);
        queue<char> q;
        bool stark = true, peter = true;
        for(i = 1; i <= n; i++) q.push(i == s ? 'S' : (i == p ? 'P' : '.'));
        
        while(q.size() > n / 2 && (stark || peter)) {
            for(i = 0; i < k; i++) {
                q.push(q.front());
                q.pop();
            }
            stark &= q.front() != 'S';
            peter &= q.front() != 'P';
            q.pop();
        }

        if(stark && !peter) fwrite("No quiero irme, Sr. Stark!\n", 1, 27, stdout);
        else if(!stark && peter) fwrite("No quiero irme, Peter!\n", 1, 23, stdout);
        else fwrite("No hay abrazo\n", 1, 14, stdout);
    }

    return 0;
}
