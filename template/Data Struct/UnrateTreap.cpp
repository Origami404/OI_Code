#include <cstdio>
using namespace std;
struct Node {
    int key, value, lt, rt;
} node[MAX_N];
int root;
pair<int, int> split(int rid, int key) {
    if (rid == -1) return make_pair(-1, -1);
    if (node[rid].key > key) {
        pair<int, int> t = split(node[rid].lt, key);
        node[rid].lt = t.second;
        return t;
    } else {
        pair<int, int> t = split(node[rid].rt, key);
        node[rid].rt = t.first;
        return t;
    }
} 
int merge(int u, int v) {
    
}
int main() {
    return 0;
}