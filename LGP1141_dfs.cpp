#include <cstdio>
#include <cstring>
#define check(x,y) (x>0&&(x<=n)&&y>0&&(y<=n))
#define SIZE 1010
char mg[SIZE][SIZE];
bool vis[SIZE][SIZE];
int ans[SIZE][SIZE];
int in_one[1000000][3], iotop = 0;
int dx[4] = {0, 1 ,-1, 0}, dy[4] = {1, 0 , 0 , -1};
int n, m;
void dfs(int x, int y) {
	//if (mg[x][y] == 'E') return;
	
	iotop++;
	in_one[iotop][0] = x;
	in_one[iotop][1] = y;
	//printf("DEBUG(dfs_in_one): %d %d\n",in_one[iotop][0], in_one[iotop][1]);

	//nans++;
	//printf("DEBUG(dfs_nans, nx, ny): %d %d %d\n", nans, x, y);
	for (int i = 0; i < 4; i++) {
		int nx = x + dx[i], ny = y + dy[i];
		if (check(nx,ny) && !(vis[nx][ny]) && (mg[x][y] != mg[nx][ny])) {
			//printf("DEBUG(dfs): %d %d\n", x + tb[i], y + tb[i+1]);
			vis[nx][ny] = true;
			dfs(nx, ny);
		}
	}
}
int main() {
	//freopen("testdata.in", "r", stdin);
	//freopen("testdata.out", "w", stdout);
	//memset(mg, 'E', sizeof(mg));
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%s", &mg[i][1]);
		//mg[i][n+1] = 'E';
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j<= n; j++) {
			if (!vis[i][j]) {
				vis[i][j] = true;
				iotop = 0;
				dfs(i, j);
				//for (int k = 0; k < iotop; k++)
				//printf("DEBUG(in_one):%d %d\n", in_one[i][0], in_one[i][1]);
				for (int i = 1; i <= iotop; i++)
					ans[in_one[i][0]][in_one[i][1]] = iotop;
			}
		}
	}
	int a, b;
	for (int k = 0; k < m; k++) {
		//memset(vis, 0, sizeof(vis));
		scanf("%d %d", &a, &b);
		printf("%d\n", ans[a][b]);
	}
	return 0;
}
