#include<iostream>
#include<vector>
#include<map>

using namespace std;


vector<int> adj;
map<string, int> dict;
string names[100];
int N;


int main() {
	
	do
	{
		cin >> N;
		string input;
		for (int i = 0; i < N; i++) {
			cin >> input;
			string node = input.substr(0, input.find(':'));
			dict[node] = i;
			names[i] = node;
		}

	} while (N != 0);
	
	
}