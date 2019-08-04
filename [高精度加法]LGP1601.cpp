#include <cstdio>
#include <cstring>
using namespace std;
template <typename T>
inline T max(T a, T b){
	return a > b ? a : b;
}
char ai[510], bi[510];
int a[510], b[510];
int len = 0;
void add(){
	int al = strlen(ai), bl = strlen(bi), jw = 0;
	memset(a, 0, sizeof(a));
	for (int i = al - 1; i >= 0; i--)
		a[al - i] = ai[i] - '0';
	memset(b, 0, sizeof(b));
	for (int i = bl - 1; i >= 0; i--)
		b[bl - i] = bi[i] - '0';
	
	len = max(al, bl);
	for (int i = 0; i <= len; i++){
		a[i] += b[i] + jw;
		jw = 0;
		if (a[i] > 9){
			a[i] -= 10;
			jw = 1;
		}
	}
	if (jw)
	   a[++len] += jw;
}
int main(){
	scanf("%s %s", ai, bi);
	add();
	for (int i = len; i > 0; i--)
		printf("%d", a[i]);
	printf("\n");
	return 0;
}
