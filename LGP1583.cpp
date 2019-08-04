#include <algorithm>
#include <cstdio>
using namespace std;
int E[13],n, k;
struct Person{
    int id, w;
    bool operator<(const Person& o) { return o.w == w ? id < o.id : w > o.w; }
} p[20010];
int main() {
    scanf("%d %d", &n, &k);
    for (int i = 1; i <= 10; i++) scanf("%d", &E[i]);
    for (int i = 1; i <= n ; i++) scanf("%d", &p[i].w), p[i].id = i;
    sort(p + 1, p + n + 1);
    for (int i = 1; i <= n; i++) p[i].w += E[(i - 1) % 10 + 1];
    sort(p + 1, p + n + 1);
    for (int i = 1; i <= k; i++) printf("%d ", p[i].id);
    return 0;
}