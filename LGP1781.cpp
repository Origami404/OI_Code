#include <iostream>
#include <string>
using namespace std;

bool strcmp(const string& a, const string& b) {
    if (a.size() != b.size())
        return a.size() < b.size();

    for (int i = a.size(); i >= 0; i--) {
        if (a[i] == b[i])
            continue;
        return a[i] < b[i];
    }
    return false;
}

int main() {
    int a, max_index = 0;
    cin >> a;
    cin.get();
    string max_num("0"), now("0");
    for (int i = 0; i < a; i++) {
        cin >> now;
        if (strcmp(max_num, now)) {
            max_num = now;
            max_index = i;
        }
    }

    cout << max_index + 1 << endl << max_num;
    return 0;
}