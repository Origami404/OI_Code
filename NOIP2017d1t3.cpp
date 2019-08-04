#include <cstdio>
#include <stack>
#include <cstring>
#include <cstdlib>
using namespace std;

#define MAX_LINE 1024 
#define MAX_LENGHT 256
char code[MAX_LINE][MAX_LENGHT], com[MAX_LENGHT];
int line;

#define X_IND 4
#define KEYWORD_IND 0
#define VAR_IND 2

//---------------------- check part ----------------------------
#define ERR_REUSED_VAR 1
#define ERR_TOO_MUCH_E 2
#define ERR_UNMATCH_F 3
#define ALL_OK 0
bool used_var[30]; // should be 26
inline int vtoi(char c) {
    return c-'a';
}

int check_err() {          
    stack<char> active_vars;
    int bracket = 0;
    memset(used_var, 0, sizeof(used_var));
    for (int nl = 1; nl <= line; nl++) {
        if (code[nl][KEYWORD_IND] == 'F') {
            ++bracket;
            char var = code[nl][VAR_IND];
            if (used_var[vtoi(var)]) {
                return ERR_REUSED_VAR;
            }        
            active_vars.push(var);
            used_var[vtoi(var)] = true;
        } else { // 'E'
            // match bracker
            --bracket;
            if (bracket < 0) {
                return ERR_TOO_MUCH_E;
            }
            // delete var
            used_var[vtoi(active_vars.top())] = false;
            active_vars.pop();
        }

    }
    return bracket != 0 ? ERR_UNMATCH_F : ALL_OK;
}
//-------------------------- parse part -------------------------
#define TOKEN_N   1
#define TOKEN_NUM 2
struct Token {
	int type, val;
};
int pos; // share between get_token and parse
Token get_token(const char* line) {
	Token ret;
	while (line[pos] == ' ') // spik blank
		++pos;
	if (line[pos] == 'n') { // catch 'n'
		ret.type = TOKEN_N;
		ret.val = 0;
		++pos;
	} else { // catch number
		int num = 0;
		while ('0' <= line[pos] && line[pos] <= '9') {
			num = num*10 + (line[pos] - '0');
			++pos;
		}
		ret.type = TOKEN_NUM;
		ret.val = num;
	}
	return ret;
}

#define ADD  1
#define KEEP 2
#define CUT  3
#define COMPARE 4
struct Result {
	int flag, val;	
};
int parse_loop() {
	stack<Result> s;
	Token x, y;
	int now_ans = 0, now_line = 1;
	do {
		char* ln = code[now_line++]; // make a shortcut and push down now_line
		pos = X_IND; // share with get_token
		if (ln[KEYWORD_IND] == 'F') {
			x = get_token(ln), y = get_token(ln);
			if (x.type == TOKEN_N && y.type == TOKEN_N) {
				s.push((Result) { KEEP, 0 });
			} else if (x.type == TOKEN_N && y.type == TOKEN_NUM) {
				s.push((Result) { CUT, 0 });
			} else if (x.type == TOKEN_NUM && y.type == TOKEN_N) {
				s.push((Result) { ADD, 0 });
			} else if (x.type == TOKEN_NUM && y.type == TOKEN_NUM) {
				if (x.val <= y.val) {
					s.push((Result) { KEEP, 0 });
				} else {
					s.push((Result) { CUT, 0 });
				}
			}
		} else { // ln[KEYWORD_IND] == 'E'
			Result htop = s.top();
			s.pop();
			if (htop.flag == ADD) {
				++now_ans;
			} else if (htop.flag == KEEP) {
				// DO NOTHING
			} else if (htop.flag == CUT) {
				now_ans = 0;
			} else if (htop.flag == COMPARE) {
				now_ans = max(now_ans, htop.val);
			}
			// pre read next line 
			if (code[now_line][KEYWORD_IND] == 'F') {
				s.push((Result) { COMPARE, now_ans });
				now_ans = 0;
			}
		}
	} while (!s.empty());
	return now_ans;
}
int parse_com() {
    if (com[2] == '1') {
        return 0;
    } else {
        return atoi(com + 4);
    }
}
//--------------------------- deal part ----------------------
void deal() {
	memset(code, 0, sizeof(code)); 
	scanf("%d %s\n", &line, com);
	for (int i = 1; i <= line; i++) {
		fgets(code[i], MAX_LENGHT, stdin);
	}
	if (check_err() != ALL_OK) {
		printf("ERR\n");
	} else {
		int should = parse_loop(), now = parse_com();
		if (should == now) {
			printf("Yes\n");
		} else {
			printf("No\n");
		}
	}
} 

int main() {
	int t;
	scanf("%d", &t);
	for (int _ = 1; _ <= t; _++) {
		deal();
	}
	return 0;
}
