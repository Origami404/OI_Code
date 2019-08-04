#include <cstdio>
#include <cstring>
#define MAXN 20007 
using namespace std;
struct Edge {
    int next, to, weight, index;
} e[MAXN << 1];
int head[MAXN], etp = 0;
void build_edge(int f, int t, int w, int i) {
    e[++etp].to = t;
	e[etp].index = i;
    e[etp].weight = w;
    e[etp].next = head[f];
    head[f] = etp;
}
int weight[MAXN], n, btp[MAXN];
int siz[MAXN], fa[MAXN], dep[MAXN], hson[MAXN];
// siz[0] = -INF;
void get_info(int now, int father) {
    dep[now] = dep[father] + 1;
    fa[now] = father;
    siz[now] = 1;
    for (int i = head[now]; i != 0; i = e[i].next) {
        int p = e[i].to;
        if (p != father) {
        	weight[p] = e[i].weight;
			btp[e[i].index] = p;
            get_info(p, now);
            siz[now] += siz[p];
            if (siz[p] > siz[hson[now]]) hson[now] = p;
        }
    }
}

int htop[MAXN], segi[MAXN], rawi[MAXN];
int tst = 1;
void reindex(int now, int nhtp) {
    segi[now] = tst; rawi[tst] = now;
    tst += 1;
	htop[now] = nhtp;
    if (hson[now]) reindex(hson[now], nhtp);
    for (int i = head[now]; i != 0; i = e[i].next) {
    	int p = e[i].to;
		if (p != fa[now] && p != hson[now]) reindex(p, p);
	}
}

inline int max(int a, int b) { return a < b ? b : a; }
inline int min(int a, int b) { return a < b ? a : b; }
#define INF 0x3f3f3f3f
#define lson(x) (x<<1)
#define rson(x) ((x<<1)|1)
#define cmid(l,r) ((l+r)>>1)
int tsum[MAXN << 2], tmax[MAXN << 2], tmin[MAXN << 2];
int lazy[MAXN << 2];
inline void update(int now) {
	int l = lson(now), r = rson(now);
	tsum[now] = tsum[l] + tsum[r];
	tmax[now] = max(tmax[l], tmax[r]);
	tmin[now] = min(tmin[l], tmin[r]);
}
inline void neg_point(int now) {
	int rmax = tmax[now];
	tmax[now] = -tmin[now];
	tmin[now] = -rmax;
	tsum[now] = -tsum[now];
	lazy[now] = !(lazy[now]);
}
inline void push_down(int now) {
	if (lazy[now]) {
		neg_point(lson(now));
		neg_point(rson(now));
		update(now);
		lazy[now] = 0;
	}
}
void build_tree(int now, int nl, int nr) {
	if (nl == nr) {
		if (nl == 1) {
			tsum[now] = 0; tmax[now] = -INF; tmin[now] = INF;
		} else {
			tsum[now] = tmax[now] = tmin[now] = weight[rawi[nl]];
		}
	} else {
		int mid = cmid(nl, nr);
		build_tree(lson(now), nl, mid);
		build_tree(rson(now), mid+1, nr);
		update(now);
	}
}
void change_point(int now, int nl, int nr, int ti, int k) {
	if (nl == nr && nr == ti) {
		if (nl != 1) {
			tsum[now] = tmax[now] = tmin[now] = k;
		}
	} else {
		int mid = cmid(nl, nr);
		push_down(now);
		if (ti <= mid) change_point(lson(now), nl, mid, ti, k);
		else change_point(rson(now), mid+1, nr, ti, k);
		update(now);
	}
}
void neg_range(int now, int nl, int nr, int tl, int tr) {
	if (nr < tl || tr < nl) {
		return;
	} else if (tl <= nl && nr <= tr) {
		if (!(nl == 1 && nr == 1)) neg_point(now);
	} else {
		int mid = cmid(nl, nr);
		push_down(now);
		neg_range(lson(now), nl, mid, tl, tr);
		neg_range(rson(now), mid+1, nr, tl, tr);
		update(now);
	}
}
int ask_sum(int now, int nl, int nr, int tl, int tr) {
	if (nr < tl || tr < nl) {
		return 0;
	} else if (tl <= nl && nr <= tr) {
		return tsum[now];
	} else {
		int mid = cmid(nl, nr);
		push_down(now);
		return ask_sum(lson(now), nl, mid, tl, tr)
			+ ask_sum(rson(now), mid+1, nr, tl, tr);
	}
}
int ask_max(int now, int nl, int nr, int tl, int tr) {
	if (nr < tl || tr < nl) {
		return -INF;
	} else if (tl <= nl && nr <= tr) {
		return tmax[now];
	} else {
		int mid = cmid(nl, nr);
		push_down(now);
		return max(ask_max(lson(now), nl, mid, tl, tr),
			ask_max(rson(now), mid+1, nr, tl, tr));
	}
}
int ask_min(int now, int nl, int nr, int tl, int tr) {
	if (nr < tl || tr < nl) {
		return INF;
	} else if (tl <= nl && nr <= tr) {
		return tmin[now];
	} else {
		int mid = cmid(nl, nr);
		push_down(now);
		return min(ask_min(lson(now), nl, mid, tl, tr), 
			ask_min(rson(now), mid+1, nr, tl, tr));
	}
}

inline void swap(int &a, int &b) { int t = a; a = b; b = t; }

int query_link_max(int x, int y) {
	int ret = -INF;
	while (htop[x] != htop[y]) {
		if (!(dep[htop[x]] > dep[htop[y]])) swap(x, y);
		ret = max(ret, ask_max(1, 1, n, segi[htop[x]], segi[x]));
		x = fa[htop[x]];
	}
	if (!(dep[x] > dep[y])) swap(x, y);
	return max(ret, ask_max(1, 1, n, segi[y] + 1, segi[x]));
}

int query_link_min(int x, int y) {
	int ret = INF;
	while (htop[x] != htop[y]) {
		if (!(dep[htop[x]] > dep[htop[y]])) swap(x, y);
		ret = min(ret, ask_min(1, 1, n, segi[htop[x]], segi[x]));
		x = fa[htop[x]];
	}
	if (!(dep[x] > dep[y])) swap(x, y);
	return min(ret, ask_min(1, 1, n, segi[y] + 1, segi[x]));
}

int query_link_sum(int x, int y) {
	int ret = 0;
	while (htop[x] != htop[y]) {
		if (!(dep[htop[x]] > dep[htop[y]])) swap(x, y);
		ret += ask_sum(1, 1, n, segi[htop[x]], segi[x]);
		x = fa[htop[x]];
	}
	if (!(dep[x] > dep[y])) swap(x, y);
	return ret + ask_sum(1, 1, n, segi[y] + 1, segi[x]);
}

inline void diff_point(int x, int k) {
	change_point(1, 1, n, segi[x], k);
}

void neg_link(int x, int y) {
	while (htop[x] != htop[y]) {
		if (!(dep[htop[x]] > dep[htop[y]])) swap(x, y);
		neg_range(1, 1, n, segi[htop[x]], segi[x]);
		x = fa[htop[x]];
	}
	if (!(dep[x] > dep[y])) swap(x, y);
	neg_range(1, 1, n, segi[y] + 1, segi[x]);
}
inline void fsrs(char* buf) {
	int c = getchar(), pos = 0;
	while (c < 'A' || 'Z' < c) c = getchar();
	while ('A' <= c && c <= 'Z') {
		buf[pos++] = c;
		c = getchar();
	}
	buf[pos] = '\0';
}
inline void fsrd(int &p) {
	int c = getchar(), sgn = 0; p = 0;
	while (c < '0' || '9' < c) {
		if (c == '-') sgn = 1;
		c = getchar();
	}
	while ('0' <= c && c <= '9') {
		p = p*10 + (c-'0');
		c = getchar();
	}
	p = sgn ? -p : p;
}
void array_print(const char* prefix, int* arr, int siz) {
	printf(prefix);
	for (int i = 1; i <= siz; i++) printf("%d ", arr[i]);
	puts("");
}
int main() {
	fsrd(n);
	for (int i = 1; i < n; i++) {
		int f = 0, t = 0, w = 0;
		fsrd(f), fsrd(t), fsrd(w);
		build_edge(f + 1, t + 1, w, i);
		build_edge(t + 1, f + 1, w, i);
	}
	siz[0] = -INF;
	get_info(1, 1);
	reindex(1, 1);
	build_tree(1, 1, n);
	/*
	array_print("DEBUG(dep): ", dep, n);
	array_print("DEBUG(weight): ", weight, n);
	array_print("DEBUG(htop): ", htop, n);
	array_print("DEBUG(fa): ", fa, n);
	array_print("DBEUG(segi): ", segi, n);
	array_print("DEBUG(hson): ", hson, n);
	array_print("DBEUG(tsum): ", tsum, n<<2);
	//*/
	//array_print("DEBUG(btp): ", btp, n << 1);
	int m = 0;
	fsrd(m);
	for (int i = 1; i <= m; i++) {
		char op[10] = {0}; int u = 0, v = 0;
		fsrs(op), fsrd(u), fsrd(v);
		#define STREQ(x) (strcmp(op, x) == 0)
		if (STREQ("C")) {
			diff_point(btp[u], v);
		} else if (STREQ("N")) {
			neg_link(u + 1, v + 1);
		} else if (STREQ("SUM")) {
			//printf("ENTER SUM\n");
			printf("%d\n", query_link_sum(u + 1, v + 1));
		} else if (STREQ("MAX")) {
			printf("%d\n", query_link_max(u + 1, v + 1));
		} else /* if (STREQ("MIN")) */ {
			printf("%d\n", query_link_min(u + 1, v + 1));
		}
	}
    return 0;
}
