#ifndef TYPE_LIST_CONCAT_MAP_H_DEFINED_14641442
#define TYPE_LIST_CONCAT_MAP_H_DEFINED_14641442

#include "core.h"
#include "concat.h"
#include "delayed_error.h"

template<template <typename> typename, typename>
struct concatMap 
{
	DELAYED_ERROR("concatMap<Metafunction_t, T> expects a type_list as its T");
};

template<template <typename> typename Metafunction_t, typename T, typename... Ts>
struct concatMap<Metafunction_t, type_list<T, Ts...>>
{
private:
	using rest = typename concatMap<Metafunction_t, type_list<Ts...>>::type;
public:
	using type = concat_t<typename Metafunction_t<T>::type, rest>;
};

template<template <typename> typename Metafunction_t>
struct concatMap<Metafunction_t, type_list<>> 
{
	using type = type_list<>;
};

template<template<typename> typename Metafunction_t, typename T>
using concatMap_t = typename concatMap<Metafunction_t, T>::type;


#endif