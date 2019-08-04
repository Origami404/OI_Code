#include <cstdio>
#include <cstring>
#include <algorithm>
#define INF 2147483647
using namespace std;
struct Edge {
	int to, weight, next;
} e[1000010];
int head[20010], etop = 0, N, M, S;
bool vis[20010];
long long dis[20010];
inline void build(int from, int to, int weight) {
	e[etop].to = to;
	e[etop].weight = weight;
	e[etop].next = head[from];
	head[from] = etop++;
}
void Dijkstra(int start) {
	int now = start;
	long long minl = INF;
	dis[now] = 0;
	while (!vis[now]) {
		vis[now] = true;
		for (int i = head[now]; i != -1; i = e[i].next) {
			if (!vis[e[i].to] && dis[e[i].to] > dis[now] + e[i].weight)
				dis[e[i].to] = dis[now] + e[i].weight;
		}
		minl = INF;
		for (int i = 1; i <= N; i++) {
			if (!vis[i] && minl > dis[i]) {
				minl = dis[i];
				now = i;
			}
		}
	}
}

int main() {
	memset(head, -1, sizeof(head));
	scanf("%d %d %d", &N, &M, &S);
	for (int i = 1; i <= N; i++)
		dis[i] = INF;
	int f, g, w;
	for (int i = 1; i <= M; i++) {
		scanf("%d %d %d", &f, &g, &w);
		build(f, g, w);
	}
	Dijkstra(S);
	for (int i = 1; i <= N; i++)
		printf("%lld ", dis[i]);
	return 0;
}




