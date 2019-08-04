#include <cstdio>
// Rational number
template <typename T>
inline T gcd(T a, T b) {
    return b == 0 ? a : gcd(b, a % b);
}
template <typename T>
inline T lcm(T a, T b) {
    return (a / gcd(a, b)) * b;
}
template <typename B>
struct RatNum {
    B a, b; // a / b
    RatNum(): a(0), b(1) {}
    RatNum(B a): a(a), b(1) {}
    RatNum(B a, B b) {
        B g = gcd(a, b);
        if (b < 0) {
            this->a = -a / g;
            this->b = -b / g;
        } else {
            this->a = a / g;
            this->b = b / g;
        }
        //printf("%d %d\n", this->a, this->b);
    }
};
template <typename B>
RatNum<B> operator+(const RatNum<B> &x, const RatNum<B> &y) {
    const B& l = lcm(x.b, y.b);
    return RatNum<B>(x.a * (l / x.b) + y.a * (l / y.b), l);
}
template <typename B>
RatNum<B> operator-(const RatNum<B> &x) {
    return RatNum<B>(-x.a, x.b);
}
template <typename B>
RatNum<B> operator-(const RatNum<B> &x, const RatNum<B> &y) {
    return x + (-y);
}
template <typename B>
RatNum<B> operator*(const RatNum<B> &x, const RatNum<B> &y) {
    return RatNum<B>(x.a * y.a, x.b * y.b);
}
template <typename B>
RatNum<B> operator/(const RatNum<B> &x, const RatNum<B> &y) {
    return x * RatNum<B>(y.b, y.a);
}
template <typename B>
FILE* operator<<(FILE* out, const RatNum<B> &x) {
    fprintf(out, "%d / %d", x.a, x.b);
    return out;
}
int main() {
    stdout << (RatNum<int>(2, 8) * RatNum<int>(2, 8) + RatNum<int>(1, 16));
    fflush(stdout);
    return 0;
}