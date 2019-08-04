#include <cstdio>
#include <algorithm>
#define MAXN 10007
using namespace std;
int a[MAXN];
int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++)
		scanf("%d", a + i);
	for (int i = 0; i < m; i++)
		next_permutation(a, a + n);
	for (int i = 0; i < n; i++)
		printf("%d ", a[i]);
	return 0;
}
