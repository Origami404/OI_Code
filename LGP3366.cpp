#include <cstdio>
#include <algorithm>
using namespace std;
struct Edge{
	int from, to, w;
	bool operator<(const Edge& o) const { return w < o.w; }
} e[200010];
int N,M, ans, cnt, uset[200010];
int find(int x){
	return x==uset[x] ? x : uset[x] = find(uset[x]);
}
void Kruskal(){
	sort(e, e+M);
	for (int i = 0; i < M; i++){
		int u = find(e[i].from), v = find(e[i].to);
		if (u == v) continue;
		uset[v] = u;
		ans += e[i].w;
		if (++cnt == N-1) return;
	}
}
int main(){
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++) uset[i] = i;
	int x, y, z;
	for (int i =0; i < M; i++){
		scanf("%d %d %d", &x, &y, &z);
		e[i].from = x; e[i].to = y; e[i].w = z;
	}
	Kruskal();
	printf("%d", ans);
	return 0;
}



