#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int n; cin >> n;
    while(n--) {
        int a, b, c;
        cin >> a >> b >> c;
        vector<int> asdf;
        asdf.push_back((b - a + c) / 2);
        asdf.push_back((a - b + c) / 2);
        asdf.push_back((a + b - c) / 2);
        sort(asdf.begin(), asdf.end());
        cout << asdf[0] << " " << asdf[1] << " " << asdf[2] << "\n";
    }

    return 0;
}