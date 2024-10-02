#include <stdlib.h>
#include <stdio.h>

static inline void read_int(long long * n) {
    char a; *n = 0;
    while((a = getchar_unlocked()) > 47) {
        *n *= 10;
        *n += a - 48;
    }
}

static inline void read_sint(long long * n) {
    char a = getchar_unlocked();
    char neg = a == '-';
    if(neg) a = getchar_unlocked();
    
    *n = a - 48;
    while((a = getchar_unlocked()) > 47) {
        *n *= 10;
        *n += a - 48;
    }
    if(neg) *n *= -1;
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
    long long r, r2, x, y, dist2, sol; read_int(&r);

    while(r) {
        read_sint(&x); read_sint(&y);

        sol = 0;
        for(; r; r /= 2) {
            r2 = r*r;
            dist2 = x*x + y*y;
            if(dist2 <= r2) sol++;
            if(abs(x) == abs(y)) break;
            if(abs(x) < abs(y)) y += r*(y > 0 ? -1 : 1);
            else x += r*(x > 0 ? -1 : 1);
        }

        write_int(sol);
        read_int(&r);
    }

    return 0;
}
