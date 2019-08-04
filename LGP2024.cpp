#include <cstdio>
#include <cctype>
#define MAX_N 50007
using namespace std;

int uset[MAX_N * 3];
int find(int x) {
    return x == uset[x] ? x : (uset[x] = find(uset[x]));
}
inline void init_uset(int n) {
    for (int i = 1; i <= n; i++) uset[i] = i;
}
int fsrd() {
    int p = 0, c = getchar();
    while (!isdigit(c)) c = getchar();
    while (isdigit(c)) {
        p = p*10 + (c-'0');
        c = getchar();
    }
    return p;
}

// 建模部分
// 核心思想是种类并查集
// 我的理解是, get_x(i)表示当i为x种类时i的关系
// 比如i吃j, 就是
//   1) 当i为a时, i会吃为b时的y
//   2) 当i为b时, i会吃为c时的y
//   3) 当i为c时, i会吃为a时的y
// 同类同理, 当i和j同类, 意味着
//   1) 当i为a时, i与为a时的y同类
//   etc...
int n;
#define get_a(x) (x)
#define get_b(x) (x+n)
#define get_c(x) (x+n+n) 
inline bool can_eat(int x, int y) {
    bool ans = false;
    ans = ans || find(get_a(x)) == find(get_b(y));
    ans = ans || find(get_b(x)) == find(get_c(y));
    ans = ans || find(get_c(x)) == find(get_a(y));
    return ans;
}
inline bool is_same(int x, int y) {
    bool ans = false;
    ans = ans || find(get_a(x)) == find(get_a(y));
    ans = ans || find(get_b(x)) == find(get_b(y));
    ans = ans || find(get_c(x)) == find(get_c(y));
    return ans;
}
inline void make_same(int x, int y) {
    uset[find(get_a(x))] = find(get_a(y));
    uset[find(get_b(x))] = find(get_b(y));
    uset[find(get_c(x))] = find(get_c(y));
}
inline void make_eat(int x, int y) {
    uset[find(get_a(x))] = find(get_b(y));
    uset[find(get_b(x))] = find(get_c(y));
    uset[find(get_c(x))] = find(get_a(y));
}

int main() {
    int k, op, x, y, fake_cnt = 0;
    n = fsrd(); k = fsrd();
    init_uset(n*3);
    for (int i = 1; i <= k; i++) {
        op = fsrd(); x = fsrd(); y = fsrd();
        if (x > n || y > n) {++fake_cnt; continue;} // Bigger than N, fake.
        if (op == 1) {
            if (can_eat(x, y) || can_eat(y, x)) {
                ++fake_cnt; continue; // x eat y, cannt be same, fake.
            } else make_same(x, y);
        } else { // op == 2
            if (x == y) {++fake_cnt; continue;} // Eat itself, fake. 
            if (is_same(x, y) || can_eat(y, x)) {
                ++fake_cnt; continue; // eat same or be eated, fake.
            } else make_eat(x, y);
        }
    }
    printf("%d\n", fake_cnt);
    return 0;
}