#include <cstdio>
#include <cstring>
using namespace std;
int V, n, w[100], f[100000];
inline int max(int a, int b) {
    return a > b ? a : b;
}
int main() {
    scanf("%d %d", &V, &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &w[i]);
    // memset(f, 0x3ffe, sizeof(f));
    for (int i = 0; i < n; i++)
        for (int j = V; j >= w[i]; j--)
            f[j] = max(f[j], f[j - w[i]] + w[i]);
    printf("%d", V - f[V]);
    return 0;
}
