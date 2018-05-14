#ifndef __INTEGER_HPP__
#define __INTEGER_HPP__

namespace ECC{

typedef long long ll;
using namespace std;

class BigInt{
    vector<ll> val;
public:
    BigInt();
    BigInt(ll val);
    BigInt(string const& decimal);

    friend BigInt operator+(BigInt const& l, BigInt const& r);
    friend BigInt operator-(BigInt const& l, BigInt const& r);
    friend BigInt operator*(BigInt const& l, BigInt const& r);
    friend BigInt operator/(BigInt const& l, BigInt const& r);
    friend BigInt operator%(BigInt const& l, BigInt const& r);
    friend BigInt operator<(BigInt const& l, BigInt const& r);
    friend BigInt operator>(BigInt const& l, BigInt const& r);
    friend BigInt operator<=(BigInt const& l, BigInt const& r);
    friend BigInt operator>=(BigInt const& l, BigInt const& r);
    friend BigInt operator==(BigInt const& l, BigInt const& r);

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
