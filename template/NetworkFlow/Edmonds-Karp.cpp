#include <cstdio>
#include <queue>
#include <cstring>
using namespace std;
#define INF 0x3f3f3f3f
#define MAXN 2007
// g[u][v] 表示边<u, v>的在容量限制下还能增加多少流量
// flow[i] 表示f(s, i), 即原点到i的最多能增加的流量
int g[MAXN][MAXN], flow[MAXN], max_flow = 0;
int s, t, n, m;

// pre[i] 记录当前路径上点i的前驱
int pre[MAXN];


int bfs() {
    // pre的-1可以用于标识哪些点没有被遍历过
    memset(pre, -1, sizeof(pre));
    queue<int> q;

    // s是路径的起点, 前驱为0
    pre[s] = 0; q.push(s); flow[s] = INF;
    while (!q.empty()) {
        int x = q.front(); q.pop();
        if (x == t) break;
        for (int i = 1; i <= n; i++) {
            if (g[x][i] > 0 && pre[i] == -1) {
                pre[i] = x;
                flow[i] = min(flow[x], g[x][i]);
                q.push(i);
            }
        }
    }
    if (pre[t] == -1) return -1;
    else return flow[t];
}
void EK() {
    int cfp = 0;
    while ((cfp = bfs()) != -1) {
        for (int k = t; k != s; k = pre[k]) {
            g[pre[k]][k] -= cfp;
            g[k][pre[k]] += cfp;
        }
        max_flow += cfp;
    }
}
int main() {
    scanf("%d %d %d %d", &n, &m, &s, &t);
    for (int i = 1; i <= m; i++) {
        int u, v, c;
        scanf("%d %d %d", &u, &v, &c);
        g[u][v] += c;
    }
    EK();
    printf("%d\n", max_flow);
    return 0;
}