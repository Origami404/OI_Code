#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#define MAX_CH 28
#define MAX_INPUT 160
#define MAX_P_LEN 80
#define MAX_NODE 800007
#define MAX_S_LEN 1000007
using namespace std;
struct ACMation {
    char input[MAX_INPUT][MAX_P_LEN];
    int trie[MAX_NODE][MAX_CH];
    int root, ttp; // 1 1
    int end[MAX_NODE];
    void insert(const char* str, int index) {
        int pos = root, len = strlen(str);
        for (int i = 0; i < len; i++) {
            int c = str[i] - 'a';
            if (trie[pos][c] == 0)
                trie[pos][c] = ++ttp;
            pos = trie[pos][c];
        }
        end[pos] = index;
    }

    int fail[MAX_NODE], last[MAX_NODE];
    void build() {
        fail[root] = last[root] = root;
        queue<int> q;
        q.push(root);
        while (!q.empty()) {
            int fa = q.front(); q.pop();
            for (int i = 0; i < 26; i++) {
                int now = trie[fa][i];
                if (now != 0) {
                    int k = fail[fa];
                    while (k != root && trie[k][i] == 0)
                        k = fail[k];
                    if (trie[k][i] != 0 && trie[k][i] != now) 
                        k = trie[k][i];
                    fail[now] = k;
                    last[now] = end[k] != 0 ? k : last[k];
                    q.push(now);
                } 
            }
        }
    }

    int count[MAX_NODE], max_count;
    inline void upd_count(int pos) {
        if (end[pos]) {
            count[pos] += 1;
            if (max_count < count[pos]) 
                max_count = count[pos];
        }

    }
    void match(const char* str) {
        int pos = root, len = strlen(str);
        for (int i = 0; i < len; i++) {
            int c = str[i] - 'a';
            while (pos != root && trie[pos][c] == 0)
                pos = fail[pos];
            if (trie[pos][c] != 0)
                pos = trie[pos][c];
            //if (end[pos]) {
            for (int lp = pos; lp != root; lp = last[lp]) 
                if (end[lp])
                    max_count = max(max_count, ++count[lp]);
            //}
        }
    }

    int ans[MAX_NODE], atp;
    void print() {
        for (int i = root; i <= ttp; i++) {
            if (count[i] == max_count)
                ans[atp++] = end[i];
        }
        sort(ans, ans + atp);
        printf("%d\n", max_count);
        for (int i = 0; i < atp; i++) {
            // printf("DEBUG: %d\n", ans[i]);
            printf("%s\n", input[ans[i]]);
        }
    }

    void init() {
        memset(trie, 0, sizeof(trie));
        memset(fail, 0, sizeof(fail));
        memset(last, 0, sizeof(last));
        memset(end, 0, sizeof(end));
        memset(count, 0, sizeof(count));
        memset(ans, 0, sizeof(ans));
        root = 1; ttp = 1; max_count = 0;
        atp = 0;
    }
} acm;
char buf[MAX_S_LEN];
void deal(int n) {
    acm.init();
    for (int i = 1; i <= n; i++) {
        scanf("%s", acm.input[i]);
        acm.insert(acm.input[i], i);
    }
    acm.build();
    scanf("%s", buf);
    acm.match(buf);
    acm.print();
}
int main() {
    int n;
    while (scanf("%d", &n), n != 0) {
        deal(n);
    }
    return 0;
}