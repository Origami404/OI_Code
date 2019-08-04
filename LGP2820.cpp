#include <cstdio>
#include <algorithm>
#define MAXN 107
using namespace std;
int n, k, i, j, m;
/*
struct Edge{
	int to, next, weight;
} e[MAXN];
int head[MAXN], etop = 0;
void build(int from, int to, int weight){
	e[++etop].to = to;
	e[etop].weight = weight;
	e[etop].next = head[from];
	head[from] = etop;
}//*/
struct Edge {
	int from, to, weight;
	bool operator<(const Edge& o) const {
		return weight < o.weight;
	}
} e[MAXN<<2];
int etop = 0, uset[MAXN];
inline int find(int x) {
	return x == uset[x] ? x : (uset[x] = find(uset[x]));
}
inline void merge(int a, int b) {
	uset[find(a)] = find(b);
}

int Kru(int start) {
	int ans = 0, cnt = 0;
	sort(e, e+etop);
	for (int i = 0; i < etop; i++) {
		if (find(e[i].to) != find(e[i].from)) {
			merge(e[i].to, e[i].from);
			ans += e[i].weight;
			cnt++;
		}
		if (cnt == n-1)
			break;
	}
	return ans;
}
int main() {
	int tot = 0;
	scanf("%d %d", &n, &k);
	for (int x = 1; x <= k; x++) {
		scanf("%d %d %d", &i, &j, &m);
		e[etop++] = (Edge) {
			i, j, m
		};
		e[etop++] = (Edge) {
			j, i, m
		};
		tot += m;
	}
	for (int i = 1; i <= n; i++)
		uset[i] = i;
	printf("%d\n", tot - Kru(1));
	return 0;
}

