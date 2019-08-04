#include <cstdio>
using namespace std;
#define MAXM 20000530
#define int long long
int inv[MAXM], p, n;
void get_inv() {
    inv[1] = 1; 
    for (int i = 2; i <= n; i++) {
        inv[i] = p - (inv[p % i] * (p / i)) % p;
    }
}
signed main() {
    scanf("%lld %lld", &n, &p);
    get_inv();
    for (int i = 1; i <=n; i++)
        printf("%lld\n", inv[i]);
    return 0;
}