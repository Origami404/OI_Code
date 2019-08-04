#include <cstdio>
#include <algorithm>
using namespace std;
struct line {
	int l, r;
	bool operator< (line o) const {
		return r < o.r;
	}
};
line ls[1000010];
int n, a, b, nr, cnt;
int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d %d", &a, &b);
		ls[i].l = a;
		ls[i].r = b;
	}
	sort(ls, ls + n);
	for (int i = 0; i < n; i++) {
		if (nr <= ls[i].l) {
			nr = ls[i].r;
			cnt++;
		}
	}
	printf("%d", cnt);

	return 0;
}
