#include <cstdio>
#include <cstring>
#define MAXN 107
using namespace std;
int a[MAXN], n;
int front_max[MAXN], end_max[MAXN];
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) 
        scanf("%d", a + i);
    front_max[1] = 1;
    for (int i = 2; i <= n; i++) {
        front_max[i] = 1;
        for (int j = 1; j < i; j++) {
            if (a[j] < a[i] && front_max[j] + 1 > front_max[i])
                front_max[i] = front_max[j] + 1;
        }
    }
    end_max[n] = 1;
    for (int i = n-1; i >= 1; i--) {
        end_max[i] = 1;
        for (int j = n; j > i; j--) {
            if (a[j] < a[i] && end_max[j] + 1 > end_max[i])
                end_max[i] = end_max[j] + 1;
        }
    }
    int max_n = 0;
    for (int t = 1; t <= n; t++) {
        int now_n = front_max[t] + end_max[t] - 1;
        if (now_n > max_n) max_n = now_n;
    }
    printf("%d\n", max_n);
    return 0;
}