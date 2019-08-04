#include <cstring>
#include <iostream>
using namespace std;
int dt[10000][4];
int main() {
    ios::sync_with_stdio(false);
    memset(dt, 0, sizeof(dt));

    int n;
    cin >> n;
    //cout << "NUM N:" << n << endl;
    for (int i = 0; i < n; i++) {
        cin >> dt[i][0] >> dt[i][1] >> dt[i][2] >> dt[i][3];
        //cout << "DT INDEX: " << dt[i][0] << ", " << dt[i][1] << ", " << dt[i][2]
             //<< ", " << dt[i][3] << endl;
    }

    int x, y, index = -1;
    cin >> x >> y;
    //cout << "NUM X Y: " << x << ", " << y << endl;

    for (int i = 0; i < n; i++)
        if ((dt[i][0] <= x && x <= (dt[i][0] + dt[i][2] - 1)) &&
            (dt[i][1] <= y && y <= (dt[i][1] + dt[i][3] - 1))) {
            index = i + 1;
            //cout << "UPDATA INDEX: " << i << endl;
        }

    cout << index;
    return 0;
}