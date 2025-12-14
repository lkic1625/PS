#include<iostream>
#include<algorithm>
#define INF 10000000000;
using namespace std;


int N, M, G, S, x, y, g, s, root[201];
long long ans;
struct Vertex {
	int x;
	int y;
	int g;
	int s;
	Vertex() { };
	Vertex(int x, int y, int g, int s) :x(x), y(y), g(g), s(s) {  };
};
inline bool cmp(const Vertex& lv, const Vertex& rv) {
	return (long long)rv.g * G + rv.s * S > (long long)lv.g *G + lv.s * S;
	return lv.g == rv.g ? lv.s < rv.s : lv.g < rv.g;
}
Vertex edge[50001];
int find(int a) {
	if (root[a] == a) return a;
	return root[a] = find(root[a]);
}
void Union(int a, int b) {
	a = find(a);
	b = find(b);
	root[a] = b;
}
int main() {
	for (int i = 0; i < 201; i++) root[i] = i;
	scanf("%d %d %d %d", &N, &M, &G, &S);
	for (int i = 1; i <= M; i++) {
		scanf("%d %d %d %d", &x, &y, &g, &s);
		edge[i] = Vertex(x, y, g, s);
	}
	sort(edge + 1, edge + M + 1, cmp);
	int gc = 0, sc = 0, cnt = 0;
	for (int i = 1; i <= M; i++) {
		int x = edge[i].x;
		int y = edge[i].y;
		if (find(x) != find(y)) {
			Union(x, y);
			cnt++;
			gc = max(gc, edge[i].g);
			sc = max(sc, edge[i].s);
		}
	}
	ans = max(ans,(long long)gc * G + sc * S);
	printf("%I64d", cnt == N - 1 ? ans : (long long)-1);

}