#include <cstdio>
#include <cstring>
using namespace std;

int main() {
	int n;
	char first_name[30];
	int max_prize = -1, total = 0;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		int now_prize = 0;

		char name[30];
		int school_mark, class_mark, paper_amount;
		char is_union, is_western;

		scanf("%s %d %d %c %c %d", name, &school_mark, &class_mark,
		      &is_union, &is_western, &paper_amount);
		//printf("%s", name);

		if (school_mark > 80 && paper_amount >= 1)
			now_prize += 8000;
		if (school_mark > 85 && class_mark > 80)
			now_prize += 4000;
		if (school_mark > 90)
			now_prize += 2000;
		if (school_mark > 85 && is_western == 'Y')
			now_prize += 1000;
		if (class_mark > 80 && is_union == 'Y')
			now_prize += 850;

		if (now_prize > max_prize) {
			strcpy(first_name, name);
			max_prize = now_prize;
		}
		total += now_prize;
	}

	printf("%s\n%d\n%d\n", first_name, max_prize, total);
	return 0;
}
