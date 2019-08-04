#include <cstdio>
#include <queue>
#include <cstring>
#include <cctype>
#define MAX_N 5007
#define MAX_E 50007
using namespace std;
struct Edge {
    int next, to, cf, cost;
} e[MAX_E << 1];
int head[MAX_N], etp = 0;
inline void build(int from, int to, int cf, int cost) {
    e[etp] = (Edge) {head[from], to, cf, cost};
    head[from] = etp++;
}
int n, m, s, t;

int cost[MAX_N], flow[MAX_N];
int pv[MAX_N], pe[MAX_N]; 
bool in_queue[MAX_N];
bool spfa() {
    memset(flow, 0x7f, sizeof(flow));
    memset(cost, 0x7f, sizeof(cost));
    memset(in_queue, false, sizeof(in_queue));
    queue<int> q;
    q.push(s); in_queue[s] = true;
    cost[s] = 0; pv[t] = -1;
    while (!q.empty()) {
        int now = q.front(); q.pop(); in_queue[now] = false;
        for (int i = head[now]; i != -1; i = e[i].next) {
            int p = e[i].to;
            if (e[i].cf != 0 && cost[p] > cost[now] + e[i].cost) {
                cost[p] = cost[now] + e[i].cost;
                pv[p] = now; pe[p] = i;
                flow[p] = min(flow[now], e[i].cf);
                if (!in_queue[p]) {
                    q.push(p); in_queue[p] = true;
                }
            }
        }
    }
    return pv[t] != -1;
}

int max_flow, min_cost;
void MCMF() {
    while (spfa()) {
        max_flow += flow[t];
        min_cost += flow[t] * cost[t];
        for (int i = t; i != s; i = pv[i]) {
            e[pe[i]].cf -= flow[t];
            e[pe[i]^1].cf += flow[t];
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
    memset(head, -1, sizeof(head));
    n = fsrd(), m = fsrd(), s = fsrd(), t = fsrd();
    for (int i = 1; i <= m; i++) {
        int u, v, w, c;
        u = fsrd(), v = fsrd(), w = fsrd(), c = fsrd();
        build(u, v, w, c), build(v, u, 0, -c);
    }
    MCMF();
    printf("%d %d\n", max_flow, min_cost);
    return 0;
}