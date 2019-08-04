#include <cstdio>
using namespace std;
char tree[10010], n;
int find(char c){
	for (int i = 1; i < 1000; i++)
		if (tree[i] == c) return i;
}
void inord(int i){
	 if (tree[i] == '*' || tree[i] == 0) return;
	 printf("%c", tree[i]);
	 inord(2*i);
	 inord(2*i+1);
}
int main(){
	scanf("%d", &n);
	char* in = new char[10];
	scanf("%s", in);
	tree[1] = in[0];tree[2] = in[1];tree[3] = in[2];
	for (int i = 1; i < n; i++){
		scanf("%s", in);
		int rt = find(in[0]);
		tree[rt*2] = in[1];
		tree[rt*2+1] = in[2];
	}
	inord(1);
	return 0;
}



