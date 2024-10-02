#include <bits/stdc++.h>
using namespace std;

static string t;
vector<string> dict;

bool str_cmp(string a, string b){
    return a.length() < b.length();
}

long long dp[1000];
long long solve(short pos) {
    int i;
    if(pos >= t.length()) return 1;
    if(dp[pos] == -1) {
        dp[pos] = 0;
        string cmp = "";
        i = 0;
        for(string s : dict) {
            if(pos + s.size() > t.length()) break;
            for(; i < s.length(); i++) cmp += t[pos+i];
            if(s == cmp) {
                dp[pos] += solve(pos + s.length());
                dp[pos] %= 1000000007;
            }
        }
    }
    return dp[pos];
}

static char number[15] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '\n' };
static inline void write_int(long long n) {
    number[13] = '0';
    int i = 13;
    for(; n > 0; n /= 10) {
        number[i] = (n % 10) + 48;
        i--;
    }
    i += i < 13;
    fwrite(number + i, 1, 15 - i, stdout);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    int n, i; cin >> n;
    while(n) {
        dict.clear();
        dict.push_back("0");
        for(i = 0; i < n; i++) {
            cin >> t;
            dict.push_back(t);
        }
        cin >> t;
        sort(dict.begin(), dict.end(), str_cmp);

        memset(dp, 0xFF, t.length()*sizeof(long long));
        write_int(solve(0));

        cin >> n;
    }

    return 0;
}
