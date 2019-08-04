#include <cstdio>
#include <cstring>
#include <cctype>
#include <cstdlib>
#define PROGRAM_SIZE 107
#define LINE_SIZE 15
#define HASH_TABLE_SIZE 107
#define hash(c) (int)(c-'A')
#define is_n(c) (bool)(c[0]=='n')
#ifndef NULL
#	define NULL 0
#endif // ifndef NULL
using namespace std;

struct loop {
	char name[LINE_SIZE], x[LINE_SIZE], y[LINE_SIZE];
	loop(char* in, char* ix, char* iy){
		strcpy(name, in); strcpy(x, ix); strcpy(y, iy);
	}
};
bool check(); int count_loop(int line);
char program[PROGRAM_SIZE][LINE_SIZE], time_fzd[LINE_SIZE];
bool hash_table[HASH_TABLE_SIZE];
int pro_count = 0;

int main() {
	scanf("%d", &pro_count);
	for (int t = 0; t < pro_count; t++){
		int pro_size;
		scanf("%d %s", &pro_size, time_fzd);
		for (int i = 0; i < pro_size; i++)
			scanf("%s", program[i]);
		if (!check()) { printf("ERR\n"); continue; }
		int w = count_loop(0); // TODO 可能会有并列的循环
		printf("O(n^%d)", w);
	}
	return 0;
}
// 检查合法性 ， 意思就是下面的函数完全不检查 
bool check(){
	// TODO 
	return true;
} 
// 从当前行抽取loop, 
loop* mk_loop(char* nowline) {
	if (nowline[0] == 'E') return NULL;
	char tmp[LINE_SIZE];
	strcpy(tmp, nowline);
	char* first_token = strtok(tmp, " ");
	//assert(strcmp(first_token, "F") == 0); 
	#define NEXT_TOKEN strtok(NULL, " ")
	return new loop(NEXT_TOKEN, NEXT_TOKEN, NEXT_TOKEN);
	#undef NEXT_TOKEN
}
// 返回w， line表示代码行数 
int count_loop(int line) {
	loop* nln = mk_loop(program[line]);
	if (nln == NULL) return 0;
	bool x_is_n = is_n(nln->x), y_is_n = is_n(nln->y);
	if (!x_is_n && !y_is_n) {
		if (atoi(nln->x) >= atoi(nln->y)) return 0;
		else return count_loop(line + 1);
	} else if (!x_is_n && y_is_n) {
		return 1 + count_loop(line + 1);
	} else return 0;
}
