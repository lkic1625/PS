///algospot BRACKETS2

#include<iostream>
#include<vector>
#include<string>
using namespace std;

int c;
vector<char> v;
string br;

bool isMatch() {

	for (int i = 0; i < br.size(); i++) {
		if (br[i] == '(' || br[i] == '{' || br[i] == '[')
			v.push_back(br[i]);
		else if (!v.empty() && (v.back() - br[i] == -1 || v.back() - br[i] == -2))
			v.pop_back();
		else
			return false;
	}

	return true;
}


int main() {
	cin >> c;	
	
	while (c-- > 0)
	{
		cin >> br;
		printf(isMatch() && v.empty() ? "YES\n" : "NO\n");
		v.clear();
	}
	
}