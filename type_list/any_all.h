#ifndef TYPE_LIST_ANY_ALL_H_DEFINED_14641442
#define TYPE_LIST_ANY_ALL_H_DEFINED_14641442

#include "core.h"
#include "delayed_error.h"

namespace details
{
	template<
		template<typename> typename,
		template<typename, typename> typename,
		bool,
		typename>
		struct reduce
	{
		DELAYED_ERROR("reduce<Predicate_t, BinaryOp_t, Default, T> expects a type_list as its T");
	};

	template<
		template<typename> typename Predicate_t,
		template<typename, typename> typename BinaryOp_t,
		bool Default>
		struct reduce<Predicate_t, BinaryOp_t, Default, type_list<>>
	{
		static constexpr bool value = Default;
	};

	template<
		template<typename> typename Predicate_t,
		template<typename, typename> typename BinaryOp_t,
		bool Default,
		typename T,
		typename... Ts>
		struct reduce<Predicate_t, BinaryOp_t, Default, type_list<T, Ts...>>
	{
	private:
		using applied_head = Predicate_t<T>;
		using applied_tail = reduce<Predicate_t, BinaryOp_t, Default, type_list<Ts...>>;
	public:
		static constexpr bool value = BinaryOp_t<applied_head, applied_tail>::value;
	};

	template<typename T, typename U>
	struct OR
	{
		static constexpr bool value = T::value || U::value;
	};

	template<typename T, typename U>
	struct AND
	{
		static constexpr bool value = T::value && U::value;
	};

	template<typename T>
	struct NOT 
	{
		static constexpr bool value = !T::value;
	};
}


template<template<typename> typename Predicate_t, typename List_t>
struct any : details::reduce<Predicate_t, details::OR, false, List_t> {};

template<template<typename> typename Predicate_t, typename T>
constexpr bool any_v = any<Predicate_t, T>::value;


template<template<typename> typename Predicate_t, typename List_t>
struct all : details::reduce<Predicate_t, details::AND, true, List_t> {};

template<template<typename> typename Predicate_t, typename T>
constexpr bool all_v = all<Predicate_t, T>::value;

template<template<typename> typename Predicate_t, typename List_t>
struct none : details::NOT<any<Predicate_t, List_t>> {};

template<template<typename> typename Predicate_t, typename List_t>
constexpr bool none_v = none<Predicate_t, List_t>::value;

#endif