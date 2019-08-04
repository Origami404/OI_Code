#include <cstdio>
using namespace std;

int a[100010], n;
inline void swap(int l, int r){ int tmp = a[l]; a[l] = a[r]; a[r] = tmp; }
void quick_sort(int begin, int end){
    if (begin >= end)
        return;

    int i = begin, j = end - 1, base = a[begin];
    while (i < j){
        while ((i < j) && (a[j] > base))
            --j;
        if (i < j)
            a[i++] = a[j];
        while ((i < j) && (a[i] <= base))
            ++i;
        if (i < j)
            a[j--] = a[i];
    }

    a[i] = base;
    quick_sort(begin, i);
    quick_sort(i + 1, end);
}

int main(){
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    quick_sort(0, n);
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
    return 0;
}