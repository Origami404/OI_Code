#include <cstdio>
#include <algorithm>
using std::sort;
#define MAX_N 107
struct Edge {
    int from, to, weight;
    bool operator<(const Edge &o) const {
        return weight < o.weight;
    }
} e[MAX_N * MAX_N];
int etp = 0;

// Remeber init
int uset[MAX_N];
int find(int x) {
    return uset[x] == x ? x : (uset[x] = find(uset[x]));
}

int kru(int n) {
    int ret = 0;
    sort(e, e + etp);
    for (int i = 0; i < etp; i++) {
        int x = e[i].from, y = e[i].to;
        int fx = find(x), fy = find(y);
        if (fx != fy) {
            uset[fx] = fy;
            ret += e[i].weight;
        }
    }
    return ret;
}

int main() {
    int n, w;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            scanf("%d", &w);
            e[etp++] = (Edge) {i, j, w};
        }
    }
    for (int i = 1; i <= n; i++)
        uset[i] = i;
    printf("%d\n", kru(n));
    return 0;
}