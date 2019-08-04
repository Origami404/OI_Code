#include <cstdio>
using namespace std;
int n, a[500010], cnt, tmp[500010];
void swap(int l, int r){
	int t = a[l];
	a[l] = a[r];
	a[r] = t;
}
void merge_sort(int begin, int end) {
	if (end - begin < 2 ) {
		if (end - begin == 2) {
			if (a[begin] > a[end]) {
				swap(begin, end);
				cnt++;
			}
		}
		return;
	}



	int middle = begin + (end - begin)/2;
	merge_sort(begin, middle);
	merge_sort(middle, end);

	int i = begin, j = middle, k = begin;
	while (i < middle || j < end) {
		if (i < middle) {
			if (j < end) {
				if (a[i] > a[j]) {
					tmp[k++] = a[j++];
					cnt+= middle - i;
				} else
					tmp[k++] = a[i++];
			} else
				tmp[k++] = a[i++];
		} else
			tmp[k++] = a[j++];
	}
	for (int i = begin; i < end; i++)
		a[i] = tmp[i];
}
int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d", &a[i]);
	merge_sort(0, n);
	printf("%d", cnt);
	return 0;
}
