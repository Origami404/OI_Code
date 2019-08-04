#include <cstdio>
#define MAXN 1000007
using namespace std;
int psum[MAXN], n;
bool chk[MAXN];
void get_sum() {
    chk[0] = chk[1] = true;
    for (int i = 2; i <= n; i++) {
        if (!chk[i]) {
            for (int j = n / i; j > 0; j--)
                if (!chk[j]) chk[i*j] = true;
            psum[i] = 1;
        } 
    }
    for (int i = 1; i <= n; i++) {
        psum[i] += psum[i-1];
    }
}
inline int fsrd() {
    int p = 0, c = getchar(), sgn = 0;
    for (; c < '0' || '9' < c; c = getchar())
        if (c == '-') sgn = 1;
    for (; '0' <= c && c <= '9'; c = getchar())
        p = p*10 + (c-'0');
    return sgn ? -p : p;
}
void deal() {
    int l, r;
    l = fsrd(), r = fsrd();
    if (l < 1 || r < 1 || l > n || r > n) {
        puts("Crossing the line");
    } else {
        printf("%d\n", psum[r] - psum[l - 1]);
    }
}
int main() {
    int m;
    m = fsrd(), n = fsrd();
    get_sum();
    for (int i = 1; i <= m; i++) deal();
    return 0;
}
