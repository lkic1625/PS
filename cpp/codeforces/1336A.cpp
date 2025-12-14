/*
Tree, Greedy

https://codeforces.com/problemset/problem/1336/A
A. Linova and Kingdom

Input
The first line contains two integers n and k (2≤n≤2⋅10^5, 1≤k<n)  — the number of cities and industry cities respectively.

Each of the next n−1 lines contains two integers u and v (1≤u,v≤n), denoting there is a road connecting city u and city v.

It is guaranteed that from any city, you can reach any other city by the roads.

Output
Print the only line containing a single integer 
— the maximum possible sum of happinesses of all envoys.

*/

#include<iostream>
#include<vector>
#include<tuple>
#include<algorithm>
#include<queue>

using namespace std;

const int MAX_ELEMENT = 2.0e5 + 1;
int n, k, u, v, happinesses;
vector<int> adj[MAX_ELEMENT];
priority_queue<tuple<int, int>> pq;
int level[MAX_ELEMENT], isIndustry[MAX_ELEMENT], industryChildren[MAX_ELEMENT];

void dfs(int bef, int cur, int height) {
	level[cur] = height;
	if(adj[cur].size() == 1) pq.push({ height, cur });
	if (isIndustry[cur]) happinesses += height;	
	else height = height + 1;

	for (int child = 0; child < adj[cur].size(); child++) {
		if (adj[cur][child] != bef) {
			dfs(cur, adj[cur][child], height);
			
		}		
	}
}


int main() {

	//fast I/O
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//input
	cin >> n >> k;
	for (int i = 0; i < n - 1; i++) {
		cin >> u >> v;
		//make adj list
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	
	dfs(0, 1, 0);
	int cnt = 0;


	while (!pq.empty() && cnt < k) {
		int height, node;
		tie(height, node) = pq.top();
		pq.pop();
		if (level[node] - industryChildren[node] != height) continue;
		industryChildren[node]++;

		for (int i = 0; i < adj[node].size(); i++) {
			int parent = adj[node][i];
			if (isIndustry[parent]) continue;

			industryChildren[parent] += industryChildren[node];
			pq.push({ level[parent] - industryChildren[parent], parent });
		}
		cnt++;
		isIndustry[node] = true;
	}



}



/*
교수님 코드

#include<iostream>
#include<vector>
#include<tuple>
#include<algorithm>
#include<queue>

using namespace std;

struct City {
	long long dist, children;
	bool operator<(const City& rv) {
		return dist - children < rv.dist - rv.children;
	}
};

const int MAX_ELEMENT = 2.0e5 + 1;
int n, k, u, v;
long long happinesses;
vector<int> adj[MAX_ELEMENT];
priority_queue<tuple<int, int>> pq;
int level[MAX_ELEMENT], isIndustry[MAX_ELEMENT], industryChildren[MAX_ELEMENT];
City node[MAX_ELEMENT];

int dfs(int parent, int cur) {
	int ret = 0;
	node[cur].dist = node[parent].dist + 1;
	for (int i = 0; i < adj[cur].size(); i++) {
		if (adj[cur][i] != parent)
			ret += dfs(cur, adj[cur][i]) + 1;
	}

	node[cur].children = ret;
	return ret;
}

int main() {

	//fast I/O
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//input
	cin >> n >> k;
	for (int i = 0; i < n - 1; i++) {
		cin >> u >> v;
		//make adj list
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	dfs(0, 1);
	sort(node + 1, node + 1 + n);
	for (int i = n; i > n - k; i--) {
		happinesses += node[i].dist - node[i].children;
	}
	cout << happinesses - k << endl;

}
*/
