#include <cstdio>
using namespace std;
int power[11] = {
    1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000,
};
int stack[1010], top = 0;
char input[1010];
int main() {
    scanf("%s", input);
    int i = 0;
    while (input[i] != '@') {
        if ('0' <= input[i] && input[i] <= '9') {
            int start = i, num = 0;
            while (input[++i] != '.')
                ;  // 是的，我 “的确想” 故意跳过while
            for (int j = i++ - start - 1; j >= 0; j--)
                num += power[j] * (input[start++] - '0');
            stack[top++] = num;
        } else {
            int a = stack[--top]; // ++和--要注意， 因为前面是后缀，这里就要前缀，反之也成立，但是反过来小心-1越界
            int b = stack[--top];
            switch (input[i++]) {  // 要注意数字顺序了， FILO
                case '+':
                    stack[top++] = b + a;
                    break;
                case '-':
                    stack[top++] = b - a;
                    break;
                case '*':
                    stack[top++] = b * a;
                    break;
                case '/':
                    stack[top++] = b / a;
                    break;
                default:
                    break;
            }
        }
        /* for (int i = 0; i < top; i++){
            printf("%d, ", stack[i]);
        }
        printf("\n");*/
    }
    printf("%d", stack[0]);
    return 0;
}
