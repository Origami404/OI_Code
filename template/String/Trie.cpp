#include <cstdio>
#include <cstring>
#define MAX_NODE 1000007
#define MAX_CH 29
using namespace std;
// LGP2580
int node[MAX_NODE][MAX_CH];
bool end[MAX_NODE], has_find[MAX_NODE];
int root, ntp;
void insert(const char* str) {
    int len = strlen(str), np = root;
    for (int i = 0; i < len; i++) {
        if (node[np][str[i] - 'a'] == -1)
            node[np][str[i] - 'a'] = ntp++;
        np = node[np][str[i] - 'a'];
    }
    end[np] = true;
}
bool is_in(const char* str) {
    int len = strlen(str), np = root;
    for (int i = 0; i < len; i++) {
        if (node[np][str[i] - 'a'] == -1)
            return false;
        np = node[np][str[i] - 'a'];
    }
    return end[np];
}

#define WRONG 1
#define OK 0
#define REPEAT 2
int judge(const char* str) {
    int len = strlen(str), np = root;
    for (int i = 0; i < len; i++) {
        if (node[np][str[i] - 'a'] == -1) 
            return WRONG;        
        np = node[np][str[i] - 'a'];
    }
    if (!end[np]) return WRONG;
    else if (has_find[np]) return REPEAT;
    else {
        has_find[np] = true;
        return OK;
    }
}

int main() {
    memset(node, -1, sizeof(node));
    int n, m;
    char buf[60];
    root = 0; ntp = 1;
    scanf("%d\n", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%s", buf);
        insert(buf);
    }
    scanf("%d\n", &m);
    for (int i = 1; i <= m; i++) {
        scanf("%s", buf);
        int res = judge(buf);
        if (res == WRONG) puts("WRONG");
        else if (res == REPEAT) puts("REPEAT");
        else puts("OK");
    }
    return 0;
}