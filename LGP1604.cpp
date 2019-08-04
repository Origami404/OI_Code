#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cctype>
using namespace std;
char ia[2010], ib[2010];
int a[2010], b[2010], c[2010]; 
int main(){
	int bn;
	scanf("%d %s %s", &bn, ia, ib);
	for (int i = 1; i <= (a[0] = strlen(ia)); i++)
		a[i] = isalpha(ia[a[0]-i]) ? ia[a[0]-i]-'A'+10 : ia[a[0]-i]-'0';
	for (int i = 1; i <= (b[0] = strlen(ib)); i++)
		b[i] = isalpha(ib[b[0]-i]) ? ib[b[0]-i]-'A'+10 : ib[b[0]-i]-'0';
	//printf("%d", a[1]);
	c[0] = max(a[0], b[0]) + 1;
	for (int i = 1; i <= c[0]; i++){
		c[i] += a[i] + b[i];
		if (c[i] >= bn){
			c[i] -= bn;
			c[i+1] += 1;
		}
	}
	
	while (c[c[0]] == 0 && c[0] > 1) --c[0];
	for (int i = c[0]; i >= 1; i--)
		printf("%c", (char)(c[i]>=10 ? c[i]-10+'A' : c[i]+'0'));
	return 0;
}
