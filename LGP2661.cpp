#include <cstdio>
#define MAXN 200010
using namespace std;
int  n, uset[MAXN], dis[MAXN], minl = 0x3f3f3f3f, now;
int find(int i) {
	//return i == uset[i] ? i : ((dis[i] += dis[uset[i]]), (uset[i] = find(uset[i])));
	if (uset[i] != i){
		int last = uset[i];
		uset[i] = find(uset[i]);
		dis[i] += dis[last];
	}
	return uset[i];
}
void chk(int a, int b) {
	int x = find(a), y = find(b), td = dis[a] + dis[b] + 1;
	if (x != y) {
		uset[x] = y;
		dis[a] = dis[b] + 1;
	} else if (minl > td) { minl = td; }
}
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) uset[i] = i;
	for (int i = 1; i <= n; i++){
		scanf("%d", &now);
		chk(i, now);
	}
	printf("%d", minl);
	return 0;
}

