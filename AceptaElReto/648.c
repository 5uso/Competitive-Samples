#include <string.h>
#include <stdio.h>

static short values[50];
static short table[51*501];

static inline void read_int(short * n) {
    char a; *n = 0;
    while((a = getchar_unlocked()) > 47) {
        *n *= 10;
        *n += a - 48;
    }
}

static char number[15];
static inline void write_int(short n) {
    number[13] = '0';
    int i = 13;
    for(; n > 0; n /= 10) {
        number[i] = (n % 10) + 48;
        i--;
    }
    i += i < 13;
    fwrite(number + i, 1, 14 - i, stdout);
}

static inline short dp(short n, short s) {
    short i, j; s++; n++;
    memset(table, 0x7F, s*n*sizeof(short));
    table[0] = table[n] = 0;

    for(i = values[0], j = 0; i < n; i += values[0]) table[i + n] = ++j;
    for(j = 2; j < s; j++) {
        short value = values[j-1];
        short off = j*n;
        memcpy(table + off, table + (j-1)*n, n*sizeof(short));
        for(i = value; i < n; i++) {
            short off2 = off + i;
            short a = table[off2 - value] + 1;
            if(a < table[off2]) table[off2] = a;
        }
    }

    s--; n--;
    return table[s*(n+1) + n];
}

static inline void trace(short n, short s) {
    short x = n, y = s;
    n++;

    while(x) {
        if(values[y-1] <= x && table[y*n + x - values[y-1]] == table[y*n + x] - 1) {
            putchar_unlocked(' ');
            write_int(values[y-1]);
            x -= values[y-1];
        } else y--;
    }
}

int main() {
    short n, s, i, ii; read_int(&n); read_int(&s);
    while(n) {
        ii = s;
        for(i = 0; i < s; i++) {
            read_int(&values[i]);
            if(ii == s && values[i] > n) ii = i;
        }
        s = ii;

        short sol = dp(n, s);
        if(sol == 32639) fwrite("Imposible\n", 1, 10, stdout);
        else {
            write_int(sol);
            putchar_unlocked(':');
            trace(n, s);
            putchar_unlocked('\n');
        }

        read_int(&n); read_int(&s);
    }

    return 0;
}
