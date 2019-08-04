#include <cstdio>
using namespace std;
int main(){
    char str[15];
    int sum = 0, j = 0;
    scanf("%s", str);
    for (int i = 0; i <= 11; i++){
        if (str[i] == '-') continue;
        sum += (str[i] - '0') * (++j);
    }
    //printf("DEBUG(sum, j): %d %d\n", sum, j);
    sum %= 11;
    if (sum == str[12] - '0' || (sum == 10 && str[12] == 'X')) printf("Right");
    else{
        str[12] = '\0';
        printf("%s%c", str, sum == 10 ? 'X' : (sum + '0'));
    } 
    return 0;
}