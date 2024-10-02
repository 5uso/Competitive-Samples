#include <bits/stdc++.h>
using namespace std;

vector<pair<int,int>> graph[10000];
static long long times[10000];
static int parent[10000];
static long long max_cost;
static int max_cost_state;

static inline void trace(int n, long long cost, int from) {
    if(cost <= times[n]) {
        if(cost == times[n] && from < parent[n]) parent[n] = from;
        return;
    }
    if(cost > max_cost || (cost == max_cost && n < max_cost_state)) {
        max_cost = cost; max_cost_state = n;
    }
    parent[n] = from;
    times[n] = cost;
    for(pair<int,int> u : graph[n]) trace(u.first, cost + u.second, n);
}

int main() {
    ios_base::sync_with_stdio(0);cin.tie(0);
    int e,t,i,a,b,c;cin>>e>>t;
    while(e){
        memset(times, 0xFF, e*sizeof(long long));
        unordered_set<int> final_states;
        for(i=0;i<e;i++) {
            final_states.insert(i);
            graph[i].clear();
        }

        for(i=0;i<t;i++){
            cin>>a>>b>>c;a--;b--;
            graph[b].push_back(make_pair(a,c));
            final_states.erase(a);
        }

        max_cost_state = max_cost = -1;
        for(int end : final_states) {
            parent[end] = -1;
            trace(end, 0, -1);
        }
        printf("%lld\n", max_cost);
        for(; parent[max_cost_state] != -1; max_cost_state = parent[max_cost_state]) printf("%d ",max_cost_state+1);
        printf("%d\n",max_cost_state+1);
        
        cin>>e>>t;
    }

    return 0;
}
