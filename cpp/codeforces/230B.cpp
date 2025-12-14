#include<iostream>
#include<math.h>
using namespace std;

int n;

bool isTprime(long long num) {
	long long sq = sqrt(num);
	if (sq * sq != num) return false;
	long long sqsq = sqrt(sq);
	
	for (int i = 2; i <= sqsq; i++) {
		if (!(sq % i)) 
			return false;
	}
	return true;
}

int main() {
	long long temp;
	cin >> n;
	while (n-- > 0) {
		scanf_s("%I64d", &temp);
		cout << (isTprime(temp) && temp != 1 ? "YES" : "NO") << endl;
	}

}