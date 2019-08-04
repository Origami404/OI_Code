#include <cstdio>
using namespace std;
int n,m;
int v[30], w[30], f[30010];

inline int max(int a, int b){
	return a > b ? a : b;
}
int main(){
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= m ; i ++){
		scanf("%d %d", &v[i], &w[i]);
	}
	
	
	for(int i = 1; i<=m;i++){
		for (int j = n;j>=v[i]; j--){
			f[j] = max(f[j], f[j-v[i]] + v[i]*w[i]);
		}
	}
	printf("%d\n", f[n]);
	return 0;
}
