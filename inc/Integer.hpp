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

    BigInt& operator+=(BigInt const&);
    BigInt& operator-=(BigInt const&);
    BigInt& operator*=(BigInt const&);
    BigInt& operator/=(BigInt const&);
    BigInt& operator%=(BigInt const&);
    BigInt operator+(BigInt const& r)const;
    BigInt operator-(BigInt const& r)const;
    BigInt operator*(BigInt const& r)const;
    BigInt operator/(BigInt const& r)const;
    BigInt operator%(BigInt const& r)const;
    bool operator<(BigInt const& r)const;
    bool operator>(BigInt const& r)const;
    bool operator<=(BigInt const& r)const;
    bool operator>=(BigInt const& r)const;
    bool operator==(BigInt const& r)const;

    void swap(BigInt& right);

    operator string()const;
    friend ostream& operator<<(ostream& os, BigInt const& integer);
    friend istream& operator>>(istream& is, BigInt& integer);
};

template<typename Int>
class Zm{
    Int mod;
public:
    class Element{
        Zm const* type;
        Int val;
    public:
        Element(Zm const* type);
        Element(Int const& val, Zm const* type);

        Element operator+(Element const& r)const;
        Element operator-(Element const& r)const;
        Element operator*(Element const& r)const;
        Element operator/(Element const& r)const;
        Element operator==(Element const& r)const;

        friend ostream& operator<<(ostream& os, Element const& integer);
        friend istream& operator>>(istream& is, Element& integer);
    };
    Zm(Int const& mod);
    Element zero()const;

};

}



#endif // __INTEGER_HPP__
