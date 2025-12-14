/*

SCPC 1차 예선 

개구리 뛰기

Greedy

input
입력 파일에는 여러 개의 테스트 케이스가 포함될 수 있다.
파일의 첫째 줄에는 테스트 케이스 개수를 나타내는 자연수 T가 주어지고,
이후 차례로 T개의 테스트 케이스가 주어진다. ( 1≤T≤5 )
각각의 테스트 케이스 첫 번째 줄에는 '좌표 0'에 놓인 돌을 제외한 나머지 돌들의 개수 N 이 주어진다. ( 1≤N≤1,000,000 )
두 번째 줄에는 돌들이 놓인 좌표를 나타내는 N 개의 정수 ai들이 빈칸(공백)을 사이에 두고 주어진다. (1≤ai≤10^9 )
여기서, 주어진 좌표들은 증가하는 순서로 주어지고 모두 다르다.
세 번째 줄에는 개구리가 한 번의 점프로 이동 가능한 최대 거리 K 가 주어진다. ( 1≤K≤10^9 )

output
각 테스트 케이스의 답을 순서대로 표준출력으로 출력하여야 하며, 각 테스트 케이스마다 첫 줄에 “Case #T”를 출력하여야 한다.
이때 T는 테스트 케이스의 번호이다.
그 다음 줄에는 개구리가 마지막 돌로 이동할 수 있는 최소 점프 횟수를 출력한다.
만약, 개구리가 마지막 돌로 이동하는 것이 불가능한 경우에는 "-1"을 출력한다.
*/
#include <iostream>
#include<algorithm>

using namespace std;

const int MAX_STONES_COUNT = 1.0e+6, MAX_VALUE = 1.0e+9;
int Answer, N, a[MAX_STONES_COUNT + 2], K, isjumpable;

int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	
	int T, test_case;
	
	cin >> T;
	for (test_case = 0; test_case < T; test_case++)
	{
		//init
		Answer = 0;

		//input
		cin >> N;
		for (int i = 1; i <= N; i++) {
			cin >> a[i];
		}
		cin >> K;

		//greedy
		for (int i = 0; i < N + 1;) {
			isjumpable = false;
			int jump = i;
			for (; a[jump + 1] - a[i] <= K && jump <= N; jump++) {
				//Go forward as much as possible if we can.
				isjumpable = true;
			}
			if (!isjumpable) {
				//If we can't move a single step, output -1.
				Answer = -1;
				break; 
			}
			i = jump;
			Answer++;
		}

		//output
		cout << "Case #" << test_case + 1 << endl;
		cout << Answer << endl;
	}

	return 0;
}