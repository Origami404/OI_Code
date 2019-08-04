/*
 * HLPP 最高标号预流推进
 * 优化: 初始化BFS gap
 */
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <cctype>
using namespace std;
#define MAX_N 1207
#define MAX_E 120007
#define INF 0x3f3f3f3f
struct Edge {
    int next, to, cf;
} e[MAX_E << 1];
int head[MAX_N], etp = 0;
inline void build(register int from, register int to, register int cf) {
    e[etp].to = to;
    e[etp].cf = cf;
    e[etp].next = head[from];
    head[from] = etp++;
}
int s, t, n, m;
int height[MAX_N], excess_flow[MAX_N];
// gap优化 当提高某高度层的最后一个点时把该层所有超额流量退回s
int gap[MAX_N << 1]; 
bool in_queue[MAX_N];

inline bool bfs() {
    queue<int> bfs_q;
    memset(height, 0x3f, sizeof(int) * (n + 7));
    // 反向BFS按到原点距离初始化标记高度
    height[t] = 0; bfs_q.push(t);
    while (!bfs_q.empty()) {
        register int now = bfs_q.front(); bfs_q.pop();
        for (int i = head[now]; i != -1; i = e[i].next) {
            register int p = e[i].to;
            // 因为反向BFS, 所以需要判断反边是否存在于原网络
            if (e[i^1].cf != 0 && height[p] > height[now] + 1) {
                height[p] = height[now] + 1;
                bfs_q.push(p);
            }
        }
    }
    return height[s] != INF;
}

struct cmp {
    bool operator()(int a, int b) const 
    { return height[a] < height[b]; }
};
priority_queue<int, vector<int>, cmp> high_q;

inline void push_flow(register int now) {
    for (register int i = head[now]; i != -1; i = e[i].next) {
        register int p = e[i].to;
        if (e[i].cf != 0 && height[now] == height[p] + 1) {
            register int detla = min(excess_flow[now], e[i].cf);
            e[i].cf -= detla;
            e[i^1].cf += detla;
            excess_flow[now] -= detla;
            excess_flow[p] += detla;
            if (p != s && p != t && !in_queue[p]) {
                high_q.push(p);
                in_queue[p] = true;
            }
            if (excess_flow[now] == 0) break;
        }
    }
}

inline void relabel(register int now) {
    height[now] = INF; // 先暴力拉最高
    for (register int i = head[now]; i != -1; i = e[i].next) {
        register int p = e[i].to;
        // 如果当前违反了高度限制, 那么调小
        if (e[i].cf != 0 && height[p] + 1 < height[now])
            height[now] = height[p] + 1;
    }
}


inline int hlpp() {
    // 如果图不连通就返回0
    if (!bfs()) return 0; 
    height[s] = n;
    // 初始化gap
    memset(gap, 0, sizeof(int) * ((n<<1) + 7));
    for (register int i = 1; i <= n; i++) 
        if (height[i] < INF) ++gap[height[i]];

    // 源点推流    
    for (register int i = head[s]; i != -1; i = e[i].next) {
        register int p = e[i].to;
        if (e[i].cf != 0) {
            register int detla = e[i].cf;
            e[i].cf -= detla;
            e[i^1].cf += detla;
            excess_flow[p] += detla;
            if (p != s && p != t && !in_queue[p]) {
                high_q.push(p);
                in_queue[p] = true;
            }
        }
    } 
    // 优先队列维护当前高度最高
    while (!high_q.empty()) {
        register int now = high_q.top(); high_q.pop();
        in_queue[now] = false;
        push_flow(now);
        // 如果不能推尽超额流 就要relabel
        if (excess_flow[now] != 0) {
            // gap优化
            if (--gap[height[now]] == 0) {
                for (register int i = 1; i <= n; i++)
                    if (i != s && i != t 
                        && height[i] > height[now] && height[i] < n + 1)
                        height[i] = n + 1;
            }
            // 重编号后维护gap
            relabel(now); ++gap[height[now]];
            high_q.push(now); in_queue[now] = true;
        } 
    }
    return excess_flow[t];
}
int fsrd() {
    register int p = 0, c = getchar();
    while(!isdigit(c)) c = getchar();
    while(isdigit(c)) {
        p = p*10 + (c-'0'); c = getchar();
    }
    return p;
}
int main() {
    n = fsrd(), m = fsrd(), s = fsrd(), t = fsrd();
    memset(head, -1, sizeof(int) * ((n<<1) + 7));
    for (int i = 1; i <= m; i++) {
        register int u, v, c;
        u = fsrd(), v = fsrd(), c = fsrd();
        build(u, v, c), build(v, u, 0);
    }
    printf("%d\n", hlpp());
    return 0;
}