#include <cstdio>
#define SIZE 5010
using namespace std;
int n, m;
struct Player{
	int id, scr;
	bool operator<(Player other){
		return other.scr == scr ? other.id < id : other.scr > scr;
	}
};
Player ps[SIZE], ts[SIZE];
inline void swap(int ai, int bi){
	Player tmp = ps[ai];
	ps[ai] = ps[bi];
	ps[bi] = tmp;
}
void merge_sort(int begin, int end) {
	if (end - begin == 2) {
		if (ps[begin] < ps[end - 1])
			swap(begin, end - 1);
		return;
	} else if (end - begin == 1 || begin == end){
		return;
	}
	
	int middle = begin + (end - begin)/2;
	merge_sort(begin, middle);
	merge_sort(middle, end); 
	
	int i = begin, j = middle, num = begin;
	while (i < middle || j < end){
		if (i < middle){
			if (j < end){
			    ts[num++] = ps[j] < ps[i] ? ps[i++] : ps[j++];
			} else {
				ts[num++] = ps[i++];
			} 
		} else {
			ts[num++] = ps[j++];
		}
	}
	for (int i = begin; i < end; i++){
		ps[i] = ts[i];
	}
}
int main() {
	scanf("%d %d", &n, &m);
	int nid, ns;
	for (int i = 1; i <= n; i++) {
		scanf("%d %d", &nid, &ns);
		ps[i].id = nid;
		ps[i].scr = ns;
	}
	merge_sort(1, n + 1);
	
	int cut = m * 1.5, cs = ps[cut].scr;
	while (ps[cut].scr == cs) cut++;
	printf("%d %d\n", cs, cut - 1);
	for (int i = 1; i < cut; i++)
		printf("%d %d\n", ps[i].id, ps[i].scr);
	return 0;
}


