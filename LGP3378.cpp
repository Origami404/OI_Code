#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAXN 1000007
#define T int
#define lt(a) ((a<<1))
#define rt(a) ((a<<1)+1)
using namespace std;
int _last = 1;
T _tree[MAXN];
void _up() {
	for (int now = _last - 1;
	        now != 1 && _tree[now] < _tree[now>>1]; now>>=1)
		swap(_tree[now], _tree[now>>1]);
}
void _down() {
	int now = 1;
	while ((now<<1) < _last) {
		int min_tree = rt(now) < _last && _tree[lt(now)] < _tree[rt(now)] ? lt(now) : rt(now); 
		if (_tree[now] > _tree[min_tree])
			swap(_tree[now], _tree[min_tree]);
		else break;
		now = min_tree;
	}
}
void push(T& v) {
	_tree[_last++] = v;
	_up();
}
inline T& top() {
	return _tree[1];
}
void pop() {
	swap(_tree[1], _tree[--_last]);
	_down();
}
void init(){
	memset(_tree, 0x7f, sizeof(_tree));
}
signed main() {
	int n, code, num;
	//printf("ooooooooooooo");
	init();
	scanf("%d", &n);
	for (int _t = 0; _t < n; _t++) {
		scanf("%d", &code);
		if (code == 1) {
			scanf("%d", &num);
			push(num);
		} else if (code == 2) {
			printf("%d\n", top());
		} else if (code == 3) {
			pop();
		} else {
			// Never reach there!
			return 0;
		}
		
	}
	return 0;
}
