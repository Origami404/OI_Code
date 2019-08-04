#include <cstdio>
#include <algorithm>
using namespace std;
int d, g;
struct Food {
    int t, f, h;
} food[107];
bool operator<(const Food &a, const Food &b) {
    return a.t < b.t;
}
int succ_ans = 100000, fail_ans = 0;
bool succ = false;
inline void upd_fail(int t) { if (t > fail_ans) fail_ans = t; }
inline void upd_succ(int t) { if (t < succ_ans) (succ_ans = t), succ = true; }
void dfs(int ni, int lf, int lh) {
    #define nh lh
    int nf = (ni != 1) ? (lf - (food[ni].t - food[ni - 1].t)) : (lf - food[ni].t);
    if (ni > g || nf <= 0) return upd_fail(food[ni].t + nf - 1);
    if (nh + food[ni].h >= d) return upd_succ(food[ni].t);
    dfs(ni + 1, nf, nh + food[ni].h);
    dfs(ni + 1, nf + food[ni].f, nh);
    #undef nh
}
int main() {
    scanf("%d %d", &d, &g);
    for (int i = 1; i <= g; i++)
        scanf("%d %d %d", &(food[i].t), &(food[i].f), &(food[i].h));
    sort(food + 1, food + g + 1);
    dfs(0, 11, 0);
    if (succ) printf("%d\n", succ_ans);
    else printf("%d\n", fail_ans);
    return 0;
}