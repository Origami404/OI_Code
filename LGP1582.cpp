#include <cstdio>
using namespace std;
int count_one(int n) {
    int res = 0;
    while (n) {
        res++;
        n &= n - 1;
    }
    return res;
}
#define lowbit(x) (x&(-x))
signed main() {
    int n, k, ans = 0;
    scanf("%d %d", &n, &k);
    while (count_one(n) > k) {
        ans += lowbit(n);
        n += lowbit(n);
    }
    printf("%d\n", ans);
    return 0;
}
