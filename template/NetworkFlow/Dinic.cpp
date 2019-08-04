/**
 * 没有当前弧优化的Dinic
 */
#include <cstdio>
#include <cctype>
#include <cstring>
#include <queue>
using namespace std;
#define MAX_N 10007
#define MAX_E 100007
struct Edge {
    int next, to, c;
} e[MAX_E << 1];
// etp 从0开始, 方便求反向边
int head[MAX_N], etp = 0;
void build(int from, int to, int c) {
    e[etp].to = to;
    e[etp].c = c;
    e[etp].next = head[from];
    head[from] = etp++; // 切记要最后++
}

int n, m, s, t;
int dist[MAX_N];

// BFS 求dist
bool bfs() {
    queue<int> q;
    memset(dist, -1, sizeof(dist));
    //while (!q.empty()) q.pop();
    dist[s] = 0;
    q.push(s);
    while (!q.empty()) {
        int now = q.front(); q.pop();
        for (int i = head[now]; i != -1; i = e[i].next) {
            int p = e[i].to;
            if (dist[p] == -1 && e[i].c != 0) {
                dist[p] = dist[now] + 1;
                q.push(p);
            }
        }
    }
    return dist[t] != -1;
}
// limit_flow 表示s -> t最多能增加多少流
int dfs(int now, int limit_flow) {
    if (now == t || limit_flow == 0) return limit_flow;
    int add_flow = 0;
    for (int i = head[now]; i != -1; i = e[i].next) {
        int p = e[i].to;
        if (e[i].c != 0 && dist[p] == dist[now] + 1) {
            // 减去已经增加的可以防止前面爆容量
            int padd = dfs(p, min(e[i].c, limit_flow - add_flow));
            e[i].c -= padd; // 本残存边减
            e[i^1].c += padd; // 反向的残存边加
            add_flow += padd; // 能增加的加
        }
    }
    return add_flow;
}
#define INF 0x7f7f7f7f
int Dinic() {
    int max_flow = 0;
    while (bfs()) max_flow += dfs(s, INF);
    return max_flow;
}
int fsrd() {
    int p = 0; int c = getchar();
    while(!isdigit(c)) c = getchar();
    while(isdigit(c)) {
        p = p*10 + (c-'0'); c = getchar();
    }
    return p;
}   
int main() {
    // -1 前向星要memset 注意!!!
    memset(head, -1, sizeof(head));
    n = fsrd(), m = fsrd(), s = fsrd(), t = fsrd();
    for (int i = 1; i <= m; i++) {
        int u, v, c; 
        u = fsrd(), v = fsrd(), c = fsrd();
        build(u, v, c), build(v, u, 0);
    }
    printf("%d\n", Dinic());
    return 0;
}