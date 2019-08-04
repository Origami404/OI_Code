#include <cstdio>
#include <cctype>
#include <cstring>
#include <queue>
using namespace std;
#define MAX_N 1007
#define INF 0x3f3f3f3f
struct Edge {
    int next, to, cf;
} e[((MAX_N * MAX_N) << 1) + (MAX_N << 1)];
int head[(MAX_N << 1) + 5], etp = 0;
inline void build(int from, int to, int cf) {
    e[etp] = (Edge) {head[from], to, cf};
    head[from] = etp++;
} 
int n, m, s, t, en;
int dist[MAX_N << 1];
bool bfs() {
    queue<int> q;
    memset(dist, 0x3f, sizeof(dist));
    q.push(s); dist[s] = 0;
    while (!q.empty()) {
        int now = q.front(); q.pop();
        for (int i = head[now]; i != -1; i = e[i].next) {
            int p = e[i].to;
            if (e[i].cf != 0 && dist[p] == INF) {
                dist[p] = dist[now] + 1;
                q.push(p);
            }   
        }
    }
    return dist[t] != INF;
}
int dfs(int now, int limit) {
    if (now == t || limit == 0) return limit;
    int add = 0;
    for (int i = head[now]; i != -1; i = e[i].next) {
        int p = e[i].to;
        if (e[i].cf != 0 && dist[p] == dist[now] + 1) {
            int detla = dfs(p, min(e[i].cf, limit - add));
            e[i].cf -= detla; e[i^1].cf += detla;
            add += detla;
            if (limit - add == 0) break;
        }
    }
    return add;
}
int dinic() {
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
    memset(head, -1, sizeof(head));
    n = fsrd(), m = fsrd(), en = fsrd();
    for (int i = 1; i <= en; i++) {
        int u, v;
        u = fsrd(), v = fsrd();
        build(u, v + n, 1), build(v + n, u, 0);
    }
    s = n + m + 1; t = s + 1;
    for (int i = 1; i <= n; i++) {
        build(s, i, 1), build(i, s, 0);
    }
    for (int i = 1; i <= m; i++) {
        build(t, n + i, 0), build(n + i, t, 1);
    }
    printf("%d\n", dinic());
    return 0;
}