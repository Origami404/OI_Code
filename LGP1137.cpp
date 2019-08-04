#include <cstdio>
#include <cstring>
#define MAXN 200007
using namespace std;
/*
#define push(i) _stack[_stop++] = i
#define pop(i) _stack[--_stop]
#define top() _stack[_stop]
#define size() _stop
int _stack[MAXN], _stop = 0;
//*/
struct Edge{
	int to, next;
} e[MAXN];
int head[MAXN], etop = 0;
void build(int from, int to){
	e[++etop].to = to;
	e[etop].next = head[from];
	head[from] = etop;
}

inline int max(int a, int b){
	return a > b ? a : b;
}
int max_cnt[MAXN];
int dfs(int fa, int now){
	if (max_cnt[now] != -1)
		return max_cnt[now];
	int ans = 1;
	for (int i = head[now]; i != 0; i = e[i].next){
		if (e[i].to == fa) continue;
		ans = max(ans, dfs(now, e[i].to) + 1);	
	}
	return (max_cnt[now] = ans);
}
//int in[MAXN], out[MAXN];
int n, m, x, y;
void print_edge(int now){
	printf("DEBUG: ");
	for (int i = head[now]; i != 0; i = e[i].next){
		printf("%d ", e[i].to);
	}
	printf("\n");
}
int main(){
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= m; i++){
		scanf("%d %d", &x, &y);
		//in[y]++, out[x]++;
		build(y, x);
	}
	//print_edge(3);
	memset(max_cnt, -1, sizeof(max_cnt));
	//printf("DEBUG: OUTPUT\n");
	for (int i = 1; i <= n; i++){
		printf("%d\n", dfs(-1, i));
	}
	return 0;
}
