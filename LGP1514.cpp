#include <cstdio>
using namespace std;
#define MAXN 400
int card[6], m;
int mark[MAXN], n;
inline int max(int a, int b) { return a < b ? b : a; }
/*
int dfs(int pos) {
    if (pos <= 0) return 0;
    
    int now_max = 0;
    for (int i = 1; i <= 4; i++) {
        if (card[i] >= 1) {
            card[i] -= 1;
            now_max = max(now_max, dfs(pos - i));
            card[i] += 1;
        }
    }
    //printf("DEBUG(pos, max_mark): %d %d\n", pos, now_max);
    return now_max + mark[pos];
}*/
int f[50][50][50][50];
void debug_array(const char* prefix, int* arr, int siz) {
    printf("DEBUG(%s): ", prefix);
    for (int i = 1; i <= siz; i++)
        printf("%d ", arr[i]);
    puts("");
}
int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", mark + i);
    for (int i = 1; i <= m; i++) {
        int p;
        scanf("%d", &p);
        card[p] += 1;
    }
    for (int a = 0; a <= card[1]; a++) {
        for (int b = 0; b <= card[2]; b++) {
            for (int c = 0; c <= card[3]; c++) {
                for (int d = 0; d <= card[4]; d++) {
                    int &nf = f[a][b][c][d], pos = 1 + a + 2*b + 3*c + 4*d; 
                    if (a) nf = max(nf, f[a-1][b][c][d]);
                    if (b) nf = max(nf, f[a][b-1][c][d]);
                    if (c) nf = max(nf, f[a][b][c-1][d]);
                    if (d) nf = max(nf, f[a][b][c][d-1]);
                    nf += mark[pos];
                }
            }
        }
    }
    printf("%d\n", f[card[1]][card[2]][card[3]][card[4]]);
    //debug_array("mark", mark, n);
    //debug_array("card", card, 4);
    //printf("%d\n", dfs(n));
    return 0;
}