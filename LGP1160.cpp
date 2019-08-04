#include <cstdio>
using namespace std;

int R[100010], L[100010], N, M;
bool not_in[100010];
int main() {
    scanf("%d", &N);
    int k, p, x, start = 0;
    R[0] = 1;
    L[0] = L[1] = R[1] = 0; // 以0做哨兵
    for (int i = 2; i <= N; i++) {
        scanf("%d %d", &k, &p);
        if (p) {
            L[i] = k; R[i] = R[k];
            L[R[k]] = i; R[k] = i;
        } else {
            L[i] = L[k]; R[i] = k;
            R[L[k]] = i; L[k] = i;
        }
    }
    scanf("%d", &M);
    for (int i = 0; i < M; i++) {
        scanf("%d", &x);
        if (!not_in[x]) { // 虽然看起来可以不用判断， 但是要当心有多于2个连续的不在的情况
            R[L[x]] = R[x]; L[R[x]] = L[x];
            not_in[x] = true;
        }
    }
    while ((start = R[start]))   // Yes, I'm sure what I'm doing.
        printf("%d ", start);
    return 0;
}
