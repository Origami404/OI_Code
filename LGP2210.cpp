#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <ctime>
using namespace std;
int rtoi[15]/* = {0, 6, 5, 1, 4, 2, 3}*/, 
    itor[15]/* = {0, 3, 5, 6, 4, 2, 1}*/;
int fri[15][5], n;
inline int abs(int x) { return x < 0 ? -x : x; }
inline void swap(int &a, int &b) { int t = a; a = b; b = t; }
int cost() {
    int ret = 0;
    for (int i = 1; i <= n; i++) {
        int ci = rtoi[i];
        for (int j = 1; j <= 3; j++) {
            if (fri[ci][j] > ci) {
                ret += abs(itor[fri[ci][j]] - i);
                //printf("DEBUG(a, b, need): %d %d\n", itor[fri[ci][j]], i);
            }
        }
    }
    return ret;
}
void change_S(int a, int b) {
    swap(itor[rtoi[a]], itor[rtoi[b]]);
    swap(rtoi[a], rtoi[b]);
}
int get_rand(int l, int r) {
    return (rand() % (r - l + 1)) + l;
}
int sa() {
    double t = 10000;
    int lsc = cost();
    while (t > 1e-10) {
        int a = get_rand(1, n), b = get_rand(1, n);
        //int c = get_rand(1, n), d = get_rand(1, n);
        //int e = get_rand(1, n), f = get_rand(1, n);
        change_S(a, b);
        //change_S(c, d);
        //change_S(e, f);
        int nc = cost();
        if (nc < lsc || exp(((double)(lsc - nc))/t) > (double) rand() / RAND_MAX) {
            lsc = nc;
        } else /*change_S(f, e), change_S(d, c), */change_S(b, a); 
        t *= 0.97;
    }
    return lsc;
}
int main() {
    srand(time(NULL));
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) 
        scanf("%d %d %d", &(fri[i][1]), &(fri[i][2]), &(fri[i][3]));
    for (int i = 1; i <= n; i++)
        rtoi[i] = itor[i] = i;
    
    //printf("%d\n", sa());
    printf("%d\n", sa());
    return 0;
}