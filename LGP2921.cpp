#include <cstdio>
#include <cstring>
#define MAXN 100010
using namespace std;
int next[MAXN],cyl[MAXN], his[MAXN], time[MAXN],  n;
int main(){
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", next + i);
	memset(cyl, -1, sizeof(cyl));
	for (int i = 1; i <= n; i++){
		memset(time, -1 , sizeof(time));
		int nt = 0, now = i, htop = 0;
		while (true){
			//if (now == 3) printf("DEBUG(when 2 cyl[3]): %d", cyl[now]);
			if (cyl[now] != -1){
				//printf("DEBUG(i, now): touch cyl: %d %d\n",i, now);
				int cyl_size = cyl[now];
				//printf("DEBUG(touch cyl,cyl_size): %d\n", cyl_size);
				for (int i = htop - 1; i >= 0; i--){
					cyl[his[i]] = cyl_size + htop - i;
				}
				break;
			} else if (time[now] != -1) {
				//printf("DEBUG(i,now): touch walked: %d %d\n",i, now);
				int bc = htop - 1, cyl_size = nt - time[now];
				//printf("DEBUG(walked,cyl_size): %d\n", cyl_size);
				for (;bc >= 0 && his[bc] != now; bc--){
					//printf("DEBUG(walked back, in cyl: his[bc]): %d\n", his[bc]);
					cyl[his[bc]]= cyl_size;
				}
				for (int i = bc; i >= 0; i--){
					//printf("DEBUG(walked back, not in cyl: his[bc]): %d\n", his[i]);
					cyl[his[i]] = cyl_size + bc - i;
				}
				break;
			} else {
				time[now] = nt++;
				his[htop++] = now;
				now = next[now];
			}
		}
		printf("%d\n", cyl[i]);
	}
	return 0;
}
