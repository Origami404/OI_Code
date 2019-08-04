#include <cstdio>
#include <cstring>
using namespace std;
char *ia, *ib;
int a[10010] = {0}, b[10010] = {0}, c[10010] = {0};
int main() {
	ia = new char[10010], ib = new char[10010];
	scanf("%s%s", ia, ib);
	int al = strlen(ia), bl = strlen(ib);
	if (al < bl || (al == bl && strcmp(ia, ib) == -1)) {
		char* t = ia; ia = ib; ib = t;
		a[0] = bl; b[0] = al; 
		printf("-");
	}else {
		a[0] = al; b[0] = bl;
	}
	
	for (int i = 1; i <= a[0]; i++)
		a[i] = ia[a[0] - i] - '0';
	for (int i = 1; i <= b[0]; i++)
		b[i] = ib[b[0] - i] - '0';
	for (int i = 1; i <= (c[0] = a[0] > b[0] ? a[0] : b[0]); i++) {
		//printf("DEBUG(now_a[i], now_b[i]): %d %d\n", a[i], b[i]);
		c[i] += a[i] - b[i];
		if (c[i] < 0 && i < c[0]) {
			c[i+1] -= 1;
			c[i] += 10;
		}
	}
	//while (c[c[0] + 1] != 0) ++c[0];
	while (c[c[0]] == 0 && c[0] > 1) --c[0];
	//if (abb == -1) printf("-");
	for (int i = c[0]; i >= 1; i--)
		printf("%d", c[i]);
	return 0;
}
