#include <cstdio>
using namespace std;
int a[100], b[100], c[100], mrk[100], n, cnt;
void dfs(int x){
	if (x == n){
		if (++cnt <= 3){
			for (int i = 0; i < n; i++)
				printf("%d ", mrk[i]);
			printf("\n");
		}
		return;
	}
	for (int y = 0; y < n; y++){
		if (!(a[y] || b[x+y] || c[x-y+n])){
			a[y] = b[x+y] = c[x-y+n] = 1;
			mrk[x] = y + 1;
			dfs(x+1);
			a[y] = b[x+y] = c[x-y+n] = 0;
		} 
	}
}

int main(){
	scanf("%d", &n);
	dfs(0);
	printf("%d", cnt);
	return 0;
}


