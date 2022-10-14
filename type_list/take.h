#ifndef TYPE_LIST_TAKE_H_DEFINED_14641442
#define TYPE_LIST_TAKE_H_DEFINED_14641442

#include "core.h"
#include "delayed_error.h"

template<size_t, typename>
struct take
{
	DELAYED_ERROR("take<N, T> expects a type_list as its T");
};

template<size_t N>
struct take<N, type_list<>>
{
	using type = type_list<>;
};

template<size_t N, typename... Ts>
requires(N == 0)
struct take<N, type_list<Ts...>>
{
	using type = type_list<>;
};

template<size_t N, typename T, typename... Ts>
requires(N != 0)
struct take<N, type_list<T, Ts...>>
{
private:
	using next = typename::take<N - 1, type_list<Ts...>>::type;
public:
	using type = cons_t<T, next>;
};

template<size_t N, typename T>
using take_t = typename take<N, T>::type;

#endif