#include<iostream>
#include<cstdio>
#include<string>
#include"../inc/Integer.hpp"
using namespace std;
using namespace ECC;


int main()
{
	BigInt x, y;
	char op;
	while(cout << ">>> " && cin >> x >> op >> y)
	{
		cout << x << " " << op << " "  << y << " = ";
		switch(op)
		{
		case '+':
			cout << x + y << endl;
			break;
		case '-':
			cout << x - y << endl;
			break;
		}
	}
	cout << endl;	
}
