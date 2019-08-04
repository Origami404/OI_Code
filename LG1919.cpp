#include <cstdio>
#include <cmath>
#define MAX_N 600007
using namespace std;

template <typename T>
inline void swap(T &a, T &b) {
    T t = a; a = b; b = t;
}

struct Complex {
    double rl, im; 
    Complex() : rl(0), im(0) {}
    Complex(double r, double i) : rl(r), im(i) {}
    Complex operator+(const Complex& o) const {
        return Complex(rl + o.rl, im + o.im); 
    }
    Complex operator-(const Complex& o) const {
        return Complex(rl - o.rl, im - o.im);
    }
    Complex operator*(const Complex& o) const {
        return Complex(rl * o.rl - im * o.im, rl * o.im + im * o.rl);
    }
    Complex& operator*=(const Complex& o) {
        double nrl = rl * o.rl - im * o.im;
        double nim = rl * o.im + im * o.rl;
        rl = nrl, im = nim;
        return *this;
    }
};
Complex A[MAX_N], B[MAX_N];

const double PI = acos(-1.0);

int rev[MAX_N];
inline void init_rev(int n, int k) {
    for (int i = 0; i < n; i++) 
        rev[i] = (rev[i>>1] >> 1) | ((i & 1) << (k - 1));
}

const int T_DFT = 1, T_IDFT = -1;
void FFT(int n, Complex* a, int type) {
    for (int i = 0; i < n; i++) 
        if (i < rev[i]) swap(a[i], a[rev[i]]);
    
    for (int m = 1; m < n; m <<= 1) {
        Complex Wn(cos(PI / m), type * sin(PI / m));
        for (int j = 0; j < n; j += (m << 1)) {
            Complex Wk(1, 0);
            for (int i = 0; i < m; i++, Wk *= Wn) {
                Complex x = a[j + i], y = Wk * a[j + m + i];
                a[j + i] = x + y;
                a[j + m + i] = x - y;
            }
        }
    }
}
char buf[MAX_N];
int nn = 1, k = 0, n = 0;
inline void input() {
    scanf("%d", &n);
    scanf("%s", buf);
    for (int i = 0; i < n; i++)
        A[n - 1 - i].rl = buf[i] - '0';
    scanf("%s", buf);
    for (int i = 0; i < n; i++)
        B[n - 1 - i].rl = buf[i] - '0';
    //n <<= 1;
    while (nn <= n + n) {
        nn <<= 1; ++k;
    }
}
int ans[MAX_N];
int main() {
    input();
    // printf("DBEUG(A.rl): ");
    // for (int i = 0; i < n + n; i++) {
    //     printf("%d ", (int)(A[i].rl + 0.5));
    // }
    // printf("\n");
    // printf("DBEUG(B.rl): ");
    // for (int i = 0; i < n + n; i++) {
    //     printf("%d ", (int)(B[i].rl + 0.5));
    // }
    // printf("\n");
    init_rev(nn, k);
    FFT(nn, A, T_DFT);
    FFT(nn, B, T_DFT);
    
    for (int i = 0; i < nn; i++)
        A[i] *= B[i];
    FFT(nn, A, T_IDFT);
    // for (int i = 0; i < n + n; i++) {
    //     putchar((int)(A[i].rl / nn + 0.5) + '0');
    // }
    // printf("DBEUG(A.rl): ");
    // for (int i = 0; i < n + n; i++) {
    //     printf("%d ", (int)(A[i].rl / nn + 0.5));
    // }
    // printf("\n");
    for (int i = 0; i < nn; i++) {
        int w = (int)(A[i].rl / nn + 0.5);
        ans[i] += w % 10;
        ans[i + 1] += ans[i] / 10;
        ans[i] %= 10;
        ans[i + 1] += w / 10;
    }
    ans[nn] = ans[nn - 1] / 10;
    ans[nn - 1] %= 10;
    int spos = nn;
    while (ans[spos] == 0) spos -= 1;
    while (spos >= 0) {
        putchar(ans[spos--] + '0');
    }
    return 0;
}