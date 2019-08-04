#include <cstdio>
#include <cstring>
using namespace std;
int a[50010], b[50010], c[50010];
int main(){
	int n;
	scanf("%d", &n);
	if (n == 0) printf("0");
	else if (n == 1 || n == 2) printf("1");
	else if (n == 3) printf("2");
	else {
		a[0] = b[0] = 1;
		a[1] = 3; b[1] = 5;
		for (int i = 5; i <= n; i++){
			//c = a + b;
			c[0] = b[0] + 1;
			for (int i = 1; i <= c[0]; i++){
				c[i] += a[i] + b[i];
				if (c[i] >= 10){
					c[i+1] +=1;
					c[i]-=10;
				}
			}
			while (c[c[0]] == 0) --c[0];
			//a = b;
			memcpy(a, b, sizeof(a));
			//b = c;
			memcpy(b, c, sizeof(b));
			memset(c, 0, sizeof(c));
		}
		for (int i = b[0]; i >= 1; i--)
			printf("%d", b[i]);
	}
	return 0;
}
