#include <cstdio>
#include <cctype>
using namespace std;
#define MAX_N 200007
template <typename T>
inline T max(T a, T b) {
    return a < b ? b : a;
}
int n;
struct SegTree {
    #define INF 0x7fffffffffffffffll
    #define lson(x) (x<<1)
    #define rson(x) ((x<<1)|1)
    #define cmid(l,r) ((l + r) >> 1)
    long long tree[MAX_N << 2];
    void update(int now) {
        tree[now] = max(tree[lson(now)], tree[rson(now)]);
    }
    void change_point(int now, int nl, int nr, int x, long long val) {
        if (nl == nr) {
            tree[now] = val;
        } else {
            int mid = cmid(nl, nr);
            if (x <= mid) change_point(lson(now), nl, mid, x, val);
            else change_point(rson(now), mid+1, nr, x, val);
            update(now);
        }
    }
    void change_point(int x, long long val) {
        change_point(1, 1, n, x, val);
    }
    long long range_max(int now, int nl, int nr, int tl, int tr) {
        if (nr < tl || tr < nl) {
            return -INF;
        } else if (tl <= nl && nr <= tr) {
            return tree[now];
        } else {
            int mid = cmid(nl, nr);
            return max(range_max(lson(now), nl, mid, tl, tr), 
                range_max(rson(now), mid+1, nr, tl, tr));
        }
    }
    long long range_max(int tl, int tr) {
        return range_max(1, 1, n, tl, tr);
    }
} segt;
char fsrd_op() {
    int c = getchar();
    while (c != 'A' && c != 'Q') c = getchar();
    return c;
}
long long fsrd() {
    long long p = 0; int c = getchar(); bool sgn = false;
    while(!isdigit(c)) {
        if(c == '-') sgn = true;
        c = getchar();
    }
    while(isdigit(c)) {
        p = p*10 + (c-'0'); c = getchar();
    }
    return sgn ? -p : p;
}
int main() {
    long long m, d, val, l;
    n = m = (int)fsrd(), d = fsrd();
    long long nR = 1, t = 0;
    for (int i = 1; i <= m; i++) {
        char op = fsrd_op();
        if (op == 'A') {
            val = fsrd();
            segt.change_point(++nR, (val % d + t % d) % d);
        } else if (op == 'Q') {
            l = fsrd();
            t = segt.range_max(nR - l + 1, nR);
            printf("%lld\n", t);
        } else {

        }
    }
    return 0;
}
