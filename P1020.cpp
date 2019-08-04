#include <cstdio>
#include <cstring>
#define MAXN 1000007
#define lowbit(x) (x&(-x))
using namespace std;
int a[MAXN], tree[MAXN], n;
inline int max(int x, int y) {
    return x > y ? x : y;
}
void change(int x, int k) {
    for (; x <= MAXN-1; x += lowbit(x))
        tree[x] = max(tree[x], k);
}
int ask(int x) {
    int ret = 0;
    for (; x; x -= lowbit(x)) {
        ret = max(tree[x], ret);
    }
    return ret;
}
int main() {
    while (scanf("%d", a + n + 1) == 1) ++n;
    int maxCount = -1;
    for (int i = n; i >= 1; i--) {
        int now = ask(a[i]) + 1;
        change(a[i], now);
        if (now > maxCount) maxCount = now;
    }
    printf("%d\n", maxCount);

    memset(tree, 0, sizeof(tree));
    maxCount = -1;
    for (int i = 1; i <= n; i++) {
        int now = ask(a[i] - 1) + 1;
        change(a[i], now);
        if (now > maxCount) maxCount = now;
    }
    printf("%d\n", maxCount);
    return 0;
}