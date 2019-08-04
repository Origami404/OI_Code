#include <iostream>
#include <queue>
#include <algorithm>
struct cmp {
    bool operator()(const int& a, const int& b) { return a > b; }
};
using namespace std;
int main(){
    priority_queue<int,vector<int> ,cmp> dui;
    int n,now, sum = 0;
    cin >> n;
    for (int i = 0; i < n; i++){
        cin >> now;
        dui.push(now);
    }
    int nmin;
    while (dui.size() != 1){
        nmin = dui.top();
        dui.pop();
        nmin += dui.top();
        dui.pop();
        dui.push(nmin);
        sum += nmin;
    }
    //sum -= dui[0];
    cout << sum << endl;

    return 0;
}

