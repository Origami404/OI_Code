#include <cstdio>
#include <cstring>
#define MAX_S 1000007
#define MAX_P 1000007
using namespace std;
int next[MAX_P], plen, slen;
char s[MAX_S], p[MAX_P];
void cal_next() {
	next[0] = 0;
	int k = 0;
	for (int i = 2; i <= plen; i++) {
		while (k > 0 && p[i] != p[k+1]) k = next[k];
		if (p[i] == p[k+1]) ++k;
		next[i] = k;
	}
}
void match(){
	int k = 0;
	for(int i = 1; i <= slen; i++){
		while (k > 0 && s[i] != p[k+1]) k = next[k];
		if (s[i] == p[k+1]) ++k;
		if (k == plen){
			printf("%d\n", i - plen + 1);
			k = next[k];
		}
	}
}
int main() {
	scanf("%s%s", s + 1, p + 1);
	(slen = strlen(s + 1)), (plen = strlen(p + 1));
	cal_next();
	match();
	for (int i = 1; i <= plen; i++)
		printf("%d ", next[i]);
	return 0;
}