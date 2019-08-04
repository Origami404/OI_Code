#include <cstdio>
#include <algorithm>
using namespace std;
struct Edge{
	int f, t, w;
	bool operator<(const Edge& o) const { return w < o.w; }
} e[100010];
int N, M, uset[1010];
int find(int x){ return x == uset[x] ? x : (uset[x] = find(uset[x])); }
int main(){
	scanf("%d %d",&N, &M);
	for (int i = 0; i < N; i++) uset[i] = i;
	for (int i = 0; i < M; i++) scanf("%d %d %d", &e[i].f, &e[i].t, &e[i].w);
	sort(e, e + M);
	for (int i = 0; i < M; i++){
		int x = find(e[i].f), y = find(e[i].t);
		if (x != y) uset[x] = y, N--;
		if (N == 1) {printf("%d", e[i].w); break;}
	}
	if (N != 1) printf("-1");
	return 0;
}
