#ifndef PAIR
#define PAIR

template <typename T, typename U>
class Pair {
	T left;
	U right;

public:
	Pair(const T& left, const U& right);
};

#endif
