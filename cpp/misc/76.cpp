#include<iostream>
#include<algorithm>
typedef long long ll;
#define INF 10000000000;
using namespace std;

ll N, M, G, S, x, y, g, s, root[201];
struct road {
	ll x;
	ll y;
	ll g;
	ll s;
	road() { };
	road(int x, int y, int g, int s) :x(x), y(y), g(g), s(s) {  };
};
inline bool cmp(const road& lv, const road& rv) {
	return lv.g == rv.g ? lv.s < rv.s : lv.g < rv.g;
}
road edge[50001];
road MST[201];
ll find(int a) {
	if (root[a] == a) return a;
	return root[a] = find(root[a]);
}
int main() {
	scanf("%d %d %d %d", &N, &M, &G, &S);
	for (int i = 1; i <= M; i++) {
		scanf("%d %d %d %d", &x, &y, &g, &s);
		edge[i] = road(x, y, g, s);
	}
	sort(edge + 1, edge + M + 1, cmp);
	int e = 0;
	long long ans = -1;
	for (int i = 1; i <= M; i++) {
		int iter = 0;
		for (int i = 0; i < 201; i++) root[i] = i;
		MST[e++] = edge[i];
		for (int j = e - 1; j > 0; j--) {
			if (MST[j].s < MST[j - 1].s)
				swap(MST[j], MST[j - 1]);
		}
		for (int j = 0; j < e; j++) {
			int rx = find(MST[j].x);
			int ry = find(MST[j].y);
			if (rx != ry) {
				root[rx] = ry;
				MST[iter++] = MST[j];
			}
		}
		e = iter;
		if (iter == N - 1 && (ans == -1 || ans > G * edge[i].g + S * MST[N - 2].s))
			ans = G * edge[i].g + S * MST[N - 2].s;
	}

	printf("%I64d", ans);

}