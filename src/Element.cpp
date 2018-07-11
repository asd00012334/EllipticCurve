#include "../inc/Integer.hpp"

namespace ECC {

template <typename Int>
Zm<Int>::Element::Element(Zm<Int> const* type_in) {
	type = type_in;
}

template <typename Int>
Zm<Int>::Element::Element(Int const& val_in, Zm<Int> const* type_in) {
	type = type_in;
	val = val_in%(type->mod);
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
	checkMod<Int>(this->type->mod, r.type->mod);
	Zm::Element ret((val+r.val)%(this->type->mod), type);
	return ret;
}

template <typename Int>
typename Zm<Int>::Element Zm<Int>::Element::operator-(
	typename Zm<Int>::Element const& r) const 
{
	checkMod<Int>(this->type->mod, r.type->mod);
	Zm::Element ret(
		(val-r.val+this->type->mod)%(this->type->mod), 
		type
	);
	return ret;
}

template <typename Int>
typename Zm<Int>::Element Zm<Int>::Element::operator*(
	typename Zm<Int>::Element const& r) const 
{
	checkMod<Int>(this->type->mod, r.type->mod);
	Zm::Element ret((val*r.val)%(this->type->mod), type);
	return ret;
}

/*
template <typename Int>
typename Zm<Int>::Element Zm<Int>::Element::operator/(
		Zm<Int>::Element const& r) const {
	checkMod(*this, r);
}
*/

template <typename Int>
bool Zm<Int>::Element::operator==(
	typename Zm<Int>::Element const& r) const 
{
	checkMod<Int>(this->type->mod, r.type->mod);
	return (this->val == r.val);
}


template class Zm<int>::Element;

}	// End namespace ECC
