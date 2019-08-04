#include <cstdio>
#include <stdint.h>
using namespace std;
class BigNum {
public:
    
private:
    #define MAX_BIT 15
    void mknum(const char* str) {
        int pos = strlen(str) - 1;
        // int pos = len - 1;
        neg = str[pos] == '-';
        pos -= neg; 
        while (pos >= 0) {
            
        }
    }
    unsigned int *num, size;
    bool neg;
};
int main() {
    return 0;
}