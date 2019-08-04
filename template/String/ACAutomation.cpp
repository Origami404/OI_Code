#include <cstdio>
#include <cstring>
#include <queue>
/* LGP3796 AC自动机 简单版
 * 大意: 求主串中出现了**多少个**模式串
 * 模式串可重复, 保证字符为小写字母
 */
// 不使用0节点(虚节点) 直接连根节点(1)
#define MAX_CH 28
#define MAX_NODE 12000007
#define MAX_S_LEN 6000007
using std::queue;
// Trie 树
int trie[MAX_NODE][MAX_CH];
// 模式串终结标记 因为可能有重复模式串所以需要int
int end[MAX_NODE];

// Trie 插入
int root = 1, ttp = 1;
void insert(const char* str) {
    int len = strlen(str), pos = root;
    for (int i = 0; i < len; i++) {
        int c = str[i] - 'a';
        if (trie[pos][c] == 0) 
            trie[pos][c] = ++ttp;
        pos = trie[pos][c];
    }
    end[pos] += 1;
}

// nxt 与 last 的计算
// nxt的含义只能意会一下了emmmm
// last[i] 表示 i 随着nxt上去碰到的第一个模式串结尾索引
// 用于加速每次找到模式串后向上搜索子模式串的时间
int nxt[MAX_NODE], last[MAX_NODE];
void cal_nxt() {
    queue<int> q;
    q.push(root);
    nxt[root] = root;
    last[root] = root;
    while (!q.empty()) {
        int fa = q.front(); 
        q.pop();
        // printf("DEBUG(fa): %d\n", fa);
        // 遍历查找下一个字符串
        for (int i = 0; i < 26; i++) {
            // 如果有 那么将 now 搞成当前节点
            // fa 搞成祖先节点
            int now = trie[fa][i]; 
            if (now != 0) {
                int k = nxt[fa];
                // printf("DEBUG(%d): Father nxt: %d\n", now, k);
                // 走到第一个可以向下扩展到当前字符的节点
                while (k != root && trie[k][i] == 0) k = nxt[k];
                // printf("DEBUG(%d): After jump up: %d\n", now, k);
                // 如果是的确找到了而不是k到了root, 那么就更新nxt
                if (trie[k][i] != 0 && trie[k][i] != now) 
                    k = trie[k][i];
                // printf("DEBUG(%d): After go down: %d\n", now, k);
                nxt[now] = k;
                // last递推很简单, 如果nxt是模式串结尾那么就是nxt
                // 如果不是那就拿nxt的last值
                last[now] = end[nxt[now]] != 0 ? nxt[now] : last[nxt[now]];
                // 塞入队列
                q.push(now); 
            }
        }
    }
}

// 是否在主串中出现过的标记数组
bool vis[MAX_NODE];
int match(const char* str) {
    int cnt = 0, tpos = root;
    int len = strlen(str), spos = 0;
    // 遍历主串
    while (spos < len) {
        int c = str[spos] - 'a';
        // printf("Matching: %d %d... ", tpos, spos);
        // 如果当前trie树可以向下走
        if (trie[tpos][c] != 0) {
            // printf("(catch) \n");
            spos += 1; // 移动主串
            tpos = trie[tpos][c];
        } else { // 如果不能走就nxt
            // printf("(miss)\n");
            tpos = nxt[tpos];
        }
        // 对于每一个点上去查找有没有子模式串
        for (int i = tpos; i != root; i = last[i]) {
            if (!vis[i]) { // 判重
                cnt += end[i];
                vis[i] = true;
            }
        }
        // cnt += end[tpos];
    }
    return cnt;
}
char buf[MAX_S_LEN];
int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%s", buf);
        // printf("DEBUG: %s\n", buf);
        insert(buf);
    }
    cal_nxt();
    // printf("DEBUG(trie):\n");
    // for (int i = 1; i <= ttp; i++) {
    //     printf("DEBUG(%d): ", i);
    //     for (int j = 0; j < 26; j++)    
    //         if (trie[i][j] != 0) printf("%c -> %d, ", j + 'a', trie[i][j]);
    //     printf("\n");
    // }

    // printf("DEBUG(nxt): ");
    // for (int i = 1; i <= ttp; i++) {
    //     printf("%d ", nxt[i]);
    // }
    // printf("\n");

    // printf("DEBUG(last): ");
    // for (int i = 1; i <= ttp; i++) {
    //     printf("%d ", last[i]);
    // }
    // printf("\n");

    scanf("%s", buf);
    printf("%d\n", match(buf));
    return 0;
}