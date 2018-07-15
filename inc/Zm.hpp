#ifndef __ZM_HPP__
#define __ZM_HPP__

#include <bits/stdc++.h>
#include <gmpxx.h>

namespace ECC {

using namespace std;

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
        bool operator==(Element const& r)const;

        friend ostream& operator<<(ostream& os, typename Zm<Int>::Element const& integer) {
			os << integer.val;
			return os;
		}
        friend istream& operator>>(istream& is, typename Zm<Int>::Element& integer) {
			is >> integer.val;
			return is;
		}
    };
    Zm(Int const& mod);
    Element zero()const;

};

}

#endif	// __ZM_HPP__
