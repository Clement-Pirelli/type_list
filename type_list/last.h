#ifndef TYPE_LIST_LAST_H_DEFINED_14641442
#define TYPE_LIST_LAST_H_DEFINED_14641442

#include "core.h"
#include "delayed_error.h"

template<typename>
struct last 
{
	DELAYED_ERROR("last<T> expects a non-empty type_list as its T");
};

template<typename T>
struct last<type_list<typename T>> 
{
	using type = T;
};

template<typename T, typename... Ts>
struct last<type_list<T, Ts...>>
{
	using type = typename last<type_list<Ts...>>::type;
};

template<typename T>
using last_t = typename last<T>::type;


#endif