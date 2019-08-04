#include <iostream>
using namespace std;

int A[100000];
int N;

int main(){
    int M;
    cin >> N >> M;
    for (int i = 0; i < N; i ++){
        cin >> A[i];
    }
    int cnt = 0, sum = 0;
    for (int i = 0; i < N; i++){
        if (sum + A[i] > M){
            sum = 0;
            cnt++;
        }
        sum += A[i];
    }
    cout << ++cnt << endl;
    return 0;
}