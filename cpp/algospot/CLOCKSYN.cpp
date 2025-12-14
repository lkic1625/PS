#include<iostream>
#include<vector>

using namespace std;

int crt_time[16]; //시계들의 현재시간 저장
int btn_times[10];
void search(const int& stack, bool& stmt);
bool check_clock();
bool stmt = false;
int arr[5] = { 0,5,6,7,8 };
vector<vector<int> > btn_list(
	{
	   vector<int>({0,3,5}),
	   vector<int>({0,8}),
	   vector<int>({0,5,8}),
	   vector<int>({1,6,8,9}),
	   vector<int>({2,3,7,8,9,}),
	   vector<int>({3,7,8,9}),
	   vector<int>({3,4}),
	   vector<int>({1,3,7}),
	   vector<int>({4}),
	   vector<int>({1,9}),
	   vector<int>({2,4}),
	   vector<int>({1}),
	   vector<int>({4}),
	   vector<int>({9}),
	   vector<int>({2,5,7}),
	   vector<int>({2,5,7})
	}
);

void set_list();
int i, j, C, sum;
int main() {
	cin >> C;
	while (C > 0)
	{
		sum = 0;
		for (i = 0; i < 16; i++) {
			cin >> crt_time[i];
		}

		set_list();

		search(0, stmt);


		for (i = 0; i < 10; i++) {
			sum += btn_times[i];
			btn_times[i] = 0;
		}
		cout << sum << endl;


		C--;
	}

}

void set_list()
{
	btn_times[1] = crt_time[11] % 4;
	btn_times[4] = crt_time[8] % 4;
	btn_times[9] = crt_time[13] % 4;
	btn_times[3] = crt_time[6] % 4 - crt_time[8] % 4;
	if (btn_times[3] < 0) btn_times[3] += 4;
	btn_times[2] = crt_time[10] % 4 - crt_time[8] % 4;
	if (btn_times[2] < 0) btn_times[2] += 4;


}

void search(const int& stack, bool& stmt) {

	if (stack == 5) stmt = check_clock();

	else {

		for (int i = 0; i <= 4; i++) {

			search(stack + 1, stmt);
			if (stmt) return;
			btn_times[arr[stack]]++;
		}
		btn_times[arr[stack]] = 0;
	}


}

bool check_clock()
{
	int sum = 0;
	for (i = 0; i < btn_list.size(); i++) {
		for (j = 0; j < btn_list[i].size(); j++) {
			sum += btn_times[btn_list[i][j]];
		}
		if (sum % 4 != crt_time[i] % 4) return false;
		else sum = 0;
	}
	return true;
}