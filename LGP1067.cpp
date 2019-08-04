#include <cstring>
#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
using namespace std;
int xs[100];
int main() {
    ios::sync_with_stdio(false);
    int n;
    cin >> n;
    cin.get(); // 吃掉换行


    string line;
    getline(cin, line);
    stringstream ss = stringstream(line);
    for (int i = 0; i <= n; i++) {
       
        ss >> xs[i];
        //cout << xs[i];
    }

    for (int i = 0; i <= n; i++){
        if(xs[i]==0)
            continue;
        if (xs[i] < 0)
            cout << '-';
        else if (i != 0)
            cout << '+';

        if (i==n || (abs(xs[i]) != 1 && xs[i] != 0)) {
            cout << abs(xs[i]);
        }

        if (i != n)
            cout << 'x' << '^' << (n - i);
    }
    //cout << endl;
    return 0;
}