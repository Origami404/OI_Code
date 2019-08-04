#include <stdio.h>
#include <stdlib.h>
#define MAXN 407
int comp(const void*, const void*);
inline int fsrd();
inline int abs(register int);
inline int dis(register int, register int);

typedef struct {
    int x, y, v;
} Plant;
Plant plants[MAXN];
int ptp = 0;

int main(){
    register int n, m, k, now;
    m = fsrd(), n = fsrd(), k = fsrd();
    for (register int i = 1; i <= m; ++i) {
        for (register int j = 1; j <= n; ++j) {
            now = fsrd();
            if (now)
                plants[ptp++] = (Plant){j, i, now};
        }
    }
    qsort(plants, ptp, sizeof(Plant), comp);
    /*
    for (int i = 0; i < ptp; i++)
        printf("DEBUG(plant: i, x, y, v): %d %d %d %d\n",
            i, plants[i].x, plants[i].y, plants[i].v);
    */
    // 令最后的植物到尾后植物的距离等于最后的植物到路的距离
    plants[ptp].x = plants[ptp-1].x;
    int d = plants[0].y, v = 0;
    for (register int i = 0; i < ptp; ++i){
        //printf("DEBUG(i, k, d, v): %d %d %d %d\n", i, k, d, v);
        if (k >= d + plants[i].y + 1){
            k -= d + 1;
            v += plants[i].v;
            d = dis(i, i+1);
        } else break;
    }
    printf("%d\n", v);
    return 0;
}
int abs(register int a){ return a < 0 ? -a : a; }
int dis(register int a, register int b) {
    return abs(plants[a].x - plants[b].x) + abs(plants[a].y - plants[b].y);
}
int comp(const void* a, const void* b) {
    return ((const Plant*)b)->v - ((const Plant*)a)->v;
}
int fsrd() {
    register int p = 0, c = getchar();
    while (c < '0' || '9' < c) c = getchar();
    while ('0' <= c && c <= '9') (p = p*10 + (c-'0')), (c = getchar());
    return p;
}
