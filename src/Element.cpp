#include "../inc/Zm.hpp"

namespace ECC {

template <typename Int>
Zm<Int>::Element::Element(Zm<Int> const* type_in) {
	type = type_in;
}

template <typename Int>
Zm<Int>::Element::Element(Int const& val_in, Zm<Int> const* type_in) {
	type = type_in;
	val = (val_in+type->mod)%(type->mod);
}

template <typename Int>
void checkMod(
	Int const& a, 
	Int const& b
) {
	if ( !(a == b) ) {
		cerr << "Error: module mismatch!!\n";
		throw "module mismatch";
	}
}

template <typename Int>
typename Zm<Int>::Element Zm<Int>::Element::operator+(
	typename Zm<Int>::Element const& r) const 
{
	checkMod<Int>(type->mod, r.type->mod);
	typename Zm<Int>::Element ret(
		(val+r.val)%(type->mod), 
		type
	);
	return ret;
}

template <typename Int>
typename Zm<Int>::Element Zm<Int>::Element::operator-(
	typename Zm<Int>::Element const& r) const 
{
	checkMod<Int>(type->mod, r.type->mod);
	typename Zm<Int>::Element ret(
		(val-r.val+type->mod)%(type->mod), 
		type
	);
	return ret;
}

template <typename Int>
typename Zm<Int>::Element Zm<Int>::Element::operator*(
	typename Zm<Int>::Element const& r) const 
{
	checkMod<Int>(type->mod, r.type->mod);
	typename Zm<Int>::Element ret(
		(val*r.val)%(type->mod), 
		type
	);
	return ret;
}

/*
// Only implement for integer.
template <typename Int>
Int extended_gcd(Int a, Int mod_in) {
	Int s = 0, pre_s = 1;
	Int t = 1, pre_t = 0;
	Int r = a, pre_r = mod_in;

	while (r != 0) {
		Int q = pre_r / r;
		Int tmp_r = r, tmp_s = s, tmp_t = t;
		
		r = pre_r-(q*r), pre_r = tmp_r;
		s = pre_s-(q*s), pre_s = tmp_s;
		t = pre_t-(q*t), pre_t = tmp_t;
	}

	if (pre_r == 1) {
		return pre_t;
	}
	else {
		cerr << "Error: inverse not exists!!\n";
		throw "inverse not exists";
	}
}

template <typename Int>
typename Zm<Int>::Element Zm<Int>::Element::operator/(
	typename Zm<Int>::Element const& r) const 
{
	checkMod<Int>(type->mod, r.type->mod);
	typename Zm<Int>::Element ret(
		extended_gcd(r.val, type->mod),
		type
	);
	return ret*(*this);
}
*/

template <typename Int>
bool Zm<Int>::Element::operator==(
	typename Zm<Int>::Element const& r) const 
{
	checkMod<Int>(type->mod, r.type->mod);
	return (val == r.val);
}

// template class Zm<int>::Element;
template class Zm<mpz_class>::Element;

}	// End namespace ECC
