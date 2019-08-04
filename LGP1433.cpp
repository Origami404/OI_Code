#include <cstdio>
#include <cmath>
#define MAXN 20
using namespace std;
bool vis[MAXN];
double dis[MAXN][MAXN],x[MAXN], y[MAXN], minl = 9e60;
int n;
void dfs(int from, int cnt, double ln){
	if (cnt == n  && ln < minl) {minl = ln; return;}
	for (int i = 1; i <= n; i ++){
		if (!vis[i] && dis[from][i] + ln < minl){
			vis[i] = true;
			dfs(i, cnt + 1, dis[from][i] + ln);
			vis[i] = false;
		}
	}
}
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%lf %lf", x + i, y+i);
	x[0] = y[0] = 0;
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= n; j++) {
			if (i == j) dis[i][j] = 0.0;
			else dis[i][j]=sqrt((x[i]-x[j])*(x[i]-x[j])
					       +(y[i]-y[j])*(y[i]-y[j]));
		}
	}
	vis[0] = true;
	dfs(0, 0, 0.0);
	printf("%.2f", minl);
	return 0;
}
