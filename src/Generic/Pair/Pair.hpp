#ifndef PAIR
#define PAIR

/*! \file Pair.hpp
 *  \brief Stores the declaration of struct Pair
 */

/*! \brief Stores two values of any types
 *
 * Values are public, so no explicit getters or setters are made.
 */
template <typename T, typename U>
struct Pair {
	T left;
	U right;

	Pair();
	Pair(const T& left, const U& right);
};

template <typename T, typename U>
Pair<T, U>::Pair() : left(), right() {}


template <typename T, typename U>
Pair<T, U>::Pair(const T& left, const U& right) : left(left), right(right) {}

#endif
