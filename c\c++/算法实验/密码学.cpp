#include<iostream>
#include<math.h>
#include<time.h>
using namespace std;
class RSA {
private:
	long long p,q,n,L;
	long long e,d;
	long long m;
	// 私钥{d , n}
	// 公钥{e , n}
public:
	
	// 求公约数
	long long gcd(long long a, long long b) {
		return  b ? gcd(b, a % b) : a;
	}
	//判断是否质数
	bool isPrime(long long n) {// O(sqrt(n)/2)
		if (n < 2) return false;
		if (n == 2) return true;
		if (n % 2 == 0) return false;
		long long foo = (long long )sqrt(n);
		for (long long i = 3; i <= foo; i += 2)
			if (n % i == 0) return false;
		return true;
	
	}

	// 欧几里得拓展 求解 e * x + L * y = 1 返回 x = d
	long long gcd_ext(long long a, long long b, long long&x, long long&y) {
	// 拓展欧几里得算法： e * x + L * y =1  
		if (!b) {
			x = 1, y = 0;
			return a; //到达递归边界，开始回代
		}
		long long xx, yy, ret = gcd_ext(b, a % b, xx, yy);
		x = yy; //返回时，计算上一层x,y值
		y = xx - a / b * yy;
		return x; //gcd值
	}
	long long gcd_extend(long long a, long long b) {
		long long x, y;
		x = y = 0;
		long int ans=gcd_ext(e, L,x,y);
		
		if (ans < 0) ans += L;
		return ans;
	}

	// 快速大数幂求模  a ^ b mod n 
	long long mod(long long a, long long b, long long c) {// a ^ b mod c
		long long ans =1;
		long long t = a % c;
		while (b) {
			if (b & 1) {
				ans = (ans * t) % c;
			}
			b >>= 1;
			t = (t * t) % c;
		}
		return ans;
	}

	void RSA_Input() {
		cout << "Input p,q(prime only):" << endl;
		cout << "p : " << endl;

		cin >> p;
		while (!isPrime(p)) {
		cout << "not prime! renter required" << endl;
			cin >> p;
		}

		cout << "q : " << endl;
		cin >> q;
		while (!isPrime(q)) {
			cout << "not prime! renter required" << endl;
			cin >> q;
		}
		RSA_Build();
		cout << "input message:" << endl;
		cin >> m;
		while (m >= n) {
			cout << "invalid message reenter required" << endl;
			cin >> m;
		
		}
	}
	void RSA_Build() {
		n = p * q;
		L = (p - 1) * (q - 1);
		e = L -1 ;// e < L
		d = gcd_extend(e, L);
	}
	long long  RSA_Encyrpt(long long m) {

		return mod(m, e, n);


	}
	long long  RSA_Decrypt(long long c) {

		return mod(c, d, n);
	
	
	}

	void RSA_Output() {
		
		long long c = RSA_Encyrpt(m);
		cout << "encryted message :" << c << endl;
		cout << "decrypted message : " << RSA_Decrypt(c) << endl;
	}

};

int main() {
	RSA test;
	test.RSA_Input();
	test.RSA_Output();
	system("pause");
	return 0;
}
