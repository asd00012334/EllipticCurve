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
		string op;
		mpz_class A, B;
		cin >> A >> op >> B;
		Zp<mpz_class>::Element AE(A, &Zn), BE(B, &Zn);
		if(op == "+")
		{
			Zp<mpz_class>::Element CE(AE + BE);
			cout << CE << endl;
		}
	}
}
