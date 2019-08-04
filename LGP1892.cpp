#include <cstdio>
#define MAXN 1007
using namespace std;
int uset[MAXN], n, m, cnt, enemy[MAXN], count[MAXN];
inline void init(){
	for (int i = 1; i <= n; i++)
		uset[i] = i;
}
inline int find(int x){
	return x == uset[x] ? x : (uset[x] = find(uset[x]));
}
inline void merge(int a, int b){
	uset[find(a)] = find(b);
}
inline void skip_char(){
	while (getchar() != '\n') continue;
}
int main(){
	scanf("%d%d", &n, &m);
	init();
	for (int i = 1; i <= m; i++){
		int a, b; char c;
		skip_char();
		scanf("%c%d%d", &c, &a, &b);
		if (c == 'F')
			merge(a, b); // ����ֱ�Ӻϲ� 
		else if (c == 'E'){
			// һ���˵ĵ��˿���ȫ���ϲ�Ϊһ�� 
			// ����ѡ��ȫ�����жԵ��˺ϲ��� ����a����enemys(b) 
			if (enemy[a] != 0)
				merge(b, enemy[a]);
			else enemy[a] = find(b);
			// һ���жԹ�ϵ�Ľ�����Ӱ�������˵ĵжԼ��� 
			if (enemy[b] != 0)
				merge(a, enemy[b]);
			else enemy[b] = find(a);
		}
	}
	for (int i = 1; i <= n; i++){
		if (count[find(i)] == 0)
			cnt++;
		count[find(i)]++;
	}
	printf("%d\n", cnt);
	return 0;
}
