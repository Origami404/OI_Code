#include <cstdio>
#include <algorithm>
#define MAXN 1000000 + 7
using namespace std;
int tree[MAXN];
int last = 1;
inline int top(){
	return tree[1];
}
inline void push(int v){
	tree[last] = v;
	int now = last++;
	while (now != 1){
		if (tree[now] < tree[now>>1])
		   swap(tree[now], tree[now>>1]);
        else break;
        now>>= 1;
	}
}
inline void pop(){
	swap(tree[1], tree[--last]);
	int now = 1;
	while ((now<<1) < last){
		int mnt = (now<<1)+1 < last && tree[(now<<1)+1] < tree[now<<1] ?
				  			 ((now<<1)+1) : now<<1;
        if (tree[mnt] < tree[now])
           swap(tree[mnt], tree[now]);
        else break;
        now = mnt;
	}
}
int main(){
	int n, num, code;
	scanf("%d", &n);
	for (int i = 0; i < n; i++){
		scanf("%d", &code);
		if (code == 1){
			scanf("%d", &num);
			push(num);
		} else if (code == 2) printf("%d\n", top());
		else if (code == 3) pop();
		else return 0; // Never reach here! 
		/*
		printf("DEBUG(tree): ");
		for (int j = 1; j < last; j++)
			printf("%d ", tree[j]);
		printf("\n"); //*/
	}
	return 0;
}
