#include<stdio.h>
#include<vector>
#include<algorithm>
#include<set>
#define MAX_SIZE 300001
using namespace std;

int root[MAX_SIZE];
int n, m, l, r, x, i, j;
vector<int> v;
set<int> s;

int main() {
	
	scanf_s("%d %d", &n, &m);
	
	for (i = 1; i < n + 1; i++) {
		root[i] = i;
		s.insert(i);
	}
	auto iter = s.lower_bound(1);
	for (i = 0; i < m; i++) {
		
		//m의 범위가 0 < m < 3x10^5 이므로 꼭 scanf로 하자
		scanf_s("%d %d %d", &l, &r, &x);
		iter = s.lower_bound(l);
		while (iter != s.end() && *iter <= r) {
			if (*iter != x) {
				root[*iter] = x;
				iter = s.erase(iter);
			}
			else iter++;
		}
	}
	for (i = 1; i < n + 1; i++)
		printf("%d ", (root[i] == i ? 0 : root[i]));
	
}