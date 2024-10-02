#include <bits/stdc++.h>
using namespace std;

static int fellas[300000];
static int aux[300000];

static inline long long merge(int left, int mid, int right) {
    int i = left, j = mid, k = left;
    long long result = 0;
    while(i <= mid - 1 && j <= right) {
        if(fellas[i] <= fellas[j]) aux[k++] = fellas[i++];
        else {
            aux[k++] = fellas[j++];
            result += mid - i;
        }
    }

    while(i <= mid - 1) aux[k++] = fellas[i++];
    while(j <= right) aux[k++] = fellas[j++];
    for(i = left; i <= right; i++) fellas[i] = aux[i];
  
    return result;
}

static inline long long count_rev(int left, int right) {
    long long result = 0;
    if(right > left) {
        int mid = (right + left) / 2;
        result += count_rev(left, mid);
        result += count_rev(mid + 1, right);
        result += merge(left, mid + 1, right);
    }

    return result;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int n, t, a; cin >> n >> t;
    while(n) {
        for(int i = 0; i < n; i++) {
            cin >> a;
            fellas[i] = a + t * i;
        }

        cout << count_rev(0, n - 1) << "\n";
        cin >> n >> t;
    }
    
    return 0;
}
