#include <cstdio>
#include <cmath>
#include <cctype>

#define MAX_N 3000100
// using namespace std;

template <typename T>
inline void swap(T &a, T &b) {
    T t = a; a = b; b = t;
}

const double PI = acos(-1.0);

template <typename T>
struct ComplexNum {
    T r, i; // a + bi                                       
    ComplexNum() : r(0), i(0) {}
    ComplexNum(T rx, T ix) : r(rx), i(ix) {}
    ComplexNum operator+(const ComplexNum& o) const {
        return ComplexNum(r + o.r, i + o.i); 
    }
    ComplexNum operator-(const ComplexNum& o) const {
        return ComplexNum(r - o.r, i - o.i);
    }
    ComplexNum operator*(const ComplexNum& o) const {
        return ComplexNum(r * o.r - i * o.i, r * o.i + i * o.r);
    }
    ComplexNum& operator*=(const ComplexNum& o) {
        T nr = r * o.r - i * o.i;
        T ni = r * o.i + i * o.r;
        r = nr; i = ni;
        return *this;
    }
};
typedef ComplexNum<double> Complex;

Complex A[MAX_N], B[MAX_N];
int rev[MAX_N];
// 2^k == n
void init_rev(int n, int k) {
    for (int i = 0; i < n; i++) {
        // i = ((i/2) << 1) & (i & 1)
        // 反转后就要把i/2 右移, 并且在最前面补i的最后一位
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (k - 1));
    }
}
void FFT_BitRev(int n, Complex* a, int type) {

    // 位反 i < rev[i] 防反转两次
    for (int i = 0; i < n; i++)
        if (i < rev[i]) swap(a[i], a[rev[i]]);

    // 枚举每两个待合并区间的中点
    for (int mid = 1; mid < n; mid <<= 1) {
        // 每一个子区间都需要 mid/2 次单位根, 约去2得下式
        Complex Wn(cos(PI / mid), type * sin(PI / mid));
        // j 枚举每两个待合并个区间的起点
        for (int j = 0; j < n; j += (mid << 1)) {
            Complex Wk(1, 0);
            // 枚举前一个要合并区间
            for (int k = 0; k < mid; k++, Wk *= Wn) {
                // 原地修改需要临时变量
                Complex x = a[j + k], y = Wk * a[j + mid + k];
                a[j + k] = x + y;
                a[j + mid + k] = x - y;
            } 
        }
    }
}

int fsrd() {
    int p = 0; int c = getchar();
    while(!isdigit(c)) c = getchar();
    while(isdigit(c)) {
        p = p*10 + (c-'0'); c = getchar();
    }
    return p;
}

#define TYPE_FFT 1
#define TYPE_IFFT -1

int main() {
    int n, m;
    n = fsrd(), m = fsrd();
    for (int i = 0; i <= n; i++) 
        A[i].r = fsrd();
    for (int i = 0; i <= m; i++) 
        B[i].r = fsrd();
    // nn = 2^k >= n + m, min{k}
    int nn = 1, k = 0;
    while (nn <= n + m)
        nn <<= 1, ++k;

    init_rev(nn, k);

    FFT_BitRev(nn, A, TYPE_FFT);
    FFT_BitRev(nn, B, TYPE_FFT);

    // mul
    for (int i = 0; i <= nn; i++) 
        A[i] *= B[i];
    
    FFT_BitRev(nn, A, TYPE_IFFT);
    for (int i = 0; i <= n + m; i++) 
        printf("%d ", (int)(A[i].r / nn + 0.5));
    return 0;
}