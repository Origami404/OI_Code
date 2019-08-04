#include <cstdio>
#define MAXN 117
using namespace std;
int la, lb, d[MAXN][MAXN];
int a[MAXN], b[MAXN];
int p[5][5] = {
	{ 5, -1, -2, -1, -3},
	{-1,  5, -3, -2, -4},
	{-2, -3,  5, -2, -2},
	{-1, -2, -2,  5, -1},
	{-3, -4, -2, -1,  0}
};
inline int max(int a, int b){
	return a > b ? a : b;
}
inline int max4(int a, int b, int c, int d) {
	return max(a, max(b, max(c, d)));
}
int main() {

	char si[MAXN];

	scanf("%d %s", &la, si);
	for (int i = 1; i <= la; i++) {
		if (si[i-1] == 'A') a[i] = 0;
		else if (si[i-1] == 'C') a[i] = 1;
		else if (si[i-1] == 'G') a[i] = 2;
		else a[i] = 3;
	}

	scanf("%d %s", &lb, si);
	for (int i = 1; i <= lb; i++) {
		if (si[i-1] == 'A') b[i] = 0;
		else if (si[i-1] == 'C') b[i] = 1;
		else if (si[i-1] == 'G') b[i] = 2;
		else b[i] = 3;
	}

	for (int i = 1; i <= la; i++)
		for (int j = 1; j <= lb; j++)
			d[i][j] = -2e8;

	for (int i = 1; i <= la; i++)
		d[i][0] = d[i-1][0] + p[a[i]][4];
	for (int i = 1; i <= lb; i++)
		d[0][i] = d[0][i-1] + p[4][b[i]];

	for (int i = 1; i <= la; i++)
		for (int j = 1; j <= lb; j++)
			d[i][j] = max4(d[i][j], d[i-1][j] + p[a[i]][4],
			               d[i][j-1] + p[4][b[j]], d[i-1][j-1] + p[a[i]][b[j]]);
    printf("%d\n", d[la][lb]);
	return 0;
}
