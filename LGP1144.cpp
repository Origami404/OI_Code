#include <cstdio>
#include <cstring>
#include <queue>
#include <cctype>
#define MAX_E 2000007
#define MAX_N 1000007
using namespace std;
struct Edge {
    int next, to;
} e[MAX_E << 1];
int head[MAX_N], etp = 0;
inline void build(int from, int to) {
    e[++etp].next = head[from];
    e[etp].to = to;
    head[from] = etp;
}

int count[MAX_N], dist[MAX_N];
bool vis[MAX_N];
void bfs(int start) {
    queue<int> q;
    q.push(start); 
    count[start] = 1;
    vis[start] = true;
    while (!q.empty()) {
        int now = q.front(); q.pop();
        for (int i = head[now]; i != 0; i = e[i].next) {
            int p = e[i].to;
            if (!vis[p]) {
                dist[p] = dist[now] + 1; vis[p] = true;
                q.push(p);
            }
            if (dist[p] == dist[now] + 1) {
                count[p] = (count[p] + count[now]) % 100003;
            }
        }
    }
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
    int n, m, u, v;
    n = fsrd(), m = fsrd();
    for (int i = 1; i <= m; i++) {
        u = fsrd(), v = fsrd();
        build(u, v);
        build(v, u);
    }
    bfs(1);
    for (int i = 1; i <= n; i++) {
        printf("%d\n", count[i]);
    }
    return 0;
}