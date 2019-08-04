#include <cstdio>
#include <stack>
#include <cctype>
#include <queue>
#include <algorithm>
#include <cstring>
#define MAX_N 10007
#define MAX_E 100007
using namespace std;
struct Graph {
    int weight[MAX_N], n;
    struct Edge {
        int next, to;
    } e[MAX_E];
    int head[MAX_N], etp;
    Graph() : n(0), etp(0) {
        memset(e, 0, sizeof(e));
        memset(head, 0, sizeof(head));
        memset(weight, 0, sizeof(weight));
    }
    inline void build(int from, int to) {
        e[++etp] = (Edge) {head[from], to};
        head[from] = etp;
    }
} rawg, newg;

int tmt = 0;
int pre[MAX_N], low[MAX_N], state[MAX_N];
stack<int> s;
const int IN_STACK = 1, NOT_VISIT = 0, IN_SCC = 2;

int sccw[MAX_N];
int belong[MAX_N], btp = 0;
void dfs(int now) {
    low[now] = pre[now] = ++tmt;
    s.push(now); state[now] = IN_STACK;
    for (int i = rawg.head[now]; i != 0; i = rawg.e[i].next) {
        int p = rawg.e[i].to;
        if (state[p] == NOT_VISIT) {
            dfs(p);
            low[now] = min(low[now], low[p]);
        } else if (state[p] == IN_STACK) {
            low[now] = min(low[now], pre[p]);
        }
    }
    if (pre[now] == low[now]) {
        int p;
        newg.n += 1;
        do {
            p = s.top(); s.pop();
            belong[p] = newg.n;
            state[p] = IN_SCC;
            newg.weight[newg.n] += rawg.weight[p];
        } while (p != now);
    }
}
void tarjin_scc() {
    tmt = 0;
    for (int i = 1; i <= rawg.n; i++)
        if (state[i] == NOT_VISIT)
            dfs(i);
}

int in_drgee[MAX_N];
void tran_graph() {
    for (int k = 1; k <= rawg.n; k++) {
        for (int i = rawg.head[k]; i != 0; i = rawg.e[i].next) {
            int p = rawg.e[i].to;
            if (belong[k] != belong[p]) {
                newg.build(belong[k], belong[p]);
                in_drgee[belong[p]] += 1;
            }
        }
    }
}

int maxw[MAX_N];
int dp() {
    memcpy(maxw, newg.weight, newg.n * sizeof(int) + 20);
    queue<int> q;
    for (int i = 1; i <= newg.n; i++) {
        if (in_drgee[i] == 0)
            q.push(i);
    }
    while (!q.empty()) {
        int now = q.front(); q.pop();
        for (int i = newg.head[now]; i != 0; i = newg.e[i].next) {
            int p = newg.e[i].to;
            maxw[p] = max(maxw[p], maxw[now] + newg.weight[p]);
            if (--in_drgee[p] == 0) 
                q.push(p);
        }
    }
    int gmax = 0;
    for (int i = 1; i <= newg.n; i++) 
        gmax = max(gmax, maxw[i]);
    return gmax;
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
    int m, u, v;
    rawg.n = fsrd(); m = fsrd();
    for (int i = 1; i <= rawg.n; i++) 
        rawg.weight[i] = fsrd();
    for (int i = 1; i <= m; i++) {
        u = fsrd(); v = fsrd();
        rawg.build(u, v);
    }   
    tarjin_scc();
    tran_graph();
    printf("%d\n", dp());
    return 0;
}


