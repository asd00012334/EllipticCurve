#ifndef __INTEGER_HPP__
#define __INTEGER_HPP__

#include <bits/stdc++.h>

namespace ECC{

typedef long long ll;
using namespace std;

class BigInt{
    static ll const dMax;
    vector<ll> val;
    int sign;
    friend void sub(BigInt&, BigInt const&);
    friend void __sub(BigInt&, BigInt const&);
    friend void add(BigInt&, BigInt const&);
    friend void nega(BigInt&);
	
public:
    BigInt();
    BigInt(ll val);
    BigInt(string const& decimal);
	//BigInt(BigInt const& r);
	//BigInt& operator=(BigInt const& r);

    friend BigInt& operator+=(BigInt&, BigInt const&);
    friend BigInt& operator-=(BigInt&, BigInt const&);
    friend BigInt& operator*=(BigInt&, BigInt const&);
    friend BigInt& operator/=(BigInt&, BigInt const&);
    friend BigInt& operator%=(BigInt&, BigInt const&);
    friend BigInt operator+(BigInt const& l, BigInt const& r);
    friend BigInt operator-(BigInt const& l, BigInt const& r);
    friend BigInt operator*(BigInt const& l, BigInt const& r);
    friend BigInt operator/(BigInt const& l, BigInt const& r);
    friend BigInt operator%(BigInt const& l, BigInt const& r);
    friend bool operator<(BigInt const& l, BigInt const& r);
    friend bool operator>(BigInt const& l, BigInt const& r);
    friend bool operator<=(BigInt const& l, BigInt const& r);
    friend bool operator>=(BigInt const& l, BigInt const& r);
    friend bool operator==(BigInt const& l, BigInt const& r);

    void swap(BigInt& right);

    operator string()const;
    friend ostream& operator<<(ostream& os, BigInt const& integer);
    friend istream& operator>>(istream& is, BigInt& integer);
};

template<typename Int>
class Zm{
    Int val, mod;
public:
    Zm(Int const& mod);
    Zm(Int const& val, Int const& mod);

    friend BigInt operator+(BigInt const& l, BigInt const& r);
    friend BigInt operator-(BigInt const& l, BigInt const& r);
    friend BigInt operator*(BigInt const& l, BigInt const& r);
    friend BigInt operator/(BigInt const& l, BigInt const& r);
    friend BigInt operator==(BigInt const& l, BigInt const& r);

    friend ostream& operator<<(ostream& os, BigInt const& integer);
    friend istream& operator>>(istream& is, BigInt& integer);
};

}

#endif // __INTEGER_HPP__
