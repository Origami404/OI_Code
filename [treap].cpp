#include <cstdio>
#include <cstdlib>
#include <algorithm>
#define LT 0
#define RT 1
#define LTI(ni) tree[ni].child[0]
#define RTI(ni) tree[ni].child[1]
#define MAXN 100007
#define INF 10000007
using namespace std;
// LT < node < RT
struct Node {
	//  值， 堆键，子树编号，同样的值的数量， 以自己为根的树的大小
	int value, aux, child[2], cnt, size;
} tree[MAXN];
int root = 0, ttop = 1;
void init() {
	srand(20021104);
	tree[root].aux = RAND_MAX; // rand(): 0 ~ RAND_MAX
	tree[root].size = 0;
}
inline void update_size(int ni) {
	tree[ni].size = tree[tree[ni].child[LT]].size + tree[ni].cnt
	                + tree[tree[ni].child[RT]].size;
}

// 可以把左右rotate统一起来
inline void rotate(int& xi, int type) {
	int yi = tree[xi].child[type];
	/* ----------------- key -------------------- */
	tree[xi].child[type] = tree[yi].child[1-type];
	tree[yi].child[1-type] = xi;
	/* ----------------- key -------------------- */
	update_size(xi), update_size(yi); // 更新一下
	xi = yi; // 修改传入xi，保持对当前的引用
}

// 方便递归查找
void _insert (int& xi, int value) {
	//*
	if (xi == 0) { // 没有这个值的节点(xi为0时满足此条件)
		xi = ++ttop; // 修改传入的指针！！！也就是修改root
		tree[xi].value = value;
		tree[xi].cnt = 1;
		tree[xi].aux = rand();
		tree[xi].child[LT] = tree[xi].child[RT] = 0;
	} else if (tree[xi].value == value) { // 有这个值的节点
		tree[xi].cnt++;
	} else { // 还需要递归
		int type = tree[xi].value < value; // BST的性质
		_insert(tree[xi].child[type], value); // 递归
		// 若破坏了堆就转一转
		if (tree[tree[xi].child[type]].aux < tree[xi].aux)
			rotate(xi, type);
	}
	update_size(xi);
	//printf("DEBUG(last xi, value):%d %d\n", xi, value);
}
inline void insert(int value) {
	_insert(root, value);
}

// 方便递归删除
void _erase(int& xi, int value) {
	if (xi == 0) return;
	if (tree[xi].value == value) { // 如果有这节点
		if (tree[xi].cnt > 1) { // 多于一个
			tree[xi].cnt--;
		} else { // 只有一个的话就要去掉这节点了
			if (!tree[xi].child[LT] && !tree[xi].child[RT]) { //左右子树都空的话
				xi = 0;  // 直接删除, 才怪, 直接去掉外层对它的引用
				return;
			}
			// 这里逻辑其实有点复杂
			/*
			 * 如果没有RT就Left转
			 * 如果没有LT就Right转
			 * 否则那边aux小就那边转
			 */
			// 由于空的节点指向的tree[0].aux为-1肯定小, 于是只要考虑aux就好
			int type =
			    tree[tree[xi].child[LT]].aux > tree[tree[xi].child[RT]].aux;
			rotate(xi, type);
			// 转完了就继续尝试删除直到完成
			_erase(xi, value);
		}
	} else { // 如果还没找到这节点, 就继续按BST性质往下找
		_erase(tree[xi].child[value > tree[xi].value], value);
	}
	update_size(xi);
}
inline void erase(int value) {
	_erase(root, value);
}

int _getKth(int& xi, int k) {
	//printf("DEBUG(getKth:xi, k)%d %d\n", xi, k);
	// 如果k比LT的size还小，那么第k大的一定在LT那里
	if (k <= tree[tree[xi].child[LT]].size)
		return _getKth(tree[xi].child[LT], k);

	// 否则把k减去自己前面的和自己的数量
	k -= tree[tree[xi].child[LT]].size + tree[xi].cnt;
	// 因为前面判断了k和LT的size, 所以这里为负的唯一可能就是第k大数是当前值
	if (k <= 0)
		return tree[xi].value;
	// 如果k还有, 说明在RT那边
	else return _getKth(tree[xi].child[RT], k);
}
inline int getKth(int k) {
	return _getKth(root, k);
}
Node& _find(int& xi, int value) {
	//printf("DEBUG(find:xi) %d\n", xi);
	if (tree[xi].value == value)
		return tree[xi];
	else if (value < tree[xi].value)
		return _find(tree[xi].child[LT], value);
	else if (value > tree[xi].value)
		return _find(tree[xi].child[RT], value);
}
Node& find(int value) {
	return _find(root, value);
}
int _get_rank(int xi, int value) {
	if (xi == 0) return 1;
	if (value <= tree[xi].value) return _get_rank(LTI(xi), value);
	else return _get_rank(RTI(xi), value) + tree[LTI(xi)].size + tree[xi].cnt; 
}
inline int get_rank(int value){
	return _get_rank(root, value);
}
int _front(int xi, int value) {
	int best;
	while(xi){
		if (tree[xi].value < value)
			(best = tree[xi].value), (xi = RTI(xi));
		else xi = LTI(xi);
	}
	return best;
}
inline int front(int value) {
	return _front(root, value);
}
int _next(int xi, int value) {
	int best;
	while (xi){
		if (tree[xi].value > value)
			(best = tree[xi].value), (xi = LTI(xi));
		else xi = RTI(xi);
	}
	return best;
}
inline int next(int value) {
	return _next(root, value);
}
int main() {
	int n, opt, v;
	scanf("%d", &n);
	init();
	for (int i = 0; i < n; i++) {
		scanf("%d %d", &opt, &v);
		switch (opt) {
			case 1:
				insert(v);
				break;
			case 2:
				erase(v);
				break;
			case 3:
				printf("%d\n", get_rank(v));
				break;
			case 4:
				printf("%d\n", getKth(v));
				break;
			case 5:
				printf("%d\n", front(v));
				break;
			case 6:
				printf("%d\n", next(v));
				break;
			default:
				break;
		}
	}
	return 0;
}
