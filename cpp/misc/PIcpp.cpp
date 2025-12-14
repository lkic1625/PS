#include<iostream>
#include<string>
#include<algorithm>
#include<string.h>

#define INF 3000001

using namespace std;

string p;
int cache[200000];
int C;

int PI(int start);

int cut(int start, int counting);

int main() {
	
	cin >> C;

	while (C-- > 0)
	{
		
		memset(cache, -1, sizeof(cache));
		p.clear();
		cin >> p;
		cout << PI(0) << endl;
	}
	
	return 0;

}

int PI(int start) {
	
	if (start > p.size()) return INF;
	if (start == p.size()) return 0;

	int& ret = cache[start];
	if (ret != -1) return ret;

	ret = INF;
	int pt[3];
	for (size_t i = 3; i <= 5; i++) {
		pt[i - 3] = cut(start, i);
		ret = min(ret, pt[i -3] + PI(start + i));
	}

	return ret; 
}

int cut(int start, int counting) {

	if (start + counting > p.size()) return INF;

	int i = counting - 1;
	while (i > 0)
		if (p[start + i] == p[start + i - 1])
			i--;
		else
			break;
	if (i == 0) return 1;

	i = counting - 1;
	while (i > 1)
		if ((p[start + i] - p[start + i - 1]) == p[start + i - 2] - p[start + i - 1])
			i--;
		else
			break;
	if (i == 1) return 4;

	i = counting - 1;
	while (i > 0)
		if ((p[start + i] - p[start + i - 1] == 1) || (p[start + i] - p[start + i - 1] == -1))
			i--;
		else
			break;
	if (i == 0) return 2;
	

	i = counting - 1;
	while (i > 1)
		if ((p[start + i] - p[start + i - 1]) == p[start + i - 1] - p[start + i - 2])
			i--;
		else
			break;
	if (i == 1) return 5;
	
	
	return 10;
}