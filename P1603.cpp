#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int to_num(const char* a) {
	#define with(a) if (false)
	#define match(str, num) else if (strcmp(a, str) == 0) return num
	with(in) ;
		match("one", 1);
		match("two", 4);
		match("three", 9);
		match("four", 16);
		match("five", 25);
		match("six", 36);
		match("seven", 49);
		match("eight", 64);
		match("nine", 81);
		match("ten", 0);
		match("eleven", 21);
		match("twelve", 44);
		match("thirteen", 69);
		match("fourteen", 96);
		match("fifteen", 25);
		match("sixteen", 56);
		match("seventeen", 89);
		match("eighteen", 24);
		match("nineteen", 61);
		match("twenty", 0);
		match("a", 1);
		match("both", 4);
		match("another", 1);
		match("first", 1);
		match("second", 4);
		match("third", 9);
	#undef match
	#undef with
	return -1;
}
char in[5000];
int x[10], xtp = 0;
int main() {
	for (int _ = 1; _ <= 6; _++) {
		scanf("%s", in);
		int num = to_num(in);
		//printf("DEBUG(num): %d\n", num);
		if (num > 0) x[xtp++] = num;
	}
	sort(x, x+xtp);
	long long res = x[0];
	for (int i = 1; i < xtp; i++) {
		res *= 100;
		res += x[i];
		//printf("DEBUG(res): %d\n", res);
	}
	printf("%lld\n", res);
	return 0;
}





