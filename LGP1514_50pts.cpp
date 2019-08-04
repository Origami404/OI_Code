#include <cstdio>
#include <cstring>
#include <queue>
#define MAXN 507
#define MAXM 507
using namespace std;
int att[MAXN][MAXM], n, m;

int count = 0;
bool vis[MAXN][MAXM];
struct Point { int x, y; };
queue<Point> q;
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};
void bfs(int start) {
    vis[n][start] = true;
    q.push((Point) {n, start});
    while (!q.empty()) {
        int x = q.front().x, y = q.front().y;
        int natt = att[x][y];
        q.pop();
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            if (1 <= nx && nx <= n && 1 <= ny && ny <= m) {
                if (!vis[nx][ny] && natt < att[nx][ny]) {
                    vis[nx][ny] = true;
                    q.push((Point) {nx, ny});
                }
            }
        }
    }
}
int now_min = 1000;
bool fail = false;
int could_offer[MAXM][MAXN];
bool dvis[MAXM];
void dfs(int now, int cnt) {
    if (cnt > now_min || fail) return;
    if (now > m) {
        if (now_min > cnt) now_min = cnt;
        return;
    }
    int ts = could_offer[now][0];
    if (ts == 0) {
        fail = true;
        return;
    }
    for (int i = 1; i <= ts; i++) {
        int nof = could_offer[now][i];
        if (dvis[nof]) {
            dfs(now + 1, cnt);
        }
        dvis[nof] = true;
        dfs(now + 1, cnt + 1);
        dvis[nof] = false;
    }
}
inline void deal() {
    for (int x = 1; x <= m; x++) {
        memset(vis, 0, sizeof(vis));
        bfs(x);
        for (int i = 1; i <= m; i++) {
            if (vis[1][i]) could_offer[x][++(could_offer[x][0])] = i;
        }
    }
    dfs(1, 0);
    if (fail) {
        int cnt = 0;
        for (int i = 1; i <= m; i++) cnt += !(could_offer[i][0]);
        printf("0\n%d\n", cnt);
    } else {
        printf("1\n%d\n", now_min);
    }
}
inline int fsrd() {
    int p = 0, c = getchar();
    while (c < '0' || '9' < c) c = getchar();
    while ('0' <= c && c <= '9') {
        p = p*10 + (c-'0');
        c = getchar();
    }
    return p;
}
inline void input() {
    n = fsrd(), m = fsrd();
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            att[i][j] = fsrd();
}
int main() {
    input();
    deal();
    return 0;
}
