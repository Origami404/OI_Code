#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
int map[55][55], n, m, sx, sy, tx, ty, sdir, minl = 0x3fffffff;
bool vis[55][55][10];
int fwd[4][2] = {{1, 0}, {0, -1}, {-1, 0}, {0, 1}};  // E S W N
struct Node {
    int x, y, d, c, cnt;
};
queue<Node> q;
// enum dir { E = 0, S = 1, W = 2, N = 3 };
// enum ctrl { Creep = 0, Walk = 1, Run = 2, Left = 3, Right = 4 };
inline void push_all_ctrl(int x, int y, int d, int cnt) {
    for (int i = 0; i <= 4; i++)
        q.push((Node){x, y, d, i, cnt});
}
void bfs(int nx, int ny, int nd) {
    if (nx <= 0 || ny <= 0 || nx >= n || ny >= m || map[nx][ny])
        return;
    if (nx == tx && ny == ty)
        minl = 0;
    // vis[nx][ny] = true;
    push_all_ctrl(nx, ny, nd, 0);
    while (!q.empty()) {
        Node now = q.front();
        q.pop();
        int& nc = now.c;
        if (now.x > 0 && now.y > 0 && now.x < n && now.y < m &&
            !map[now.x][now.y] && now.cnt <= minl &&
            (now.cnt <= vis[now.x][now.y][now.c])) {
            vis[now.x][now.y][now.c] = now.cnt;
            printf("DEBUG(catch )(cnt, x, y, d, c): %d %d %d %d %d\n", now.cnt,
                   now.x, now.y, now.d, now.c);
            // printf("DEBUG(q.size()): %d\n", q.size());
            if (now.c == 0 || now.c == 1 || now.c == 2) {
               // printf("DEBUG(c in if): %d", now.c);
                int nnx = now.x + fwd[now.d][0] * (nc + 1),
                    nny = now.y + fwd[now.d][1] * (nc + 1);
                push_all_ctrl(nnx, nny, now.d, now.cnt + 1);
                // vis[nnx][nny] = true;
            } else if (now.c == 3) {
                push_all_ctrl(now.x, now.y, (now.d + 3) % 4, now.cnt + 1);
                //printf("DEBUG(nc == 3 of d):%d\n", (now.d + 3) % 4, now.cnt + 1);
            }

            else if (now.c == 4)
                push_all_ctrl(now.x, now.y, (now.d + 1) % 4, now.cnt + 1);
        } else if (now.x == tx && now.y == ty) {
            printf("DEBUG(accept)(cnt, x, y, d, c): %d %d %d %d %d\n", now.cnt,
                   now.x, now.y, now.d, now.c);
            minl = minl > now.cnt ? now.cnt : minl;
        } else {
            printf("DEBUG(skip  )(cnt, x, y, d, c): %d %d %d %d %d\n", now.cnt, now.x,
                   now.y, now.d, now.c);
        }
    }
}
int main() {
    // freopen("LGP1126.out", "w", stdout);
    memset(vis, 0x3f,sizeof(vis));
    int dxy[2][4] = {{0, 0, 1, 1}, {0, 1, 0, 1}};
    scanf("%d %d", &n, &m);
    int tmp;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &tmp);
            for (int k = 0; k < 4; k++)
                map[i + dxy[0][k]][j + dxy[1][k]] = tmp;
        }
    }
    char dir_str[10];
    scanf("%d %d %d %d %s", &sx, &sy, &tx, &ty, dir_str);
    printf("DEBUG(dir): %c\n", dir_str[0]);
    switch (dir_str[0]) {
        case 'E':
            bfs(sx, sy, 0);
            break;
        case 'S':
            bfs(sx, sy, 1);
            break;
        case 'W':
            bfs(sx, sy, 2);
            break;
        case 'N':
            bfs(sx, sy, 3);
            break;
        default:
            break;
    }
    printf("%d\n", minl == 0x3fffffff ? -1 : minl);
    return 0;
}
