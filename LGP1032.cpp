#include <iostream>
#include <string>
#include <set>
#include <queue>
using namespace std;
string as[7], bs[7], a, b;
set<string> rep;
int N = 0;
struct Node {
	int tran_cnt;
	string str;
	Node(int num, string s): tran_cnt(num), str(s) {}
};
string tran(const string& in, int ind) {
	string res;
	size_t nowi = 0;
	while (nowi < in.size()) {
		size_t ffi = in.find(as[ind], nowi);
		if (ffi == string::npos) break;
		res += in.substr(nowi, ffi);
		res += bs[ind];
		nowi = ffi + as[ind].size();
	}
	res += in.substr(nowi, in.size());
	//cout<<"DEBUG(raw, rule, after): "<<in<<"; "
	//<<as[ind]<<" -> "<<bs[ind]<<"; "<<res<<endl;
	return res;
}
bool bfs() {
	queue<Node> q;
	q.push((Node) {
		0, a
	});
	while (!q.empty()) {
		Node now = q.front();
		q.pop();
		if (now.tran_cnt > 10) {
			cout<<"NO ANSWER!"<<endl;
			return false;
		}
		for (int i = 0; i < N; i++) {
			if (now.str.find(as[i])!=-1) {
				
				for (int j=now.str.find(as[i]); j<now.str.length(); j=now.str.find(as[i],j+1)) {
					string res=now.str;
					res.replace(j,as[i].length(),bs[i]);
				

				if (res == b) {
					cout<<now.tran_cnt + 1<<endl;
					return true;
				}
				if(!rep.count(res)) {
					q.push((Node) {
						now.tran_cnt+1, res
					});
					rep.insert(res);
				}}
			}
		}
		return false;
	}
}
	int main() {
		cin>>a>>b;
		while (cin>>as[N]>>bs[N]) N++;
		if (!bfs()) {
			cout<<"NO ANSWER!\n"<<endl;
		}
		return 0;
	}



