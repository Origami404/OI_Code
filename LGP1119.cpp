#include <cstdio>
#include <cstring>
#include <cctype>
#define MAX_N 207
int g[MAX_N][MAX_N];
int d[MAX_N][MAX_N];
int latest[MAX_N];
int fsrd() {
    int p = 0; int c = getchar();
    while(!isdigit(c)) c = getchar();
    while(isdigit(c)) {
        p = p*10 + (c-'0'); c = getchar();
    }
    return p;
}
int main() {
    int n, m, u, v, w, t;
    n = fsrd(), m = fsrd();
    for (int i = 0; i < n; i++)
        latest[i] = fsrd();
    memset(d, 0x3f, sizeof(d));
    for (int i = 0; i < n; i++) 
        d[i][i] = 0;
    for (int i = 1; i <= m; i++) {
        u = fsrd(), v = fsrd(), w = fsrd();
        d[u][v] = d[v][u] = w;
    }
    
    int q = fsrd(), k = 0;
    for (int i = 1; i <= q; i++) {
        u = fsrd(), v = fsrd(), t = fsrd();
        while (k < n && latest[k] <= t) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (d[i][j] > d[i][k] + d[k][j]) {
                        d[i][j] = d[i][k] + d[k][j];
                    }
                }
            }
            k += 1;
        }
        if (latest[u] > t || latest[v] > t || d[u][v] == 0x3f3f3f3f) {
            printf("-1\n");
        } else {
            printf("%d\n", d[u][v]);
        }
    }
    return 0;
}