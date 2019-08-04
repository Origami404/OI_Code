#include <cstdio>
using namespace std;
#define MAXN 2000007
int tree[MAXN], lson[MAXN], rson[MAXN], n;
//bool vaild[MAXN];
/*
bool is_vaild(int l, int r) {
    if (l == -1 && r == -1) {
        return true;
    } else if (l == -1) {
        is_vaild(lson[r], rson[r]);
        return vaild[r] = false;
    } else if (r == -1) {
        is_vaild(lson[l], rson[l]);
        return vaild[l] = false;
    } else {
        return vaild[l] = vaild[r] = tree[l] == tree[r]
            && is_vaild(lson[l], rson[r]) && is_vaild(rson[l], lson[r]);
    }
}*/

int siz[MAXN];
void get_siz(int now) {
    siz[now] = 1;
    if (lson[now] != -1) {
        get_siz(lson[now]);
        siz[now] += siz[lson[now]];
    } 
    if (rson[now] != -1) {
        get_siz(rson[now]);
        siz[now] += siz[rson[now]];
    }
}
/*
int now_max = 0;
void find_max(int now) {
    if (now == -1) {
    } else if (vaild[now]) {
        if (siz[now] > now_max) now_max = siz[now];
    } else {
        find_max(lson[now]);
        find_max(rson[now]);
    }
}*/
bool is_vaild(int left, int right) {
    if (left == -1 && right == -1) return true;
    else if (left != -1 && right != -1 && tree[left] == tree[right]
        && is_vaild(lson[left], rson[right]) && is_vaild(rson[left], lson[right]))
        return true;
    return false;
}

inline int fsrd() {
    int p = 0, c = getchar(), sgn = 0;
    while (c < '0' || '9' < c) {
        if (c == '-') sgn = 1;
        c = getchar();
    } 
    while('0' <= c && c <= '9') {
        p = p*10 + (c-'0');
        c = getchar();
    }
    return sgn ? -p : p;
}

void input() {
    n = fsrd();
    for (int i = 1; i <= n; i++) 
        tree[i] = fsrd();
    for (int i = 1; i <= n; i++) 
        lson[i] = fsrd(), rson[i] = fsrd();
}
template<typename T>
void print_array(const char* prefix, T* arr, int siz) {
    puts(prefix);
    for (int i = 1; i <= siz; i++) 
        printf("%d ", (int)arr[i]);
    puts("");
}
int main() {
    input();
    get_siz(1);
    //print_array("DEBUG(siz): ", siz, n);
    int now_max = 0;
    for (int i = 1; i <= n; i++) {
        if (siz[i] > now_max && is_vaild(lson[i], rson[i]))
            now_max = siz[i];
    }
    printf("%d\n", now_max);
    return 0;
}
