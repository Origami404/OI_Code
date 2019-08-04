#include <cstdio>
using namespace std;
int exgcd(int a, int b, int &x, int &y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    } else {
        int g = exgcd(b, a % b, x, y);
        int py = y;
        y = x - (a / b) * y, x = py;
        return g;
    }
}
int main() {
    int a, b, x, y;
    printf("DEBUG(input: a, b): ");
    scanf("%d %d", &a, &b);
    exgcd(a, b, x, y);
    printf("DEBUG(x, y): %d %d\n", x, y);
    return 0;
}