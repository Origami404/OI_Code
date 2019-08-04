#include <cstdio>
int p[10010], N, M;
int find(int x){
	return p[x] == x ? x : p[x] = find(p[x]);
}
inline void init(){
	for (int i = 1; i <= N; i++)
		p[i] = i;
}
inline void merge(int x, int y){
	p[find(x)] = find(y);
}
using namespace std;
int main(){
	scanf("%d %d", &N, &M);
	init();
	int z, x, y;
	for (int i = 1; i <= M; i++){
		scanf("%d %d %d", &z, &x, &y);
		if (z == 1) merge(x,y);
		if (z == 2) {
			if (find(x) == find(y)) printf("Y\n");
			else printf("N\n");
		}
	}
	return 0;
}
