#ifndef TYPE_LIST_TAKE_WHILE_H_DEFINED_14641442
#define TYPE_LIST_TAKE_WHILE_H_DEFINED_14641442

#include <type_traits>
#include "core.h"
#include "delayed_error.h"

template<template<typename> typename, typename>
struct takeWhile
{
	DELAYED_ERROR("takeWhile<Predicate_t, T> expects as type_list as its T");
};

template<template<typename> typename Predicate_t>
struct takeWhile<Predicate_t, type_list<>>
{
	using type = type_list<>;
};

template<template<typename> typename Predicate_t, typename T, typename... Ts>
struct takeWhile<Predicate_t, type_list<T, Ts...>>
{
private:
	static constexpr bool result = Predicate_t<T>::value;
	using rest = typename takeWhile<Predicate_t, type_list<Ts...>>::type;
public:
	using type = std::conditional_t<result, cons_t<T, rest>, type_list<>>;
};

template<template<typename> typename Predicate_t, typename List_t>
using takeWhile_t = typename takeWhile<Predicate_t, List_t>::type;

#endif