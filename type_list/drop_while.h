#ifndef TYPE_LIST_DROP_WHILE_H_DEFINED_14641442
#define TYPE_LIST_DROP_WHILE_H_DEFINED_14641442

#include <type_traits>
#include "core.h"
#include "delayed_error.h"

namespace details 
{
	template<typename T>
	struct identity
	{
		using type = T;
	};
}

template<template<typename> typename, typename>
struct dropWhile
{
	DELAYED_ERROR("dropWhile<Predicate_t, T> expects a type_list as its T");
};

template<template<typename> typename Predicate_t>
struct dropWhile<Predicate_t, type_list<>>
{
	using type = type_list<>;
};

template<template<typename> typename Predicate_t, typename T, typename... Ts>
struct dropWhile<Predicate_t, type_list<T, Ts...>>
{
private:
	using rest = dropWhile<Predicate_t, type_list<Ts...>>;
	static constexpr bool result = Predicate_t<T>::value;
	using remaining = details::identity<type_list<T, Ts...>>;
public:
	using type = typename std::conditional_t<result, rest, remaining>::type;
};

template<template<typename> typename Predicate_t, typename List_t>
using dropWhile_t = typename dropWhile<Predicate_t, List_t>::type;

#endif