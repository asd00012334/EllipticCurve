#include<cstdio>
#include<iostream>
#include<string>
#include<vector>

using namespace std;


#define ll long long
vector<ll> val;
ll dMax = 1e9;

void a(string const& decimal){
    ll carry = 0;
    ll base = 1;
    for(int i=decimal.size() - 1; i >= 0; --i){
        carry += base*(decimal[i]-'0');
		cout << carry << endl;
        if(base >= dMax){
            base = 10;
            val.push_back(carry%dMax);
            carry /= dMax;
        } else base*=10;
    }
    val.push_back(carry);
    for(auto e: val) printf("test: %d\n",e);
}

int main()
{
	string s;
	cin >> s;
	a(s);
}
