#include <cstdio>
#define MAXN 100007
using namespace std;
struct Edge {
    int to, next;
} e[MAXN << 1];
int head[MAXN], etp = 0;
void build_edge(int f, int t) {
    e[++etp].to = t;
    e[etp].next = head[f];
    head[f] = etp;
}
//int weight[MAXN]; // needn't
int n;

int hson[MAXN], dep[MAXN], fa[MAXN], siz[MAXN];
// siz[0] = INF
void get_info(int now, int father) {
    fa[now] = father;
    dep[now] = dep[father] + 1;
    siz[now] = 1;
    for (int i = head[now]; i != 0; i = e[i].next) {
        int p = e[i].to;
        if (p != father) {
            get_info(p, now);
            siz[now] += siz[p];
            if (siz[p] > siz[hson[now]]) hson[now] = p;
        }
    }  
}

int htop[MAXN], segi[MAXN], rawi[MAXN];
int tst = 1;
void reindex(int now, int nhtp) {
    htop[now] = nhtp;
    segi[now] = tst;
    rawi[tst] = now; // may needn't
    tst += 1;
    if (hson[now]) reindex(hson[now], nhtp);
    for (int i = head[now]; i != 0; i = e[i].next) {
        int p = e[i].to;
        if (p != fa[now] && p != hson[now]) reindex(p, p);
    }
}

#define INSTALL 1
#define UNINSTALL -1
#define ROOT 1
#define INF 0x3f3f3f3f
#define lson(x) (x<<1)
#define rson(x) ((x<<1)|1)
#define cmid(l, r) ((l+r)>>1)
int tree[MAXN << 2], lazy[MAXN << 2];
inline void change_point(int now, int nl, int nr, int k) {
    tree[now] = k == INSTALL ? (nr - nl + 1) : 
		(k == UNINSTALL ? 0 : tree[now]);
    lazy[now] = k;
}
inline void update(int now) {
    tree[now] = tree[lson(now)] + tree[rson(now)];
}
inline void push_down(int now, int nl, int mid, int nr) {
    if (lazy[now]) {
        change_point(lson(now), nl, mid, lazy[now]);
        change_point(rson(now), mid+1, nr, lazy[now]);
        update(now); // may needn't
        lazy[now] = 0;
    }
}
void build_tree(int now, int nl, int nr) {
    // needn't 
}
void change_range(int now, int nl, int nr, int tl, int tr, int k) {
    if (nr < tl || tr < nl) {
        return;
    } else if (tl <= nl && nr <= tr) {
        change_point(now, nl, nr, k);
    } else {
        int mid = cmid(nl, nr);
        push_down(now, nl, mid, nr);
        change_range(lson(now), nl, mid, tl, tr, k);
        change_range(rson(now), mid+1, nr, tl, tr, k);
        update(now);
    }
}
int ask_range(int now, int nl, int nr, int tl, int tr) {
    if (nr < tl || tr < nl) {
        return 0;
    } else if (tl <= nl && nr <= tr) {
        return tree[now];
    } else {
        int mid = cmid(nl, nr);
        push_down(now, nl, mid, nr);
        return ask_range(lson(now), nl, mid, tl, tr) 
            + ask_range(rson(now), mid+1, nr, tl, tr);
    }
}

int query_subtree(int now) {
    return ask_range(1, 1, n, segi[now], segi[now] + siz[now] - 1);
}
void change_subtree(int now, int k) {
    change_range(1, 1, n, segi[now], segi[now] + siz[now] - 1, k);
}
int query_link(int now) {
    int ret = 0;
    while (htop[now] != ROOT) {
        ret += ask_range(1, 1, n, segi[htop[now]], segi[now]);
        now = fa[htop[now]];
    }
    return ret + ask_range(1, 1, n, segi[ROOT], segi[now]);
}
void change_link(int now, int k) {
    while (htop[now] != ROOT) {
        change_range(1, 1, n, segi[htop[now]], segi[now], k);
        now = fa[htop[now]];
    }
    change_range(1, 1, n, segi[htop[now]], segi[now], k);
}
// i -> i + 1
int main() {
    int m, y, f;
    char op[30];
    scanf("%d", &n);
    for (int i = 1; i <= n-1; i++) {
        scanf("%d", &f);
        build_edge(f+1, i+1);
    }
    build_tree(1, 1, n);
    siz[0] = -INF;
    get_info(1, 1);
    reindex(1, 1);
    scanf("%d", &m);
    for (int i = 1; i <= m; i++) {
        scanf("%s %d", op, &y);
        if (op[0] == 'i') {
            printf("%d\n", dep[y+1] - query_link(y+1));
            change_link(y+1, INSTALL);
        } else {
            printf("%d\n", query_subtree(y+1));
            change_subtree(y+1, -1);
        }
    }
    return 0;
}
