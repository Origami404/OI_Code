#include <cstdio>
#include <cstring>
using namespace std;
#define MAX_NODE 100007
#define MAX_CH 15
int node[MAX_NODE][MAX_CH];
bool end[MAX_NODE];
int root, ntp; // Need init
bool insert(const char* str) {
    bool mef = true, of = false;
    int np = root, len = strlen(str);
    for (int i = 0; i < len; i++) {
        int ind = str[i] - '0';
        if (node[np][ind] == -1) {
            mef = false;
            node[np][ind] = ntp++;
        }
        of = of || end[np];
        np = node[np][ind];
    }
    end[np] = true;
    return mef || of;
}
void deal(int n) {
    memset(node, -1, sizeof(node));
    memset(end, false, sizeof(end));
    char buf[20];
    bool total = false;
    for (int i = 1; i <= n; i++) {
        scanf("%s", buf);
        total = total || insert(buf);
    }
    puts(total ? "NO" : "YES");
    fflush(stdin);
}
int main() {
    root = 0; ntp = 1;
    int t, n;
    scanf("%d", &t);
    for (int i = 1; i <= t; i++) {
        scanf("%d", &n);
        deal(n);
    }
    return 0;
}