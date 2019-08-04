#include <cstdio>
#include <cstring>
#include <cctype>
#define MAX_N 1000007
#define MAX_M 1000007
using namespace std;
char s[MAX_N], p[MAX_M];
int sbegin = 0, slen, plen, next[MAX_M];
void cal_next() {
	next[1] = 0;
	int k = 0;
	for (int i = 1; i < plen; i++) {
		while (k && p[i] != p[k]) k = next[k];
		next[i+1] = p[i] == p[k] ? ++k : 0;
	}
}
void match() {
	int j = 0;
	for (int i = 0; i < slen; i++) {
		while (j && s[i] != p[j]) j = next[j];
		if (s[i] == p[j]) ++j;
		if (j == plen) printf("%d\n", i - plen + 2);
	}
}
int main() {
	scanf("%s%s", s, p);
	slen = strlen(s);
	plen = strlen(p);
	cal_next();
	match();
	for (int i = 1; i <= plen; i++)
		printf("%d ", next[i]);
	return 0;
}

