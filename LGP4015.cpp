#include <cstdio>
#include <cstring>
#include <cctype>
#include <queue>

#define MAX_N 127
#define MAX_E 307
#define INF 0x3f3f3f3f

using namespace std;

struct Edge {
    int next, to, cf, cost;
} e[MAX_E << 1];
int head[MAX_N], etp = 0;
inline void build(int from, int to, int cf, int cost) {
    e[etp] = (Edge) {head[from], to, cf, cost};
    head[from] = etp++;
}

int cost[MAX_N], flow[MAX_N];
int pv[MAX_N], pe[MAX_N];
int n, m, s, t;
bool in_queue[MAX_N];
bool spfa() {
    memset(cost, 0x3f, sizeof(cost)), memset(flow, 0x3f, sizeof(flow));
    //memset(pv, -1, sizeof(pv)), memset(pe, -1, sizeof(pe));
    memset(in_queue, false, sizeof(in_queue));
    queue<int> q;
    pv[t] = -1; cost[s] = 0;
    q.push(s); in_queue[s] = true;
    while (!q.empty()) {
        int now = q.front(); q.pop(); in_queue[now] = false;
        for (int i = head[now]; i != -1; i = e[i].next) {
            int p = e[i].to;
            if (e[i].cf != 0 && cost[p] > cost[now] + e[i].cost) {
                cost[p] = cost[now] + e[i].cost;
                flow[p] = min(flow[now], e[i].cf);
                pv[p] = now; pe[p] = i;
                if (!in_queue[p]) {
                    q.push(p); in_queue[p] = true;
                }
            }
        }
    }
    return pv[t] != -1;
}

int max_flow = 0, min_cost = 0;
void MCMF() {
    while (spfa()) {
        int add = flow[t];
        max_flow += add;
        min_cost += cost[t] * add;
        for (int i = t; i != s; i = pv[i]) {
            e[pe[i]].cf -= add;
            e[pe[i]^1].cf += add;
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
int node[MAX_N];
int main() {
    memset(head, -1, sizeof(head));
    int avg = 0;
    n = fsrd();
    for (int i = 1; i <= n; i++) 
        avg += (node[i] = fsrd());
    avg /= n; // Make AVG really an AVG
    s = n + 1; t = n + 2;
    for (int i = 1; i <= n; i++) {
        //if (node[i] == avg) continue;
        if (node[i] < avg) {
            build(s, i, avg - node[i], 0);
            build(i, s, 0, 0);
        } else if (node[i] > avg) {
            build(i, t, node[i] - avg, 0);
            build(t, i, 0, 0);
        }
    }
    for (int i = 1; i < n; i++) {
        build(i, i + 1, INF, 1), build(i + 1, i, 0, -1); 
        build(i + 1, i, INF, 1), build(i, i + 1, 0, -1);
    }
    build(n, 1, INF, 1), build(1, n, 0, -1);
    build(1, n, INF, 1), build(n, 1, 0, -1);
    MCMF();
    printf("%d\n", min_cost);
    return 0;
}