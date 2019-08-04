#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#define MAXN 300
char input[MAXN], result[MAXN<<4];
bool used[MAXN];
int p1, p2, p3, ri = 0;
char mkchar(char c){
	if (p1 == 1) return tolower(c);
	else if (p1 == 2) return toupper(c);
	else return '*';
}
void send(int ind){
	if (!used[ind]){
		result[ri++] = input[ind];
		used[ind] = true;
	}
}
bool check(int ind){
	if (ind == 0 || input[ind+1] == '\0') 
	   return false;
    char l = input[ind-1], r = input[ind + 1];
    if (!((isalpha(l) ^ isalpha(r)) || (isdigit(l) ^ isdigit(r)))) 
	   return false;
    if (l >= r) 
	   return false;
    return true;
}
void succ_fill(int ind){
	send(ind - 1);
	send(ind + 1);
}
void normal_fill(int ind){
	send(ind - 1);
	char l = input[ind-1], r = input[ind + 1];
	for (char c = l + 1; c < r; c++){
		char p = mkchar(c);
		for (int i = 0; i < p2; i++)
			result[ri++] = p;
	}
	used[ind] = true;
	send(ind + 1);
}
void back_fill(int ind){
	send(ind - 1);
	char l = input[ind-1], r = input[ind + 1];
	for (char c = r - 1; c > l; c--){
		char p = mkchar(c);
		for (int i = 0; i < p2; i++)
			result[ri++] = p;
	}
	used[ind] = true;
	send(ind + 1);
}
void tran(){
	for (int i = 0; input[i] != '\0'; i++){
		if (input[i] == '-' && check(i)){
			
			char l = input[i-1], r = input[i+1];
			if (r - l == 1) {
				succ_fill(i);
			}else if (p3 == 1){
				normal_fill(i);
			} else if (p2 == 2){
				back_fill(i);
			}
		}
		else send(i);
	}
}
int main(void){
	scanf("%d %d %d %s", &p1, &p2, &p3, input);
	tran();
	result[ri++] = '\0';
	printf("%s\n", result);
	return 0;
}








