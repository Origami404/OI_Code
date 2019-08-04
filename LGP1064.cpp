#include <cstdio>
#include <algorithm>
using namespace std;
int N,m;
int mv[70], mp[70], f[32010];
int anv[70][2], anp[70][2], ani[70];
//int in[70];

int main() {
	scanf("%d %d", &N, &m);
	int v,p,q;
	for (int i = 1; i <= m; i++){
		scanf("%d %d %d", &v, &p, &q);
		if (!q){
			mv[i] = v; mp[i] = p;
		}else{
			anv[q][ani[q]] = v;
			anp[q][ani[q]] = p;
			ani[q]++;
		}
	}
	for (int i = 1; i <= m; i++){
		// is main?
		for (int j = N; mv[i] !=0 && j >= mv[i]; j--){
			f[j] = max(f[j], f[j-mv[i]] + mv[i]*mp[i]);
			if (j >= mv[i] + anv[i][0])
				f[j] = max(f[j], f[j - mv[i] - anv[i][0]] + mv[i]*mp[i] + anv[i][0]*anp[i][0]);
			if (j >= mv[i] + anv[i][1])
				f[j] = max(f[j], f[j - mv[i] - anv[i][1]] + mv[i]*mp[i] + anv[i][1]*anp[i][1]);
			if (j >= mv[i] + anv[i][0] + anv[i][1])
				f[j] = max(f[j], f[j - mv[i] - anv[i][0] - anv[i][1]] + mv[i]*mp[i] + anv[i][0]*anp[i][0] + anv[i][1]*anp[i][1]);
		}
	}
	/*
	for (int i = 1; i <= m; i++)
		printf("%d %d %d\n", v[i], p[i], q[i]);
	*/ /*
	in[0] = 1;
	for (int i = 1; i <= m; i++) {
		if (in[q[i]]) {
			for (int j = N; j >= v[i]; j--) {
				f[j] = max(f[j], f[j - v[i]] + v[i] * p[i]);
				in[i] = 1;
			}
		}
	}*/
	
	printf("%d", f[N]);
	return 0;
}


