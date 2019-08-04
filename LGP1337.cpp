#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <ctime>
#define MAXN 1007
using namespace std;
int hx[MAXN], hy[MAXN], w[MAXN], n;
double drand() {
    return (rand()*2 - RAND_MAX);
}
double stat(double x, double y) {
    double E = 0.0;
    for (int i = 1; i <= n; i++) {
        double dx = x - hx[i], dy = y - hy[i];
        E += w[i] * sqrt(dx * dx + dy * dy);
    }
    return E;
}
double ax = 0, ay = 0;
void sa() {
	for (int i = 1; i <= n; i++) 
		(ax += hx[i]), (ay += hy[i]);
    (ax /= n), (ay /= n);
    double t = 1000;
    double nowE = stat(ax, ay), nextE;
    while (t > 1e-15) {
        double dx = drand() * t, dy = drand() * t;
        nextE = stat(ax + dx, ay + dy);
        if (nextE < nowE || exp((nowE-nextE)/t) * RAND_MAX > rand()) {
            (ax += dx), (ay += dy);
            nowE = nextE;
        }
        t *= 0.999;
    }
}
int main() {
    srand(time(NULL));
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d %d %d", hx + i, hy + i, w + i);
    sa();
    printf("%.3f %.3f", ax, ay);
    return 0;
}
