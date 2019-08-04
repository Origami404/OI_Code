#include <cstdio>
using namespace std;
bool used[MAXN];
void euler() {
	for (int i = 2; i <= MAXN; i++) {
		if (!used[i]) {
			// i is prime
			for (int j = n / i; j > 0; j--) {
				if (!used[j]) {
					// i * j isn't prime
					// i is its smallest prime factor
					used[i*j] = true;
				}
			}
		}
	}
}
