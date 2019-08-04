#include <iostream>
#include <string>
using namespace std;
/*
bool strcmp(const string& a, const string& b) {
    if (a.size() != b.size())
        return a.size() < b.size();

    for (int i = 0; i < a.size(); i++) {
        if (a[i] == b[i]) continue;
        return a[i] < b[i];
    }
    return false;
}*/

int main() {
    int a, max_index = 0;
    cin >> a;
    string max_num(""), now("");
    for (int i = 0; i < a; i++) {
        cin>>now;
        if (now.size() > max_num.size() ||
  			   (now.size() >= max_num.size() && now > max_num)) {
            max_num = now;
            max_index = i;
        }
    }

    cout << max_index + 1 << endl << max_num << endl;
    return 0;
}
