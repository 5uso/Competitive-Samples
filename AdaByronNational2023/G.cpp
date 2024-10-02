#include <bits/stdc++.h>
using namespace std;

int h, w;

static int board[30][30];
static bool visited[30][30];
static int currsum;

void traverse(int y, int x) {
    visited[y][x] = true;
    currsum += board[y][x];
    int get_max = 0, dy = 0, dx = 0;
    if(y > 0 && !visited[y-1][x] && board[y-1][x] > get_max) {
        get_max = board[y-1][x]; dy = -1; dx = 0;
    }
    if(x < w-1 && !visited[y][x+1] && board[y][x+1] > get_max) {
        get_max = board[y][x+1]; dy = 0; dx = 1;
    }
    if(y < h-1 && !visited[y+1][x] && board[y+1][x] > get_max) {
        get_max = board[y+1][x]; dy = 1; dx = 0;
    }
    if(x > 0 && !visited[y][x-1] && board[y][x-1] > get_max) {
        get_max = board[y][x-1]; dy = 0; dx = -1;
    }

    if(get_max > 0) {
        traverse(y + dy, x + dx);
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int n, a, b;
    cin >>n;
    while(n--) {
        cin >> h >> w;
        for(int i = 0; i < h ; i++) {
            for(int j = 0; j < w; j++) {
                cin >> a;
                board[i][j] = a;
            }
        }

        int maxi = 0;
        for(int i = 0; i < h ; i++) {
            for(int j = 0; j < w; j++) {
                currsum = 0;
                memset(visited, 0x00, sizeof(visited));
                traverse(i, j);
                maxi = max(maxi, currsum);
            }
        }

        cout << maxi << "\n";
    }

    return 0;
}