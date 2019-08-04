#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#define INF 0x3fffffff
using namespace std;
struct Edge{
	int to, weight, next;
} e[400005];
int etop, N, M, cnt, ans, head[5005], dis[5005], vis[5005];
void Build(int from, int to, int weight){
	e[++etop].to = to;
	e[etop].weight = weight;
	e[etop].next = head[from];
	head[from] = etop;
}
typedef pair<int, int> iip_t; // weight, to
priority_queue<iip_t, vector<iip_t>, greater<iip_t> >Q;
void prim(int start) { 
	 dis[start] = 0;
	 Q.push(make_pair(0, start));
	 while (!Q.empty() && cnt < N){
	 	iip_t now = Q.top();
	 	Q.pop();
	 	if (vis[now.second]) continue;
	 	cnt++;
	 	ans+=now.first;
	 	vis[now.second] = 1;
	 	for (int i = head[now.second]; i != -1; i = e[i].next){
	 		if (e[i].weight < dis[e[i].to]){
	 			dis[e[i].to] = e[i].weight;
	 			Q.push(make_pair(dis[e[i].to], e[i].to));
			 }
		 }
	 }
}
int main(){
	memset(dis, 0x3f, sizeof(dis));
	memset(head, -1, sizeof(head));
	scanf("%d %d", &N, &M);
	int x, y, z;
	for (int i = 1; i <= M; i++){
		scanf("%d %d %d", &x, &y, &z);
		Build(x, y, z);
		Build(y, x, z);
	}
	prim(1);
	if (cnt == N) printf("%d", ans);
	else printf("orz");
	return 0;
}
