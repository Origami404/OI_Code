#include <cstdio>
#include <cstring>
#define MAXN 1507
using namespace std;
int n, m;
char map[MAXN][MAXN];
const int IS_VIS = 2, X_IND = 0, Y_IND = 1;
int vis[MAXN][MAXN][3];
bool succ = false;
int dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};
inline int abs_mod(int a, int n) { 
    int t = a % n;
    return t < 0 ? t + n : t;
}
void dfs(int x, int y) {
    //printf("Pass (%d, %d)\n", x, y);
    if (succ) return;
    for (int i = 0; i < 4; i++) {
        int rnx = x + dx[i], rny = y + dy[i];
        int nx = abs_mod(rnx, n), ny = abs_mod(rny, m);
        int *nvis = vis[nx][ny];
        if (nvis[IS_VIS] && (nvis[X_IND] != rnx || nvis[Y_IND] != rny)) {
            succ = true;
            //printf("Succ: (%d %d), Diff: (%d %d), (%d %d)\n", nx, ny, nvis[X_IND], nvis[Y_IND], rnx, rny);
        }
        if (!nvis[IS_VIS] && map[nx][ny] != '#') {
            nvis[IS_VIS] = true;
            nvis[X_IND] = rnx, nvis[Y_IND] = rny;
            dfs(rnx, rny);
        }
    }
}
#define CLEAR_ARR(arr) (memset(arr, 0, sizeof(arr)))
bool deal() {
    CLEAR_ARR(map), CLEAR_ARR(vis), succ = false;
    if (scanf("%d %d", &n, &m) != 2) return false;
    for (int i = 0; i < n; i++) scanf("%s", map[i]);
    for (int i = 0; !succ && i < n; i++)
        for (int j = 0; !succ && j < m; j++)
            if (!vis[i][j][2] && map[i][j] == 'S')
                dfs(i, j);
    puts(succ ? "Yes" : "No");
    return true;
}
int main() {
    while (deal());
    return 0;
}