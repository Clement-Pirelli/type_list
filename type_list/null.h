#ifndef TYPE_LIST_NULL_H_DEFINED_14641442
#define TYPE_LIST_NULL_H_DEFINED_14641442

#include "core.h"
#include "delayed_error.h"

template<typename T>
struct null
{
	DELAYED_ERROR("null<T> expects a type_list as its T")
};

template<typename T, typename... Ts>
struct null<type_list<T, Ts...>> 
{
	static constexpr bool value = false;
};

template<>
struct null<type_list<>>
{
	static constexpr bool value = true;
};


template<typename T>
constexpr bool null_v = null<T>::value;

#endif