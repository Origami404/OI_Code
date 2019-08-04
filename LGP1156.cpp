#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int d, g, fail_ans = 0;
struct Food { int t, f, h; } food[107];
bool operator<(const Food &a, const Food &b) { return a.t < b.t; }
int life[107][1007];
int main() {
    scanf("%d %d", &d, &g);
    for (int i = 1; i <= g; i++)
        scanf("%d %d %d", &(food[i].t), &(food[i].f), &(food[i].h));
    sort(food + 1, food + g + 1);
    memset(life, ~0x3f, sizeof(life)); // fill with -INF
    life[0][0] = 10; // bag DP
    for (int i = 1; i <= g; i++) {
        for (int h = d; h >= 0; h--) { 
            int dt = food[i].t - food[i - 1].t, nh = h + food[i].h;
            if (life[i - 1][h] < dt) continue; // die
            if (nh >= d) return (printf("%d", food[i].t), 0); // find a way out
            life[i][nh] = max(life[i][nh], life[i - 1][h] - dt); // put
            life[i][h] = max(life[i][h], life[i - 1][h] + food[i].f - dt); // eat
        }
        fail_ans = max(fail_ans, life[i][0] + food[i].t);
    }
    return (printf("%d\n", fail_ans), 0);
}