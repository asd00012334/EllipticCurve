#ifndef __ZP_HPP__
#define __ZP_HPP__

#include <bits/stdc++.h>
#include <gmp.h>
#include "Zm.hpp"

namespace ECC {

using namespace std;

template <typename Int>
class Zp : public Zm<Int> {	
public:
	class Element: public Zm<Int>::Element {
	public:
		Element(Zp const* type);
		Element(typename Zp::Element const& e);
		Element(Int const& val, Zp const* type);
		~Element() { Zp::Element::type = NULL; }

		Element operator/(Element const& r)const;

		friend ostream& operator<<(ostream& os, typename Zp<Int>::Element const& integer) {
			os << integer.val;
			return os;
		}
		friend istream& operator>>(istream& is, typename Zp<Int>::Element const& integer) {
			is >> integer.val;
			return is;
		}
	};
	Zp(Int const& mod);
	Element zero()const;
};

template <typename Int>
Zp<Int>::Zp(Int const& mod_in): Zm<Int>(mod_in) {
	if (mpz_probab_prime_p(mod_in.get_mpz_t(), 50) == 0) {
		cerr << "Error: " << mod_in << " is not prime!!\n";
		throw "not prime";
	}
}

template <typename Int>
typename Zp<Int>::Element Zp<Int>::zero()const {
	Element ret(0, this);
	return ret;
}

template <typename Int>
Zp<Int>::Element::Element(Zp<Int> const* type_in)
	: Zm<Int>::Element(type_in) {}

template <typename Int>
Zp<Int>::Element::Element(typename Zp<Int>::Element const& e)
	: Zm<Int>::Element(e.get_val(), e.get_type()) {}

template <typename Int>
Zp<Int>::Element::Element(Int const& val_in, Zp<Int> const* type_in)
	: Zm<Int>::Element(val_in, type_in) {}

template <typename Int>
typename Zp<Int>::Element Zp<Int>::Element::operator/(typename Zp<Int>::Element const& r)const {
	mpz_class g(1);
	mpz_t s, t;
	
	mpz_init(s);
	mpz_init(t);
	mpz_gcdext (g.get_mpz_t(), s, t, r.val.get_mpz_t(), r.type->get_mod().get_mpz_t());
	
	Element r_inv(mpz_class(s), this->type);
	Element ret((*this)*r_inv);

	return ret;
}

}	// End namespace ECC

#endif	// __ZM_HPP__
