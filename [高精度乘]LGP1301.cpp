#include <cstdio>
#include <cstring>
#define MAXN 20100
using namespace std;
char ia[MAXN], ib[MAXN];
int a[MAXN] = {0}, b[MAXN] = {0}, c[MAXN*20+10] = {0};
int main() {
    scanf("%s%s", ia, ib);
    for (int i = 1; i <= (a[0] = strlen(ia)); i++) a[i] = ia[a[0] - i] - '0';
    for (int i = 1; i <= (b[0] = strlen(ib)); i++) b[i] = ib[b[0] - i] - '0';
    c[0] = a[0] + b[0] - 1;
    for (int i = 1; i <= a[0]; i++) {
        for (int j = 1; j <= b[0]; j++) {
            c[i+j-1] += a[i] * b[j];
            c[i+j] += c[i+j-1]/10;
            c[i+j-1] %= 10;
        }
    }
    if(c[c[0]+1]>=1) c[0]++;
    while(c[c[0]] == 0 && c[0] > 1) --c[0];
    for (int i = c[0]; i >= 1; i--) printf("%d", c[i]);
    return 0;
}
