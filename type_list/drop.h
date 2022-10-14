#ifndef TYPE_LIST_DROP_H_DEFINED_14641442
#define TYPE_LIST_DROP_H_DEFINED_14641442

#include "core.h"
#include "delayed_error.h"

//drop
template<size_t, typename>
struct drop
{
	DELAYED_ERROR("drop<N, T> expects a type_list as its T");
};

template<size_t N>
struct drop<N, type_list<>>
{
	using type = type_list<>;
};

template<size_t N, typename... Ts>
requires(N == 0)
struct drop<N, type_list<Ts...>>
{
	using type = type_list<Ts...>;
};

template<size_t N, typename T, typename... Ts>
requires(N != 0)
struct drop<N, type_list<T, Ts...>>
{
	using type = typename drop<N - 1, type_list<Ts...>>::type;
};

template<size_t N, typename T>
using drop_t = typename drop<N, T>::type;

#endif