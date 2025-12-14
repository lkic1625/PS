#include<algorithm>
#include<iostream>
#include<stack>
#include<string.h>
#include<vector>

using namespace std;

const int MAX = 100000 + 5;

char NEW_LINE;
int T, N, M, A, B;
int visited[MAX];
stack<int> st;
vector<int> graph[MAX], graph_with_reverse_edge[MAX];
vector<int> scc;


void dfs(int v) {
	if (visited[v]) return;
	visited[v] = true;

	for (auto child : graph[v]) {
		dfs(child);
	}

	st.push(v);
}

void scc_traversal(int v) {
	if (visited[v]) return;
	visited[v] = true;

	for (auto child : graph_with_reverse_edge[v]) {
		scc_traversal(child);
	}

	scc.push_back(v);
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> T;
	while (T-- > 0)
	{
		cin >> N >> M;
		//make graph
		for (int i = 0; i < M; i++) {
			cin >> A >> B;
			graph[A].push_back(B);
			graph_with_reverse_edge[B].push_back(A);
		}
		
		//Kosaraju algorithm
		for (int vertex = 0; vertex < N; vertex++) if (!visited[vertex]) {
			dfs(vertex);
		}

		memset(visited, 0, sizeof visited);
		int start = st.top(); st.pop();
		scc_traversal(start);
		
		while (!st.empty()) st.pop();
		memset(visited, 0, sizeof visited);

		dfs(scc.back());
		if (st.size() != N) cout << "Confused\n\n";
		else {
			sort(scc.begin(), scc.end());
			for (auto vertex : scc) {
				cout << vertex << "\n";
			}
			cout << "\n";
		}

		//init for next test case
		while (!st.empty()) st.pop();
		scc.clear();
		memset(visited, 0, sizeof visited);
		for (int vertex = 0; vertex < N; vertex++){
			
			graph[vertex].clear();
			graph_with_reverse_edge[vertex].clear();
		}
	}
}