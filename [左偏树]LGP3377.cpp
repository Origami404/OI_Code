#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
typedef int T;
const int MAXN = 100000 + 7;
struct Node {
	T val;
	int dis, lc, rc, fa;
} nodes[MAXN];
inline int top_ind(int ind){
	while (nodes[ind].fa) ind = nodes[ind].fa;
	return ind;
}
int merge(int xi, int yi){
	// 递归边界：有任意一颗树为空， 直接返回另一棵树 
	if (xi == 0 || yi == 0) return xi + yi;
	// 保证xi为大（大根堆就反过来）的那个，方便下面操作，也可以直接绑引用 
	if (nodes[xi].val > nodes[yi].val 
	   || (nodes[xi].val == nodes[yi].val && xi > yi)) // 为了保证排序稳定性 
	   swap(xi, yi);
	// 递归求解， 将大（大根堆反过来）的树的右子树与小（大根堆反过来）树合并 
	nodes[xi].rc = merge(nodes[xi].rc, yi);
	// 回溯， 因为只是连接了xi与现rc，还要让现rc的fa指回xi 
	nodes[nodes[xi].rc].fa = xi;
	// 如果破坏了左偏性质，那么交换左右子树改回来 
	if (nodes[nodes[xi].lc].dis < nodes[nodes[xi].rc].dis)
	   swap(nodes[xi].lc, nodes[xi].rc);
    // 更新dist，利用节点dist = 右节点（dis较小的节点）+ 1的性质 
    // 上述性质只在外节点dist为-1时成立，但是外节点的dis我默认是0
	// 方便实现，所以要根据0特判 
    nodes[xi].dis = nodes[nodes[xi].rc].dis + 1;
    //返回已经合并完成的树根 
    return xi; 
}
inline void pop(int ind){
	   // 方便题目，题目要求被删除节点的val返回-1 
	nodes[ind].val = -1;
	// 删除就把左右子树的父节点搞成0，再合并一次（分成两堆再合并） 
	nodes[nodes[ind].rc].fa = nodes[nodes[ind].lc].fa = 0;
	merge(nodes[ind].rc, nodes[ind].lc);
	//nodes[ind].fa = 0; 
}
int main(){
	memset(nodes, 0, sizeof(nodes));
	nodes[0].dis = -1;
	int n, m;
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++)
		scanf("%d", &nodes[i].val);
	for (int i = 1; i <= m; i++){
		int x, y, opc;
		scanf("%d", &opc);
		if (opc == 1){
			scanf("%d %d", &x, &y);
			// 去掉不存在的情况，如果一样就不用合并了 
			if (nodes[x].val == -1 || nodes[y].val == -1 || x == y)
			   continue;
            // 找到根， 合并 
			merge(top_ind(x), top_ind(y));
		} else if (opc == 2){
			scanf("%d", &x);
			if (nodes[x].val == -1) printf("-1\n");
			else{
				int x_top = top_ind(x); 
				printf("%d\n", nodes[x_top].val);
				pop(x_top);
			} 
		}
	}
	return 0;
}
