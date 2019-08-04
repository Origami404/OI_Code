#include <cstdio>
#define MAX_N 100007
#define LOG_N 18
using namespace std;
// f[i][j] 表示 a[i, i + 2^j - 1]中极值 
int a[MAX_N], n, m, log_2[MAX_N], f[MAX_N][LOG_N], l, r;
inline int max(int a, int b) {
	return a < b ? b : a;
}
inline void pre_deal() {
	// LOG_2 预处理 
	log_2[0] = -1;
	for (int i = 1; i <= n; i++)
		(f[i][0] = a[i]), (log_2[i] = log_2[i>>1] + 1);
	
	// f[i][j] = max(f[i][j-1], f[i+2^(j-1)][j-1]) 
	for (int j = 1; j <= LOG_N; j++)
		for (int i = 1; i + (1<<j) - 1 <= n; i++)
			f[i][j] = max(f[i][j-1], f[i+(1 << (j-1))][j-1]);
}
inline int ask(int l, int r) {
	// 先求出最大的 x 满足 2^x <= r - l + 1 
    // 分开两个区间[l, l + 2^x - 1], [r - 2^x + 1, r]
	// 有重叠也不怕 
	int x = log_2[r - l + 1];
	return max(f[l][x], f[r - (1<<x) + 1][x]);
}
int main() {
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++)
		scanf("%d", a + i);
	pre_deal();
	for (int i = 1; i <= m; i++) {
		scanf("%d %d", &l, &r);
		printf("%d\n", ask(l, r));
	}
	return 0;
}
