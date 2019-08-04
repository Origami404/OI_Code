#include <cstdio>
#define MAXN 50007
#define int long long
using namespace std;
int L, N, M;
// the dis between two rocks
int dis[MAXN];
bool check(int mind) {
    int now_d = 0, cnt = 0;
    for (int i = 1; i <= N; i++) {
        now_d += dis[i];
        if (now_d < mind) 
            cnt++;
        else 
            now_d = 0;
        if (cnt > M) 
            return false;
    }
    return true;
}
int binary_find() {
    int l = 0, r = L, mid;
    while (l <= r) {
    	//printf("Now range: [%lld %lld]\n", l, r);
        mid = (l+r)>>1;
        if (check(mid)) 
            l = mid + 1;
        else 
            r = mid - 1;
    }
    return r;
}
signed main() {
    scanf("%lld %lld %lld", &L, &N, &M);
    int last_d = 0, now_d;
    for (int i = 1; i <= N; i++) {
        scanf("%lld", &now_d);
        dis[i] = now_d - last_d;
        last_d = now_d;
    }
    printf("%lld\n", binary_find());
    return 0;
}