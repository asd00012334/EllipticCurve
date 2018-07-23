#include"Zp.hpp"
#include"Zm.hpp"
#include<gmpxx.h>
#include<string>
using namespace std;
using namespace ECC;

int main()
{
	int n;
	cin >> n;
	Zp<mpz_class> Zn(n);
	
	while(1)
	{
		string a, op, b;
		cin >> a >> op >> b;
		mpz_class A, B;
		A = a;
		B = b;
		Zp<mpz_class>::Element AE(A, &Zn), BE(B, &Zn);
		if(op == "+")
			cout << (AE + BE) << endl;
	}
}
