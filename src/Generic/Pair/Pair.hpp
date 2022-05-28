#ifndef PAIR
#define PAIR

template <typename T, typename U>
class Pair {
	T left;
	U right;

public:
	Pair();
	Pair(const T& left, const U& right);

	const T& l();
	const U& r();
};

template <typename T, typename U>
Pair<T, U>::Pair() : left(), right() {}


template <typename T, typename U>
Pair<T, U>::Pair(const T& left, const U& right) : left(left), right(right) {}

template <typename T, typename U>
const T& Pair<T, U>::l() {
	return left;
}

template <typename T, typename U>
const U& Pair<T, U>::r() {
	return right;
}

#endif
