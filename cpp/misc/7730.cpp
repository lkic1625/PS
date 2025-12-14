//7730 ³ª¹«±ð´Â È«ÁØ
//Binary Search
//https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWq43PI6L64DFARG&categoryId=AWq43PI6L64DFARG&categoryType=CODE

#include<iostream>
#include<algorithm>

using namespace std;

int T, N, M;
int tree[1000001];

int search(int l, int r) {

	if (r == l) return l - 1;
	long long m = 0;
	int middle = (r + l) / 2;
	for (int i = 0; i < N; i++) {
		m += max(0, tree[i] - middle);
	}
	if (m > M)
		return search(middle + 1, r);
	else if (m < M)
		return search(l, middle);

	return middle;
}

int main() {
	cin >> T;
	int test_case = T;
	while (T-- > 0) {
		int r = 0;
		cin >> N >> M;
		for (int i = 0; i < N; i++) {
			cin >> tree[i];
			r = max(r, tree[i]);
		}
		cout << "#" << test_case - T << " " << search(0, r) << endl;

	}
}