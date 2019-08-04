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
int head[MAX_N], etp = 0;
void build(int from, int to, int c) {
    e[etp].to = to;
    e[etp].c = c;
    e[etp].next = head[from];
    head[from] = etp++;
}
int s, t, n, m;
int dist[MAX_N], cur[MAX_N];
int rcur[MAX_N];

bool bfs() {
    queue<int> q;
    while (!q.empty()) q.pop();
    memset(dist, -1, sizeof(dist));
    // 初始化当前弧
    for (int i = 1; i <= n; i++) 
        cur[i] = head[i];
    dist[s] = 0; q.push(s);
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

int dfs(int now, int limit_flow) {
    if (now == t || limit_flow == 0) return limit_flow;
    int add_flow = 0;
    // 这一次bfs后的dfs增广过的边一定不会再次增广
    // 因为已经到了当前bfs增广的允许最大值
    for (int &i = cur[now]; i != -1; i = e[i].next) {
        //cur[now] = i; // 使用引用修改
        int p = e[i].to;
        if (e[i].c != 0 && dist[p] == dist[now] + 1) {
            int t = dfs(p, min(e[i].c, limit_flow - add_flow));
            e[i].c -= t;
            e[i^1].c += t;
            add_flow += t;
            if (limit_flow == 0) break;
        }
    }
    return add_flow;
}
#define INF 0x7f7f7f7f
int Dinic() {
    int max_flow = 0;
    while (bfs())
        max_flow += dfs(s, INF);
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