#include<iostream>
#include<queue>
#include<algorithm>

using namespace std;

queue<int> q[100001];
queue<int> ans;
int n, e[100001], l[100001], u, v, p[100001];

void bfs(int odd, int even, int node, bool isOdd) {
	int oper = isOdd ? odd : even;
	while (q[node].size() != 0) {
		int nextNode = q[node].front();
		bool flipFlag = (e[nextNode] + oper) % 2 != l[nextNode];

		if (flipFlag)
			ans.push(nextNode);

		if (isOdd)
			bfs(odd + flipFlag, even, nextNode, !isOdd);
		else
			bfs(odd, even + flipFlag, nextNode, !isOdd);

		q[node].pop();
	}
}

int main() {

	scanf_s("%d", &n);//n°ª ÀÔ·Â
	p[1]++;
	for (int i = 0; i < n - 1; i++) {
		scanf_s("%d %d", &u, &v);
		p[u]++; p[v]++;
		if (p[u] < p[v])
			q[v].push(u);
		else 
			q[u].push(v);
	}
	for (int i = 1; i <= n; i++) {
		scanf_s("%d", &e[i]);
	}
	for (int i = 1; i <= n; i++) {
		scanf_s("%d", &l[i]);
	}
	q[0].push(1);
	bfs(0, 0, 0, true);
	printf("%d\n", ans.size());
	while (ans.size() != 0) {
		printf("%d\n", ans.front());
		ans.pop();
	}


}