#include <cstdio>
#include <algorithm>
#define MAXN 5007
using namespace std;
int y[MAXN], ytp = 0;
int highest, n, s;
int main() {
    int a, b;
    scanf("%d %d", &n, &s);
    scanf("%d %d", &a, &b);
    highest = a + b;
    for (int i = 1; i <= n; i++) {
        int xi, yi; scanf("%d %d", &xi, &yi);
        if (xi <= highest) y[++ytp] = yi;
    }
    sort(y + 1, y + ytp + 1);
    int sum = 0, pos = 1;
    while (sum <= s) {
        if (pos > n) return printf("%d\n", n), 0;
        sum += y[pos++];
    }
    printf("%d\n", pos - 2);
    return 0;
}