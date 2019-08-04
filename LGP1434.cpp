#include <algorithm>
#include <cstdio>
#include <cstring>
#define MAXN 1100
using namespace std;
int R, C, high[MAXN][MAXN];
int ans = 0, maxl[MAXN][MAXN];
int dlt[2][4] = {{0, 0, 1, -1}, {1, -1, 0, 0}};
int dfs(int x, int y) {
	if (maxl[x][y] != 1)
		return maxl[x][y];
	// maxl[x][y] = cnt;
	// ans = ans > cnt ? ans : cnt;
	int nh = high[x][y], t = 1;
	for (int i = 0; i < 4; i++) {
		int nx = x + dlt[0][i], ny = y + dlt[1][i];
		if (nx >= 1 && ny >= 1 && x <= R && y <= C && high[nx][ny] < nh)
			t = max(dfs(nx, ny) + 1, t);
	}
	maxl[x][y] = max(maxl[x][y], t);
	return maxl[x][y];
}
int main() {
	//memset(maxl, 1, sizeof(maxl));
	scanf("%d %d", &R, &C);
	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			scanf("%d", &high[i][j]);
			maxl[i][j] = 1;
		}
	}


	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			maxl[i][j] = dfs(i, j);
			ans = max(ans, maxl[i][j]);
		}
	}
	printf("%d\n", ans);
	return 0;
}
