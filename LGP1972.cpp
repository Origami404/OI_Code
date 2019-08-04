#include <cstdio>
#include <cctype>
#include <algorithm>
#define MAX_N 500007
#define MAX_M 500007
#define MAX_T 1000007
using namespace std;
int n, m;
struct BIT {
    #define lowbit(x) (x&(-x))
    int tree[MAX_N];
    int query(int L, int R) {
        return _query(R) - _query(L - 1);
    }
    void change(int x, int v) {
        for (; x <= n; x += lowbit(x))
            tree[x] += v;
    }
    int _query(int x) {
        int ans = 0;
        for (; x >= 1; x -= lowbit(x))
            ans += tree[x];
        return ans;
    }
    #undef lowbit
} bit;

struct Query {
    int L, R, ind;
    bool operator<(const Query &o) const {
        return R < o.R;
    }
} query[MAX_M];

int a[MAX_N], lh[MAX_T];
int ans[MAX_M];

int fsrd() {
    int p = 0; int c = getchar();
    while(!isdigit(c)) c = getchar();
    while(isdigit(c)) {
        p = p*10 + (c-'0'); c = getchar();
    }
    return p;
}
inline void input() {
    n = fsrd();
    for (int i = 1; i <= n; i++)
        a[i] = fsrd();
    m = fsrd();
    for (int i = 1; i <= m; i++) {
        query[i].L = fsrd();
        query[i].R = fsrd();
        query[i].ind = i;
    }
}
int main() {
    input();
    sort(query + 1, query + 1 + m);
    int qpos = 1;
    for (int i = 1; i <= n && qpos <= m; i++) {
        bit.change(i, 1);
        if (lh[a[i]] != 0) 
            bit.change(lh[a[i]], -1);
        lh[a[i]] = i;
        while (i == query[qpos].R) {
            ans[query[qpos].ind] = bit.query(query[qpos].L, query[qpos].R);
            qpos += 1;
        }
    }
    for (int i = 1; i <= m; i++) 
        printf("%d\n", ans[i]);
    return 0;
}