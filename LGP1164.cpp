#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int N,M,a[1010],f[1000000];
int main(){
	scanf("%d %d", &N, &M);
	for(int i = 1; i <= N; i++){
		scanf("%d", &a[i]);
	}
	//memset(f,-1,sizeof(f));
	f[0] = 1;
	for(int i = 1; i <= N; i++){
		for(int j = M; j >= a[i]; j--){
			f[j] = max(f[j], f[j] + f[j-a[i]]);
		}
	}
	printf("%d", f[M]);
	return 0;
}
