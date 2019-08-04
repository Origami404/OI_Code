#include <cstdio>
#include <algorithm>
using namespace std;
int n, t[1000010];
int main(){
    scanf("%d", &n);
    for (int i = 1; i <= n; i++){
        scanf("%d", t + i);
        /*
         * 题目保证ti小于1e6， 所以可以乘1001+#include 
         * 在获得编号时mod 1001， 获得时间时除1001就好了
         * 同时保证ti相同时可以按顺序来， 使sort稳定
         */
        (t[i] *= 1001) += i;
    }
        
    sort(t + 1, t + n + 1);

    double ans = 0;

    for (int i = 1; i <= n; i++){
        printf("%d ", t[i] % 1001);
        ans += t[i] / 1001 * (n - i);
    }
    printf("\n%.2lf", ans/n);
    return 0;
}