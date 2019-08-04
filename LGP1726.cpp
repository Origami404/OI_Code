#include <cstdio>
#include <cctype>
#include <cstring>
#include <stack>
#define MAX_N 5007
#define MAX_E 50007
using namespace std;
struct Edge {
    int next, to;
} e[MAX_E << 1];
int head[MAX_N], etp = 0;
inline void build(int from, int to) {
    e[++etp].to = to;
    e[etp].next = head[from];
    head[from] = etp;
}

inline int min(int a, int b) {
    return a < b ? a : b;
}

int max_weight_i, max_weight_val = -1;

const int NOT_VISIT = 0, IN_STACK = 1, IN_SCC = 2;
int state[MAX_N];

int low[MAX_N], pre[MAX_N];
stack<int> s;

int belong[MAX_N], scc_cnt = 0;
int tmt = 0;
void dfs(int now) {
    s.push(now);
    state[now] = IN_STACK;
    low[now] = pre[now] = ++tmt;
    for (int i = head[now]; i != 0; i = e[i].next) {
        int p = e[i].to;
        if (state[p] == NOT_VISIT) {
            dfs(p);
            low[now] = min(low[now], low[p]);
        } else if (state[p] == IN_STACK) {
            low[now] = min(low[now], pre[p]);
        }
    }
    if (low[now] == pre[now]) {
        int p, nw = 0;
        scc_cnt += 1;
        do {
            p = s.top(); s.pop();
            belong[p] = scc_cnt;
            state[p] = IN_SCC;
            nw += 1;
        } while (p != now);
        // Update max weight scc.
        if (nw > max_weight_val) {
            max_weight_val = nw;
            max_weight_i = scc_cnt;
        }
    }
}

int fsrd() {
    int p = 0, c = getchar();
    while (!isdigit(c)) c = getchar();
    while (isdigit(c)) {
        p = p*10 + (c-'0');
        c = getchar();
    }
    return p;
}

int main() {
    int n, m, x, y, t;
    n = fsrd(); m = fsrd();
    for (int i = 1; i <= m; i++) {
        x = fsrd(); y = fsrd(); t = fsrd();
        if (t == 1) {
            build(x, y);
        } else {
            build(x, y); build(y, x);
        }
    }
    for (int i = 1; i <= n; i++) {
        if (state[i] == NOT_VISIT)
            dfs(i);
    }
    printf("%d\n", max_weight_val);
    for (int i = 1; i <= n; i++) {
        if (belong[i] == max_weight_i)
            printf("%d ", i);
    }
    return 0;
}