#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

struct Player {
    int id;
    int score;
    // bool operator<(const Player& other) { return score < other.score; }
    // Player(int i, int s): id(i),score(s){}
};
ostream& operator<<(ostream& out, Player p) {
    out << p.id << " " << p.score;
    return out;
}
int main(int argc, char const* argv[]) {
    int n, m;
    cin >> n >> m;
    vector<Player> pls;
    Player tmp;
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &(tmp.id), &(tmp.score));
        pls.push_back(tmp);
    }
    m += m / 2;
    sort(pls.begin(), pls.end(), [](Player p1, Player p2) {
        return p1.score == p2.score ? p1.id < p2.id : p1.score > p2.score;
    });

    int fsx = pls[m].score;
    while (m < pls.size() && pls[m].score >= fsx)
        m++;
    cout << fsx << " " << m << endl;
    for (int i = 0; i < m; i++) {
        cout << pls[i] << endl;
    }

    return 0;
}
