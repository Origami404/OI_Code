#include <stdio.h>
#define MAXN 500007
#define lowbit(x) (x&(-x))
int tree[MAXN], n, m;

inline void update(int i, int k);
inline long long ask(int l, int r);
inline int fsrd();

int main(){
    n = fsrd(), m = fsrd();
    for (register int i = 1; i <= n; ++i)
        update(i, fsrd());
    for (register int i = 0; i < m; ++i){
        register int opt = fsrd(), x = fsrd(), y = fsrd();
        if (opt == 1)
            update(x, y);
        else 
            printf("%d\n", ask(x, y));
    }
    return 0;
}

void update(register int i, register int k) {
    for (; i <= n; i += lowbit(i))
        tree[i] += k;
}
long long query(register int i) {
    int ans = 0;
    for (; i; i -= lowbit(i))
        ans += tree[i];
    return ans;
}
long long ask(register int l, register int r) {
    return query(r) - query(l-1);
}
int fsrd() {
    register int sgn = 1, p = 0; register char c = getchar();
    while (c < '0' || '9' < c) {
        if (c == '-') sgn = -1;
        c = getchar();
    }
    while ('0' <= c && c <= '9') {
        p = p*10 + (c-'0');
        c = getchar();
    }
    //printf("DEBUG(input): %d\n", sgn*p);
    return sgn*p;
}
