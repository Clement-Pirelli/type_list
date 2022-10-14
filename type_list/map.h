#ifndef TYPE_LIST_MAP_H_DEFINED_14641442
#define TYPE_LIST_MAP_H_DEFINED_14641442

#include "core.h"
#include "delayed_error.h"

template<template<typename> typename, typename>
struct map
{
	DELAYED_ERROR("map<Metafunction_t, T> expects a type_list as its T");
};

template<template<typename> typename Metafunction_t>
struct map<Metafunction_t, type_list<>>
{
	using type = type_list<>;
};

template<template<typename> typename Metafunction_t, typename T, typename... Ts>
struct map<Metafunction_t, type_list<T, Ts...>>
{
private:
	using tail_mapped = typename map<Metafunction_t, type_list<Ts...>>::type;
	using head_mapped = typename Metafunction_t<T>::type;
public:
	using type = cons_t<head_mapped, tail_mapped>;
};

template<template<typename> typename Metafunction_t, typename T>
using map_t = typename map<Metafunction_t, T>::type;

#endif