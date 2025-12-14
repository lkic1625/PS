/*

scpc 1차 예선

방속의 거울

input
입력 파일에는 여러 개의 테스트 케이스가 포함되어 있다.
파일의 첫째 줄에는 테스트 케이스 개수를 나타내는 자연수 T 가 주어지고,
이후 차례로 T 개의 테스트 케이스가 주어진다. ( 1≤T≤20)
각각의 테스트 케이스 첫 번째 줄에는 정사각형 격자구조의 '한 변의 방 개수'를 나타내는 정수 N 이 주어진다. ( 1≤N≤1,000 )
다음 줄부터는 N 개의 줄이 주어지고, 각 줄마다 N 개의 문자가 주어진다, 각 문자는 { ‘0’, ‘1’ , ‘2’ }에 속하는 문자 중 하나이다.
문자 ‘1’은 우측 상단에서 좌측 하단으로 45도 기울어진 양면거울이 그 방에 있다는 것을 나타내며,
문자 ‘2’는 좌측 상단에서 우측 하단으로 45도 기울어진 양면거울이 그 방에 있다는 것을 나타낸다.
그리고 문자 ‘0’은 거울이 없는 방임을 나타낸다. 각 줄에 들어 있는 문자들 사이에 빈칸(공백)은 없다.

output
각 테스트 케이스의 답을 순서대로 표준출력으로 출력하여야 하며, 각 테스트 케이스마다 첫 줄에 “Case #T”를 출력하여야 한다.
이때 T는 테스트 케이스의 번호이다.
그 다음 줄에는 정사각형 격자구조 건물의 '맨 위 맨 왼쪽 방'의 왼쪽에서 수평(0도)으로 들어간 빛이
그 건물을 빠져나올 때까지 거치는 서로 다른 거울의 개수를 출력한다.

*/

/*

case 1 ╱

U -> L
R -> D
D -> R
L -> U

case 2 ╲

U -> R
R -> U
D -> L
L -> D

*/

#include <iostream>
#include<string>
#include<set>
#include<stdlib.h>

using namespace std;

enum Direction
{
	UP = 0b00000001,
	DOWN = 0b00000010,
	RIGHT = 0b00000100,
	LEFT = 0b00001000
};

void travel(int y, int x, int dir) {
	if (lattice[y][x] == '9') return;
	int type = (int)(lattice[y][x] - '0');
	int reflextion_dir = reflection(type);

	switch (reflextion_dir)
	{
	case UP:
		y = y - 1;
		break;
	case RIGHT:
		x = x + 1;
		break;
	case DOWN:
		y = y + 1;
		break;
	case LEFT:
		x = x - 1;
		break;
	}

	return travel(y, x, dir);


}

int reflection(int type) {

}

const int MAX_ROOMS = 1000;
int Answer, N;
string lattice[MAX_ROOMS + 2];
set<pair<int, int>> s;

int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int T, test_case;
	cin >> T;
	for (test_case = 0; test_case < T; test_case++)
	{
		Answer = 0;
		
		cin >> N;
		for (int i = 0; i < N + 2; i++) {
			lattice[0] += "9";
			lattice[N + 1] += "9";
		}
		for (int i = 1; i <= N; i++) {
			cin >> lattice[i];
			lattice[i] = "9" + lattice[i] + "9";
		}
		
		Answer = s.size();
		
		cout << "Case #" << test_case + 1 << endl;
		cout << Answer << endl;
	}

	return 0;
}