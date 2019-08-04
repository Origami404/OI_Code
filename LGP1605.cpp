#include <cstdio>
using namespace std;
int N, M, T, sx, sy, fx, fy, ans = 0;
bool tx[100][100], map[100][100];
void dfs(int nx, int ny) {
    if ((nx <= 0 || nx > N || ny <= 0 || ny > M) || (tx[nx][ny]) || (map[nx][ny]))
        return;
    else if (nx == fx && ny == fy) {
        ans++;
        return;
    } else {
        map[nx][ny] = true;
        dfs(nx, ny + 1);
        dfs(nx, ny - 1);
        dfs(nx + 1, ny);
        dfs(nx - 1, ny);
        map[nx][ny] = false;
    }
}
int main() {
    scanf("%d %d %d", &N, &M, &T);
    scanf("%d %d %d %d", &sx, &sy, &fx, &fy);
    int ttx, tty;
    for (int i = 0; i < T; i++) {
        scanf("%d %d", &ttx, &tty);
        tx[ttx][tty] = true;
    }
    dfs(sx, sy);
    printf("%d", ans);
    return 0;
}