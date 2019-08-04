#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cctype>
using namespace std;
#define MAX_N 100007
#define MAX_E 500007
#define MAX_LOG_N 18
struct Edge {
    int next, to, weight;
} e[MAX_E << 1];
int head[MAX_N], etp = 0;
inline void build(int from, int to, int weight) {
    e[++etp] = (Edge) {head[from], to, weight};
    head[from] = etp;
}
inline void new_build(int from, int to, int weight) {
	// printf("DEBUG(new_build): %d <--> %d (%d)\n", from, to, weight);
    build(from, to, weight), build(to, from, weight);
}
int n;

struct Kru {
    struct kru_edge {
        int from, to, weight;
        bool operator<(const kru_edge& o) const {
            return weight > o.weight; // GET MAX
        }
    } tg[MAX_E << 1];
    int uset[MAX_N], tgp;
    void init_kru() { 
        tgp = 0;
        for (int i = 1; i <= n; i++) uset[i] = i;
    }

    int find(int x) {
        return x == uset[x] ? x : (uset[x] = find(uset[x]));
    }

    void kru() {
        // 最大生成树
        sort(tg + 1, tg + tgp + 1);
        for (int i = 1; i <= tgp; i++) {
            int fx = find(tg[i].from), fy = find(tg[i].to);
            // printf("D:%d %d %d %d\n", tg[i].from, tg[i].to, fx, fy);
            if (fx != fy) {
            	// printf("%d != %d\n", fx, fy);
                uset[fx] = fy;
                new_build(tg[i].from, tg[i].to, tg[i].weight);
            }
        }
        // 补全联通
        int ti = find(1);
        for (int i = 2; i <= n; i++) {
            int fi = find(i);
            if (fi != ti) {
                new_build(1, i, -1);
                uset[fi] = ti;
            }
        }
    }
    void build(int from, int to, int weight) {
        tg[++tgp] = (kru_edge) {from, to, weight};
    } 
} kru;

int root = 1;

int dep[MAX_N];
int last[MAX_N][MAX_LOG_N];
int minw[MAX_N][MAX_LOG_N];
void lca_init_dfs(int now, int father) {
    dep[now] = dep[father] + 1;
    last[now][0] = father;

    for (int k = 1; k < MAX_LOG_N; k++) {
        last[now][k] = last[ last[now][k-1] ][k-1];
        minw[now][k] = min(minw[now][k-1], minw[ last[now][k-1] ][k-1]);
    }

    for (int i = head[now]; i != 0; i = e[i].next) {
        int p = e[i].to;
        if (p != father) {
            // printf("DEBUG: update %d: %d\n", p, e[i].weight);
            minw[p][0] = e[i].weight;
            lca_init_dfs(p, now);
        }
    }
}
// void lca_init() {
//     lca_init_dfs(root, root);
//     for (int i = 1; i <= n; i++) {
//         // last[i][0] = fa[i];
//         for (int k = 1; k < MAX_LOG_N; k++) {
//             last[i][k] = last[ last[i][k-1] ][k-1]; 
//             minw[i][k] = min(minw[i][k-1], 
//                              minw[ last[i][k-1] ][k-1]);
//         }
//     }
// }
#define INF 0x7f7f7f7f
int lca_min_weight(int x, int y) {
    int ret = INF;
    if (!(dep[x] > dep[y]))
        swap(x, y);
    //printf("DEBUG(1: x, y): %d %d\n", x, y);
    for (int k = MAX_LOG_N - 1; k >= 0; k--) {
        if (dep[last[x][k]] >= dep[y]) {
            //printf("DEBUG(2: x, y, minw): %d %d (%d)\n", x, y, minw[x][k]);
            ret = min(ret, minw[x][k]);
            x = last[x][k];
        }
    }   
    //printf("DEBUG(3: x, y): %d %d\n", x, y);
    if (x == y) return ret;

    for (int k = MAX_LOG_N - 1; k >= 0; k--) {
        if (last[x][k] != last[y][k]) {
            ret = min(ret, min(minw[x][k], minw[y][k]));
            x = last[x][k]; y = last[y][k];
        }
    }
    ret = min(ret, min(minw[x][0], minw[y][0]));
    return ret;
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
	int m, x, y, z;
    n = fsrd(); m = fsrd();
    kru.init_kru();
    for (int i = 1; i <= m; i++) {
        x = fsrd(); y = fsrd(); z = fsrd();
        kru.build(x, y, z);
    }  
    
    kru.kru();
    //puts("DEBUG: Finish kru.");
    // lca_init();
    //memset(minw, 0x3f, sizeof(minw));
    minw[root][0] = 0x3f3f3f3f;
    lca_init_dfs(root, root);

    // printf("DEBUG(last:minw):\n");
    // for (int i = 1; i <= 4; i++) {
    //     printf("%d=> ", i);
    //     for (int k = 0; k < MAX_LOG_N; k++)
    //         printf("%d:%d ", last[i][k], minw[i][k]);
    //     printf("\n");
    // }

    m = fsrd();
    for (int i = 1; i <= m; i++) {
        x = fsrd(); y = fsrd();
        printf("%d\n", lca_min_weight(x, y));
    }
    return 0;
}