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
