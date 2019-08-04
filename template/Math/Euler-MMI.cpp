#include <cstdio>
using namespace std;
int phi(int x) {
    int rphi = 1;
    for (int i = 2; i * i <= x; i++) {
        if (x % i == 0) {
            rphi *= i - 1, x /= i;
            while (x % i == 0) rphi *= i, x /= i;
        }
    }
    return x > 1 ? rphi * (x - 1) : rphi;
}
int fpow(int a, int x) {
    int ret = 1;
    while (x) {
        if (x & 1) ret *= a;
        a *= a; x >>= 1;
    }
    return ret;
}
int main() {
    int a, n;
    scanf("%d %d", &a, &n);
    printf("%d\n", fpow(a, phi(n) - 1));
    return 0;
}