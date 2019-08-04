#include <cstdio>
#include <cstring>
#include <queue>
#define INF 2147483647
using namespace std;
struct Edge {
	int to, weight, next;
} e[1000010];
int head[20010], etop, N, M, S;
long long dis[20010];
bool vis[20010] = {0};
inline void build(int from, int to, int weight) {
	e[etop].to = to;
	e[etop].weight = weight;
	e[etop].next = head[from];
	head[from] = etop++;
}
void spfa(int start) {
	queue<int> q;
	q.push(start);
	dis[start] = 0;
	vis[start] = true;
	while (!q.empty()) {
		int now = q.front();
		q.pop();
		vis[now] = false;
		for (int i = head[now]; i != -1; i = e[i].next) {
			if (dis[e[i].to] > dis[now] + e[i].weight) {
				dis[e[i].to] =  dis[now] + e[i].weight;
				if (!vis[e[i].to]) {
					q.push(e[i].to);
					vis[e[i].to] = true;
				}
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
	spfa(S);
	for (int i = 1; i <= N; i++)
		printf("%lld ", dis[i]);
	return 0;
}





