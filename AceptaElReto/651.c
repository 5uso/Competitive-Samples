#include <stdio.h>

typedef struct player {
    char d, m, a;
} player;

static int playern;
static player players[25];

static inline void read_int(int * n) {
    char a; *n = 0;
    while((a = getchar_unlocked()) > 47) {
        *n *= 10;
        *n += a - 48;
    }
}

static inline void read_player(player * p) {
    char a; p->d=0;p->m=0;p->a=0;
    while((a = getchar_unlocked()) > ' ') {
        p->d |= (a == 'F');
        p->m |= (a == 'C');
        p->a |= (a == 'D');
    }
}

char solve(char i, char hd, char hm, char ha, char d, char m, char a) {
    if(d <= 0 && m <= 0 && a <= 0) return 1;
    if(d > hd || m > hm || a > ha || i >= playern) return 0;

    return (players[i].d && d && solve(i+1, hd-1, hm, ha, d-1, m, a)) ||
           (players[i].m && m && solve(i+1, hd, hm-1, ha, d, m-1, a)) ||
           (players[i].a && a && solve(i+1, hd, hm, ha-1, d, m, a-1)) ||
                                (solve(i+1, hd, hm, ha, d, m, a));
}

int main() {
    int d, m, a, i, hd, hm, ha; read_int(&d); read_int(&m); read_int(&a);
    while (d | m | a) {
        read_int(&playern);
        hd = hm = ha = 0;
        for(i = 0; i < playern; i++) {
            read_player(&players[i]);
            hd += players[i].d; hm += players[i].m; ha += players[i].a; 
        }

        fwrite(solve(0, hd, hm, ha, d, m, a) ? "SI\n" : "NO\n", 1, 3, stdout);
        read_int(&d); read_int(&m); read_int(&a);
    }
    return 0;
}
