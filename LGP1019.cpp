#include <cstdio>
#include <cctype>
#include <cstring>
struct Str{
    char* s;
    int len;
    char operator[](int i) { return s[i]; }
    Str(char* is, int il) : s(is), len(il) {}
    Str() : s(NULL), len(-1) {}
} strs[30];
bool used[30];
int n, longest;
Str cat(Str a, Str b){
    int i = a.len, j = 0;
    while (i >= 0 && j < b.len && a[i] == b[j])
        i--, j++;
    if (j == 0 || i == 0)
        return Str();
        
    char* res = new char[300];
    for (int i = 0; i < a.len; i++)
        res[i] = a[i];
    for (int i = j; i < b.len; i++)
        res[i - j + a.len] = b[i];
        
    return Str(res, a.len + b.len - j);
}
int dfs(Str now){
    if (now.len == -1)
        return -1;
    bool flag = true;
    for (int i = 0; i < n; i++){
        if (used[i])
            continue;
        // 不做了！！ 妈耶
        
        
    }
}
int main(){

    
    scanf("%d", &n);
    for (int i = 0; i < n; i++){
        strs[i].s = new char[100];
        scanf("%s", strs[i].s);
        strs[i].len = strlen(strs[i].s);
    }
}