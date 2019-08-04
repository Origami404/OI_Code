#include <cstdio>
#include <cctype>
#include <queue>
#include <cstring>
#define RAW_N 53
// #define MAX_N ((RAW_N << 1) + 20)
// #define MAX_E ((MAX_N * MAX_N) + (MAX_N << 1) + 203)
#define MAX_N 126
#define MAX_E 1000007
using namespace std;
struct Edge {
    int next, to, cf;
} e[MAX_E << 1];
int head[MAX_N], etp = 0;
inline void build(int from, int to, int cf) {
    e[etp] = (Edge) {head[from], to, cf};
    head[from] = etp++;
}

// char debug_out[1000][1000];
// int dotp = 0;
inline void build_edge(int from, int to, int weight) {
    build(from, to, weight); build(to, from, 0);
    // sprintf(debug_out[dotp++], "Build edge %d -%d-> %d", from, weight, to);
}

int s, t, n;

int dist[MAX_N];
bool bfs() {
    memset(dist, -1, sizeof(dist));
    queue<int> q;
    dist[s] = 0;
    q.push(s); 
    while (!q.empty()) {
        int now = q.front();
        q.pop(); 
        for (int i = head[now]; i != -1; i = e[i].next) {
            int p = e[i].to;
            if (dist[p] == -1 && e[i].cf != 0) {
                dist[p] = dist[now] + 1;
                q.push(p);
            }
        }
    }
    return dist[t] != -1;
}

int dfs(int now, int limit_flow) {
    if (now == t || limit_flow == 0) 
        return limit_flow;
    int add_flow = 0;
    for (int i = head[now]; i != -1; i = e[i].next) {
        int p = e[i].to;
        if (e[i].cf != 0 && dist[p] == dist[now] + 1) {
            int padd = dfs(p, min(e[i].cf, limit_flow - add_flow));
            e[i].cf -= padd;
            e[i^1].cf += padd;
            add_flow += padd;
            if (limit_flow - add_flow == 0) break;
        }
    }
    return add_flow;
}

int Dinic() {
    int max_flow = 0;
    while (bfs()) 
        max_flow += dfs(s, 0x7f7f7f7f);
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

int bfsrd() {
    int c = getchar();
    while (c != '1' && c != '0') c = getchar();
    return c - '0';
}

int type[MAX_N];
const int TYPE_VISITER = 1, TYPE_IN_SCHOOL = 2, 
    TYPE_IN_HOME = 3, TYPE_STUDENT = 4;
#define get_in(x) (x)
#define get_out(x) (x + n)
#define get_s(x) ((x<<1) + 1)
#define get_t(x) ((x<<1) + 2)

int visiter_cnt;
void input() {
    n = fsrd();
    for (int i = 1; i <= n; i++) {
        type[i] = bfsrd() ? TYPE_STUDENT : TYPE_VISITER;
        visiter_cnt += (type[i] == TYPE_VISITER);
    }
    for (int i = 1; i <= n; i++) {
        int u = bfsrd();
        if (type[i] == TYPE_STUDENT) 
            type[i] = u ? TYPE_IN_HOME : TYPE_IN_SCHOOL;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int k = bfsrd();
            // 防止重复建边, 使用i < j
            // 不认识就没什么好说的了
            if (k == 1 && i < j) {
                if (type[i] == TYPE_VISITER) {
                    if (type[j] == TYPE_IN_HOME)
                        // 游客认识回家的, 游客 -1-> 回家
                        build_edge(i, j, 1);
                    else if (type[j] == TYPE_IN_SCHOOL) 
                        // 游客认识住校的, 游客 -1-> 住校IN
                        build_edge(i, get_in(j), 1);
                } else if (type[i] == TYPE_IN_SCHOOL) {
                    if (type[j] == TYPE_IN_HOME) 
                        // 住校认识回家的, 住校OUT -1-> 回家
                        build_edge(get_out(i), j, 1);
                    else if (type[j] == TYPE_IN_SCHOOL) 
                        // 住校i认识住校j的, i-OUT -1-> j-IN
                        build_edge(get_out(i), get_in(j), 1), // 逗号
                        // j-OUT -1-> i-IN
                        build_edge(get_out(j), get_in(i), 1);
                    else if (type[j] == TYPE_VISITER)
                        // 住校的认识游客, 游客 -1-> 住校IN
                        build_edge(j, get_in(i), 1);
                } else if (type[i] == TYPE_IN_HOME) {
                    if (type[j] == TYPE_IN_SCHOOL) 
                        // 回家认识住校, 住校OUT -1-> 回家
                        build_edge(get_out(j), i, 1);
                    else if (type[j] == TYPE_VISITER)
                        // 回家认识游客, 游客 -1-> 回家
                        build_edge(j, i, 1);
                }
            }
        }
    }
    s = get_s(n); t = get_t(n);
    for (int i = 1; i <= n; i++) {
        if (type[i] == TYPE_IN_HOME)
            build_edge(i, t, 1); // 回家 -1-> 总汇点
        else if (type[i] == TYPE_VISITER)
            build_edge(s, i, 1); // 总源点 -1-> 游客
        else if (type[i] == TYPE_IN_SCHOOL)
            // 住校IN -1-> 住校OUT
            build_edge(get_in(i), get_out(i), 1);
    }

    // printf("DBEUG START\n");
    // for (int i = 0; i < dotp; i++)  
    //     puts(debug_out[i]);
    // printf("DEBUG END\n");
}

void deal() {
    memset(head, -1, sizeof(head));
    memset(e, 0, sizeof(e)); etp = 0;
    memset(type, 0, sizeof(type));
    visiter_cnt = 0;
    input();
    // 直接等于怕炸
    puts(Dinic() >= visiter_cnt ? "^_^" : "T_T");
}

int main() {
    int t = fsrd();
    for (int i = 1; i <= t; i++)
        deal();
    return 0;
}