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
	// �ݹ�߽磺������һ����Ϊ�գ� ֱ�ӷ�����һ���� 
	if (xi == 0 || yi == 0) return xi + yi;
	// ��֤xiΪ�󣨴���Ѿͷ����������Ǹ����������������Ҳ����ֱ�Ӱ����� 
	if (nodes[xi].val > nodes[yi].val 
	   || (nodes[xi].val == nodes[yi].val && xi > yi)) // Ϊ�˱�֤�����ȶ��� 
	   swap(xi, yi);
	// �ݹ���⣬ ���󣨴���ѷ���������������������С������ѷ����������ϲ� 
	nodes[xi].rc = merge(nodes[xi].rc, yi);
	// ���ݣ� ��Ϊֻ��������xi����rc����Ҫ����rc��faָ��xi 
	nodes[nodes[xi].rc].fa = xi;
	// ����ƻ�����ƫ���ʣ���ô�������������Ļ��� 
	if (nodes[nodes[xi].lc].dis < nodes[nodes[xi].rc].dis)
	   swap(nodes[xi].lc, nodes[xi].rc);
    // ����dist�����ýڵ�dist = �ҽڵ㣨dis��С�Ľڵ㣩+ 1������ 
    // ��������ֻ����ڵ�distΪ-1ʱ������������ڵ��dis��Ĭ����0
	// ����ʵ�֣�����Ҫ����0���� 
    nodes[xi].dis = nodes[nodes[xi].rc].dis + 1;
    //�����Ѿ��ϲ���ɵ����� 
    return xi; 
}
inline void pop(int ind){
	   // ������Ŀ����ĿҪ��ɾ���ڵ��val����-1 
	nodes[ind].val = -1;
	// ɾ���Ͱ����������ĸ��ڵ���0���ٺϲ�һ�Σ��ֳ������ٺϲ��� 
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
			// ȥ�������ڵ���������һ���Ͳ��úϲ��� 
			if (nodes[x].val == -1 || nodes[y].val == -1 || x == y)
			   continue;
            // �ҵ����� �ϲ� 
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
