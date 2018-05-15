#include "Integer.hpp"
#include "fft.hpp"

namespace ECC{

ll const BigInt::dMax = 1e9;

BigInt::BigInt(): val(1,0){}

BigInt::BigInt(ll vin): val(1,vin){
    if(val.back() >= dMax){
        ll carryOut = val.back()/dMax;
        val.back() %= dMax;
        val.push_back(carryOut);
    }
}

BigInt::BigInt(string const& decimal){
    sign = decimal[0]!='-';
    ll carry = 0;
    ll base = 1;
    for(int i=decimal.size() - 1; i >= (!sign); --i){
        carry += base*(decimal[i]-'0');
        if(base >= dMax){
            base = 10;
            val.push_back(carry%dMax);
            carry /= dMax;
        } else base*=10;
    }
    val.push_back(carry);
}

BigInt::operator string()const{
    string buf;
    for(int i=0;i<val.size();++i){
        ll tmp = val[i];
        for(int p=BigInt::dMax; p>=10; p/=10){
            buf.push_back('0'+tmp%10);
            tmp /= 10;
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
    vector<complex<double> > lval(l.val.begin(),l.val.end());
    vector<complex<double> > rval(r.val.begin(),r.val.end());
    lval.resize(len);
    rval.resize(len);
    fft(lval.begin(), lval.end());
    fft(rval.begin(), rval.end());

    for(int i=0;i<len;++i)
        lval[i] *= rval[i];
    ifft(lval.begin(), lval.end());
    BigInt out;
    out.val.resize(len);
    for(int i=0;i<len;++i)
        out.val[i] = round(lval[i].real());
    while(out.val.size()>1 && out.val.back() == 0)
        out.val.pop_back();
    out.sign = !(l.sign ^ r.sign);
    return out;
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
