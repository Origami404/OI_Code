#include <cstdio>
using namespace std;
#define LTI(x) ((x)<<1)
#define RTI(x) (((x)<<1)|1)
#define MID(l, r) ((l + r)>>1)
#define root 1
#define MAXN 1000007
// 线段树一定是（比较平衡的）完全二叉树, 因为有时候怕访问到叶子节点的子节点, 开4倍
long long tree[MAXN<<2], mark[MAXN<<2], a[MAXN];
// 注意是全闭区间（方便描述线段树）
// 递归来构建树
void build(int now, int l, int r) {
	mark[now] = 0;
	if (l == r) // 叶子节点代表单个点([x, x] == x), 赋值
		tree[now] = a[l];
	else { // 递归
		int mid = MID(l, r);
		build(LTI(now), l, mid); // 左边区间
		build(RTI(now), mid+1, r); // 右边区间
		tree[now] = tree[LTI(now)] + tree[RTI(now)];
	}
}

void app_mark(int now, int nl, int nr, int addv){
	mark[now] += addv;
	tree[now] += addv * (nr - nl + 1);
}
// 标记的下传
void push_down(int now, int nl, int nr) {
	if (mark[now] != 0) {
		// 下传标记
		int mid = MID(nl, nr);
		app_mark(LTI(now), nl, mid, mark[now]);
		app_mark(RTI(now), mid+1, nr, mark[now]);
		// 清空标记
		mark[now] = 0;
	}
}


void change_range(int now, int nl, int nr, int tl, int tr, int addv) {
	// 若无交集：___nl__nr____tl___tr 或 __tl__tr___nl__nr
	if (nr < tl || tr < nl)
		return;
	// 若包含在内
	else if (tl <= nl && nr <= tr) {
		// 啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊
		app_mark(now, nl, nr, addv);
	} else {
		push_down(now, nl, nr);
		int mid = MID(nl, nr);
		change_range(LTI(now), nl, mid, tl, tr, addv);
		change_range(RTI(now), mid+1, nr, tl, tr, addv);
		tree[now] = tree[LTI(now)] + tree[RTI(now)];
	}
}
// 在这里也许叫add_point比较好
void change_point(int now, int nl, int nr, int ind, int addv) {
	/*
	// 如果已经是叶子了就return
	if (nl == nr) {
		// 如果就是要找的节点就修改
		if (ind == nl)
			tree[now] += addv;
		return; // 否则返回
	}
	// 否则分类
	int mid = MID(nl, nr);
	if (ind <= mid) // 左边
		change_point(LTI(now), nl, mid, ind, addv);
	else // 右边
		change_point(RTI(now), mid+1, nr, ind, addv);
	// 更新本节点的值
	tree[now] = tree[LTI(now)] + tree[RTI(now)];
	//*/
	change_range(now, nl, nr, ind, ind, addv);
}

void print_tree(int now, int nl, int nr) {
	push_down(now, nl, nr);
	if (nl == nr) {
		printf("%lld ", tree[now]);
	} else {
		int mid = MID(nl, nr);
		print_tree(LTI(now), nl, mid);
		print_tree(RTI(now), mid+1, nr);
	}
}
// nl, nr是当前区间的首尾， tl, tr是查询目标区间的首尾
// 在这里也许叫sum吧
long long ask(int now, int nl, int nr, int tl, int tr) {
	// 若无交集：___nl__nr____tl___tr 或 __tl__tr___nl__nr
	if (nr < tl || tr < nl)
		return 0;
	// 区间内就直接返回当前节点保存的值
	if (tl <= nl && nr <= tr)
		return tree[now];
	// 下传延迟标记
	push_down(now, nl, nr);
	// 下面的加法是题目要求
	int mid = MID(nl, nr);
	return ask(LTI(now), nl, mid, tl, tr)
	       + ask(RTI(now), mid+1, nr, tl, tr);
}
int main() {
	int n, m, opt, l, r, k;
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++)
		scanf("%lld", a+i);
	build(root, 1, n);
	for (int i = 1; i <= m; i++) {
		scanf("%d %d %d", &opt, &l, &r);
		if (opt == 1) {
			scanf("%d", &k);
			change_range(root, 1, n, l, r, k);
		} else {
			printf("%lld\n", ask(root, 1, n, l, r));
		}
		/*
		printf("DEBUG(tree): ");
		print_tree(1, 1, n);
		printf("\n");
		if (opt == 0)
			break;//*/

	}
	return 0;
}
