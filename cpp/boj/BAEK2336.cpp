#include<iostream>
#include<algorithm>
#include<string.h>

using namespace std;

const int MAX = 500000 + 10, INF = MAX * 2, NUMBER_OF_TESTS = 3;

enum 
{
	FIRST,
	SECOND,
	THIRD
};

int seg[MAX * 4];
int N, student;
int grade_to_student[NUMBER_OF_TESTS][MAX], student_to_grade[NUMBER_OF_TESTS][MAX];

//SEGMENT TREE
void update(int lo, int hi, int value, int node, int left, int right) {
	if (hi < left || right < lo) {
		return;
	}
	if (lo <= left && right <= hi) {
		seg[node] = min(seg[node], value);
	}
	if (left == right) return;

	int mid = (left + right) / 2;
	update(lo, hi, value, node * 2, left, mid);
	update(lo, hi, value, node * 2 + 1, mid + 1, right);

	seg[node] = min(seg[node * 2], seg[node * 2 + 1]);
}

int load(int lo, int hi, int node, int left, int right) {
	if (hi < left || right < lo) {
		return INF;
	}
	if (lo <= left && right <= hi) {
		return seg[node];
	}

	int mid = (left + right) / 2;
	return min(load(lo, hi, node * 2, left, mid), load(lo, hi, node * 2 + 1, mid + 1, right));
}

int main() {
	//FAST IO
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	memset(seg, INF, sizeof seg);

	cin >> N;
	for (int test = 0; test < NUMBER_OF_TESTS; test++) {
		for (int grade = 1; grade <= N; grade++) {
			cin >> student;
			grade_to_student[test][grade] = student;
			student_to_grade[test][student] = grade;
		}
	}

	int ans = 0;
	for (int grade = 1; grade <= N; grade++) {

		int student = grade_to_student[FIRST][grade];

		//자신의 2번째 시험 등수 앞에 있는 학생들의 3번째 등수 중 가장 작은 값을 불러온다.
		//만약 그 값이 자신의 3번째 등수보다 낮다면 굉장한 학생일 수 없다.
		int isAmaizing = load(1, student_to_grade[SECOND][student], 1, 1, N) > student_to_grade[THIRD][student];
		if (isAmaizing) {
			ans++;
		}
		//자신의 2번째 시험 등수 위치에 3번째 등수를 저장한다.
		//이렇게 하므로써 이후 쿼리에서 자신보다 두번째 등수가 앞인 사람들의 3번째 등수를 알 수 있으며,
		//그 값을 통해 괴장한 학생임을 판별한다.
		update(student_to_grade[SECOND][student], student_to_grade[SECOND][student], student_to_grade[THIRD][student], 1, 1, N);
	}

	cout << ans;
	
}