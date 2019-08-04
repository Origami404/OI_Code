#include <iostream>
#include <string>
using namespace std;

void front(string mid, string las) {
	if (mid.size() > 0 ) {
		int rti = mid.find(las[las.size() - 1]);
		cout<<las[las.size()-1];
		front(mid.substr(0, rti), las.substr(0, rti));
		front(mid.substr(rti+1, mid.size()), las.substr(rti, las.size()-rti-1));
	}
}
int main() {
	string mid, las;
	cin>>mid>>las;
	front(mid, las);
	cout<<endl;
	return 0;
}


