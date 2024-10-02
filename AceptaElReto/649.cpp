#include <bits/stdc++.h>
using namespace std;

struct task {
    int start, end, period;
};

static inline bool task_cmp(task a, task b) {
    return a.start > b.start;
}

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

    int n, m, t, i; cin >> n >> m >> t;
    while(!cin.eof()) {
        priority_queue<task, vector<task>, decltype(task_cmp)*> q(task_cmp);
        for(i = 0; i < n; i++) {
            task tsk;
            cin >> tsk.start >> tsk.end;
            tsk.period = 0;
            if(tsk.start < t) q.push(tsk);
        }

        for(i = 0; i < m; i++) {
            task tsk;
            cin >> tsk.start >> tsk.end >> tsk.period;
            if(tsk.start < t) q.push(tsk);
        }

        bool conflict = false; int curr = -1;
        while(!q.empty() && !conflict) {
            task tsk = q.top(); q.pop();
            if(tsk.start < curr) conflict = true;
            curr = max(curr, tsk.end);
            //printf("%d %d %d\n", tsk.start, tsk.end, tsk.period);
            if(tsk.period) {
                tsk.start += tsk.period;
                tsk.end += tsk.period;
                if(tsk.start < t) q.push(tsk);
            }
        }
        fwrite(conflict ? "SI\n" : "NO\n", 1, 3, stdout);

        cin >> n >> m >> t;
    }

    return 0;
}
