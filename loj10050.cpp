#include <cstdio>
#include <cctype>
#include <cstring>
using namespace std;
#define MAX_N 100007 
#define MAX_CH 4
int node[10003333][MAX_CH], ntp = 1;
const int root = 0;
void insert(int num) {
    int pos = root;
    //printf("DEBUG(%d): ", num);
    for (int i = 3; i >= 0; i--) {
        int c = (bool)(num & (1 << i));
        //printf("%d", c);
        if (node[pos][c] == -1) {
            
            node[pos][c] = ntp++;
            // if (c == 1) printf("%d\n", node[pos][c]);
        }
        pos = node[pos][c];
        //if (num == 9 && i == 3)printf("%d", pos);
    }
    //printf("\n");
}
int cal_max(int num) {
    int pos = root; int val = 0;
    //printf("DEBUG(num:%d,i): ", num);
    for (int i = 3; i >= 0; i--) {
        int c = (bool)(num & (1 << i));
        //printf("(%d)", !c);
        if (node[pos][!c] != -1) {
        //    printf("%d ", i);
            val |= (1 << i); pos = node[pos][!c];
        } else pos = node[pos][c];
    }
    //printf("\n");
    //printf("DEBUG: %d %d\n", num, val);
    return val;
}
int fsrd() {
    int p = 0; int c = getchar();
    while(!isdigit(c)) c = getchar();
    while(isdigit(c)) {
        p = p*10 + (c-'0'); c = getchar();
    }
    return p;
}
int a[MAX_N];
int main() {
    memset(node, -1, sizeof(node));
    int n = fsrd();
    for (int i = 1; i <= n; i++) 
        insert(a[i] = fsrd());
    //printf("DEBUG: %d %d\n", node[0][0], node[0][1]);
    //for (int i = 0; i <= 20; i++) {
    //    printf("DEBUG(%d): %d %d\n", i, node[i][0], node[i][1]);
    //}
    int gmax = 0;
    for (int i = 1; i <= n; i++) {
        int now = cal_max(a[i]);
        if (now > gmax) gmax = now;
    }
    printf("%d\n", gmax);
    return 0;
}