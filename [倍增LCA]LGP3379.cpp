#include <cstdio>
// ������Ԥ����emmm.... 
#define MAXN 500007
#define LOG_MAXN 21
// Ϊ��ĳ�̶ֳȵĿɶ��԰�... 
#define exp2(i) (1<<i)
#define is_deeper_after_up_exp2i(a, b, i) \
	dep[(b)] <= dep[(a)] - exp2((i))
#define up_exp2i(x, i) ((x) = nxt[(x)][(i)])
using namespace std;
// ǰ����
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

// dep[i]��ʾi�����, rootΪ 1 , Խ��Խ��
// nxt[n][k]��ʾn�ڵ�����2^k���ڵ��Ľڵ���, �����Ժ����0
// ������ʵ�ڳ�ʼ��ʱ��Զ������ʵ�0 (��Ϊdfs���ж���now�����ʼ��λ�õ�����Ա�֤����)
// ��lca�з��ʵ���Ҳ����ν, ��Ϊ0���κνڵ㶼����ͬ, ���Կ��Է��ĵıȽ� 
int dep[MAXN], nxt[MAXN][LOG_MAXN], n, m, root;

// ����dfs��ʼ��
void dfs(int now,int father) {
	dep[now] = dep[father] + 1;
	nxt[now][0] = father;
	// ��2^i�����С��now(Ҳ���ǻ�û��)�������
	for (int i = 1; exp2(i) <= dep[now]; i++)
		// ���� 2^(i-1) + 2^(i-1) == 2^i ������
		nxt[now][i] = nxt[nxt[now][i-1]][i-1];
	for (int i = head[now]; i != 0; i = e[i].next)
		if (e[i].to != father) // ����ͼ����
			dfs(e[i].to, now);
}
inline int lca(int x, int y) {
	// ��xΪ��ȴ��
	if (dep[x] < dep[y])
		swap(x, y);
	
	// Q: Ϊʲô�����Ӿ��ܱ�֤�����ͬ��? 
	// ���γ�������2^i��
	for (int i = LOG_MAXN - 1; i >= 0; i--)
		// ����x��y���������yһ����
		// ��Ϊ2^0 == 1, ���Կ϶��ܱ�֤���һ����
		// ��������Ȳ�ΪH, ��ô���ݶ����Ʒֽ�Hһ���ܱ���ʾ
		if (is_deeper_after_up_exp2i(x, y, i))
			up_exp2i(x, i);
	
	// Q: ΪʲôҪ������? 
	// ����, ���ȥ���Ļ��ڸոպ�x����lca(x,y)ʱ�ͻ᷵��x�ĸ��ڵ��� 
	if (x == y)
		return x;
	
	// һֱ���Ե�nxt[x][0](���ڵ�)�����������Ƕ�lca��lca������ 
	for (int i = LOG_MAXN - 1; i >= 0; i--)
		// һ���Ļ��������ǵ�lca��lca������ 
		// Q: Ϊʲô����ֱ��һ��forѭ��? ��һ�ƶ���֮��Ҫ����һ���ȵ�ǰi���2������? 
		// �����˽ϴ���ݲ���֮��Ϳ���һֱ���ó�������
		// ��Ϊ����ں��滹��Ҫ����ݵĻ�, ˵��ǰ��Ϳ����������  
		if (nxt[x][i] != nxt[y][i]) 
			up_exp2i(x, i), up_exp2i(y, i);
	// һֱ�����ǵĸ��ڵ㶼��lca��lca������ 
	// ��ô���ǵĸ��ڵ��һ����lca��, ��Ϊ�������ڵ���������С 
	return nxt[x][0];
}
int main() {
	scanf("%d %d %d", &n, &m, &root);
	int x, y, a, b;
	for (int i = 0; i < n-1; i++) {
		scanf("%d %d", &x, &y);
		// Q: ����ͼ? �ѵ�������ֱ�Ӵ�ָ��/�ӽڵ�ı���? 
		// Ҫ������ͼ, ��Ϊ��һ�����Ǹպ�x����y��father
		build(x, y);
		build(y, x);
	}
	// ��ʼ��
	dfs(root, 0);
	for (int i = 0; i < m; i++) {
		scanf("%d %d", &a, &b);
		printf("%d\n", lca(a, b));
	}
	return 0;
}



