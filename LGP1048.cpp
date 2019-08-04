#include <cstdio>
using namespace std;
int T, M, w[110], c[110], f[101000];
inline int max(int a, int b){
    return a > b ? a : b;
}
int main(){
    scanf("%d %d", &T, &M);
    for (int i = 0; i < M; i++)
        scanf("%d %d", &w[i], &c[i]);

    for (int i = 0; i < M; i++)
        for (int j = T; j >= w[i]; j--)
            if (j >= w[i])
                f[j] = max(f[j], f[j - w[i]] + c[i]);
    printf("%d", f[T]);
    return 0;
}

