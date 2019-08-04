#include <cstdio>
using namespace std;
template <class T>
inline T min(const T &a, const T &b)
    { return a < b ? a : b; }

// 分块 给定n, k, 求和 i:1->n (k % i)
// 原式 = i:1->n (k - (k/i)*i) = nk - (i:1->n ((k/i)*i))
int main() {
    long long n, k;
    scanf("%lld %lld", &n, &k);
    long long l = 1, r, ans = n * k;
    while (l <= n) {
        long long t = k / l;
        if (t == 0) r = n;
        else r = min(k / t, n);
        // 乘法分配 等差求和
        ans -= t * ((l + r) * (r - l + 1) / 2);
        l = r + 1;
    }
    printf("%lld\n", ans);
    return 0;
}