#include <cstdio>
using namespace std;
int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }
int main() {
    int s = 0, na, n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &na);
        if (na < 0) na = -na;
        s = gcd(s, na);
    }
    printf("%d\n", s);
    return 0;
}