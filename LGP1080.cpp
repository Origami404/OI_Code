#include <cstdio>
#include <algorithm>

using namespace std;

struct man{
    int left, right;
    bool operator<(const man& other){
        return left * other.right < other.left * right;
    }
};
man ms[1000];
int ji[1000];
int main()
{
    int n;
    man king;
    scanf("%d", &n);
    scanf("%d %d", &(king.left), &(king.right));
    for (int i = 0; i < n; i++){
        scanf("%d %d", &(ms[i].left), &(ms[i].right));
    }
    sort(ms, ms + n);
    
    ji[0] = ms[0].left;
    for (int i = 1; i < n; i++){
        ji[i] = ji[i - 1] * ms[i].left;
    }

    int maxmin = king.left / ms[0].right, jingbi;
    for (int i = 1; i < n; i++){
        jingbi = ji[i-1] * king.left / ms[i].right;
        maxmin = max(jingbi, maxmin);
    }
    printf("%d", maxmin);
    return 0;
}


