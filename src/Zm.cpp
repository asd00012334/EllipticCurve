#include "../inc/Integer.hpp"

namespace ECC {

template <typename Int>
Zm<Int>::Zm(Int const& mod_in) {
	mod = mod_in;
}

template <typename Int>
typename Zm<Int>::Element Zm<Int>::zero() const {
	Element tmp(0, this);
	return tmp;
}

template class Zm<int>;

}	// End namespace ECC
