#include<iostream>
#include<set>
#include<vector>
#define MAX_SIZE 100001
using namespace std;

int n, m, a, b, MST[MAX_SIZE];
set<int> graphEdge, MSTEdge;
vector<pair<int, int>> ans;
bool isMST() {
	for (auto iter = graphEdge.begin(); iter != graphEdge.end(); iter++) {
		int i = 1;
		for (auto it = MSTEdge.begin(); it != MSTEdge.end(); i++, it++) {
			if (*iter < *it) return false;

		}
	}
}

int main() {
	scanf("%d %d", &n, &m);
	for (int i = 0; i < m; i++) {
		scanf("%d %d", &a, &b);
		if (b) MSTEdge.insert(a);
		else graphEdge.insert(a);
	}
	
}