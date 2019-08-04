#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
char mg[1010][1010];
bool vis[1010][1010];
int d[1010][1010];
int tb[] = {0, 1, 0, -1, 0};
int n, m;
void bfs(int x, int y){
	queue<pair<int,int> > q;
	q.push(make_pair(x, y));
	vis[x][y] = true;
	while (!q.empty()){
		int nx = q.front().first, ny = q.front().second;
		q.pop();
		d[x][y]++;
		//printf("NOW X, Y:%d %d; D: %d\n", nx, ny, d[x][y]);
		for (int i = 0; i < 4; i++){
			if (mg[nx + tb[i]][ny + tb[i+1]]!='E' && !vis[nx + tb[i]][ny + tb[i+1]]
			   && (mg[nx + tb[i]][ny + tb[i+1]] != mg[nx][ny])){
			   	//printf("DEBUG: %d %d\n", nx + tb[i], ny + tb[i+1]);
			   	q.push(make_pair(nx+tb[i], ny+tb[i+1]));
			   	vis[nx + tb[i]][ny + tb[i+1]] = true;
			   }
		}
	}
	//d[x][y] = ans;
}
int main(){
	memset(mg, 'E', sizeof(mg));
	memset(d, 0, sizeof(d));
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++){
		scanf("%s", &mg[i][1]);
		mg[i][n+1] = 'E';
	}
		
	int i, j; 
	for (int k = 0; k < m; k++){
		memset(vis, 0, sizeof(vis));
		scanf("%d %d", &i, &j);
		bfs(i, j);
		printf("%d\n", d[i][j]);
	}
	return 0;
}






