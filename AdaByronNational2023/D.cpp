#include <bits/stdc++.h>
using namespace std;

char wow;

unordered_set<int> lmaoX;
unordered_set<int> lmaoO;
unordered_set<int> winX;
unordered_set<int> winO;
unordered_set<int> draw;

static inline int place_simu(char turn, int pos, int state) {
    return state | (1 << (((turn == 'O') ? 0 : 16) + pos));
}

static inline char is_there_win(vector<char> v) {
    if((v[0] == 'X' && v[1] == 'X' && v[2] == 'X') ||
       (v[3] == 'X' && v[4] == 'X' && v[5] == 'X') ||
       (v[6] == 'X' && v[7] == 'X' && v[8] == 'X') ||
       (v[0] == 'X' && v[3] == 'X' && v[6] == 'X') ||
       (v[1] == 'X' && v[4] == 'X' && v[7] == 'X') ||
       (v[2] == 'X' && v[5] == 'X' && v[8] == 'X') ||
       (v[0] == 'X' && v[4] == 'X' && v[8] == 'X') ||
       (v[6] == 'X' && v[4] == 'X' && v[2] == 'X')) return 'X';

    if((v[0] == 'O' && v[1] == 'O' && v[2] == 'O') ||
       (v[3] == 'O' && v[4] == 'O' && v[5] == 'O') ||
       (v[6] == 'O' && v[7] == 'O' && v[8] == 'O') ||
       (v[0] == 'O' && v[3] == 'O' && v[6] == 'O') ||
       (v[1] == 'O' && v[4] == 'O' && v[7] == 'O') ||
       (v[2] == 'O' && v[5] == 'O' && v[8] == 'O') ||
       (v[0] == 'O' && v[4] == 'O' && v[8] == 'O') ||
       (v[6] == 'O' && v[4] == 'O' && v[2] == 'O')) return 'O';

    return 0;
}

static inline void calculame_esta(vector<char> b, int state, char turn) {
    if(wow == 'X') lmaoX.insert(state);
    else lmaoO.insert(state);

    char w = is_there_win(b);
    if(w) {
        if(w == 'X') winX.insert(state);
        else if(w == 'O') winO.insert(state);
        return;
    }

    int cnt = 0;
    for(int i = 0; i < b.size(); i++) {
        if(b[i] == '.') {
            vector<char> b_cpy = b;
            b_cpy[i] = turn;
            calculame_esta(b_cpy, place_simu(turn, i, state), turn == 'X' ? 'O' : 'X');

            cnt++;
        }
    }

    if(!cnt) draw.insert(state);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    vector<char> b = { '.', '.', '.', '.', '.', '.', '.', '.', '.' };
    wow = 'X'; calculame_esta(b, 0, 'X');
    wow = 'O'; calculame_esta(b, 0, 'O');

    int n; char start, a; cin >> n; int cx, co;
    while(n--) {
        cin >> start;
        int state = 0;
        cx = co = 0;
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                cin >> a;
                if(a == 'X' || a == 'O') state = place_simu(a, i * 3 + j, state);
                if(a == 'X') cx++;
                if(a == 'O') co++;
            }
        }

        if(start == 'X' && !lmaoX.count(state)) {
            cout << "IMPOSIBLE\n";
            continue;
        }

        if(start == 'O' && !lmaoO.count(state)) {
            cout << "IMPOSIBLE\n";
            continue;
        }

        if(winX.count(state)) {
            cout << "GANA X\n";
            continue;
        }

        if(winO.count(state)) {
            cout << "GANA O\n";
            continue;
        }

        if(draw.count(state)) {
            cout << "EMPATE\n";
            continue;
        }

        if(cx == co) {
            cout << "SIGUE " << start << "\n";
            continue;
        }

        if(cx < co) {
            cout << "SIGUE X\n";
            continue;
        }

        if(co < cx) {
            cout << "SIGUE O\n";
            continue;
        }
    }

    return 0;
}