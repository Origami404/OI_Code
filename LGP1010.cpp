#include <cstdio>
#include <cstring>
using namespace std;
int pow2 [] = {
	1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024,
	 2048, 4096, 8192, 16384, 32768
};
const char* bs[16] = {
	//0   1     2       3       4         5            6
	"","2(0)", "2", "2+2(0)", "2(2)", "2(2)+2(0)", "2(2)+2",
	//7               8             9               10
	"2(2)+2+2(0)", "2(2+2(0))", "2(2+2(0))+2(0)", "2(2+2(0))+2",
	//11              12                13
	"2(2+2(0))+2+1", "2(2+2(0))+2(2)", "2(2+2(0))+2(2)+1",
	//14                 15
	"2(2+2(0))+2(2)+2", "2(2+2(0))+2(2)+2+1",
};
const char* bs2[] ={
	  "2(0)", "2", "2(2)"
};
int main(){
	int n;
	scanf("%d", &n);
	char* str = new char[100010];
	str[0] = '\0';
	bool fis = true;
	for (int i = 15; i>= 0;i--){
		if (pow2[i] <= n ){
			n-=pow2[i];
			char* tstr = new char[60];
			if (i <= 1){
				sprintf(tstr, fis ? "%s" : "+%s", bs2[i]);
			} else{
				sprintf(tstr ,fis ? "2(%s)" : "+2(%s)", bs[i]);
			}
			
			fis = false;
			strcat(str, tstr);
			delete[] tstr;
		}
	}
	//printf("%d", n);
	printf("%s", str);
	return 0;
}
