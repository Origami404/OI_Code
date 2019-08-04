#include <cstdio>
using namespace std;
int T, M, w[10010], c[10010], f[10000010], maxf;
inline int max(int a, int b) {
    return a > b ? a : b;
}
int main() {
    scanf("%d %d", &T, &M);
    for (int i = 0; i < M; i++)
        scanf("%d %d", &w[i], &c[i]);
    for (int i = 0; i < M; i++)
        for (int j = w[i]; j <= T; j++){
            f[j] = max(f[j], f[j - w[i]] + c[i]);
            maxf = max(maxf, f[j]);
        }
                
    printf("%d", maxf);
    return 0;
}
