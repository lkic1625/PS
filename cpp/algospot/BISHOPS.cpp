/*
Bishops
https://algospot.com/judge/problem/read/BISHOPS

bipartite matching.

input
입력은 여러 개의 테스트 케이스로 주어진다. 입력의 첫 줄에는 테스트 케이스의 개수 T가 들어온다.
각각의 테스트 케이스의 첫 줄에는 체스판의 크기 N (1 <= N <= 8)이 주어진다.
이후 N줄에는 체스판의 상태가 주어진다. .은 Bishop을 놓을 수 있는 곳이며, *은 장애물이다.

output
각각의 테스트 케이스들에 대해 최대로 놓을 수 있는 Bishop의 개수를 출력한다.

*/


#include<iostream>
#include<vector>
#include<string>
#include<string.h>

using namespace std;

const int MAX_CHESS_BOARD_SIZE = 8, MAX = 100;

int T, N, n, m;
string chessboard[MAX_CHESS_BOARD_SIZE + 2];
int id[2][MAX_CHESS_BOARD_SIZE + 2][MAX_CHESS_BOARD_SIZE + 2], adj[MAX][MAX];
int dy[2] = { 1, 1 }, dx[2] = { 1, -1 };
vector<int> match;
vector<bool> visited;

bool dfs(int a) {
	if (visited[a]) return false;
	visited[a] = true;
	for (int b = 1; b < m; b++) {
		if (adj[a][b]) {//b가 매칭되어 있지 않거나 이미 매칭된 정점이 다른 정점과 매칭이 가능할 경우 bMatch[b]에서부터 시작해 증가경로를 찾는다
			if (match[b] == -1 || dfs(match[b])) {
				//증가 경로를 발견할 경우 a와 b를 매치 시킨다
				match[b] = a;
			//	cout << a << "와 " << b << "를 매칭시킵니다." << endl;
				return true;
			}
		}
	}

	return false;
}

int bipartiteMatch() {
	//처음에는 정점이 모두 연결되어 있지 않음.

	match = vector<int>(m, -1);
	int size = 0;
	for (int start = 1; start < n; start++) {
		visited = vector<bool>(n, false);
		if (dfs(start))
			++size;
	}
	return size;
}


void binding() {
	//starting number for each node is 1.
	int idx[2] = { 1, 1 };
	
	for (int direction = 0; direction < 2; direction++) {
		int visited[MAX_CHESS_BOARD_SIZE + 2][MAX_CHESS_BOARD_SIZE + 2];
		memset(visited, false, sizeof(visited));
		for (int y = 1; y <= N; y++) {
			for (int x = 1; x <= N; x++) {
				int cy = y, cx = x;
				//verify that we have not visited, and can create nodes
				while (chessboard[cy][cx] != '*' && !visited[cy][cx]) {
					visited[cy][cx] = true;
					//numbering
					id[direction][cy][cx] = idx[direction];
					cy += dy[direction];
					cx += dx[direction];
				}
				idx[direction]++;
			}
		}
	}
	n = idx[0];
	m = idx[1];
}


int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> T;
	while (T-- > 0) {
		
		//input
		cin >> N;		
		for (int i = 1; i <= N; i++) {
			cin >> chessboard[i];
			chessboard[i] = "*" + chessboard[i] + "*";
		}

		//init
		chessboard[N + 1] = "**********";
		chessboard[0] = "**********";
		memset(adj, 0, sizeof(adj));
		memset(id, 0, sizeof(id));

		//creating nodes.
		binding();
		//connecting edges.
		for (int y = 1; y <= N; y++) {
			for (int x = 1; x <= N; x++) {
				if (chessboard[y][x]) {
					adj[id[0][y][x]][id[1][y][x]] = 1;
				}
			}
		}

		//bipartite matching
		int Answer = bipartiteMatch();
		
		//output
		cout << Answer << "\n";
	
	}

}
