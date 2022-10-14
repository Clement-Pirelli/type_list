#ifndef TYPE_LIST_FILTER_H_DEFINED_14641442
#define TYPE_LIST_FILTER_H_DEFINED_14641442

#include "core.h"
#include "delayed_error.h"

template<template<typename> typename, typename>
struct filter
{
	DELAYED_ERROR("filter<Predicate_t, T> expects a type_list as its T");
};

template<template<typename> typename Predicate_t>
struct filter<Predicate_t, type_list<>>
{
	using type = type_list<>;
};


template<template<typename> typename Predicate_t, typename T, typename... Ts>
struct filter<Predicate_t, type_list<T, Ts...>>
{
private:
	using rest = typename filter<Predicate_t, type_list<Ts...>>::type;
public:
	using type = std::conditional_t<Predicate_t<T>::value, cons_t<T, rest>, rest>;
};

template<template<typename> typename Predicate_t, typename List_t>
using filter_t = typename filter<Predicate_t, List_t>::type;

#endif