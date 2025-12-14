#include<iostream>
#include<string>
const int MASK = 1;
const int REG_SIZE = 32;
const int MAX = INT_MAX - 1;

using namespace std;

bool cache[REG_SIZE];

struct FA {
	bool a, b, c, s;
	
	bool loadCarry() { return a & b | ((a ^ b) & c); }
	FA(int a, int b, int c) : a(a), b(b), c(c), s(a^b^c){}
	
};
//Parallel Adder Subtractor 
struct PAS {
	FA *fa[REG_SIZE];

	bool flagV, flagZ, flagS, flagC, signBit;
	PAS(bool signBit,int a, int b): signBit(signBit) {
		//true false 출력에 필요한 lambda
		auto temp = [](bool flag)->string {
			return flag ? "true" : "false";
		};

		bool carry = signBit;
		for (int i = 0; i < REG_SIZE; i++){	
			fa[i] = new FA(a & MASK, b & MASK ^ signBit, carry);	
			a = a >> 1; b = b >> 1; 
			carry = fa[i]->loadCarry();
			cache[i] = fa[i]->s;
			
			printf("%d 번째 레지스터 a[%d] = %d, b[%d] = %d, sum[%d] = %d, carry[%d] = %d, next carry flag =  %d\n", 
				i + 1, i, fa[i]->a, i, fa[i]->b, i, fa[i]->s, i, fa[i]->c, carry);
			for (int i = REG_SIZE - 1; i >= 0; i--)
				cout << cache[i];
			cout << "\n\n";
			
		}
		
		loadFlag();
		cout << "V: " << temp(flagV)  << " Z: " << temp(flagZ) << " S: " << temp(flagS) << " C: " << temp(flagC) << "\n";
	}
	
	void loadFlag() {
		
		flagV = fa[REG_SIZE - 1]->c ^ fa[REG_SIZE - 1]->loadCarry();
		for (int i = 0; i < REG_SIZE; i++)
			flagZ |= fa[i]->s;
		flagZ != flagZ;
		flagS = fa[REG_SIZE - 1]->s;
		flagC = fa[REG_SIZE - 1]->loadCarry();
	}
	
};

void add() {
	int subtrahend, minuend;
	cout << "피감수 :";
	cin >> minuend;
	cout << "감수 : ";
	cin >> subtrahend;
	PAS pas = PAS(false, minuend, subtrahend);
}

void sub() {
	int subtrahend, minuend;
	cout << "피감수 :";
	cin >> minuend;
	cout << "감수 : ";
	cin >> subtrahend;
	PAS pas = PAS(true, minuend, subtrahend);
}

void func() {

	int subtrahend, minuend;
	string temp;
	bool flag;
	cout << "뺄셈일 경우 1을 입력하시오. " << "\n";
	cout << ":";
	cin >> temp;
	flag = temp == "1";
	cout << "피감수 :";
	cin >> minuend;
	cout << "감수 : ";
	cin >> subtrahend;
	PAS pas = PAS(flag, minuend, subtrahend);
	
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	func();
}