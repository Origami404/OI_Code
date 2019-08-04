#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;
int n, num[15], tsum, sum, log_a[15][15];
bool flag;
inline void debug_in_while() {
    printf("DEBUG(num, cou[1]): ");
    for (int i = 1; i <= n; i++)
        printf("%d ", num[i]);
    // printf("; %d\n", cou[1]);
}
inline int cmp(int a, int b) {
    return a > b;
}
int main() {
    scanf("%d %d", &n, &sum);
    for (int i = 1; i <= n; i++)
        num[i] = i;
    for (int i = 1; i <= n; i++)
        log_a[i][1] = log_a[i][i] = 1;
    for (int i = 3; i <= n; i++) {
        for (int k = 1; k <= (i - 1) / 2; k++) {
            log_a[i][k + 1] = log_a[i][i - k] =
                log_a[i - 1][k] + log_a[i - 1][k + 1];
        }
    }

    do {
        flag = false;
        tsum = 0;
        // ni = n;
        // memcpy(cou + 1, num + 1, sizeof(num));
        // printf("DEBUG(init_cou): ");
        // for (int i = 1; i <= n; i++)
        // printf("%d ", cou[i]);
        // printf("\n");

        for (int i = 1; i <= n; i++) {
            tsum += num[i] * log_a[n][i];
            // printf("DEBUG(ni, after_cou[i], i): %d %d %d\n", ni + 1,
            // cou[i], i);
            if (tsum > sum) {
                flag = true;
                sort(num + i, num + n + 1, cmp);
                break;
            }
        }
        if (flag)
            continue;
        /*
        printf("DEBUG(possible_num): ");
        for (int i = 1; i <= n; i++)
            printf("%d ", num[i]);
        printf("; %d", tsum);
        printf("\n");
        //*/
        // debug_in_while();
        // printf("DEBUG(now_sum,sum): %d %d \n", cou[1], sum);
        if (tsum == sum) {
            for (int i = 1; i <= n; i++)
                printf("%d ", num[i]);
            break;
        }
        // printf("DDDDDDDD\n");
    } while (next_permutation(num + 1, num + n + 1));
    return 0;
}