#include <cstdio>
using namespace std;
int main(){
    char expr[265];
    scanf("%s", expr);
    int khcnt = 0;
    for (int i = 0; expr[i] != '@'; i++){
        if (expr[i] == '(')
            khcnt++;
        if (expr[i] == ')')
            khcnt--;
        if (khcnt < 0)
            break;
    }
    if (!khcnt)
        printf("YES");
    else
        printf("NO");
    return 0;
}