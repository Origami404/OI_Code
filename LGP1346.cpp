#include <cstdio>
#include <cstring>
#define MAX_N 107
using namespace std;
int g[MAX_N][MAX_N];
int main() {
    int n, a, b, k, p;
    memset(g, 0x3f, sizeof(g));
    scanf("%d %d %d", &n, &a, &b);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &k);
        if (k != 0) {
            scanf("%d", &p);
            g[i][p] = 0;
        }
        for (int j = 2; j <= k; j++) {
            scanf("%d", &p);
            g[i][p] = 1;
        }
        g[i][i] = 0;
    }
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (g[i][j] > g[i][k] + g[k][j])
                    g[i][j] = g[i][k] + g[k][j];
            }
        }
    }
    if (g[a][b] == 0x3f3f3f3f) {
        printf("-1\n");
    } else {
        printf("%d\n", g[a][b]);
    }
    
    return 0;
}