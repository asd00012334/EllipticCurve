#include "../inc/Zm.hpp"

namespace ECC {

template <typename Int>
Zm<Int>::Zm(Int const& mod_in) {
	mod = mod_in;
}

// Only implement for integer.
template <typename Int>
typename Zm<Int>::Element Zm<Int>::zero() const {
	Element tmp(0, this);
	return tmp;
}

template class Zm<int>;
// template class Zm<BigInt>;

}	// End namespace ECC
