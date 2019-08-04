#include <cstdio>
#include <algorithm>
#define MAXN 307
using namespace std;
struct Student {
	int no, chinese, total;
	bool operator<(const Student& other) const {
		if (total != other.total) {
			return other.total < total;
		} else if (chinese != other.chinese) {
			return other.chinese < chinese;
		} else {
			return no < other.no;
		}
	}
} s[MAXN];
int main() {
	int n, c, m, e;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d %d %d", &c, &m, &e);
		s[i] = (Student){i, c, c+m+e};
	}
	sort(s+1, s+n+1);
	for (int i = 1; i <= 5; i++) {
		printf("%d %d\n", s[i].no, s[i].total);
	}
	return 0;
}



