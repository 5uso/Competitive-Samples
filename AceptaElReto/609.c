#include <string.h>
#include <stdio.h>

static int x_axis[100001];
static int y_axis[100001];

static inline void read_int(int * n) {
    char a; *n = 0;
    while((a = getchar_unlocked()) > 47) {
        *n *= 10;
        *n += a - 48;
    }
}

static char number[15];
static inline void write_int(int n, char end) {
    number[13] = '0';
    number[14] = end;
    int i = 13;
    for(; n > 0; n /= 10) {
        number[i] = (n % 10) + 48;
        i--;
    }
    i += i < 13;
    fwrite(number + i, 1, 15 - i, stdout);
}

int main() {
    int n, t, i, x, y, a, b; read_int(&n); read_int(&t);
    while(n) {
        memset(x_axis, 0x00, n*sizeof(int)+1);
        memset(y_axis, 0x00, n*sizeof(int)+1);
        for(i = 0; i < t; i++) {
            read_int(&a);
            y_axis[a]++;
            read_int(&a);
            x_axis[a]++;
        }

        a = 0; b = t;
        for(x = 0; x <= n && a < b; x++) {
            a += x_axis[x];
            b -= x_axis[x];
        }
        x--;

        a = 0; b = t;
        for(y = 0; y <= n && a < b; y++) {
            a += y_axis[y];
            b -= y_axis[y];
        }
        y--;

        write_int(y, ' ');
        write_int(x, '\n');
        read_int(&n); read_int(&t);
    }
}
