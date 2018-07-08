#include"../inc/Integer.hpp"

namespace ECC{


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


BigInt& BigInt::operator+=(BigInt const& r)
{
	BigInt& l = *this;
	if(l.sign == r.sign)
		add(l, r);
	else
		sub(l, r);
	return l;
}

BigInt& BigInt::operator-=(BigInt const& r)
{
	BigInt& l = *this;
	if(l.sign == r.sign)
		sub(l, r);
	else
		add(l, r);
	return l;
}

BigInt BigInt::operator+(BigInt const& r) const
{
	BigInt ret(*this);
	ret += r;
	return ret;
}

BigInt BigInt::operator-(BigInt const& r) const
{
	BigInt ret(*this);
	ret -= r;
	return ret;
}



//BigInt operator+(BigInt const& l, BigInt const& r)
} // namespace ECC
