#include "Integer.hpp"
#include "fft.hpp"

namespace ECC{

template<typename Vec>
void reduce(Vec& arr, int& sign, int lenMax=INT_MAX){
    if(arr.empty()) arr.push_back(0);
    while(arr.size()>=1)
        if(arr.back()==0) arr.pop_back();
        else break;
    if(arr.size()==1 && arr[0]==0) sign = 1;
    if(arr.size()<=lenMax) return;
    for(int i=0;i<lenMax;++i)
        arr[i] = arr[arr.size()-lenMax+i];
    arr.resize(lenMax);
}

ll const BigInt::dMax = 1<<20;

BigInt::BigInt(): val(1,0), sign(1){}

BigInt::BigInt(ll vin): val(1,abs(vin)), sign(vin>=0){
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
    else throw "hex to digit error";
}

inline char digitToHex(int digit){
    if(digit<10) return digit+'0';
    else if(digit<16) return digit-10+'a';
    else throw "digit to hex error";
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

BigInt BigInt::operator*(BigInt const& r)const{
    BigInt const& l = *this;
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

template<typename Vec>
void shiftBack(Vec& arr, int n){
    arr.resize(arr.size()+n);
    for(int i=arr.size()-1;i>=n;--i)
        arr[i] = arr[i-n];
    for(int i=0;i<n;++i)
        arr[i] = 0;
}

BigInt BigInt::operator/(BigInt const& r)const{

    struct BigFloat{
        BigInt frac;
        int offset;

        BigFloat(): frac(0), offset(0){}
        BigFloat(BigInt const& i): frac(i), offset(0){}
        BigFloat(int val, int offset):frac(val),offset(offset){}

        BigFloat operator*(BigFloat const& r)const{
            BigFloat out;
            out.frac = frac * r.frac;
            out.offset = offset + r.offset;
            return out;
        }

        BigFloat& operator-=(BigFloat r){
            if(offset > r.offset){
                offset -= r.offset;
                shiftBack(frac.val,offset);
            } else{
                r.offset -= offset;
                shiftBack(r.frac.val,r.offset);
            }
            frac -= r.frac;
            return *this;
        }
    };

    BigInt out;
    out.sign = !(sign^r.sign);

    BigFloat a(1,-r.val.size()), b(r);

    /// TODO: fix this iteration count
    for(int i=0;i<30;++i){
        cout << a.frac<<"!!\n";
        BigFloat c(2,0);
        c -= b*a;
        a = a*c;
        reduce(a.frac.val,a.frac.sign,r.val.size()+5);
    }
    a = a*BigFloat(*this);
    out.val.resize(a.frac.val.size()-a.offset);
    for(int i=a.offset;i<a.frac.val.size();++i)
        out.val[i-a.offset] = a.frac.val[i];
    reduce(out.val, out.sign);
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


void nega(BigInt &l)
{
	l.sign = !l.sign;
}
bool operator<(vector<ll>& l, vector<ll>& r)
{
	if(l.size() != r.size())
		return l.size() < r.size();
	for(int i = l.size() - 1; i >= 0; i++)
		if(l[i] != r[i])
			return l[i] < r[i];
	return 0;
}

void add(BigInt &l, BigInt const& r)
{
	vector<ll>& L = l.val;
	const vector<ll>& R = r.val;
	int MaxLen = max(L.size(), R.size());
	int MinLen = min(L.size(), R.size());
	L.resize(MaxLen + 1, 0);
	for(int i = 0; i < R.size(); ++i)
		L[i] += R[i];
	for(int i = 0; i < MaxLen; ++i)
	{
		if(L[i] >= BigInt::dMax)
		{
			L[i + 1] += 1;
			L[i] -= BigInt::dMax;
		}
	}
	if(L.back() == 0)
		L.pop_back();
}

void sub(BigInt &l, BigInt const& r)
{
	if(l.val > r.val)
		__sub(l, r);
	else
	{
		BigInt x = l;
		nega(l = r);
		__sub(l, x);
	}

}

void __sub(BigInt &l, BigInt const& r)
{
	vector<ll>& L = l.val;
	const vector<ll>& R = r.val;
	int MaxLen = max(L.size(), R.size());
	int MinLen = min(L.size(), R.size());
	for(int i = 0; i < MinLen; ++i)
		L[i] -= R[i];
	for(int i = 0; i < MaxLen; ++i)
	{
		if(L[i] < 0)
		{
			L[i + 1] -= 1;
			L[i] += BigInt::dMax;
		}
	}
}


BigInt& BigInt::operator+=(BigInt const& r){
	BigInt& l = *this;
	if(l.sign == r.sign)
		add(l, r);
	else
		sub(l, r);
	return l;
}

BigInt& BigInt::operator-=(BigInt const& r){
    BigInt& l = *this;
	if(l.sign == r.sign)
		sub(l, r);
	else
		add(l, r);
	return l;
}

BigInt BigInt::operator+(BigInt const& r)const{
    BigInt const& l = *this;
	BigInt ret(l);
	ret += r;
	return ret;
}

BigInt BigInt::operator-(BigInt const& r)const{
	BigInt const& l = *this;
	BigInt ret(l);
	ret -= r;
	return ret;
}

}

int main(){
    std::string s;
    for(int i=0;i<1000;++i) s.push_back('f');
    ECC::BigInt t1, t2(-2);
    t1.swap(t2);
    std::cout<<t1*t1*t1<<"\n";
    for(int i=0;i<1000;++i)
        t1*t1;
    std::cout<< (ECC::BigInt)5 <<"\n";
    std::cout<< ((ECC::BigInt)5/2);
}
