#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <cctype>
using namespace std;
#define MAX_N 400007
int sum[MAX_N];
int a[MAX_N], n;
inline void sum_init() {
    // sum[0] = 0;
    for (int i = 1; i <= n; i++)
        sum[i] = sum[i-1] ^ a[i];
}
inline int query(int l, int r) {
    return sum[l-1] ^ sum[r];
}
int cost(int l1, int r1, int l2, int r2) {
    return query(l1, r1) + query(l2, r2);
}
// [l, r)
inline int rand_range(int l, int r) {
    return rand() % (r - l) + l;
}
int sa() {
    double T = 1000000000000000;
    int lsc = 0;
    while (T > 1e-15) {
        int l1 = rand_range(1, n + 1);
        int r1 = rand_range(l1, n + 1);
        if (r1 == n) continue;
        int l2 = rand_range(r1 + 1, n + 1);
        int r2 = rand_range(l2, n + 1);
        //printf("DEBUG: %d %d %d %d\n", l1, r1, l2, r2);
        int dc = cost(l1, r1, l2, r2) - lsc;

        if (dc > 0 || exp(dc / T) * RAND_MAX > rand()) 
            lsc += dc;
        T *= 0.99999; 
    }
    return lsc;
}
int fsrd() {
    int p = 0; int c = getchar();
    while(!isdigit(c)) c = getchar();
    while(isdigit(c)) {
        p = p*10 + (c-'0'); c = getchar();
    }
    return p;
}
int main() {
    srand(time(NULL));
    n = fsrd();
    for (int i = 1; i <= n; i++)
        a[i] = fsrd();
    sum_init();
    printf("%d\n", sa());
    return 0;
}