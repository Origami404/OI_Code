#include <cstdio>
#include <cstring>
inline int max(int a, int b){
	return a > b ? a : b; 
}
using namespace std;
int M,N;
int c[10000], w[10000];
int f[10000];
int main(void){
	memset(f, 0,sizeof(f));
	scanf("%d %d", &M, &N);
	for (int i = 1; i <= N;i++){
		scanf("%d %d", &c[i], &w[i]);
	}
	
	for (int i = 1; i <= N; i++){
		for(int j = w[i]; j <= M ; j++){
			f[j] = max(f[j], f[j-w[i]] + c[i]);
		} 
	}
	printf("%d", f[M]);
	return 0;
}
