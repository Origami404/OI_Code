#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main(){
    int N;
    cin >> N;
    vector<int> vec;
    int nm;
    for (int i = 0; i < N;i++){
        cin >> nm;
        vec.push_back(nm);
    }
    sort(vec.begin(), vec.end());
    vector<int>::iterator nwend = unique(vec.begin(), vec.end());
    vec.erase(nwend, vec.end());
    cout << vec.size() << endl;
    for (vector<int>::iterator pos = vec.begin(); pos != nwend; ++pos){
        cout << *pos << ' ';
    }
    cout << endl;
    return 0;
}

