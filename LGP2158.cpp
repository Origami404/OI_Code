#include <cstdio>
#define MAXN 40007
int phi[MAXN], n, ps[MAXN], ptp = 0;
bool chk[MAXN];
int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}
void shieve() {
    int p = 0;
    phi[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (!chk[i]) {
            //printf("Find prime: %d\n", i);
            ps[ptp++] = i;
            phi[i] = i - 1;
        }
        for (int j = 0; j < ptp && (p = ps[j] * i) <= n; j++) {
            //printf("Find unprime: %d\n", p);
            chk[p] = true;
            //phi[p] = phi[ps[j]] * phi[i] / gcd(i, ps[j]);
            if (i % ps[j] == 0) {
                phi[p] = phi[i] * ps[j];
                break;
            } else {
                phi[p] = phi[i] * (ps[j] - 1);
            }
        }
    }
}
int main() {
    scanf("%d", &n);
    if (n == 1) {
    	printf("0");
    	return 0;
	}
    --n;
    shieve();
    //for (int i = 1; i <= n; i++)
    //	printf("%d ", phi[i]);
    //printf("\n");
    int count = 0;
    for (int i = 1; i <= n; i++) 
        count += phi[i];
    printf("%d\n", count*2+1);
}
