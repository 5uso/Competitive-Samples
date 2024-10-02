#include <bits/stdc++.h>
using namespace std;

#define int long long

vector<int> egcd(int n, int m){
    int r0 = n, r1 = m;
    int s0 = 1, s1 = 0;
    int t0 = 0, t1 = 1;
    while(r1 != 0) {
        int q = r0 / r1;
        int r = r0 - q*r1; r0 = r1; r1 = r;
        int s = s0 - q*s1; s0 = s1; s1 = s;
        int t = t0 - q*t1; t0 = t1; t1 = t;
    }
    return { r0, s0, t0 };
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int casos, n, ex, ey, ec;
    cin >> casos;
    while(casos--) {
        cin >> n;
        int bx, by, bc, solx = -1, soly = -1;
        bool super_cuaderno_con_errores_galaxial_equisdedededede = false;
        cin >> bx >> by >> bc;
        for(int i = 1; i < n; i++) {
            cin >> ex >> ey >> ec;
            if(super_cuaderno_con_errores_galaxial_equisdedededede) continue;
            if(solx == -1) {
                int cramer1 = bx * ey - ex * by;
                int cramer2 = bc * ey - ec * by;
                int cramer3 = bx * ec - ex * bc;
                if(cramer1 == 0 && (cramer2 | cramer3) != 0) super_cuaderno_con_errores_galaxial_equisdedededede = true;
                if((cramer1 | cramer2 | cramer3) == 0) continue;
                if(cramer1 != 0) {
                    if((cramer2 % cramer1) != 0 || (cramer3 % cramer1) != 0) super_cuaderno_con_errores_galaxial_equisdedededede = true;
                    solx = cramer2 / cramer1, soly = cramer3 / cramer1;
                    if(solx < 0 || soly < 0) super_cuaderno_con_errores_galaxial_equisdedededede = true;
                }
            } else {
                if(ex * solx + ey * soly != ec) super_cuaderno_con_errores_galaxial_equisdedededede = true;
            }
        }

        if(super_cuaderno_con_errores_galaxial_equisdedededede) {
            cout << "CUADERNO CON ERRORES\n";
            continue;
        }
        
        if(solx != -1) {
            cout << solx << " " << soly << "\n";
            continue;
        }

        if(bx == 0) {
            cout << ((bc % by) == 0 ? "NO HAY SUFICIENTES DATOS\n" : "CUADERNO CON ERRORES\n");
            continue;
        }

        if(by == 0) {
            cout << ((bc % bx) == 0 ? "NO HAY SUFICIENTES DATOS\n" : "CUADERNO CON ERRORES\n");
            continue;
        }

        vector<int> dia_result = egcd(bx, by);
        int d = dia_result[0], s = dia_result[1], t = dia_result[2];
        if((bc % d) != 0) {
            cout << "CUADERNO CON ERRORES\n";
            continue;
        }

        int x0 = s * (bc / d), y0 = t * (bc / d);
        int I0 = floor(-x0 * d / by), IF = ceil(y0 * d / bx);
        int count = 0;
        for(int t = I0; t <= IF; t++) {
            if(((t * by) % d) == 0 && ((t * bx) % d) == 0) {
                int hjahax = x0 + t * by / d, hjahay = y0 - t * bx / d;
                if(hjahax >= 0 && hjahay >= 0) {
                    solx = hjahax, soly = hjahay;
                    count++;
                    if(count > 1) break;
                }
            }
        }

        if(count < 1) {
            cout << "CUADERNO CON ERRORES\n";
            continue;
        }

        if(count == 1) {
            cout << solx << " " << soly << "\n";
            continue;
        }

        cout << "NO HAY SUFICIENTES DATOS\n";
    }

    return 0;
}