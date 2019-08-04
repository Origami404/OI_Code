#include <cstdio>
using namespace std;
int p[1000010];
int main(){
    int n;
    scanf("%d", &n);
    int now = 1;
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= 2; j++){
            if (++now > n)
                now = 1;
            if (p[now])
                j--;
        }
        p[now] = i;
    }
    for (int i = 2; i <= n; i++){
        printf("%d ", p[i]);
    }
    printf("%d", p[1]);
    return 0;
}