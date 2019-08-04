#include <cstdio>
#define MAXN 40
using namespace std;
int n, ns;
struct Point {
    int x, y;
};
Point pos[MAXN * MAXN];
int magic[MAXN][MAXN];
inline void put_num(int k, int x, int y) {
    magic[x][y] = k;
    pos[k].x = x;
    pos[k].y = y;
}
#define getx(i) pos[i].x
#define gety(i) pos[i].y
void mk_magic() {
    put_num(1, 1, (n+1)>>1);
    for (int k = 2; k <= ns; k++) {
        int p = k - 1;
        if (getx(p) == 1 && gety(p) != n) {
            put_num(k, n, gety(p) + 1);
        } else if (getx(p) != 1 && gety(p) == n) {
            put_num(k, getx(p) - 1, 1);
        } else if (getx(p) == 1 && gety(p) == n) {
            put_num(k, getx(p) + 1, gety(p));
        } else {
            if (magic[getx(p) - 1][gety(p) + 1] == 0) {
                put_num(k, getx(p) - 1, gety(p) + 1);
            } else {
                put_num(k, getx(p) + 1, gety(p));
            }
        }
    }
}
int main() {
    scanf("%d", &n);
    ns = n * n;
    mk_magic();
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) 
            printf("%d ", magic[i][j]);
        putchar('\n');
    }
    return 0;
}