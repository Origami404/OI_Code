#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cctype>
#define MAX_E 100007
#define MAX_N 20007
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
int newi[MAX_N], hbi[MAX_N], tmt = 0;
bool is_cut[MAX_N];
int ans[MAX_N], atp = 0;
void dfs(int now, int fa) {
    //printf("DEBUG(now): %d\n", now);
    hbi[now] = newi[now] = ++tmt;
    int child = 0; // 用于根节点判断是否为割点
    for (int i = head[now]; i != 0; i = e[i].next) {
        int p = e[i].to;
        if (newi[p] == 0) {
            dfs(p, now);
            hbi[now] = min(hbi[now], hbi[p]);
            // 如果存在子节点
            // 其无连到本节点的祖先的反边
            // 那么本节点就是割点
            if (hbi[p] >= newi[now] && !is_cut[now] && now != fa) {
                ans[++atp] = now; is_cut[now] = true;
            } 
            // now == fa 必为每个联通分量的DFS树根节点
            if (now == fa) child += 1;
        }
        // 事实上可以加else 
        // 如果i未访问的话 必有 hbi[i] <= newi[i] 
        hbi[now] = min(hbi[now], newi[p]);
    }
    // 根节点判断
    if (child >= 2 && now == fa && !is_cut[now])
        ans[++atp] = now, is_cut[now] = true; 
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
        build(u, v), build(v, u);
    }
    // 不一定联通
    for (int i = 1; i <= n; i++)
        if (newi[i] == 0) 
            dfs(i, i); 
    sort(ans + 1, ans + atp + 1);
    printf("%d\n", atp);
    for (int i = 1; i <= atp; i++) 
        printf("%d ", ans[i]);
    return 0;
}