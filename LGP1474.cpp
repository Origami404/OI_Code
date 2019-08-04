#include <cstdio>
#include <algorithm>
using namespace std;
// 价值即是大小 
int c[26];
int v, n;
long long f[10010];
int main(){
	scanf("%d %d", &v, &n);
	for (int i = 0; i< v;i++){
		scanf("%d", &c[i]);
	}
	int tot = 0;
	
	for (int i = 0; i < v; i++){
		for (int j = c[i]; j < n;j++){
			f[j] = max(f[j-1], f[j-c[i]]);
			if (f[j] == n)
				tot++;
		}
	}
	
	
	printf("%d\n", tot);
	return 0;
}

