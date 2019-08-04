#include <cstdio>
using namespace std;
int N, data[35][35];
bool vis[35][35];
int tc[5] = {1, 0, -1, 0, 1};
bool dfs(int x, int y) {
	//printf("DEBUG(x, y): %d %d\n", x, y);
	if (x >= N || y >= N || x < 0 || y < 0 || data[x][y] == 3)
		return false;
	if (vis[x][y] || data[x][y] == 1 || data[x][y] == 2)
		return true;
	vis[x][y] = true;
	bool is_in = dfs(x+1, y) && dfs(x-1, y) && dfs(x, y +1) && dfs(x, y -1);
	vis[x][y] = false;
	data[x][y] = is_in ? 2 : 3;
	return is_in;
}
int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			scanf("%d", &data[i][j]);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			dfs(i, j);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			printf("%d ", data[i][j] == 3 ? 0 : data[i][j]);
		printf("\n");
	}
	return 0;
}
