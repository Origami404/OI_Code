#include <cstdio>
using namespace std;
int main(){
	long long b, p, k, ans=1; // ³õÊ¼»¯£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡ 
	scanf("%lld%lld%lld", &b, &p, &k);
	printf("%lld^%lld mod %lld=", b, p, k);
	while(p>0){
		if (p%2 != 0) ans = ans*b % k;
		b = b*b % k;
		p>>=1;
	}
	printf("%lld", ans%k);
	return 0;
}
