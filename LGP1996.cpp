#include <cstdio>
using namespace std;
int m, n;
bool death[110];
int main(){
    scanf("%d %d", &n, &m);
    int now = 0;
    for (int j = 0; j < n; j++){
        for (int i = 0; i < m; i++){
            if (++now > n)
                now = 1; // 循环
            if (death[now])
                i--; // 死了把数加回去
        }
        printf("%d ", now);
        death[now] = true;
    }
        return 0;
}