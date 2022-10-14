#ifndef TYPE_LIST_REPLICATE_H_DEFINED_14641442
#define TYPE_LIST_REPLICATE_H_DEFINED_14641442

#include "core.h"

template<size_t N, typename T>
struct replicate
{
private:
	using rest = typename replicate<N - 1, T>::type;
public:
	using type = cons_t<T, rest>;
};

template<typename T>
struct replicate<0, T>
{
	using type = type_list<>;
};

template<size_t N, typename T>
using replicate_t = typename replicate<N, T>::type;

#endif