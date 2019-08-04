#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;

struct milk {
    int p, a;
    bool operator<(const milk& other) const { return p == other.p ? a > other.a : p < other.p; }
};
/*
struct cmp{
    bool operator()(const milk& a, const milk& b){
        return a.p == b.p ? a.a > b.a : a.p < b.p;
    }
};*/
milk all[5000];
int N, M;
int main() {
    scanf("%d %d", &N, &M);
    //priority_queue<milk, vector<milk>, cmp> all;
    //milk now;
    for (int i = 0; i < M; i++) {
        scanf("%d %d", &(all[i].p), &(all[i].a));
        //all.push(now);
    }
    sort(all, all + M);
    int sum = 0;
    //int t = 0;
    for (int t = 0; N;t++) {
        if (all[t].a > N) {
            // 之前下面两行是换过来
            sum += N * all[t].p;
            N = 0;
        } else {
            N -= all[t].a;
            sum += all[t].a * all[t].p;
        }
    }
    printf("%d\n", sum);

    return 0;
}
