#include <cstdio>
#include <cstring>
using namespace std;
bool isp[10000010];
int p[2500010],N,M;
void check(){
	isp[1] = false;
	int psize = 0;
	for (int i = 2; i <= N; i++){
		if (isp[i]) p[psize++] = i;
		for (int j = 0; j < psize && i * p[j] <= N; j++){
			isp[i * p[j]] = false;
			if (!i%p[j]) break;
		}
	}
}
int main(){
	scanf("%d %d", &N, &M);
	memset(isp, 1, sizeof(isp));
	check();
	int now;
	for (int i = 0; i < M; i++){
		scanf("%d", &now);
		printf(isp[now] ? "Yes\n" : "No\n");
	}
	return 0;
}
