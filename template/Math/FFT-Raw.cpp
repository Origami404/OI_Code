#include <cstdio>
#include <cmath>
#include <cctype>

#define MAX_N 3000100
// using namespace std;

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

void FFT_Raw(int n, Complex* a, int type) {
    if (n == 1) return;
    Complex A1[n >> 1], A2[n >> 1];
    // step +2 ! 要用小于号 !
    for (int i = 0; i < n; i += 2) {
        A1[i >> 1] = a[i];
        A2[i >> 1] = a[i + 1];
    }
    FFT_Raw(n >> 1, A1, type);
    FFT_Raw(n >> 1, A2, type);
    Complex Wn = Complex(cos(2.0 * PI / n), type * sin(2.0 * PI / n));
    Complex Wk = Complex(1, 0); // Wn0
    for (int i = 0; i < (n >> 1); i++, Wk *= Wn) {
        Complex t = Wk * A2[i];
        a[i] = A1[i] + t;
        a[i + (n >> 1)] = A1[i] - t;
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
    int nn = 1;
    while (nn <= n + m)
        nn <<= 1;
    FFT_Raw(nn, A, TYPE_FFT);
    FFT_Raw(nn, B, TYPE_FFT);

    // mul
    for (int i = 0; i <= nn; i++) 
        A[i] *= B[i];
    
    FFT_Raw(nn, A, TYPE_IFFT);
    for (int i = 0; i <= n + m; i++) 
        printf("%d ", (int)(A[i].r / nn + 0.5));
    return 0;
}