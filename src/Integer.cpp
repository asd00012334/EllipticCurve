#include "Integer.hpp"
#include "fft.hpp"

namespace ECC{

ll const BigInt::dMax = 1<<20;

BigInt::BigInt(): val(1,0){}

BigInt::BigInt(ll vin): val(1,vin){
    if(val.back() >= dMax){
        ll carryOut = val.back()/dMax;
        val.back() %= dMax;
        val.push_back(carryOut);
    }
}

inline int hexToDigit(char ascii){
    if(isdigit(ascii))
        return ascii - '0';
    else if('a'<=ascii && ascii <='z')
        return ascii-'a'+10;
    else if('A'<=ascii && ascii<='Z')
        return ascii-'A'+10;
    else assert(0);
}

inline char digitToHex(int digit){
    if(digit<10) return digit+'0';
    else if(digit<16) return digit-10+'a';
    else assert(0);
}

BigInt::BigInt(string const& hexadecimal){
    sign = hexadecimal[0]!='-';
    ll carry = 0;
    ll base = 1;
    for(int i=hexadecimal.size() - 1; i >= (!sign); --i){
        carry += base*hexToDigit(hexadecimal[i]);
        if(base >= dMax){
            base = 16;
            val.push_back(carry%dMax);
            carry /= dMax;
        } else base*=16;
    }
    val.push_back(carry);
}

BigInt::operator string()const{
    string buf;
    for(int i=0;i<val.size();++i){
        ll tmp = val[i];
        for(int p=BigInt::dMax; p>=16; p/=16){
            buf.push_back( digitToHex(tmp%16) );
            tmp /= 16;
        }
    }
    reverse(buf.begin(),buf.end());
    int trailZero = 0;
    for(;trailZero<buf.size();++trailZero)
        if(buf[trailZero]!='0') break;
    string out;

    if(!sign) out.push_back('-');
    out += buf.substr(trailZero,buf.size()-trailZero);
    if(out.empty() || !sign && out.size()==1) out = "0";
    return out;
}

BigInt operator*(BigInt const& l, BigInt const& r){
    int len = l.val.size() + r.val.size();
    if(len&(len-1)) len = 1<<__lg(len<<1);
    vector<complex<long double> > lval(l.val.begin(),l.val.end());
    vector<complex<long double> > rval(r.val.begin(),r.val.end());
    lval.resize(len);
    rval.resize(len);
    fft(lval.begin(), lval.end());
    fft(rval.begin(), rval.end());

    for(int i=0;i<len;++i)
        lval[i] *= rval[i];
    ifft(lval.begin(), lval.end());
    BigInt out;
    out.val.resize(len,0);
    for(int i=0;i<len;++i)
        out.val[i] = round(lval[i].real());
    for(int i=0;i<len-1;++i)
        if(out.val[i]>=BigInt::dMax){
            out.val[i+1] += out.val[i]/BigInt::dMax;
            out.val[i] %= BigInt::dMax;
        }
    while(out.val.size()>1 && out.val.back() == 0)
        out.val.pop_back();
    out.sign = !(l.sign ^ r.sign);
    return out;
}

void BigInt::swap(BigInt& right){
    val.swap(right.val);
    std::swap(sign,right.sign);
}

ostream& operator<<(ostream& os, BigInt const& integer){
    os << string(integer);
    return os;
}

istream& operator>>(istream& is, BigInt& integer){
    string buf; cin>>buf;
    integer = BigInt(buf);
    return is;
}

}
