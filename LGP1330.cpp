#include <cstdio>
using namespace std;
struct Edge{
	int to, next;
} e[200010];
int etop = 0, color[20010],head[200010], N, M, bcnt = 0, wcnt = 0, ans = 0;
void build(int from, int to){
	e[++etop].to = to; 
	e[etop].next = head[from];
	head[from] = etop;
}
bool dfs(int now, int nc){
	if (color[now]){
		if (color[now] == nc) return true;
		else return false;
	}
	color[now] = nc;
	nc == 1 ? bcnt++ : wcnt++;
	bool res = true;
	for (int i = head[now]; i != 0; i = e[i].next){
		res = res && dfs(e[i].to, nc == 1 ? 2 : 1);
	}
	return res;
}
int main(){
	scanf("%d %d", &N, &M);
	for (int i = 0; i < M ; i++){
		int a, b;
		scanf("%d %d", &a, &b);
		build(a, b);
		build(b, a);
	}
	for (int i = 1; i <= N; i++){
		if (color[i]) continue;
		bcnt = wcnt = 0;
		if (!dfs(i, 1)){
			printf("Impossible");
			return 0;
		}
		ans += bcnt > wcnt ? wcnt : bcnt;
	}
	printf("%d", ans);
	return 0;
}
