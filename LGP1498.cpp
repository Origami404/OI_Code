#include <cstdio>
using namespace std;
int a[100010] = {1};
int main(){
	int n;
	scanf("%d", &n);
	n = (1<<n);
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n - i; j++)
			printf(" ");
		for (int j = i; j >= 0; j--)
			a[j] ^= a[j - 1];
		for (int j = 0; j <= i && !(i%2); j++)
			printf(a[j] ? "/\\" : "  ");
		for (int j = 0; j <= i && (i%2); j+=2)
			printf(a[j] ? "/__\\" : "    ");
		printf("\n");
	}
	return 0;
}


