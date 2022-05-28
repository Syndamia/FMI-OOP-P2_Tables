#ifndef PAIR
#define PAIR

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
