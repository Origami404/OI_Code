#include <cstdio>
#include <cctype>
using namespace std;
int phi(int x) {
    int rphi = 1;
    for (int i = 2; i * i <= x; i++) {
        if (x % i == 0) {
            (rphi *= i - 1), (x /= i);
            while (x % i == 0) (rphi *= i), (x /= i);
        }   
    }
    return x > 1 ? rphi * (x - 1) : rphi;
}
int fpow(int a, int x, int mod) {
    int ret = 1;
    while (x) {
        if (x & 1) ret = 1ll * a * ret % mod;
        a = 1ll * a * a % mod;
        x >>= 1; 
    }
    return ret;
}
int main() {
    int a, m;
    scanf("%d %d", &a, &m);
    //a %= m;
    int phim = phi(m);
    int c = getchar(), b = 0, need_exphi = false;
    while (!isdigit(c)) c = getchar();
    while (isdigit(c)) {
        b = b*10 + (c-'0');
        if (b >= phim) (b %= phim), (need_exphi = true);
        c = getchar();
    } if (need_exphi) b += phim;
    printf("%d\n", fpow(a, b, m));
    return 0;
}