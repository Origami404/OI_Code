#include <algorithm>
#include <deque>
#include <iostream>

using namespace std;

deque<int> ram;
int M;
int N;

int main(int argc, char const* argv[]) {
    cin >> M >> N;
    int nc;
    int cnt = 0;
    for (int i = 0; i < N; i++) {
        cin >> nc;
        if (find(ram.cbegin(), ram.cend(), nc) != ram.cend())
            continue;
        else {
            if (ram.size() >= M) {
                ram.pop_front();
            }
            ram.push_back(nc);
            cnt++;
        }
    }
    cout << cnt << endl;
    return 0;
}
