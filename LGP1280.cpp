#include <cstdio>
#include <cstring>
using namespace std;
int procress[10007][10007], n, k, mt[10007], p, t;
inline int max(int a, int b) { return a < b ? b : a; }
int dfs2(int t) {
    if (mt[t] != -1) return mt[t];
    if (t > n) return 0;
    int ps = procress[t][0], now = 0;
    if (ps) {
        for (int i = 1; i <= ps; i++) now = max(now, dfs2(procress[t][i]));
        return mt[t] = now;
    } else return mt[t] = dfs2(t + 1) + 1;
    
}
int main() {
    memset(mt, -1, sizeof(mt));
    scanf("%d %d", &n, &k);
    for (int i = 1; i <= k; i++)
        scanf("%d %d", &p, &t), procress[p][++(procress[p][0])] = p + t;
    printf("%d\n", dfs2(1));
    return 0;
}