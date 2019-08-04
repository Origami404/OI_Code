#include <cstdio>
using namespace std;
int main(){
    int N;
    scanf("%d", &N);
    int now;
    scanf("%d", &now);
    int sub_sum = now, max_sum = now;
    for (int i = 1; i < N; i++) {
        scanf("%d", &now);
        sub_sum = sub_sum > 0 ? sub_sum : 0;
        sub_sum += now;
        max_sum = max_sum > sub_sum ? max_sum : sub_sum;
    }
    printf("%d", max_sum);

    return 0;
}