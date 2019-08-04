#include <cstdio>
// 计算器预处理emmm.... 
#define MAXN 500007
#define LOG_MAXN 21
// 为了某种程度的可读性吧... 
#define exp2(i) (1<<i)
#define is_deeper_after_up_exp2i(a, b, i) \
	dep[(b)] <= dep[(a)] - exp2((i))
#define up_exp2i(x, i) ((x) = nxt[(x)][(i)])
using namespace std;
// 前向星
struct Edge {
	int to, next;
} e[MAXN<<1];
int head[MAXN], etop = 0;
void build(int from, int to) {
	e[++etop].to = to;
	e[etop].next = head[from];
	head[from] = etop;
}
inline void swap(int& x, int& y) {
	int t = x;
	x = y;
	y = t;
}

// dep[i]表示i的深度, root为 1 , 越深越大
// nxt[n][k]表示n节点往上2^k个节点后的节点编号, 爆了以后就是0
// 但是其实在初始化时永远不会访问到0 (因为dfs中判断了now与待初始化位置的深度以保证存在)
// 在lca中访问到了也无所谓, 因为0与任何节点都不相同, 所以可以放心的比较 
int dep[MAXN], nxt[MAXN][LOG_MAXN], n, m, root;

// 利用dfs初始化
void dfs(int now,int father) {
	dep[now] = dep[father] + 1;
	nxt[now][0] = father;
	// 在2^i的深度小于now(也就是还没爆)的情况下
	for (int i = 1; exp2(i) <= dep[now]; i++)
		// 利用 2^(i-1) + 2^(i-1) == 2^i 来更新
		nxt[now][i] = nxt[nxt[now][i-1]][i-1];
	for (int i = head[now]; i != 0; i = e[i].next)
		if (e[i].to != father) // 无向图防环
			dfs(e[i].to, now);
}
inline int lca(int x, int y) {
	// 令x为深度大的
	if (dep[x] < dep[y])
		swap(x, y);
	
	// Q: 为什么这样子就能保证深度相同呢? 
	// 依次尝试往上2^i步
	for (int i = LOG_MAXN - 1; i >= 0; i--)
		// 保持x比y深或至少与y一样深
		// 因为2^0 == 1, 所以肯定能保证最后一样深
		// 或者设深度差为H, 那么根据二进制分解H一定能被表示
		if (is_deeper_after_up_exp2i(x, y, i))
			up_exp2i(x, i);
	
	// Q: 为什么要特判呢? 
	// 特判, 如果去掉的话在刚刚好x就是lca(x,y)时就会返回x的父节点了 
	if (x == y)
		return x;
	
	// 一直尝试到nxt[x][0](父节点)都可能是他们都lca或lca的祖先 
	for (int i = LOG_MAXN - 1; i >= 0; i--)
		// 一样的话就是他们的lca或lca的祖先 
		// Q: 为什么可以直接一次for循环? 万一移动了之后还要向上一个比当前i大的2的幂呢? 
		// 尝试了较大的幂不行之后就可以一直不用尝试它了
		// 因为如果在后面还需要这个幂的话, 说明前面就可以跳这个幂  
		if (nxt[x][i] != nxt[y][i]) 
			up_exp2i(x, i), up_exp2i(y, i);
	// 一直到他们的父节点都是lca或lca的祖先 
	// 那么他们的父节点就一定是lca了, 因为与其他节点相比深度最小 
	return nxt[x][0];
}
int main() {
	scanf("%d %d %d", &n, &m, &root);
	int x, y, a, b;
	for (int i = 0; i < n-1; i++) {
		scanf("%d %d", &x, &y);
		// Q: 无向图? 难道不可以直接存指向父/子节点的边吗? 
		// 要存无向图, 因为不一定就是刚好x就是y的father
		build(x, y);
		build(y, x);
	}
	// 初始化
	dfs(root, 0);
	for (int i = 0; i < m; i++) {
		scanf("%d %d", &a, &b);
		printf("%d\n", lca(a, b));
	}
	return 0;
}



