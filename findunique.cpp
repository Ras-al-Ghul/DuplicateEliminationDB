#include <bits/stdc++.h>
using namespace std;

int main(){
	ifstream ip;
	ip.open("output.txt");
	string lines;
	set<string> hello;
	while(getline(ip, lines)){
		hello.insert(lines);
	}
	cout<<hello.size()<<endl;
}