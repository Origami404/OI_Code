#include <cstdio>
#include <cctype>
#define MAXN 200007
using namespace std;
int n;
unsigned long long p, a[MAXN];
struct SegmentTree {
    #define lson(x) (x<<1)
    #define rson(x) ((x<<1)|1)
    #define cmid(l,r) ((l + r) >> 1)
    unsigned long long tsum[MAXN << 2], ladd[MAXN << 2], lmul[MAXN << 2];
    inline void update(int now) {
        tsum[now] = (tsum[lson(now)] + tsum[rson(now)]) % p; 
    }
    inline void addtag_add(int now, int nl, int nr, unsigned long long v) {
        unsigned long long mv = v % p;
        ladd[now] = (ladd[now] + mv) % p;
        tsum[now] = (tsum[now] + ((nr - nl + 1) % p) * (mv) % p) % p;
    }
    inline void addtag_mul(int now, unsigned long long v) {
        unsigned long long mv = v % p;
        lmul[now] = (lmul[now] * mv) % p;
        ladd[now] = (ladd[now] * mv) % p;
        tsum[now] = (tsum[now] * mv) % p;
    }
    void push_down(int now, int nl, int mid, int nr) {
        if (ladd[now] != 0 || lmul[now] != 1) {
            addtag_mul(lson(now), lmul[now]);
            addtag_mul(rson(now), lmul[now]);

            addtag_add(lson(now), nl, mid, ladd[now]);
            addtag_add(rson(now), mid+1, nr, ladd[now]);

            ladd[now] = 0;
            lmul[now] = 1;
        }
    }
    void build(int now, int nl, int nr) {
        ladd[now] = 0;
        lmul[now] = 1;
        if (nl == nr) {
            tsum[now] = a[nl] % p;
        } else {    
            int mid = cmid(nl, nr);
            build(lson(now), nl, mid);
            build(rson(now), mid+1, nr);
            update(now);
        }
    }
    void change_range_add(int now, int nl, int nr, int tl, int tr, unsigned long long val) {
        if (nr < tl || tr < nl) {
            return;
        } else if (tl <= nl && nr <= tr) {
            addtag_add(now, nl, nr, val);
        } else {
            int mid = cmid(nl, nr);
            push_down(now, nl, mid, nr);
            change_range_add(lson(now), nl, mid, tl, tr, val);
            change_range_add(rson(now), mid+1, nr, tl, tr, val);
            update(now);
        }
    }
    void change_range_mul(int now, int nl, int nr, int tl, int tr, unsigned long long val) {
        if (nr < tl || tr < nl) {
            return;
        } else if (tl <= nl && nr <= tr) {
            addtag_mul(now, val);
        } else {
            int mid = cmid(nl, nr);
            push_down(now, nl, mid, nr);
            change_range_mul(lson(now), nl, mid, tl, tr, val);
            change_range_mul(rson(now), mid+1, nr, tl, tr, val);
            update(now);
        }
    }
    unsigned long long ask_range_sum(int now, int nl, int nr, int tl, int tr) {
        if (nr < tl || tr < nl) {
            return 0;
        } else if (tl <= nl && nr <= tr) {
            return tsum[now];
        } else {
            int mid = cmid(nl, nr);
            push_down(now, nl, mid, nr);
            return (ask_range_sum(lson(now), nl, mid, tl, tr) 
                + ask_range_sum(rson(now), mid+1, nr, tl, tr)) % p;
        }
    }
} segtree;
int fsrd() {
    int p = 0; int c = getchar();
    while(!isdigit(c)) c = getchar();
    while(isdigit(c)) {
        p = p*10 + (c-'0'); c = getchar();
    }
    return p;
}
unsigned long long fsrdll() {
    unsigned long long p = 0; int c = getchar();
    while(!isdigit(c)) c = getchar();
    while(isdigit(c)) {
        p = p*10 + (c-'0'); c = getchar();
    }
    return p;
}
signed main() {
    n = fsrd(), p = fsrdll();
    for (int i = 1; i <= n; i++) 
        a[i] = fsrdll();
    segtree.build(1, 1, n);
    int m = fsrd(), op, l, r;
    unsigned long long val;
    for (int i = 1; i <= m; i++) {
        op = fsrd(); l = fsrd(); r = fsrd();
        if (op == 1) {
            val = fsrdll();
            segtree.change_range_mul(1, 1, n, l, r, val % p);
        } else if (op == 2) {
            val = fsrdll();
            segtree.change_range_add(1, 1, n, l, r, val % p);
        } else /* if (op == 3) */ {
            printf("%llu\n", segtree.ask_range_sum(1, 1, n, l, r) % p);
        }
    }
    return 0;
}